/* キャラクターのベースクラスの定義 */

/* 使用する要素のインクルード */
// 標準ライブラリ
#define NOMINMAX
#include <algorithm>
// ヘッダファイル
#include "Character_Base.h"
// 関連クラス
#include "DataList_Object.h"
#include "DataList_GameStatus.h"
#include "Ground_Base.h"
#include "Ground_Model.h"
// 共通定義
#include "ConstantDefine.h"
#include "FunctionDefine.h"

// コンストラクタ
Character_Base::Character_Base() : Actor_Base()
{
	// データリスト取得
	this->pDataList_GameStatus				= std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));							// ゲーム状態管理
	this->pDataList_2DPartsAnimCreateTool	= std::dynamic_pointer_cast<DataList_2DPartsAnimCreateTool>(gpDataListServer->GetDataList("DataList_2DPartsAnimCreateTool"));	// 2Dパーツアニメーションツール

	// 画像データ作成
	this->iScreenHandle_Animation = MakeScreen(CHARACTER_PARTS_ANIM_DRAW_SIZE_WIDE, CHARACTER_PARTS_ANIM_DRAW_SIZE_HEIGHT, TRUE);

	/* 初期化 */
	// アニメーション関係
	this->AnimFileName		= "";
	this->NowMotionName		= "";
	this->iMotionCount		= 0;
	this->bMotionEndFlg		= false;
	this->bMotionLoopFlg	= true;
	// パラメーター系(プレイヤー、NPC共通)
	this->iHealth			= 0;	// 体力
	this->iMaxHealth		= 0;	// 最大体力
	this->iAttack			= 0;	// 攻撃力
	this->iSpeed			= 0;	// 速度
	this->iAutoHealDelay	= 0;	// 自動回復待機時間
	this->iAutoHealAmount	= 0;	// 自動回復量
	// パラメーター系(NPC用)
	this->fSearchRange		= 0.f;		// 探索範囲
	this->fAttackRange		= 0.f;		// 攻撃範囲
	this->bContactDamageFlg	= false;	// 接触によりダメージ発生するかのフラグ
	this->bAttackMeleeFlg	= false;	// 近接攻撃を行うかのフラグ
	// 行動パターンフラグ(NPC用)
	for (int i = 0; i < NPC_ENEMY_ACTION_PATTERN_MAX; ++i)		{ abEnemyActionPatternFlg[i]		= false; }
	for (int i = 0; i < LONG_RANGE_ATTACK_DIR_PATTERN_MAX; ++i)	{ abLongRangeAttackPatternFlg[i]	= false; }
	// 状態系
	this->bDeadFlg			= false;	// 死亡フラグ
	this->iInvincibleTime	= 0;		// 残り無敵時間(フレーム数)
	// コリジョン
	// ※ ブロックと同じサイズに設定
	this->stBox.vecBoxCenter	= VGet(0.0f, 0.0f, 0.0f);
	this->stBox.vecBoxHalfSize	= VGet(MAP_BLOCK_SIZE_X / 2.f, MAP_BLOCK_SIZE_Y / 2.f, MAP_BLOCK_SIZE_Z / 2.f);	
}

// デストラクタ
Character_Base::~Character_Base()
{
	/* 画像データ削除 */
	// アニメーション用
	DeleteGraph(this->iScreenHandle_Animation);
}

// 初期設定
// ※ アニメーションファイル名やステータスは子クラスのほうで読み込むこと
void Character_Base::InitialSetup()
{
	// パーツアニメーションセットアップ
	this->pDataList_2DPartsAnimCreateTool->LoadPartsAnimData(this->AnimFileName);
}

// 更新
// ※ 基準座標の更新が完了してから実行すること
void Character_Base::Update()
{
	/* HPが残っているか確認 */
	if (this->iHealth <= 0)
	{
		// HPが0以下なら死亡フラグを立てる
		this->bDeadFlg = true;
	}

	/* 無敵時間の更新 */
	if (this->iInvincibleTime > 0)
	{
		--this->iInvincibleTime;
	}

	/* コリジョンの更新 */
	Update_Collision();

	/* アニメーションの更新 */
	Update_Animation();
}

// 描写
void Character_Base::Draw()
{
	/* アニメーション描写 */
	Draw_Animation();
}

