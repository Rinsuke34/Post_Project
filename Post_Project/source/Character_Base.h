/* キャラクターのベースクラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Actor_Base.h"
// 共通定義
#include "AppFrame.h"

// キャラクターベースクラス
class Character_Base : public Actor_Base
{
	public:
		Character_Base();					// コンストラクタ
		virtual ~Character_Base() {};		// デストラクタ

		/* 関数 */
		virtual void	Update()			override;	// 更新
		virtual void	Draw_Shadow()		override;	// 描画(シャドウマップ用)
		virtual void	Draw_Collision()	override;	// 描画(当たり判定)

		/* セッター */
		// ステータス系
		void SetHealth(int iHealth)					{ this->iHealth			=	std::clamp(iHealth, 0, this->iMaxHealth); }	// 体力の設定
		void HelthChange(int iHelthChange)			{ this->iMaxHealth		+=	iHelthChange; }								// 引数の値分体力を変動
		void SetMaxHelth(int iMaxHelth)				{ this->iMaxHealth		= iMaxHelth; }									// 最大体力の設定
		void SetSpeed(int iSpeed)					{ this->iSpeed			= iSpeed; }										// 速度の設定
		// 状態系
		void SetDeadFlg(bool bDeadFlg)				{ this->bDeadFlg		= bDeadFlg; }									// 死亡フラグの設定
		void SetInvicibleTime(int iInvicibleTime)	{ this->iInvincibleTime = iInvicibleTime; }								// 無敵時間の設定

		/* ゲッター */
		// ステータス系
		int		iGetHealth()		{ return this->iHealth; }			// 体力の取得
		int		iGetMaxHealth()		{ return this->iMaxHealth; }		// 最大体力の取得
		int		iGetSpeed()			{ return this->iSpeed; }			// 速度の取得
		// 状態系
		bool	bGetDeadFlg()		{ return this->bDeadFlg; }			// 死亡フラグの取得
		int		GetInvincibleTime() { return this->iInvincibleTime; }	// 無敵時間の取得

	protected:
		/* 変数 */
		// ステータス系
		int	iHealth;			// 体力
		int	iMaxHealth;			// 最大体力
		int iSpeed;				// 速度
		// 状態系
		bool bDeadFlg;			// 死亡フラグ
		int iInvincibleTime;	// 残り無敵時間(フレーム数)
		// コリジョン
		Struct_Collision::COLLISION_BOX	stBox;

		/* 関数 */
		void Update_Collision();	// コリジョン更新
};
