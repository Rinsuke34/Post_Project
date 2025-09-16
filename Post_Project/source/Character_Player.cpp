/* プレイヤークラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Character_Player.h"
// 関連クラス
#include "DataList_GameStatus.h"
// 共通定義
#include "Test_ConstantDefine.h"
#include "ConstantDefine.h"
#include "FunctionDefine.h"

// コンストラクタ
Character_Player::Character_Player() : Character_Base()
{
	/* 初期化 */
	this->iMotionCount		= 0;
	this->bMotionLoopFlg	= true;

	/* アニメーション初期設定 */
	// アニメーション設定
	this->AnimFileName		= "Test_Player";
	this->NowMotionName		= "Delay";
	// パーツアニメーションセットアップ
	this->pDataList_2DPartsAnimCreateTool->LoadPartsAnimData(this->AnimFileName);

	/* チームタグ設定 */
	this->SetTeamTag("Player");

	/* ステータス関係 */
	// ※仮設定
	this->iSpeed = TEST_PLAYER_MOVE_SPEED;
}

// デストラクタ
Character_Player::~Character_Player()
{
	
}

// 更新
void Character_Player::Update()
{
	/* 移動・重力処理 */
	Update_ApplyGravity();
	Update_ApplyMovement();

	/* ワールドマップ上の座標を設定 */
	this->pDataList_GameStatus->SetPlayerPosition_WoldMap(this->vecBasePosition);

	/* ベースクラスの更新処理 */
	Character_Base::Update();

	/* アニメーションの更新 */
	Character_Base::Update_Animation();
}

// 描画
void Character_Player::Draw()
{
	/* アニメーション描写 */
	Character_Base::Draw_Animation();

	/* 中心点テスト描写 */
	DrawLine3D(VAdd(this->vecBasePosition, VGet(100.f, 0.f, 0.f)), VAdd(this->vecBasePosition, VGet(-100.f, 0.f, 0.f)), GetColor(255, 0, 0));
	DrawLine3D(VAdd(this->vecBasePosition, VGet(0.f, 100.f, 0.f)), VAdd(this->vecBasePosition, VGet(0.f, -100.f, 0.f)), GetColor(0, 255, 0));
	DrawLine3D(VAdd(this->vecBasePosition, VGet(0.f, 0.f, 100.f)), VAdd(this->vecBasePosition, VGet(0.f, 0.f, -100.f)), GetColor(0, 0, 255));

	/* グリッド範囲テスト描写 */
	int iGridX = iGetGridIndexX(this->vecBasePosition.x);
	int iGridZ = iGetGridIndexZ(this->vecBasePosition.z);
	for (int iX = iGridX - 1; iX <= iGridX + 1; ++iX)
	{
		for (int iZ = iGridZ - 1; iZ <= iGridZ + 1; ++iZ)
		{
			// グリッド左上座標
			float fGridMinX = static_cast<float>(iX * GRID_SIZE_WORLD_X);
			float fGridMinZ = static_cast<float>(iZ * GRID_SIZE_WORLD_Z);
			float fGridMaxX = fGridMinX + GRID_SIZE_WORLD_X;
			float fGridMaxZ = fGridMinZ + GRID_SIZE_WORLD_Z;
			float fY = this->vecBasePosition.y; // 高さはプレイヤー基準

			VECTOR v0 = VGet(fGridMinX, fY, fGridMinZ); // 左上
			VECTOR v1 = VGet(fGridMaxX, fY, fGridMinZ); // 右上
			VECTOR v2 = VGet(fGridMaxX, fY, fGridMaxZ); // 右下
			VECTOR v3 = VGet(fGridMinX, fY, fGridMaxZ); // 左下

			// 四辺を線で描画
			DrawLine3D(v0, v1, GetColor(255, 255, 0));
			DrawLine3D(v1, v2, GetColor(255, 255, 0));
			DrawLine3D(v2, v3, GetColor(255, 255, 0));
			DrawLine3D(v3, v0, GetColor(255, 255, 0));
		}
	}
}