// 描画(シャドウマップ用)
void Character_Base::Draw_Shadow()
{
	/* コリジョンの中心座標と半径から球体を作成し、影とする */
	DrawSphere3D(this->stBox.vecBoxCenter, this->stBox.vecBoxHalfSize.x, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
}

// コリジョン描画(デバッグ用)
void Character_Base::Draw_Collision()
{
	/* 頂点を設定 */
	VECTOR aVertex[8];
	aVertex[0] = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[1] = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);
	aVertex[2] = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[3] = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);
	aVertex[4] = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[5] = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);
	aVertex[6] = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[7] = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);

	/* 線分を描画 */
	PUBLIC_FUNCTION::DrawCubeLine3D(aVertex, GetColor(255, 255, 255));
}

// コリジョン更新
void Character_Base::Update_Collision()
{
	/* コリジョンの中心座標を更新 */
	// ※ 現在の基準座標からコリジョンの中心座標を設定
	this->stBox.vecBoxCenter = VAdd(this->vecBasePosition, VGet(0.f, this->stBox.vecBoxHalfSize.y, 0.f));
}

// アニメーション更新
void Character_Base::Update_Animation()
{
	/* アニメーション描写開始 */
	SetDrawScreen(this->iScreenHandle_Animation);

	/* 画面クリア */
	ClearDrawScreen();

	/* 画面サイズを設定 */
	this->pDataList_2DPartsAnimCreateTool->SetDrawScreenSize(CHARACTER_PARTS_ANIM_DRAW_SIZE_WIDE, CHARACTER_PARTS_ANIM_DRAW_SIZE_HEIGHT);

	/* 現在モーションのパーツアニメーションの描写 */
	this->pDataList_2DPartsAnimCreateTool->DrawPartsAnim(this->AnimFileName, this->NowMotionName, this->iMotionCount);

	/* アニメーション描写終了 */
	SetDrawScreen(DX_SCREEN_BACK);

	/* モーションカウントを進める */
	++this->iMotionCount;

	/* モーション終了フラグをリセット */
	this->bMotionEndFlg = false;

	/* 現在のモーションの最大カウントを超えているか確認 */
	if (this->iMotionCount >= this->pDataList_2DPartsAnimCreateTool->iGetPartsAnimMaxTime(this->AnimFileName, this->NowMotionName))
	{
		// 超えている場合
		/* モーション終了フラグを有効化 */
		this->bMotionEndFlg = true;

		/* モーションループフラグを確認 */
		if (this->bMotionLoopFlg)
		{
			// ループフラグが有効な場合
			/* モーションカウントをリセット */
			this->iMotionCount = 0;
		}
	}
}

// アニメーション描写
void Character_Base::Draw_Animation()
{
	/* 中心座標を基準としたアニメーションを描写するパネルの頂点座標を計算 */
	float fHalfWide	= CHARACTER_PARTS_ANIM_DRAW_SIZE_WIDE / 2;
	float fHeight	= CHARACTER_PARTS_ANIM_DRAW_SIZE_HEIGHT;
	// 正方形を維持するためのY+側のY座標補正
	float fYLean = sqrtf(fHeight * fHeight - TOPVIEW_LEAN_AMOUNT * TOPVIEW_LEAN_AMOUNT);

	VERTEX3D aVertex[4];
	aVertex[0].pos = VGet(this->vecBasePosition.x + fHalfWide, this->vecBasePosition.y + fYLean, this->vecBasePosition.z - 32.f + TOPVIEW_LEAN_AMOUNT);
	aVertex[1].pos = VGet(this->vecBasePosition.x + fHalfWide, this->vecBasePosition.y, this->vecBasePosition.z - 32.f);
	aVertex[2].pos = VGet(this->vecBasePosition.x - fHalfWide, this->vecBasePosition.y + fYLean, this->vecBasePosition.z - 32.f + TOPVIEW_LEAN_AMOUNT);
	aVertex[3].pos = VGet(this->vecBasePosition.x - fHalfWide, this->vecBasePosition.y, this->vecBasePosition.z - 32.f);

	// 頂点の初期化
	for (int i = 0; i < 4; ++i)
	{
		aVertex[i].dif = GetColorU8(255, 255, 255, 255);
		aVertex[i].spc = GetColorU8(0, 0, 0, 0);
		aVertex[i].su = 0.f;
		aVertex[i].sv = 0.f;
	}

	/* 各面の描画 */
	// インデックスデータ（奥面の2ポリゴン）
	unsigned short IndexBack[6] = { 3, 2, 1, 1, 2, 0 };

	// 法線ベクトルを設定
	for (int i = 0; i < 4; ++i)
	{
		aVertex[i].norm = VGet(0.0f, 0.0f, -1.0f);
	}

	// uv座標を設定
	// 右上
	aVertex[0].u = 1.f;
	aVertex[0].v = 0.f;
	// 右下
	aVertex[1].u = 1.f;
	aVertex[1].v = 1.f;
	// 左上
	aVertex[2].u = 0.f;
	aVertex[2].v = 0.f;
	// 左下
	aVertex[3].u = 0.f;
	aVertex[3].v = 1.f;

	// 四角形（板ポリゴン）の描画
	DrawPolygonIndexed3D(aVertex, 8, IndexBack, 2, this->iScreenHandle_Animation, TRUE);
}

