/* キャラクター(NPC)のベースクラスの定義 */

/* 使用する要素のインクルード */
// 標準ライブラリ
#define NOMINMAX
#include <algorithm>
#include <fstream>
// ヘッダファイル
#include "Npc_Base.h"
// 関連クラス
#include "DataList_GameStatus.h"
#include "DataList_Object.h"
#include "DataList_Sound.h"
#include "Ground_Base.h"
#include "Ground_Model.h"
#include "Building_CoreTree.h"
#include "Item_Coin.h"
// 共通定義
#include "ConstantDefine.h"
#include "FunctionDefine.h"
#include "VariableDefine.h"

// コンストラクタ
Npc_Base::Npc_Base() : Character_Base()
{
	/* 初期化 */
	this->vecTargetPos	= VGet(0.f, 0.f, 0.f);
}

// デストラクタ
Npc_Base::~Npc_Base()
{
	/* ルート探索スレッドが動作中であるなら終了を待機 */
	if (thred_RouteSearch.valid())
	{
		thred_RouteSearch.wait();
	}
}

// 初期設定
// ※ 名前を設定してから呼び出すこと
void Npc_Base::InitialSetup()
{
	/* アニメーションファイル名をこのNPC名に設定 */
	this->AnimFileName = this->Name;

	/* キャラクター情報の読み込み */
	JsonLoad_CharacterStatus();

	/* ベースクラスの初期設定処理 */
	Character_Base::InitialSetup();
}

// 更新
void Npc_Base::Update()
{
	/* 重力落下処理 */
	bGround_PushBack_Gravity();

	/* 行動パターン管理 */
	Update_Action();

	/* ベースクラスの計算処理 */
	Character_Base::Update();

	/* 死亡フラグの確認 */
	if (this->bDeadFlg)
	{
		// 死亡フラグが有効であるなら
		/* 削除フラグを有効化 */
		this->bDeleteFlg = true;

		/* エネミーであるか */
		if (bCheckTeamTag("Enemy"))
		{
			// エネミーである場合
			/* 現在の座標にアイテム"コイン"を生成する */
			// ※ めり込ませないため、少し上にずらして生成
			std::shared_ptr<Item_Coin> pItem_Coin = std::make_shared<Item_Coin>();
			pItem_Coin->SetPosition(VAdd(this->vecBasePosition, VGet(0.f, MAP_BLOCK_SIZE_Y / 2.f, 0.f)));
			pItem_Coin->InitialSetup();
			this->pDataList_Object->AddObject_Item(pItem_Coin);
		}

		/* SEを再生 */
		this->pDataList_Sound->SE_Play("Npc_Death", this->vecBasePosition);
	}
}

// 描写
void Npc_Base::Draw()
{
	/* ベースクラスの描写処理 */
	Character_Base::Draw();

	/* HPバーの描写 */
	Draw_HpBar();

	/* デバッグモードであるか */
	if (gbDebugMode)
	{
		// デバッグモードであるなら
		/* 移動ルートの描写 */
		Draw_Route();
	}
}

