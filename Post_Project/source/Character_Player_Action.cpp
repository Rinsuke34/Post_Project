/* プレイヤークラスの定義 */
// ※ 行動や攻撃処理を行う

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Character_Player.h"
// 関連クラス
#include "DataList_GameStatus.h"
#include "DataList_Object.h"
#include "DataList_Sound.h"
#include "Ground_Base.h"
#include "Ground_Model.h"
#include "Bullet_Player.h"
#include "Scene_GameMain_Building.h"

// 行動処理
void Character_Player::Update_Action()
{
	/* 建築モード起動処理 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_Q] == TRUE)
	{
		/* 建築モードが使用可能か確認 */
		if (this->pDataList_GameStatus->GetBuildModeChangePossibleFlg())
		{
			// 建築モードに変更可能な場合
			/* シーン"建築モード"を作成 */
			gpSceneServer->AddSceneReservation(std::make_shared<Scene_GameMain_Building>());

			/* SEを再生する */
			this->pDataList_Sound->SE_Play("Select_OK");
			return;
		}
		else
		{
			// 建築モードに変更不可能な場合
			/* SEを再生する */
			this->pDataList_Sound->SE_Play("Select_Error");
		}
	}

	/* 武器切り替え処理 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_E] == TRUE)
	{
		/* 武器を切り替える */
		this->bMeleeFlg = !this->bMeleeFlg;
		this->pDataList_GameStatus->SetPlayerMeleeFlg(this->bMeleeFlg);

		/* 武器切り替えに応じてモーションを変更 */
		if (this->bMeleeFlg)
		{
			// 近接攻撃状態に変更
			this->NowMotionName		= "Delay_Sowrd";
			this->iMotionCount		= 0;
			this->bMotionLoopFlg	= true;
		}
		else
		{
			// 遠距離攻撃状態に変更
			this->NowMotionName		= "Delay_Rod";
			this->iMotionCount		= 0;
			this->bMotionLoopFlg	= true;
		}
	}

	/* 移動・重力処理 */
	Update_ApplyGravity();
	Update_ApplyMovement();

	/* 射程範囲内の敵に対する攻撃処理 */
	// ※ 攻撃後のインターバルが1以下である場合のみ実施
	if (this->iAttackInterval <= 1)
	{
		// 射程距離設定(近接攻撃状態では攻撃範囲、遠距離攻撃状態では索敵範囲を射程とする)
		float fAttackRangeA = this->bMeleeFlg ? this->fAttackRange : this->fSearchRange;
		for (auto& chara : this->pDataList_Object->GetCharacterList())
		{
			// 敵陣営のキャラクターであるか
			if (!chara->bCheckTeamTag("Enemy"))
			{
				// 敵陣営のキャラクターでない場合はスルー
				continue;
			}

			// 射程範囲内に存在するか
			if (fDistanceToTargetSquare(chara->GetPosition()) <= fAttackRangeA * fAttackRangeA)
			{
				// 射程範囲内に存在する場合
				/* モーションが攻撃かつ、完了フラグが有効なら攻撃処理 */
				if (this->NowMotionName == "Attack_Sowrd" && this->bMotionEndFlg && this->bMeleeFlg)
				{
					/* 近接攻撃処理 */
					Character_Base* pChara = dynamic_cast<Character_Base*>(chara.get());
					if (pChara)
					{
						int iHp = pChara->iGetHealth();
						iHp -= this->iAttack + this->pDataList_GameStatus->GetBuilldingBuff_Sword();;
						pChara->SetHealth(iHp);

						/* 攻撃音を再生 */
						this->pDataList_Sound->SE_Play("Player_Attack_Sowrd");
					}

					/* 攻撃後のインターバルを設定 */
					this->iAttackInterval = DEFAULT_ATTACK_INTERVAL_MELE - this->iSpeed;
				}
				else if (this->NowMotionName == "Attack_Rod" && this->bMotionEndFlg && !this->bMeleeFlg)
				{
					/* 遠距離攻撃処理 */
					// ※ バレットを作成し、敵の方向に発射する
					std::shared_ptr<Bullet_Player> pBullet = std::make_shared<Bullet_Player>();
					// 発射方向を設定
					// ※ 速度はプレイヤーの移動速度の2倍に設定
					VECTOR vecDirection = VNorm(VSub(chara->GetPosition(), this->vecBasePosition));
					vecDirection = VScale(vecDirection, this->iSpeed * 2.f);
					pBullet->SetMoveVector(vecDirection);
					// 初期地点を設定
					// ※ めり込ませないため、少し上にずらして生成
					pBullet->SetPosition(VAdd(this->vecBasePosition, VGet(0.f, MAP_BLOCK_SIZE_Y / 2.f, 0.f)));
					// 攻撃力を設定
					pBullet->SetAttack(this->iAttack + this->pDataList_GameStatus->GetBuilldingBuff_Rod());
					// バレットを登録
					this->pDataList_Object->AddObject_Bullet(pBullet);

					/* 攻撃音を再生 */
					this->pDataList_Sound->SE_Play("Player_Attack_Rod");

					/* 攻撃後のインターバルを設定 */
					this->iAttackInterval = DEFAULT_ATTACK_INTERVAL_LONG - this->iSpeed;
				}

				/* モーションが攻撃以外であるなら攻撃モーションに設定 */
				if (this->bMeleeFlg)
				{
					if (this->NowMotionName != "Attack_Sowrd")
					{
						this->NowMotionName		= "Attack_Sowrd";
						this->iMotionCount		= 0;
						this->bMotionLoopFlg	= true;
					}
				}
				else
				{
					if (this->NowMotionName != "Attack_Rod")
					{
						this->NowMotionName		= "Attack_Rod";
						this->iMotionCount		= 0;
						this->bMotionLoopFlg	= true;
					}
				}

				return;
			}
		}
	}

	/* 移動モーションの設定 */
	// 移動フラグによってモーションを設定
	if (this->bMoveFlg)
	{
		// 移動を行った場合
		/* 移動モーションに設定する */
		if (this->bMeleeFlg == true)
		{
			// 近接攻撃状態である場合
			/* モーションが移動(剣)以外であるなら移動(剣)に設定 */
			if (this->NowMotionName != "Move_Sowrd")
			{
				this->NowMotionName		= "Move_Sowrd";
				this->iMotionCount		= 0;
				this->bMotionLoopFlg	= true;
			}
		}
		else
		{
			// 遠距離攻撃状態である場合
			/* モーションが移動(杖)以外であるなら移動(杖)に設定 */
			if (this->NowMotionName != "Move_Rod")
			{
				this->NowMotionName		= "Move_Rod";
				this->iMotionCount		= 0;
				this->bMotionLoopFlg	= true;
			}
		}
	}
	else
	{
		// 移動を行っていない場合
		/* 待機モーションに設定する */
		if (this->bMeleeFlg == true)
		{
			// 近接攻撃状態である場合
			/* モーションが待機(剣)以外であるなら待機(剣)に設定 */
			if (this->NowMotionName != "Delay_Sowrd")
			{
				this->NowMotionName		= "Delay_Sowrd";
				this->iMotionCount		= 0;
				this->bMotionLoopFlg	= true;
			}
		}
		else
		{
			// 遠距離攻撃状態である場合
			/* モーションが待機(杖)以外であるなら待機(杖)に設定 */
			if (this->NowMotionName != "Delay_Rod")
			{
				this->NowMotionName		= "Delay_Rod";
				this->iMotionCount		= 0;
				this->bMotionLoopFlg	= true;
			}
		}
	}
}