// 地形からの押し出し処理(重力処理用)
bool Character_Base::bGround_PushBack_Gravity()
{
	// 戻り値
	// bool					: 押し出しが発生したかどうか(false:未発生 / true:発生)

	bool bPushBackFlg = false;	// 押し出し発生フラグ

	/* 重力加速度を加算 */
	this->fGravityVelocity -= this->fGravityAcceleration;

	/* 移動前の基準座標を保存 */
	VECTOR vecPrevPosition = this->vecBasePosition;

	/* 移動後の基準座標を算出 */
	VECTOR vecMovePosition = VAdd(vecPrevPosition, VGet(0.f, this->fGravityVelocity, 0.f));

	/* 移動後の座標と移動前の座標からボックスコリジョンを作成 */
	// ※ 中心点を平均値、大きさは高さを(移動量 + 直径)にすれば2点を通るボックスになるのでそれを基準にコリジョンをつくる
	// ※ 横方向には少し余裕を持たせる(壁に接触した状態でジャンプができるようにするため)
	Struct_Collision::COLLISION_BOX stMoveBox;
	stMoveBox.vecBoxCenter		= VGet(this->vecBasePosition.x, (vecMovePosition.y + this->vecBasePosition.y) / 2.f, this->vecBasePosition.z);
	stMoveBox.vecBoxHalfSize	= VGet(this->stBox.vecBoxHalfSize.x - COLLISION_CHECK_CEILING_PREVENTION, (fabsf(vecMovePosition.y - this->vecBasePosition.y) / 2) + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxHalfSize.z - COLLISION_CHECK_CEILING_PREVENTION);

	// 上昇中、下降中それぞれの補正
	if (this->fGravityVelocity > 0)
	{
		// 上昇中
		// ボックスコリジョンの下部分を判定しないようにする(ジャンプ直後に着地判定が出てしまう問題対策)
		stMoveBox.vecBoxCenter.y	+= COLLISION_CHECK_CEILING_PREVENTION / 2.f;
		stMoveBox.vecBoxHalfSize.y	-= COLLISION_CHECK_CEILING_PREVENTION;
	}
	else
	{
		// 下降中
		// ボックスコリジョンの上部分を判定しないようにする(天井に対して着地判定が出てしまう問題対策)
		stMoveBox.vecBoxCenter.y	-= COLLISION_CHECK_CEILING_PREVENTION / 2.f;
		stMoveBox.vecBoxHalfSize.y	-= COLLISION_CHECK_CEILING_PREVENTION;
	}

	/* 地形との接地判定 */
	// ※ 軽量化のため現在のエリアの足場のみ確認
	// ※ エリア外の場合は足場との当たり判定を行わない
	bool bGroundHit = false;	// 地面に接地しているか
	int iAreaNo = iCheckCurrentAreaNo();
	if (iAreaNo != -1)
	{
		/* 判定対象リストを作成 */
		std::vector<std::shared_ptr<Ground_Base>> CollisionList;
		// 現在のグリッドとその四方のグリッドの地形
		int iGridX = iGetGridIndexX(this->vecBasePosition.x);
		int iGridZ = iGetGridIndexZ(this->vecBasePosition.z);
		for (int iX = iGridX - 1; iX <= iGridX + 1; ++iX)
		{
			for (int iZ = iGridZ - 1; iZ <= iGridZ + 1; ++iZ)
			{
				for (auto& Ground : this->pDataList_Object->GetGroundList(iX, iZ))
				{
					CollisionList.push_back(Ground);
				}
			}
		}
		// 全ての建造物
		for (auto& Building : this->pDataList_Object->GetBuildingList())
		{
			CollisionList.push_back(Building);
		}

		/* 接触判定 */
		for (auto& Collision : CollisionList)
		{
			/* 接触しているか確認 */
			if (Collision->HitCheck(stMoveBox))
			{
				// 接触している場合
				/* 接地しているとみなす */
				bGroundHit = true;

				/* 対象のオブジェクトのコリジョン情報を取得 */
				Struct_Collision::COLLISION_BOX stGroundBoxCollision;

				stGroundBoxCollision = Collision->GetBoxCollision();

				/* プレイヤーが上昇中であるか下降中であるか判定 */
				// ※ 上昇中の場合は下方向に押し出し、下降中の場合は上方向に押し出し
				if (this->fGravityVelocity > 0)
				{
					// 上昇中(下方向へ押し出し)
					vecMovePosition.y = stGroundBoxCollision.vecBoxCenter.y - stGroundBoxCollision.vecBoxHalfSize.y;
				}
				else
				{
					// 下降中(上方向へ押し出し)
					vecMovePosition.y = stGroundBoxCollision.vecBoxCenter.y + stGroundBoxCollision.vecBoxHalfSize.y;
				}

				/* 押し出し発生フラグを有効化 */
				bPushBackFlg = true;
				break;
			}
		}
	}

	/* 建造物に対しての押し出し処理も行う */
	if (iAreaNo != -1)
	{
		for (auto& Building : this->pDataList_Object->GetBuildingList())
		{
			/* 接触しているか確認 */
			if (Building->HitCheck(stMoveBox))
			{
				// 接触している場合
				/* 接地しているとみなす */
				bGroundHit = true;

				/* 対象のオブジェクトのコリジョン情報を取得 */
				Struct_Collision::COLLISION_BOX stBuildingBoxCollision;
				stBuildingBoxCollision = Building->GetBoxCollision();

				/* プレイヤーが上昇中であるか下降中であるか判定 */
				// ※ 上昇中の場合は下方向に押し出し、下降中の場合は上方向に押し出し
				if (this->fGravityVelocity > 0)
				{
					// 上昇中(下方向へ押し出し)
					vecMovePosition.y = stBuildingBoxCollision.vecBoxCenter.y - stBuildingBoxCollision.vecBoxHalfSize.y;
				}
				else
				{
					// 下降中(上方向へ押し出し)
					vecMovePosition.y = stBuildingBoxCollision.vecBoxCenter.y + stBuildingBoxCollision.vecBoxHalfSize.y;
				}

				/* 押し出し発生フラグを有効化 */
				bPushBackFlg = true;
				break;
			}
		}
	}


	/* 接地しているか確認 */
	if (bGroundHit == true)
	{
		// 接地している場合
		/* 基準座標を移動後の座標に設定 */
		this->vecBasePosition = vecMovePosition;

		/* 落下速度をリセット */
		this->fGravityVelocity = 0.f;
	}
	else
	{
		// 接地していない場合
		/* 基準座標を移動後の座標に設定 */
		this->vecBasePosition = vecMovePosition;
	}

	return  bPushBackFlg;
}