// キャラクター情報の読み込み
void Npc_Base::JsonLoad_CharacterStatus()
{
	/* キャラクターの情報を読み込む */
	// ※ 名前から判断してステータスや行動パターンを読み込む

	/* JSONファイル読み込み */
	std::string FilePath = "resource/CharacterData/CharacterData_NPC.json";

	std::ifstream ifs(FilePath);
	if (!ifs) return;

	using json = nlohmann::json;
	json j;
	ifs >> j;

	/* キャラクター情報を取得 */
	for (const auto& status : j)
	{
		/* 名前が一致するキャラクター情報を探す */
		if (status.value("Name", "") == this->Name)
		{
			// 名前が一致しているなら
			/* キャラクター情報を読み込み */
			// ステータス系
			this->iMaxHealth			= status.value("MaxHealth", 0);				// 最大体力
			this->iHealth				= this->iMaxHealth;							// 体力(最大体力で初期化)
			this->iAttack				= status.value("Attack", 0);				// 攻撃力
			this->iSpeed				= status.value("Speed", 0);					// すばやさ
			this->iAutoHealDelay		= status.value("AutoHealDelay", 0);			// 自動回復待機時間
			this->iAutoHealAmount		= status.value("AutoHealAmount", 0);		// 自動回復量
			this->fSearchRange			= status.value("SearchRange", 0.f);			// 探索範囲
			this->fAttackRange			= status.value("AttackRange", 0.f);			// 攻撃範囲
			this->bContactDamageFlg		= status.value("ContactDamageFlg", false);	// 接触によりダメージ発生するかのフラグ
			this->bAttackMeleeFlg		= status.value("AttackMelee", false);		// 近接攻撃を行うかのフラグ
			this->bEnableGravityFlg		= status.value("EnableGravityFlg", true);	// 重力影響を受けるかのフラグ
			// 行動パターンフラグ(エネミー)
			auto& actionPattern = status["EnemyActionPattern"];
			for (int i = 0; i < actionPattern.size(); ++i)
			{
				this->abEnemyActionPatternFlg[i] = actionPattern[i].get<bool>();
			}
			// 行動パターンフラグ(味方NPC)
			auto& friendActionPattern = status["FriendActionPattern"];
			for (int i = 0; i < friendActionPattern.size(); ++i)
			{
				this->abFriendActionPatternFlg[i] = friendActionPattern[i].get<bool>();
			}
			// 長距離攻撃パターンフラグ
			auto& longRangePattern = status["LongRangeAttackPattern"];
			for (int i = 0; i < longRangePattern.size(); ++i)
			{
				this->abLongRangeAttackPatternFlg[i] = longRangePattern[i].get<bool>();
			}
			// チームタグ
			if (status.contains("TeamTag") && status["TeamTag"].is_array())
			{
				for (const auto& tag : status["TeamTag"])
				{
					SetTeamTag(tag.get<std::string>());
				}
			}

			/* 読み込み完了したのでループを抜ける */
			break;
		}
	}
}

