/* キャラクター(NPC)のベースクラスの定義 */
// ※ NPCの行動パターンや攻撃処理を行う

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Npc_Base.h"
// 関連クラス
#include "DataList_GameStatus.h"
#include "DataList_Object.h"
#include "DataList_Sound.h"
#include "Bullet_Npc.h"
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
		/* 索敵範囲内に"Player"あるいは"Friend"チームのキャラクターが存在するか確認 */
		for (auto& Character : this->pDataList_Object->GetCharacterList())
		{
			/* プレイヤー陣営のキャラクターであるか */
			if (!Character->bCheckTeamTag("Player") && !Character->bCheckTeamTag("Friend"))
			{
				// プレイヤー陣営のキャラクターでない場合はスルー
				continue;
			}

			/* 索敵範囲内に存在するか */
			if (fDistanceToTargetSquare(Character->GetPosition()) <= this->fSearchRange * this->fSearchRange)
			{
				// 索敵範囲内に存在する場合は逃走処理を実行
				/* 移動方向を算出 */
				VECTOR vecMoveDirection = VSub(this->vecBasePosition, Character->GetPosition());
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
					this->NowMotionName = "Move";
					this->iMotionCount = 0;
					this->bMotionLoopFlg = true;
				}

				/* 現在所持しているルート情報を破棄 */
				this->avecMovePath.clear();

				/* 追跡フラグを有効化 */
				this->bTrackingFlg = true;
				return;
			}
		}
	}

	/* 射程範囲内のプレイヤーに攻撃が有効であるか */
	// ※ 攻撃後のインターバルが0以下であることも条件とする
	if (this->abEnemyActionPatternFlg[NPC_ENEMY_ACTION_PATTARN_PLAYER_ATTACK] && this->iAttackInterval <= 1)
	{
		// 有効である場合
		/* 射程範囲内にプレイヤー陣営のキャラクターが存在するか確認 */
		for (auto& chara : this->pDataList_Object->GetCharacterList())
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
					/* 対象のキャラクター情報を取得 */
					Character_Base* pChara = dynamic_cast<Character_Base*>(chara.get());

					/* 攻撃の種類が近接攻撃であるか確認 */
					if (this->bAttackMeleeFlg)
					{
						// 近接攻撃である場合
						/* キャラクターのHPを減少させる */
						if (pChara)
						{
							int iHp = pChara->iGetHealth();
							iHp -= this->iAttack;
							pChara->SetHealth(iHp);
						}

						/* 攻撃音を再生 */
						this->pDataList_Sound->SE_Play("Npc_Attack_Melee", this->vecBasePosition);

						/* 攻撃後のインターバルを設定 */
						this->iAttackInterval = DEFAULT_ATTACK_INTERVAL_MELE - this->iSpeed;
					}
					else
					{
						// 遠距離攻撃である場合
						/* バレットを作成し、パターンに応じた方向へ発射する */
						Update_MakeBullet(pChara->GetPosition(), "Enemy");

						/* 攻撃音を再生 */
						this->pDataList_Sound->SE_Play("Npc_Attack_Long", this->vecBasePosition);

						/* 攻撃後のインターバルを設定 */
						this->iAttackInterval = DEFAULT_ATTACK_INTERVAL_LONG - this->iSpeed;
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
		/* 索敵範囲内に"Player"あるいは"Friend"チームのキャラクターが存在するか確認 */
		for (auto& Character : this->pDataList_Object->GetCharacterList())
		{
			/* プレイヤー陣営のキャラクターであるか */
			if (!Character->bCheckTeamTag("Player") && !Character->bCheckTeamTag("Friend"))
			{
				// プレイヤー陣営のキャラクターでない場合はスルー
				continue;
			}

			/* 索敵範囲内に存在するか */
			if (fDistanceToTargetSquare(Character->GetPosition()) <= this->fSearchRange * this->fSearchRange)
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
					this->NowMotionName = "Move";
					this->iMotionCount = 0;
					this->bMotionLoopFlg = true;
				}

				/* 現在所持しているルート情報を破棄 */
				this->avecMovePath.clear();

				/* 追跡フラグを有効化 */
				this->bTrackingFlg = true;
				return;
			}
		}
	}

	/* 神木(防衛対象)への侵攻が有効であるか */
	// ※ 攻撃後のインターバルが0以下であることも条件とする
	if (this->abEnemyActionPatternFlg[NPC_ENEMY_ACTION_PATTERN_INVASION_CORETREE] && this->iAttackInterval <= 0)
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

				/* 攻撃後のインターバルを設定 */
				if (this->bAttackMeleeFlg == true)
				{
					this->iAttackInterval = DEFAULT_ATTACK_INTERVAL_MELE - this->iSpeed;
				}
				else
				{
					this->iAttackInterval = DEFAULT_ATTACK_INTERVAL_LONG - this->iSpeed;
				}
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
 			thred_RouteSearch = std::async(std::launch::async, [this]() { this->Route_Search(this->pDataList_GameStatus->GetCoreTreePosition()); });
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
	/* 味方NPCとしての行動パターンの処理を記述する */
	// ※ 行動フラグの優先度が高いものを優先して実行する。
	// 優先度　高
	// ↓索敵範囲内のエネミーから逃走
	// ↓射程範囲内のエネミーに攻撃
	// ↓索敵範囲内のエネミーを追跡
	// ↓プレイヤーを追跡
	// 優先度 低

	/* 敵からの逃走が有効であるか */
	if (this->abFriendActionPatternFlg[NPC_FRIEND_ACTION_PATTERN_ENEMY_ESCAPE])
	{
		// 有効である場合
		/* 索敵範囲内に"Enemy"チームのキャラクターが存在するか確認 */
		for (auto& Character : this->pDataList_Object->GetCharacterList())
		{
			/* エネミー陣営のキャラクターであるか */
			if (!Character->bCheckTeamTag("Enemy"))
			{
				// エネミー陣営のキャラクターでない場合はスルー
				continue;
			}

			/* 索敵範囲内に存在するか */
			if (fDistanceToTargetSquare(Character->GetPosition()) <= this->fSearchRange * this->fSearchRange)
			{
				// 索敵範囲内に存在する場合は逃走処理を実行
				/* 移動方向を算出 */
				VECTOR vecMoveDirection = VSub(this->vecBasePosition, Character->GetPosition());
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
					this->NowMotionName = "Move";
					this->iMotionCount = 0;
					this->bMotionLoopFlg = true;
				}

				/* 現在所持しているルート情報を破棄 */
				this->avecMovePath.clear();

				/* 追跡フラグを有効化 */
				this->bTrackingFlg = true;
				return;
			}
		}
	}

	/* 敵への攻撃が有効であるか */
	// ※ 攻撃後のインターバルが0以下であることも条件とする
	if (this->abFriendActionPatternFlg[NPC_FRIEND_ACTION_PATTERN_ENEMY_ATTACK] && this->iAttackInterval <= 0)
	{
		// 有効である場合
		/* 索敵範囲内に"Enemy"チームのキャラクターが存在するか確認 */
		for (auto& Character : this->pDataList_Object->GetCharacterList())
		{
			/* エネミー陣営のキャラクターであるか */
			if (!Character->bCheckTeamTag("Enemy"))
			{
				// エネミー陣営のキャラクターでない場合はスルー
				continue;
			}

			// 射程範囲内に存在するか
			if (fDistanceToTargetSquare(Character->GetPosition()) <= this->fAttackRange * this->fAttackRange)
			{
				// 射程範囲内に存在する場合
				/* モーションが攻撃かつ、完了フラグが有効なら攻撃処理 */
				if (this->NowMotionName == "Attack" && this->bMotionEndFlg)
				{
					/* 対象のキャラクター情報を取得 */
					Character_Base* pChara = dynamic_cast<Character_Base*>(Character.get());

					/* 攻撃の種類が近接攻撃であるか確認 */
					if (this->bAttackMeleeFlg)
					{
						// 近接攻撃である場合
						/* キャラクターのHPを減少させる */
						if (pChara)
						{
							int iHp = pChara->iGetHealth();
							iHp -= this->iAttack;
							pChara->SetHealth(iHp);
						}

						/* 攻撃音を再生 */
						this->pDataList_Sound->SE_Play("Npc_Attack_Melee", this->vecBasePosition);

						/* 攻撃後のインターバルを設定 */
						this->iAttackInterval = DEFAULT_ATTACK_INTERVAL_MELE - this->iSpeed;
					}
					else
					{
						// 遠距離攻撃である場合
						/* バレットを作成し、パターンに応じた方向へ発射する */
						Update_MakeBullet(pChara->GetPosition(), "Friend");

						/* 攻撃音を再生 */
						this->pDataList_Sound->SE_Play("Npc_Attack_Long", this->vecBasePosition);

						/* 攻撃後のインターバルを設定 */
						this->iAttackInterval = DEFAULT_ATTACK_INTERVAL_LONG - this->iSpeed;
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

	/* 敵への追跡が有効であるか */
	if (this->abFriendActionPatternFlg[NPC_FRIEND_ACTION_PATTERN_ENEMY_TRACKING])
	{
		// 有効である場合
		/* 索敵範囲内に"Enemy"チームのキャラクターが存在するか確認 */
		for (auto& Character : this->pDataList_Object->GetCharacterList())
		{
			/* エネミー陣営のキャラクターであるか */
			if (!Character->bCheckTeamTag("Enemy"))
			{
				// エネミー陣営のキャラクターでない場合はスルー
				continue;
			}

			/* 索敵範囲内に存在するか */
			if (fDistanceToTargetSquare(Character->GetPosition()) <= this->fSearchRange * this->fSearchRange)
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
					this->NowMotionName = "Move";
					this->iMotionCount = 0;
					this->bMotionLoopFlg = true;
				}

				/* 現在所持しているルート情報を破棄 */
				this->avecMovePath.clear();

				/* 追跡フラグを有効化 */
				this->bTrackingFlg = true;
				return;
			}
		}
	}

	/* プレイヤーへの追跡が有効であるか */
	if (this->abFriendActionPatternFlg[NPC_FRIEND_ACTION_PATTERN_PLAYER_TRACKING])
	{
		// 有効である場合
		/* 射程範囲の半分の距離内にプレイヤーが存在するか */
		if (fDistanceToTargetSquare(this->pDataList_GameStatus->GetPlayerPosition_WoldMap()) <= (this->fAttackRange / 2.f) * (this->fAttackRange / 2.f))
		{
			// 射程範囲内にプレイヤーが存在する場合
			/* 現在所持しているルート情報を破棄 */
			this->avecMovePath.clear();
		}
		else
		{
			// 射程範囲内にプレイヤーが存在しない場合
			/* 移動ルートが確定していない、あるいはプレイヤーがサーチ開始地点から1ブロック以上移動したか */
			if( this->vecTargetPos.x - MAP_BLOCK_SIZE_X > this->pDataList_GameStatus->GetPlayerPosition_WoldMap().x ||
			    this->vecTargetPos.x + MAP_BLOCK_SIZE_X < this->pDataList_GameStatus->GetPlayerPosition_WoldMap().x ||
			    this->vecTargetPos.z - MAP_BLOCK_SIZE_Z > this->pDataList_GameStatus->GetPlayerPosition_WoldMap().z ||
			    this->vecTargetPos.z + MAP_BLOCK_SIZE_Z < this->pDataList_GameStatus->GetPlayerPosition_WoldMap().z ||
				this->avecMovePath.empty())
			{
				// 移動ルートが確定していない、あるいはプレイヤーがサーチ開始地点から1ブロック以上移動した場合
				/* 現在所持しているルート情報を破棄 */
				this->avecMovePath.clear();

				/* ルート設定を別スレッドで実行 */
				thred_RouteSearch = std::async(std::launch::async, [this]() { this->Route_Search(this->pDataList_GameStatus->GetPlayerPosition_WoldMap()); });

				/* 現在のターゲット座標をプレイヤーポジションに設定 */
				this->vecTargetPos = this->pDataList_GameStatus->GetPlayerPosition_WoldMap();
				return;
			}

			/* 移動ルートに沿った移動処理 */
			Update_RouteMove();

			/* モーションが移動以外であるなら移動モーションに設定 */
			if (this->NowMotionName != "Move")
			{
				this->NowMotionName = "Move";
				this->iMotionCount = 0;
				this->bMotionLoopFlg = true;
			}
		}
	}
}

// 弾の生成
void Npc_Base::Update_MakeBullet(VECTOR vecTarget, std::string TeamTag)
{
	// 引数
	// vecTarget	: 弾を発射する対象の座標
	// TeamTag		: 発射する弾のチームタグ

	std::vector<VECTOR> vecAddBulletVector;	// 追加で発射する弾の移動ベクトルリスト

	/* 遠距離攻撃のパターンに応じて球を生成する */
	if(this->abLongRangeAttackPatternFlg[LONG_RANGE_ATTACK_DIR_PATTERN_AIM])
	{
		// 対象へ向けて狙い撃ちの場合
		// ※めり込み対策込みの座標から狙う
		vecAddBulletVector.push_back(VNorm(VSub(VAdd(vecTarget, VGet(0.f, MAP_BLOCK_SIZE_Y / 2.f, 0.f)), VAdd(this->vecBasePosition, VGet(0.f, MAP_BLOCK_SIZE_Y / 2.f, 0.f)))));
	}
	if (this->abLongRangeAttackPatternFlg[LONG_RANGE_ATTACK_DIR_PATTERN_DIAGONAL_WAY])
	{
		// 斜め4方向に発射する場合
		vecAddBulletVector.push_back(VNorm(VGet(+1.f, 0.f, +1.f)));
		vecAddBulletVector.push_back(VNorm(VGet(+1.f, 0.f, -1.f)));
		vecAddBulletVector.push_back(VNorm(VGet(-1.f, 0.f, +1.f)));
		vecAddBulletVector.push_back(VNorm(VGet(-1.f, 0.f, -1.f)));
	}
	if (this->abLongRangeAttackPatternFlg[LONG_RANGE_ATTACK_DIR_PATTERN_CARDINAL_WAY])
	{
		// 十字4方向に発射する場合
		vecAddBulletVector.push_back(VNorm(VGet(+1.f, 0.f, 0.f)));
		vecAddBulletVector.push_back(VNorm(VGet(-1.f, 0.f, 0.f)));
		vecAddBulletVector.push_back(VNorm(VGet(0.f, 0.f, +1.f)));
		vecAddBulletVector.push_back(VNorm(VGet(0.f, 0.f, -1.f)));
	}

	/* 弾の生成処理 */
	// ※ バレットを作成し、対象の方向に発射する
	for (auto& BulletVector : vecAddBulletVector)
	{
		/* バレットを生成 */
		std::shared_ptr<Bullet_Npc> pBullet = std::make_shared<Bullet_Npc>();
		// 発射方向を設定
		// ※ 速度はNPCの移動速度の二倍に設定
		pBullet->SetMoveVector(VScale(BulletVector, this->iSpeed * 2.f));
		// 初期地点を設定
		// ※ めり込ませないため、少し上にずらして生成
		pBullet->SetPosition(VAdd(this->vecBasePosition, VGet(0.f, MAP_BLOCK_SIZE_Y / 2.f, 0.f)));
		// 攻撃力を設定
		pBullet->SetAttack(this->iAttack);
		// チームタグを設定
		pBullet->SetTeamTag(TeamTag);
		// 初期化処理
		pBullet->InitialSetup();
		// バレットを登録
		this->pDataList_Object->AddObject_Bullet(pBullet);
	}
}