// 地形からの押し出し処理(移動処理用)
bool Character_Base::bGround_PushBack_Movement(VECTOR vecMoveDirection)
{
	// 引数
	// vecMoveDirectiron	: 移動方向(速度未反映、正規化不要)
	// 戻り値
	// bool					: 押し出しが発生したかどうか(false:未発生 / true:発生)

	bool bPushBackFlg = false;	// 押し出し発生フラグ

	/* 移動前の座標を保存 */
	VECTOR vecPrevPosition = this->vecBasePosition;

	/* 移動している場合の処理 */
	// 正規化→速度反映
	vecMoveDirection = VScale(VNorm(vecMoveDirection), static_cast<float>(this->iSpeed));

	/* 移動後の基準座標を算出 */
	VECTOR vecMovePosition = VAdd(vecPrevPosition, vecMoveDirection);

	/* 移動後座標のコリジョン作成 */
	// ※ 縦方向には少し余裕を持たせる(地形の凹凸に引っかからないようにするため)
	Struct_Collision::COLLISION_BOX stMoveBox;
	stMoveBox.vecBoxCenter		= VAdd(vecMovePosition, VGet(0.f, this->stBox.vecBoxHalfSize.y, 0.f));
	stMoveBox.vecBoxHalfSize	= this->stBox.vecBoxHalfSize;
	stMoveBox.vecBoxHalfSize.y	+= COLLISION_CHECK_FLOOR_MARGIN;

	/* 地形との接地判定 */
	// ※ 軽量化のため現在のエリアの足場のみ確認
	// ※ エリア外の場合は足場との当たり判定を行わない
	int iAreaNo = iCheckCurrentAreaNo();
	if (iAreaNo != -1)
	{
		/* 判定対象リストを作成 */
		std::vector<std::shared_ptr<Ground_Base>> CollisionList;
		// 現在のグリッドとその四方のグリッドの地形
		int iGridX = iGetGridIndexX(stMoveBox.vecBoxCenter.x);
		int iGridZ = iGetGridIndexZ(stMoveBox.vecBoxCenter.z);
		for (int iX = iGridX - 1; iX <= iGridX + 1; iX++)
		{
			for (int iZ = iGridZ - 1; iZ <= iGridZ + 1; iZ++)
			{
				for (auto& Ground : this->pDataList_Object->GetGroundList(iX, iZ))
				{
					CollisionList.push_back(Ground);
				}
			}
		}
		// 全ての建造物
		for (auto& Building : this->pDataList_Object->GetBuildingList())
		{
			CollisionList.push_back(Building);
		}

		/* 接触した全ての地形を記録 */
		std::vector<Struct_Collision::COLLISION_BOX> hitGroundBoxes;
		for (auto& Collision : CollisionList)
		{
			/* 接触しているか確認 */
			if (Collision->HitCheck(stMoveBox))
			{
				// 接触している場合
				/* 接触した地形のコリジョン情報を保存 */
				hitGroundBoxes.push_back(Collision->GetBoxCollision());

				/* 押し出し発生フラグを有効化 */
				bPushBackFlg = true;
			}
		}

		/* 押し出しが完了するまで判定を繰り返す */
		int		iLoopCount = 0;	// ループ回数
		bool	bPushed;	// 押し出しが発生したか
		do
		{
			bPushed = false;
			for (const auto& stGroundBox : hitGroundBoxes)
			{
				/* 各軸の最小・最大座標を計算 */
				float playerMinX = vecMovePosition.x - stMoveBox.vecBoxHalfSize.x;
				float playerMaxX = vecMovePosition.x + stMoveBox.vecBoxHalfSize.x;
				float playerMinZ = vecMovePosition.z - stMoveBox.vecBoxHalfSize.z;
				float playerMaxZ = vecMovePosition.z + stMoveBox.vecBoxHalfSize.z;

				float groundMinX = stGroundBox.vecBoxCenter.x - stGroundBox.vecBoxHalfSize.x;
				float groundMaxX = stGroundBox.vecBoxCenter.x + stGroundBox.vecBoxHalfSize.x;
				float groundMinZ = stGroundBox.vecBoxCenter.z - stGroundBox.vecBoxHalfSize.z;
				float groundMaxZ = stGroundBox.vecBoxCenter.z + stGroundBox.vecBoxHalfSize.z;

				// X軸の重なり量
				float overlapX = std::min(playerMaxX, groundMaxX) - std::max(playerMinX, groundMinX);
				// Z軸の重なり量
				float overlapZ = std::min(playerMaxZ, groundMaxZ) - std::max(playerMinZ, groundMinZ);

				// 接触していなければスキップ
				if (overlapX <= 0.f || overlapZ <= 0.f) continue;

				// 最小の重なり方向に押し出し
				if (overlapX < overlapZ)
				{
					// X軸方向に押し出し
					if (vecPrevPosition.x < stGroundBox.vecBoxCenter.x)
					{
						vecMovePosition.x = groundMinX - stMoveBox.vecBoxHalfSize.x;
					}
					else
					{
						vecMovePosition.x = groundMaxX + stMoveBox.vecBoxHalfSize.x;
					}
				}
				else
				{
					// Z軸方向に押し出し
					if (vecPrevPosition.z < stGroundBox.vecBoxCenter.z)
					{
						vecMovePosition.z = groundMinZ - stMoveBox.vecBoxHalfSize.z;
					}
					else
					{
						vecMovePosition.z = groundMaxZ + stMoveBox.vecBoxHalfSize.z;
					}
				}
				// 押し出しが発生したので再判定
				stMoveBox.vecBoxCenter = VAdd(vecMovePosition, VGet(0.f, this->stBox.vecBoxHalfSize.y, 0.f));
				bPushed = true;
			}

			/* 無限ループ防止処理 */
			iLoopCount++;
			if (iLoopCount > COLLISION_PUSH_MAX_LOOP)
			{
				// 最大ループ回数を超えた場合は強制終了
				/* 元の座標に戻す */
				vecMovePosition = vecPrevPosition;
				break;
			}
		} while (bPushed);
	}

	// 押し出し後の座標を基準座標に反映
	this->vecBasePosition = vecMovePosition;

	return  bPushBackFlg;
}
