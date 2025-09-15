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
#include "Building_CoreTree.h"
// 共通定義
#include "ConstantDefine.h"

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
	this->bMotionLoopFlg	= false;
	// ステータス系
	this->iHealth			= 0;		// 体力
	this->iMaxHealth		= 0;		// 最大体力
	this->iSpeed			= 0;		// 速度
	// 状態系
	this->bDeadFlg			= false;	// 死亡フラグ
	this->iInvincibleTime	= 0;		// 残り無敵時間(フレーム数)
	// コリジョン
	// ※デフォルトではブロックと同じサイズに設定
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
void Character_Base::InitialSetup()
{
	/* ステータス設定 */
	// ※未実装だがJsonから読み込む予定
	//this->iHealth		= 0;	// 体力
	//this->iMaxHealth	= 0;	// 最大体力
	//this->iSpeed		= 0;	// 速度	
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
void Character_Base::Ground_PushBack_Gravity()
{
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
		for (auto& Ground : this->pDataList_Object->GetGroundList(iAreaNo)) { CollisionList.push_back(Ground); }	// 足場		
		for (auto& Building : this->pDataList_Object->GetBuildingList()) { CollisionList.push_back(Building); }	// 建造物


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
}

// 地形からの押し出し処理(移動処理用)
void Character_Base::Ground_PushBack_Movement(VECTOR vecMoveDirection)
{
	// 引数
	// vecMoveDirectiron	: 移動方向(速度未反映、正規化不要)

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
	stMoveBox.vecBoxCenter = VAdd(vecMovePosition, VGet(0.f, this->stBox.vecBoxHalfSize.y, 0.f));
	stMoveBox.vecBoxHalfSize = this->stBox.vecBoxHalfSize;
	stMoveBox.vecBoxHalfSize.y += COLLISION_CHECK_FLOOR_MARGIN;

	/* 地形との接地判定 */
	// ※ 軽量化のため現在のエリアの足場のみ確認
	// ※ エリア外の場合は足場との当たり判定を行わない
	int iAreaNo = iCheckCurrentAreaNo();
	if (iAreaNo != -1)
	{
		/* 判定対象リストを作成 */
		std::vector<std::shared_ptr<Ground_Base>> CollisionList;
		for (auto& Ground : this->pDataList_Object->GetGroundList(iAreaNo)) { CollisionList.push_back(Ground); }	// 足場		
		for (auto& Building : this->pDataList_Object->GetBuildingList()) { CollisionList.push_back(Building); }	// 建造物

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
}

// 移動経路検索
void Character_Base::Route_Search()
{
	/* 移動ルートをA*アルゴリズムで算出 */

	/* 現在の座標を設定 */
	VECTOR vecStart = this->vecBasePosition;

	/* 目的地の座標を設定 */
	VECTOR vecGoal = this->pDataList_GameStatus->GetCoreTreePosition();

	/* 評価値リストを作成 */
	std::vector<ASTAR_EVALUATION_LIST> astEvaluationList;

	/* スタート地点の情報をオープンリストとして評価値リストへ追加 */
	ASTAR_EVALUATION_LIST stStartNode;
	stStartNode.bStartNodeFlg		= true;														// スタート地点フラグを有効
	stStartNode.bGoalNodeFlg		= false;													// ゴール地点フラグを無効
	stStartNode.iCost_G				= 0;														// Gコスト(累計のコスト)を0に設定
	stStartNode.iCost_H				= static_cast<int>(VSquareSize(VSub(vecGoal, vecStart)));	// Hコスト(ゴールまでの予測コスト)を設定
	stStartNode.iCost_F				= stStartNode.iCost_G + stStartNode.iCost_H;				// Fコスト(Gコスト + Hコスト)を設定
	stStartNode.bOpenListFlg		= true;														// オープンリストフラグを有効に設定
	stStartNode.bCloseListFlg		= false;													// クローズリストフラグを無効に設定
	stStartNode.vecParentPosition	= vecStart;													// 親ノードは自分自身に設定
	stStartNode.vecPosition			= vecStart;													// ノードの座標を設定
	astEvaluationList.push_back(stStartNode);

	/* A*アルゴリズムを用いた経路検索処理 */
	bool	bGoalFoundFlg	= false;					// ゴールを発見したかのフラグ
	VECTOR	vecCurrentNode	= this->vecBasePosition;	// 現在処理中のノードの座標
	VECTOR	vecGoalHitNode	= VGet(0.f, 0.f, 0.f);		// ゴールに接触したノードの座標
	while (true)
	{
		/* 評価値リスト内のオープンリストからFコストが最少のノードを検索 */
		int		iMinF_Cost		= INT_MAX;	// Fコストの最小値
		bool	bFoundFlg		= false;	// Fコストが最小のノードを発見したかのフラグ
		int		iMinF_Cost_G	= 0;		// Fコストが最小のノードのGコスト

		for (auto& node : astEvaluationList)
		{
			/* オープンリストに登録されていて、F値が最小値であるか */
			if (node.bOpenListFlg && node.iCost_F < iMinF_Cost)
			{
				// 条件を満たす場合
				/* Fコストの最小値を更新 */
				iMinF_Cost		= node.iCost_F;
				iMinF_Cost_G	= node.iCost_G;
				vecCurrentNode	= node.vecPosition;
				bFoundFlg = true;
			}
		}

		/* Fコストが最小のノードが見つからなかった場合は探索失敗とする */
		if (!bFoundFlg) { break; }

		/* 現在のノードをオープンリストからクローズリストに移動させる */
		for (auto& node : astEvaluationList)
		{
			if (node.vecPosition.x == vecCurrentNode.x &&
				node.vecPosition.y == vecCurrentNode.y &&
				node.vecPosition.z == vecCurrentNode.z)
			{
				node.bOpenListFlg = false;
				node.bCloseListFlg = true;
				break;
			}
		}

		/* 現在地点を基準に8方向のノードを検索 */
		const int POS_INDEX = 8;	// 8方向
		VECTOR avecNextPosition[POS_INDEX] =
		{
			VGet(+ROUTE_SEARCH_MOVE_DISTANCE,	0.f,	0.f),							// X+方向
			VGet(+ROUTE_SEARCH_MOVE_DISTANCE,	0.f,	+ROUTE_SEARCH_MOVE_DISTANCE),	// X+、Z+方向
			VGet(0.f,							0.f,	+ROUTE_SEARCH_MOVE_DISTANCE),	// Z+方向
			VGet(-ROUTE_SEARCH_MOVE_DISTANCE,	0.f,	+ROUTE_SEARCH_MOVE_DISTANCE),	// X-,Z+方向
			VGet(-ROUTE_SEARCH_MOVE_DISTANCE,	0.f,	0.f),							// X-方向
			VGet(-ROUTE_SEARCH_MOVE_DISTANCE,	0.f,	-ROUTE_SEARCH_MOVE_DISTANCE),	// X-,Z-方向
			VGet(0.f,							0.f,	-ROUTE_SEARCH_MOVE_DISTANCE),	// Z-方向
			VGet(+ROUTE_SEARCH_MOVE_DISTANCE,	0.f,	-ROUTE_SEARCH_MOVE_DISTANCE)	// X+,Z-方向
		};

		for (int i = 0; i < POS_INDEX; ++i)
		{
			// 移動コストをデフォルト値に設定
			int iMoveCost = ROUTE_SEARCH_MOVE_COST_DEFAULT;

			/* 移動可能か確認する座標を取得 */
			VECTOR vecNextPosition = VAdd(vecCurrentNode, avecNextPosition[i]);

			/* 移動可能であるか確認 */
			int iCheckResult = iCheck_Moveble(vecNextPosition);
			if (iCheckResult != MOVE_NOT)
			{
				// 移動可能である場合
				/* 斜め方向への移動であるならコストを変更 */
				if (i % 2 == 1) { iMoveCost = ROUTE_SEARCH_MOVE_COST_DIAG; }
				/* 上方向への移動であるならコストを加算 + 座標を変更 */
				if (iCheckResult == MOVE_UP)
				{
					vecNextPosition.y	+= MAP_BLOCK_SIZE_Y;
					iMoveCost			+= ROUTE_SEARCH_MOVE_COST_YCHANGE;
				}
			}
			else
			{
				// 移動不可能である場合はスキップ
				continue;
			}

			/* 移動先座標の情報をオープンリストに登録する */
			ASTAR_EVALUATION_LIST stAddNode;
			stAddNode.bGoalNodeFlg		= false;													// ゴール地点フラグを無効
			stAddNode.bStartNodeFlg		= false;													// スタート地点フラグを無効
			stAddNode.iCost_G			= iMinF_Cost_G + iMoveCost;									// Gコスト(累計のコスト)を現在の値 + 移動コストに設定
			stAddNode.iCost_H			= static_cast<int>(VSquareSize(VSub(vecGoal, vecStart)));	// Hコスト(ゴールまでの予測コスト)を設定
			stAddNode.iCost_F			= stStartNode.iCost_G + stStartNode.iCost_H;				// Fコスト(Gコスト + Hコスト)を設定
			stAddNode.bOpenListFlg		= true;														// オープンリストフラグを有効に設定
			stAddNode.bCloseListFlg		= false;													// クローズリストフラグを無効に設定
			stAddNode.vecParentPosition	= vecCurrentNode;											// 親ノードの座標を現在のノードの座標に設定
			stAddNode.vecPosition		= vecNextPosition;											// ノードの座標を移動先に設定

			/* すでに評価値リストに類似座標が登録されているか確認 */
			// ※ 同じ座標が登録されている場合は登録しない
			bool bAlreadyRegisteredFlg = false;
			for (auto& node : astEvaluationList)
			{
				/* 各ブロック座標の半分の値までは誤差の範囲内とする */
				if (PUBLIC_PROCESS::bIsFloatDiffWithinThreshold(node.vecPosition.x, stAddNode.vecPosition.x, MAP_BLOCK_SIZE_X / 2.f) &&
					PUBLIC_PROCESS::bIsFloatDiffWithinThreshold(node.vecPosition.y, stAddNode.vecPosition.y, MAP_BLOCK_SIZE_Y / 2.f) &&
					PUBLIC_PROCESS::bIsFloatDiffWithinThreshold(node.vecPosition.z, stAddNode.vecPosition.z, MAP_BLOCK_SIZE_Z / 2.f))
				{
					// 類似座標が登録されている場合
					bAlreadyRegisteredFlg = true;
					break;
				}
			}

			/* 類似座標が登録されていないのであれば評価値リストに登録を行う */
			if (!bAlreadyRegisteredFlg)
			{
				/* 目的地に到達しているか確認 */
				if (iCheckResult == MOVE_GOALHIT)
				{
					// 目的地に到達している場合
					stAddNode.bGoalNodeFlg	= true;				// ゴール地点フラグを有効化
					bGoalFoundFlg			= true;				// ゴール発見フラグを有効化
					vecGoalHitNode			= vecNextPosition; // ゴールに接触したノードの座標を保存
					astEvaluationList.push_back(stAddNode);
					break;
				}
				else
				{
					astEvaluationList.push_back(stAddNode);
				}
			}
		}

		/* ゴールへ到達している場合はループを抜ける */
		if (bGoalFoundFlg) { break; }
	}

	/* ゴールへ到達しているか確認 */
	if (!bGoalFoundFlg) { return; }	// ゴールへ到達していない場合は処理を終了

	/* 経路の復元を実施 */
	// ※ ゴールのノードから親ノードを辿っていく
	bool bSartFoundFlg	= false;				// スタート地点を発見したかのフラグ
	vecCurrentNode		= vecGoalHitNode;		// ゴール地点の座標に設定

	/* 評価値リストをループしてゴールからスタートへのルートを復元 */
	while (true)
	{
		/* 移動前座標を評価値リストから検索し、親座標を見つける */
		for (auto& Evaluation : astEvaluationList)
		{
			/* チェック座標が一致するノードを探す */
			// ※ 各ブロック座標の半分の値までは誤差の範囲内とする
			if (PUBLIC_PROCESS::bIsFloatDiffWithinThreshold(Evaluation.vecPosition.x, vecCurrentNode.x, MAP_BLOCK_SIZE_X / 2.f) &&
				PUBLIC_PROCESS::bIsFloatDiffWithinThreshold(Evaluation.vecPosition.y, vecCurrentNode.y, MAP_BLOCK_SIZE_Y / 2.f) &&
				PUBLIC_PROCESS::bIsFloatDiffWithinThreshold(Evaluation.vecPosition.z, vecCurrentNode.z, MAP_BLOCK_SIZE_Z / 2.f))
			{
				// 対象のノードを発見した場合
				/* チェック座標を親座標に更新する */
				vecCurrentNode = Evaluation.vecParentPosition;

				/* ノードの座標を移動ルートに設定 */
				avecMovePath.push_back(Evaluation.vecPosition);

				/* スタート地点であるか確認 */
				if (Evaluation.bStartNodeFlg)
				{
					// スタート地点である場合
					bSartFoundFlg = true;
					break;
				}
			}
		}

		/* スタート地点に到達した場合、ループを抜ける */
		if (bSartFoundFlg) { break; }
	}
}

// 移動可能か確認
int Character_Base::iCheck_Moveble(VECTOR vecMovePos)
{
	// 引数
	// vecMovePos	: 移動先の座標
	// 戻り値
	// int			: (MOVE_NOT:移動不可 / MOVE_OK:そのまま移動可能 / MOVE_UP:上方向へ移動すれば移動可能) / MOVE_GOALHIT:目標へ到達

	int iReturnValue = MOVE_OK;	// 戻り値

	/* 確認するコリジョンを作成 */
	// ※ 縦方向には少し余裕を持たせる(地形の凹凸に引っかからないようにするため)
	Struct_Collision::COLLISION_BOX stCheckBox;
	stCheckBox.vecBoxCenter		= VAdd(vecMovePos, VGet(0.f, this->stBox.vecBoxHalfSize.y, 0.f));
	stCheckBox.vecBoxHalfSize	= this->stBox.vecBoxHalfSize;
	stCheckBox.vecBoxHalfSize.y	+= COLLISION_CHECK_FLOOR_MARGIN;

	/* 地形との接地判定 */
	// ※ 軽量化のため現在のエリアの足場のみ確認
	// ※ エリア外の場合は足場との当たり判定を行わない
	int iAreaNo = iCheckCurrentAreaNo();
	if (iAreaNo == -1) { return MOVE_NOT; }	// エリア外の場合は移動不可とする

	/* 判定対象リストを作成 */
	std::vector<std::shared_ptr<Ground_Base>> CollisionList;
	for (auto& Ground : this->pDataList_Object->GetGroundList(iAreaNo)) { CollisionList.push_back(Ground); }	// 足場
	for (auto& Building : this->pDataList_Object->GetBuildingList())	{ CollisionList.push_back(Building); }	// 建造物

	/* 接触した全ての地形を記録 */
	std::vector<Struct_Collision::COLLISION_BOX> hitGroundBoxes;
	for (auto& Collision : CollisionList)
	{
		/* 接触しているか確認 */
		if (Collision->HitCheck(stCheckBox))
		{
			// 接触している場合
			/* 接触した対象が神木(防衛対象)であるか確認 */
			// キャストを行い、神木であるか確認
			Building_CoreTree* pCoreTree = dynamic_cast<Building_CoreTree*>(Collision.get());
			if (pCoreTree != nullptr)
			{
				// 神木である場合
				/* 目標へ到達とする */
				return MOVE_GOALHIT;
			}

			/* ブロック1マス分上昇させた場合、接触しているか確認 */
			Struct_Collision::COLLISION_BOX stCheckBox_Up = stCheckBox;
			stCheckBox_Up.vecBoxCenter.y += MAP_BLOCK_SIZE_Y;
			if (Collision->HitCheck(stCheckBox_Up))
			{
				// 接触している場合
				/* 移動不可とする */
				return MOVE_NOT;
			}
			else
			{
				// 接触していない場合
				/* 上方向へ移動すれば移動可能とする */
				iReturnValue = MOVE_UP;
			}
		}
	}

	return iReturnValue;
}