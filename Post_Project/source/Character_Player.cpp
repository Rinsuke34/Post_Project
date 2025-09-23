/* プレイヤークラスの定義 */

/* 使用する要素のインクルード */
// 標準ライブラリ
#include <fstream>
// ヘッダファイル
#include "Character_Player.h"
// 関連クラス
#include "DataList_GameStatus.h"
// 共通定義
#include "ConstantDefine.h"
#include "FunctionDefine.h"
#include "VariableDefine.h"

// コンストラクタ
Character_Player::Character_Player() : Character_Base()
{
	/* 初期化 */
	this->iMotionCount		= 0;
	this->bMotionLoopFlg	= true;
	this->bMeleeFlg			= true;
	this->bMoveFlg			= false;

	/* アニメーション初期設定 */
	// アニメーション設定
	this->AnimFileName		= "Player";
	this->NowMotionName		= "Delay_Sowrd";
	// パーツアニメーションセットアップ
	this->pDataList_2DPartsAnimCreateTool->LoadPartsAnimData(this->AnimFileName);

	/* チームタグ設定 */
	this->SetTeamTag("Player");
}

// 初期設定
void Character_Player::InitialSetup()
{
	/* プレイヤー情報の読み込み */
	JsonLoad_PlayerStatus();

	/* HP更新 */
	this->pDataList_GameStatus->SetHp_Player(this->iHealth);
	this->pDataList_GameStatus->SetMaxHp_Player(this->iMaxHealth);

	/* ベースクラスの初期設定処理 */
	Character_Base::InitialSetup();
}

// プレイヤー情報の読み込み
void Character_Player::JsonLoad_PlayerStatus()
{
	/* プレイヤーの情報を読み込む */

	/* JSONファイル読み込み */
	std::string FilePath = "resource/CharacterData/CharacterData_Player.json";

	std::ifstream ifs(FilePath);
	if (!ifs) return;

	using json = nlohmann::json;
	json j;
	ifs >> j;

	/* プレイヤーの情報を取得 */
	this->iMaxHealth		= j.value("HP", 0);                // 最大体力
	this->iHealth			= this->iMaxHealth;                // 体力(最大体力で初期化)
	this->iAttack			= j.value("Attack", 0);            // 攻撃力
	this->iSpeed			= j.value("Speed", 0);             // すばやさ
	this->iAutoHealDelay	= j.value("AutoHealDelay", 0);     // 自動回復待機時間
	this->iAutoHealAmount	= j.value("AutoHealAmount", 0);    // 自動回復量
	this->fSearchRange		= j.value("SearchRange", 0.f);     // 探索範囲(プレイヤーの場合は遠距離攻撃範囲として扱う)
	this->fAttackRange		= j.value("AttackRange", 0.f);     // 攻撃範囲
	this->bContactDamageFlg	= j.value("ContactDamage", false); // 接触ダメージフラグ
	this->bAttackMeleeFlg	= j.value("AttackMelee", false);   // 近接攻撃フラグ
}

// 更新
void Character_Player::Update()
{
	/* 行動処理 */
	Update_Action();

	/* ワールドマップ上の座標を設定 */
	this->pDataList_GameStatus->SetPlayerPosition_WoldMap(this->vecBasePosition);

	/* ベースクラスの更新処理 */
	Character_Base::Update();

	/* HP更新 */
	this->pDataList_GameStatus->SetHp_Player(this->iHealth);
	this->pDataList_GameStatus->SetMaxHp_Player(this->iMaxHealth);

	/* アニメーションの更新 */
	Character_Base::Update_Animation();
}

// 描画
void Character_Player::Draw()
{
	/* ベースクラスの描写処理 */
	Character_Base::Draw();

	/* デバッグモードであるか */
	if (gbDebugMode)
	{
		// デバッグモードであるなら
		/* グリッド範囲描写 */
		Draw_Grid();
	}
}

// 移動処理
void Character_Player::Update_ApplyMovement()
{
	/* 移動フラグをリセット */
	this->bMoveFlg = false;

	/* 移動方向を取得 */
	VECTOR vecMoveDirection = VGet(0.f, 0.f, 0.f);
	// 入力から移動方向を取得
	bool bIsMoving = false;
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_W] == TRUE)
	{
		vecMoveDirection = VAdd(vecMoveDirection, VGet(0.f, 0.f, 1.f));
		bIsMoving = true;
	}
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_S] == TRUE)
	{
		vecMoveDirection = VAdd(vecMoveDirection, VGet(0.f, 0.f, -1.f));
		bIsMoving = true;
	}
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_A] == TRUE)
	{
		vecMoveDirection = VAdd(vecMoveDirection, VGet(-1.f, 0.f, 0.f));
		bIsMoving = true;
	}
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_D] == TRUE)
	{
		vecMoveDirection = VAdd(vecMoveDirection, VGet(1.f, 0.f, 0.f));
		bIsMoving = true;
	}

	/* 入力がない場合は処理を終了する */
	if (!bIsMoving) { return; }

	/* 移動＆押し出し処理 */
	bGround_PushBack_Movement(vecMoveDirection);

	/* 移動フラグを有効化 */
	this->bMoveFlg = true;
}

// 重力処理
void Character_Player::Update_ApplyGravity()
{
	/* ジャンプ処理 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_SPACE] == TRUE)
	{
		Update_Jump();
	}

	/* 押し出し処理 */
	bGround_PushBack_Gravity();
}

// グリッド範囲の描写
void Character_Player::Draw_Grid()
{
	/* 判定を実施するグリッドを描写 */
	int iGridX = iGetGridIndexX(this->vecBasePosition.x);
	int iGridZ = iGetGridIndexZ(this->vecBasePosition.z);
	for (int iX = iGridX - 1; iX <= iGridX + 1; ++iX)
	{
		for (int iZ = iGridZ - 1; iZ <= iGridZ + 1; ++iZ)
		{
			/* グリッドの左上座標を算出 */
			// ※ 高さはプレイヤー基準とする
			float fGridMinX = static_cast<float>(iX * GRID_SIZE_WORLD_X);
			float fGridMinZ = static_cast<float>(iZ * GRID_SIZE_WORLD_Z);
			float fGridMaxX = fGridMinX + GRID_SIZE_WORLD_X;
			float fGridMaxZ = fGridMinZ + GRID_SIZE_WORLD_Z;
			float fY = this->vecBasePosition.y;

			VECTOR vecPosA = VGet(fGridMinX, fY, fGridMinZ); // 左上
			VECTOR vecPosB = VGet(fGridMaxX, fY, fGridMinZ); // 右上
			VECTOR vecPosC = VGet(fGridMaxX, fY, fGridMaxZ); // 右下
			VECTOR vecPosD = VGet(fGridMinX, fY, fGridMaxZ); // 左下

			/* 四辺を線で描画 */
			DrawLine3D(vecPosA, vecPosB, GetColor(255, 255, 0));
			DrawLine3D(vecPosB, vecPosC, GetColor(255, 255, 0));
			DrawLine3D(vecPosC, vecPosD, GetColor(255, 255, 0));
			DrawLine3D(vecPosD, vecPosA, GetColor(255, 255, 0));
		}
	}
}