// 移動経路検索
void Npc_Base::Route_Search(VECTOR vecGoalPos)
{
	// 引数
	// vecGoalPos	<- 目的地の座標

	/* 移動ルートをA*アルゴリズムで算出 */

	/* 現在の座標を設定 */
	VECTOR vecStart = this->vecBasePosition;

	/* 評価値リストを作成 */
	std::vector<ASTAR_EVALUATION_LIST> astEvaluationList;

	/* スタート地点の情報をオープンリストとして評価値リストへ追加 */
	ASTAR_EVALUATION_LIST stStartNode;
	stStartNode.bStartNodeFlg		= true;														// スタート地点フラグを有効
	stStartNode.bGoalNodeFlg		= false;													// ゴール地点フラグを無効
	stStartNode.iCost_G				= 0;														// Gコスト(累計のコスト)を0に設定
	stStartNode.iCost_H				= iCost_H_CalcHeuristicCost(vecStart, vecGoalPos);				// Hコスト(ゴールまでの予測コスト)を設定
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
		int		iMinF_Cost_F	= INT_MAX;	// Fコストの最小値
		bool	bFoundFlg		= false;	// Fコストが最小のノードを発見したかのフラグ
		int		iMinF_Cost_G	= 0;		// Fコストが最小のノードのGコスト

		for (auto& node : astEvaluationList)
		{
			/* オープンリストに登録されていて、F値が最小値であるか */
			if (node.bOpenListFlg && node.iCost_F < iMinF_Cost_F)
			{
				// 条件を満たす場合
				/* Fコストの最小値を更新 */
				iMinF_Cost_F	= node.iCost_F;
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
			int iCheckResult = iCheck_Moveble(vecNextPosition, vecGoalPos);
			if (iCheckResult != MOVE_NOT)
			{
				// 移動可能である場合
				/* 斜め方向への移動であるならコストを変更 */
				if (i % 2 == 1)
				{
					iMoveCost = ROUTE_SEARCH_MOVE_COST_DIAG;
				}
				/* 上方向への移動であるならコストを加算 + 座標を変更 */
				if (iCheckResult == MOVE_UP)
				{
					vecNextPosition.y	+= MAP_BLOCK_SIZE_Y;
					iMoveCost			+= ROUTE_SEARCH_MOVE_COST_YCHANGE;
				}
				/* 足場がなく、重力の影響を受ける場合は、足場に接触する高さまで座標を変更 */
				else if (iCheckResult == MOVE_DOWN && this->bEnableGravityFlg)
				{
					/* 下方向へ移動させる */
					// ※ 一マス分ずつ下げていき、足場があるか確認する(最大8マス分)
					for(int i = 0; i < 8; i++)
					{
						vecNextPosition.y -= MAP_BLOCK_SIZE_Y;
						int iCheckResult_Down = iCheck_Moveble(vecNextPosition, vecGoalPos);
						if (iCheckResult_Down == MOVE_NOT || iCheckResult_Down == MOVE_UP)
						{
							// 移動不可能であるか、上方向への移動であるなら
							vecNextPosition.y += MAP_BLOCK_SIZE_Y;
							break;
						}
					}
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
			stAddNode.iCost_G			= iMinF_Cost_G + iMoveCost;									// Gコスト(累計のコスト)を現在のGコスト + 移動コストに設定
			stAddNode.iCost_H			= iCost_H_CalcHeuristicCost(vecNextPosition, vecGoalPos);		// Hコスト(ゴールまでの予測コスト)を設定
			stAddNode.iCost_F			= stAddNode.iCost_G + stAddNode.iCost_H;					// Fコスト(Gコスト + Hコスト)を設定
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
int Npc_Base::iCheck_Moveble(VECTOR vecMovePos, VECTOR vecGoalPos)
{
	// 引数
	// vecMovePos	: 移動先の座標
	// 戻り値
	// int			: (MOVE_NOT:移動不可 / MOVE_OK:そのまま移動可能 / MOVE_UP:上方向へ移動すれば移動可能 / MOVE_GOALHIT:目標へ到達 / MOVE_DOWN:移動可能だが、足場がないので落下する)

	int iReturnValue = MOVE_OK;	// 戻り値

	/* 目標地点へ到達しているか */
	if (PUBLIC_PROCESS::bIsFloatDiffWithinThreshold(vecMovePos.x, vecGoalPos.x, MAP_BLOCK_SIZE_X / 2.f) &&
		PUBLIC_PROCESS::bIsFloatDiffWithinThreshold(vecMovePos.z, vecGoalPos.z, MAP_BLOCK_SIZE_Z / 2.f))
	{
		// 目標地点へ到達している場合
		/* 目標へ到達とする */
		return MOVE_GOALHIT;
	}

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
				/* Enemy陣営であるか */
				if (this->bCheckTeamTag("Enemy"))
				{
					// Enemy陣営である場合
					/* 移動可能とする */
					return MOVE_OK;
				}
				else
				{
					// Enemy陣営でない場合
					/* 移動不可とする */
					return MOVE_NOT;
				}
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

	/* 移動後座標に足場があるか確認 */
	if (iReturnValue == MOVE_OK)
	{
		// そのまま移動可能である場合
		/* 足場があるか確認 */
		// ※ 1ブロック分下にずらしたコリジョンを作成し、接触するかを確認する
		Struct_Collision::COLLISION_BOX stCheckBox_Floor = stCheckBox;
		stCheckBox_Floor.vecBoxCenter.y -= MAP_BLOCK_SIZE_Y;

		/* 接触確認 */
		bool bFloorFoundFlg = false;
		for (auto& Collision : CollisionList)
		{
			/* 接触しているか確認 */
			if (Collision->HitCheck(stCheckBox_Floor))
			{
				// 接触している場合
				bFloorFoundFlg = true;
				break;
			}
		}
		if (!bFloorFoundFlg)
		{
			// 足場がない場合
			/* 移動可能だが、落下することになるとする */
			iReturnValue = MOVE_DOWN;
		}
	}

	return iReturnValue;
}

// 移動ルートに沿った移動
void Npc_Base::Update_RouteMove()
{
	/* ルートが登録されていないのであれば何もしない */
	if (this->avecMovePath.empty()) { return; }

	/* 現在の移動目的座標を取得 */
	VECTOR vecTargetPos = this->avecMovePath.back();

	/* 移動処理 */
	// 移動方向と移動量を算出
	VECTOR vecMoveDirection = VSub(vecTargetPos, this->vecBasePosition);
	vecMoveDirection.y = 0.f;
	// 移動処理を実行
	if (bGround_PushBack_Movement(vecMoveDirection))
	{
		// 接触が発生した場合
		/* ジャンプ処理を実行 */
		Update_Jump();
	}
	
	/* 目的地到達確認処理 */
	// ※ Y座標は無視
	// 移動目的地までの距離の二乗を算出
	VECTOR vecTempTargetPos = vecTargetPos;
	vecTempTargetPos.y = this->vecBasePosition.y;

	float fDistSq = VSquareSize(VSub(vecTempTargetPos, this->vecBasePosition));
	// 目的地に到達しているか判定
	// ※ 移動速度の二条よりも近い場合は到達しているとみなす
	if (fDistSq < this->iSpeed * this->iSpeed)
	{
		// 到達しているのであればリストから削除
		this->avecMovePath.pop_back();
	}
}

// 移動ルートの描写
void Npc_Base::Draw_Route()
{
	/* ルート検索中であるなら処理を行わない */
	if (!bCheck_FutureReady(this->thred_RouteSearch)) { return; }

	/* 移動ルートに沿って線を描写する */
	if (this->avecMovePath.size() >= 2)
	{
		for (size_t i = 1; i < this->avecMovePath.size(); ++i)
		{
			DrawLine3D(
				this->avecMovePath[i - 1],
				this->avecMovePath[i],
				GetColor(0, 255, 0)
			);
		}
	}
}

// HPバーの描写
void Npc_Base::Draw_HpBar()
{
	/* HPバーを描写する */
	// ※ 現在の座標をスクリーン座標に変換して、その上に描写する
	VECTOR vecScreenPos = ConvWorldPosToScreenPos(this->vecBasePosition);

	/* HPバーの描写 */
	int iHpBarX = static_cast<int>(vecScreenPos.x) + HPBAR_POS_X;	// HPバーのX座標
	int iHpBarY = static_cast<int>(vecScreenPos.y) - HPBAR_POS_Y;	// HPバーのY座標
	// HPバーの背景を描写
	DrawBox(
		iHpBarX - HPBAR_BACK_WIDE,
		iHpBarY - HPBAR_BACK_WIDE,
		iHpBarX + HPBAR_WIDE + HPBAR_BACK_WIDE,
		iHpBarY + HPBAR_HEIGHT + HPBAR_BACK_WIDE,
		GetColor(0, 0, 0),
		true
	);
	// HPバー本体を描写
	int iCurrentHpBarWidth = static_cast<int>(static_cast<float>(this->iHealth) / static_cast<float>(this->iMaxHealth) * static_cast<float>(HPBAR_WIDE));
	DrawBox(
		iHpBarX,
		iHpBarY,
		iHpBarX + iCurrentHpBarWidth,
		iHpBarY + HPBAR_HEIGHT,
		GetColor(255, 0, 0),
		true
	);
}

// 現在ノードからゴールノードまでの推定コスト（ヒューリスティック値）を算出
int Npc_Base::iCost_H_CalcHeuristicCost(const VECTOR& vecCurrentPosition, const VECTOR& vecGoalPosition)
{
	// 引数
	// vecCurrentPosition	<- 現在のノードの座標
	// vecGoalPosition		<- ゴールノードの座標
	// 戻り値
	// int					<- 現在ノードからゴールノードまでの推定コスト

	/* オクタイル距離を用いて推定コストを計算 */
	int differenceX = static_cast<int>(std::abs(vecGoalPosition.x - vecCurrentPosition.x) / ROUTE_SEARCH_MOVE_DISTANCE);
	int differenceZ = static_cast<int>(std::abs(vecGoalPosition.z - vecCurrentPosition.z) / ROUTE_SEARCH_MOVE_DISTANCE);

	/* 斜め移動できる回数と直線移動が必要な回数を計算 */
	int diagonalMoveCount = std::min(differenceX, differenceZ);
	int straightMoveCount = std::abs(differenceX - differenceZ);

	// 斜め移動と直線移動のコストを合計して返す
	return ROUTE_SEARCH_MOVE_COST_DIAG * diagonalMoveCount + ROUTE_SEARCH_MOVE_COST_DEFAULT * straightMoveCount;
}
