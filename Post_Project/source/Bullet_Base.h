/* バレットのベースクラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Actor_Base.h"

/* 前方宣言 */
class DataList_GameStatus;

// バレットベースクラス
class Bullet_Base : public Actor_Base
{
	public:
		Bullet_Base();				// コンストラクタ
		virtual ~Bullet_Base() {};	// デストラクタ

		/* 定数 */
		static const int DESPAWN_TIME			= 300;	// 弾が消滅するまでの時間(フレーム数)
		static const int COLLISION_HALF_SIZE	= 16;	// コリジョンの半径

		/* 関数 */
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描画

		/* セッター */
		void SetAttack(int iAttack)								{ this->iAttack		= iAttack; }	// 攻撃力の設定
		void SetMoveVector(VECTOR vecMove)						{ this->vecMove		= vecMove; }	// 移動量の設定
		void SetImageHandle(std::shared_ptr<int> iGrhandle)		{ this->piGrHandle	= iGrhandle; }	// 画像のハンドルの設定

		/* ゲッター */
		int								iGetAttack()		{ return this->iAttack; }				// 攻撃力の取得
		VECTOR							vecGetMoveVector()	{ return this->vecMove; }				// 移動量の取得

	protected:
		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_GameStatus>	pDataList_GameStatus;		// ゲーム状態管理
		// パラメーター系
		int						iAttack;		// 攻撃力
		// 描画系
		std::shared_ptr<int>	piGrHandle;		// 使用する画像のハンドル
		// 状態系
		int						iDespawnTime;	// 弾が消滅するまでの時間 
		VECTOR					vecMove;		// 移動量
};
