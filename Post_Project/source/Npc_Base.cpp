/* キャラクター(NPC)のベースクラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Npc_Base.h"
// 関連クラス
#include "DataList_GameStatus.h"
#include "DataList_Object.h"
#include "Ground_Base.h"
#include "Ground_Model.h"
#include "Building_CoreTree.h"
// 共通定義
#include "ConstantDefine.h"
#include "FunctionDefine.h"

// コンストラクタ
Npc_Base::Npc_Base() : Character_Base()
{
	/* 初期化 */
	// パラメーター系(NPC独自)
	this->fSearchRange		= 0.f;		// 探索範囲
	this->fAttackRange		= 0.f;		// 攻撃範囲
	this->bContactDamageFlg	= false;	// 接触によりダメージ発生するかのフラグ
	this->bAttackMeleeFlg	= false;	// 近接攻撃を行うかのフラグ
	// 行動パターンフラグ
	for (int i = 0; i < NPC_ENEMY_ACTION_PATTERN_MAX; ++i)		{ abEnemyActionPatternFlg[i]		= false; }
	for (int i = 0; i < LONG_RANGE_ATTACK_DIR_PATTERN_MAX; ++i) { abLongRangeAttackPatternFlg[i]	= false; }
}

// デストラクタ
Npc_Base::~Npc_Base()
{

}

// 移動経路検索
void Npc_Base::Route_Search()
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
				bFoundFlg		= true;
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
					vecGoalHitNode			= vecNextPosition;	// ゴールに接触したノードの座標を保存
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
	bool bSartFoundFlg = false;				// スタート地点を発見したかのフラグ
	vecCurrentNode = vecGoalHitNode;		// ゴール地点の座標に設定

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
int Npc_Base::iCheck_Moveble(VECTOR vecMovePos)
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
	// 現在のグリッドとその四方のグリッドの地形
	int iGridX = iGetGridIndexX(vecMovePos.x);
	int iGridZ = iGetGridIndexZ(vecMovePos.z);
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
