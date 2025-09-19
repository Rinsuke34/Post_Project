/* キャラクター(NPC)のベースクラスの定義 */
// ※ NPCの行動パターンや攻撃処理を行う

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Npc_Base.h"
// 関連クラス
#include "DataList_GameStatus.h"
#include "DataList_Object.h"
// 共通定義
#include "FunctionDefine.h"

// 行動パターン管理
void Npc_Base::Update_Action()
{
	/* 行動パターンに基づいた行動を行う */

	/* 追跡フラグをリセット */
	this->bTrackingFlg = false;

	/* ルート検索中であるなら待機状態にする */
	if (!bCheck_FutureReady(this->thred_RouteSearch))
	{
		this->NowMotionName		= "Delay";
		this->bMotionLoopFlg	= true;
		return;
	}

	/* エネミーであるか */
	// ※ チームタグに"Enemy"が含まれている場合はエネミーとみなす
	if (Character_Base::bCheckTeamTag("Enemy"))
	{
		// エネミーである場合
		Update_Action_Enemy();
	}
	/* 味方NPCであるか */
	else if (Character_Base::bCheckTeamTag("Friend"))
	{
		Update_Action_Friend();
	}
}

// 行動パターン管理(エネミー用)
void Npc_Base::Update_Action_Enemy()
{
	/* エネミーとしての行動パターンの処理を記述する */
	// ※ 行動フラグの優先度が高いものを優先して実行する。
	// 優先度　高
	// ↓索敵範囲内のプレイヤーから逃走
	// ↓射程範囲内のプレイヤーに攻撃
	// ↓索敵範囲内プレイヤーを追跡
	// ↓神木(防衛対象)への侵攻
	// 優先度 低

	/* プレイヤーからの逃走が有効であるか */
	if (this->abEnemyActionPatternFlg[NPC_ENEMY_ACTION_PATTERN_PLAYER_ESCAPE])
	{
		// 有効である場合
		/* 索敵範囲内にプレイヤーが存在するか確認 */
		if (fDistanceToTargetSquare(this->pDataList_GameStatus->GetPlayerPosition_WoldMap()) <= this->fSearchRange * this->fSearchRange)
		{
			// 索敵範囲内にプレイヤーが存在する場合
			/* プレイヤーから距離を取る */
			/* 移動方向を算出 */
			VECTOR vecMoveDirection = VSub(this->vecBasePosition, this->pDataList_GameStatus->GetPlayerPosition_WoldMap());
			vecMoveDirection.y = 0.f;

			/* 移動処理を実行 */
			if (bGround_PushBack_Movement(vecMoveDirection))
			{
				// 接触が発生した場合
				/* ジャンプ処理を実行 */
				Update_Jump();
			}

			/* モーションが移動以外であるなら移動モーションに設定 */
			if (this->NowMotionName != "Move")
			{
				this->NowMotionName		= "Move";
				this->iMotionCount		= 0;
				this->bMotionLoopFlg	= true;
			}

			/* 現在所持しているルート情報を破棄 */
			this->avecMovePath.clear();

			/* 追跡フラグを有効化 */
			this->bTrackingFlg = true;

			return;
		}
	}

	/* 射程範囲内のプレイヤーに攻撃が有効であるか */
	if (this->abEnemyActionPatternFlg[NPC_ENEMY_ACTION_PATTARN_PLAYER_ATTACK])
	{
		// 有効である場合
		/* 射程範囲内にプレイヤー陣営のキャラクターが存在するか確認 */
		for (auto& chara : this->pDataList_Object->GetActorList())
		{
			// プレイヤー陣営のキャラクターであるか
			if (!chara->bCheckTeamTag("Player") && !chara->bCheckTeamTag("Friend"))
			{
				// プレイヤー陣営のキャラクターでない場合はスルー
				continue;
			}

			// 射程範囲内に存在するか
			if (fDistanceToTargetSquare(chara->GetPosition()) <= this->fAttackRange * this->fAttackRange)
			{
				// 射程範囲内に存在する場合
				/* モーションが攻撃かつ、完了フラグが有効なら攻撃処理 */
				if (this->NowMotionName == "Attack" && this->bMotionEndFlg)
				{
					/* キャラクターのHPを減少させる */
					Character_Base* pChara = dynamic_cast<Character_Base*>(chara.get());
					if (pChara)
					{
						int iHp	= pChara->iGetHealth();
						iHp		-= this->iAttack;
						pChara->SetHealth(iHp);
					}
				}

				/* モーションが攻撃以外であるなら攻撃モーションに設定 */
				if (this->NowMotionName != "Attack")
				{
					this->NowMotionName = "Attack";
					this->iMotionCount = 0;
					this->bMotionLoopFlg = true;
				}

				/* 現在所持しているルート情報を破棄 */
				this->avecMovePath.clear();
				return;
			}
		}
	}

	/* 索敵範囲内のプレイヤーを追跡が有効であるか */
	if (this->abEnemyActionPatternFlg[NPC_ENEMY_ACTION_PATTERN_PLAYER_TRACKING])
	{
		// 有効である場合
		/* 索敵範囲内にプレイヤーが存在するか確認 */
		if (fDistanceToTargetSquare(this->pDataList_GameStatus->GetPlayerPosition_WoldMap()) <= this->fSearchRange * this->fSearchRange)
		{
			// 索敵範囲内にプレイヤーが存在する場合
			/* プレイヤーに向かって移動する */
			/* 移動方向を算出 */
			VECTOR vecMoveDirection = VSub(this->pDataList_GameStatus->GetPlayerPosition_WoldMap(), this->vecBasePosition);
			vecMoveDirection.y = 0.f;

			/* 移動処理を実行 */
			if (bGround_PushBack_Movement(vecMoveDirection))
			{
				// 接触が発生した場合
				/* ジャンプ処理を実行 */
				Update_Jump();
			}

			/* モーションが移動以外であるなら移動モーションに設定 */
			if (this->NowMotionName != "Move")
			{
				this->NowMotionName		= "Move";
				this->iMotionCount		= 0;
				this->bMotionLoopFlg	= true;
			}

			/* 現在所持しているルート情報を破棄 */
			this->avecMovePath.clear();

			/* 追跡フラグを有効化 */
			this->bTrackingFlg = true;
			return;
		}
	}

	/* 神木(防衛対象)への侵攻が有効であるか */
	if (this->abEnemyActionPatternFlg[NPC_ENEMY_ACTION_PATTERN_INVASION_CORETREE])
	{
		// 有効である場合
		/* 射程範囲内に神木(防衛対象)が存在するか確認 */
		// ※ 神木へのめり込みを防止するため、1ブロック分の距離を射程範囲に加算して判定
 		if (fDistanceToTargetSquare(this->pDataList_GameStatus->GetCoreTreePosition()) <= (this->fAttackRange + MAP_BLOCK_SIZE_X) * (this->fAttackRange + MAP_BLOCK_SIZE_X))
		{
			// 射程範囲内に神木(防衛対象)が存在する場合
			/* 神木(防衛対象)に攻撃処理を行う */

			/* モーションが攻撃かつ、完了フラグが有効なら神木のHPを減少 */
			if (this->NowMotionName == "Attack" && this->bMotionEndFlg)
			{
				/* 神木のHPを減少させる */
				int iCoreTreeHp = this->pDataList_GameStatus->GetHp_CoreTree();
				iCoreTreeHp -= this->iAttack;
				this->pDataList_GameStatus->SetHp_CoreTree(iCoreTreeHp);
			}

			/* モーションが攻撃以外であるなら攻撃モーションに設定 */
			if (this->NowMotionName != "Attack")
			{
				this->NowMotionName		= "Attack";
				this->iMotionCount		= 0;
				this->bMotionLoopFlg	= true;
			}
			return;
		}

		/* 移動ルートが確定しているか確認 */
		if (this->avecMovePath.empty())
		{
			// 移動ルートが確定していない場合
			/* ルート設定を別スレッドで実行 */
 			thred_RouteSearch = std::async(std::launch::async, [this]() { this->Route_Search(); });

			return;
		}

		/* 移動ルートに沿った移動処理 */
		Update_RouteMove();

		/* モーションが移動以外であるなら移動モーションに設定 */
		if (this->NowMotionName != "Move")
		{
			this->NowMotionName		= "Move";
			this->iMotionCount		= 0;
			this->bMotionLoopFlg	= true;
		}
	}
}

// 行動パターン管理(味方NPC用)
void Npc_Base::Update_Action_Friend()
{

}
