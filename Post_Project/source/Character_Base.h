/* キャラクターのベースクラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Actor_Base.h"
// 共通定義
#include "AppFrame.h"
#include "ConstantDefine.h"

/* 前方宣言 */
class DataList_GameStatus;
class DataList_Sound;

// キャラクターベースクラス
class Character_Base : public Actor_Base
{
	public:
		Character_Base();				// コンストラクタ
		virtual ~Character_Base();		// デストラクタ

		/* 関数 */
		virtual void	InitialSetup()		override;	// 初期設定
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描写
		virtual void	Draw_Shadow()		override;	// 描画(シャドウマップ用)

		/* セッター */
		// パラメーター系
		void SetHealth(int iHealth)					{ this->iHealth			=	std::clamp(iHealth, 0, this->iMaxHealth); }	// 体力の設定
		void HelthChange(int iHelthChange)			{ this->iMaxHealth		+=	iHelthChange; }								// 引数の値分体力を変動
		void SetMaxHelth(int iMaxHelth)				{ this->iMaxHealth		= iMaxHelth; }									// 最大体力の設定
		void SetAttack(int iAttack)					{ this->iAttack			= iAttack; }									// 攻撃力の設定
		void SetSpeed(int iSpeed)					{ this->iSpeed			= iSpeed; }										// すばやさの設定
		void SetAutoHealDelay(int iAutoHealDelay)	{ this->iAutoHealDelay	= iAutoHealDelay; }								// 自動回復待機時間の設定
		void SetAutoHealAmount(int iAutoHealAmount)	{ this->iAutoHealAmount	= iAutoHealAmount; }							// 自動回復量の設定
		// 状態系
		void SetDeadFlg(bool bDeadFlg)				{ this->bDeadFlg		= bDeadFlg; }									// 死亡フラグの設定
		void SetInvicibleTime(int iInvicibleTime)	{ this->iInvincibleTime = iInvicibleTime; }								// 無敵時間の設定
		void SetJumpUseFlg(bool bJumpUseFlg)		{ this->bJumpUseFlg		= bJumpUseFlg; }								// ジャンプ使用可能フラグの設定
		void SetAttackInterval(int iAttackInterval) { this->iAttackInterval = iAttackInterval; }							// 攻撃後の待機時間の設定

		/* ゲッター */
		// パラメーター系
		int		iGetHealth()			{ return this->iHealth; }			// 体力の取得
		int		iGetMaxHealth()			{ return this->iMaxHealth; }		// 最大体力の取得
		int		iGetAttack()			{ return this->iAttack; }			// 攻撃力の取得
		int		iGetSpeed()				{ return this->iSpeed; }			// すばやさの取得
		int		iGetAutoHealDelay()		{ return this->iAutoHealDelay; }	// 自動回復待機時間の取得
		int		iGetAutoHealAmount()	{ return this->iAutoHealAmount; }	// 自動回復量の取得
		bool	bGetContactDamageFlg()	{ return this->bContactDamageFlg; }	// 接触によりダメージ発生するかのフラグの取得
		// 状態系
		bool	bGetDeadFlg()			{ return this->bDeadFlg; }			// 死亡フラグの取得
		int		GetInvincibleTime()		{ return this->iInvincibleTime; }	// 無敵時間の取得
		bool	bGetJumpUseFlg()		{ return this->bJumpUseFlg; }		// ジャンプ使用可能フラグの取得
		int		iGetAttackInterval()	{ return this->iAttackInterval; }	// 攻撃後の待機時間の取得

	protected:
		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_GameStatus>			pDataList_GameStatus;				// ゲーム状態管理
		std::shared_ptr<DataList_2DPartsAnimCreateTool>	pDataList_2DPartsAnimCreateTool;	// 2Dパーツアニメーションツール
		std::shared_ptr<DataList_Sound>					pDataList_Sound;					// サウンド管理
		// アニメーション関係
		int				iScreenHandle_Animation;	// アニメーション描写用画像データ
		std::string		AnimFileName;				// アニメーションファイル名
		std::string		NowMotionName;				// 現在のモーション名
		int				iMotionCount;				// モーションカウント
		bool			bMotionEndFlg;				// モーション終了フラグ
		bool			bMotionLoopFlg;				// モーションループフラグ
		bool			bDrawReversalFlg;			// 左右反転フラグ
		// パラメーター系(プレイヤー、NPC共通)
		int	iHealth;				// 体力
		int	iMaxHealth;				// 最大体力
		int iAttack;				// 攻撃力
		int iSpeed;					// すばやさ
		int iAutoHealDelay;			// 自動回復待機時間
		int iAutoHealDelay_Timer;	// 自動回復までの残り待機時間
		int iAutoHealAmount;		// 自動回復量
		// パラメーター系(NPC用)
		float	fSearchRange;		// 探索範囲
		float	fAttackRange;		// 攻撃範囲
		bool	bContactDamageFlg;	// 接触によりダメージ発生するかのフラグ
		bool	bAttackMeleeFlg;	// 近接攻撃を行うかのフラグ
		// 行動パターンフラグ(NPC用)
		bool	abEnemyActionPatternFlg[NPC_ENEMY_ACTION_PATTERN_MAX];			// エネミー行動パターンフラグ
		bool	abFriendActionPatternFlg[NPC_FRIEND_ACTION_PATTERN_MAX];		// 友好NPC行動パターンフラグ
		bool	abLongRangeAttackPatternFlg[LONG_RANGE_ATTACK_DIR_PATTERN_MAX];	// 遠距離攻撃パターンフラグ
		// 状態系
		bool bDeadFlg;			// 死亡フラグ
		int iInvincibleTime;	// 残り無敵時間(フレーム数)
		bool bJumpUseFlg;		// ジャンプ使用可能フラグ
		bool bTrackingFlg;		// 追跡中であるかのフラグ
		int iAttackInterval;	// 攻撃後の待機時間

		/* 関数 */
		void	Update_Collision();									// コリジョン更新
		void	Update_Animation();									// アニメーション更新
		void	Draw_Animation();									// アニメーション描写
		bool	bGround_PushBack_Gravity();							// 地形からの押し出し処理(重力処理用)
		bool	bGround_PushBack_Movement(VECTOR vecMoveDirection);	// 地形からの押し出し処理(移動処理用)
		void	Update_Jump();										// ジャンプ処理
		void	Draw_SearchRange();									// 探索範囲の描写
		void	Draw_AttackRange();									// 攻撃範囲の描写
		void	Update_Damage();									// ダメージ処理
};
