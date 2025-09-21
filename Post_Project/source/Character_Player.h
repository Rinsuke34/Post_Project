/* プレイヤークラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Character_Base.h"

// プレイヤークラス
class Character_Player : public Character_Base
{
	public:
		Character_Player();				// コンストラクタ
		virtual ~Character_Player() {};	// デストラクタ

		/* 関数 */
		virtual void	InitialSetup()	override;	// 初期設定
		virtual void	Update()		override;	// 更新
		virtual void	Draw()			override;	// 描画

	protected:
		/* 関数 */
		void	JsonLoad_PlayerStatus();	// プレイヤー情報の読み込み
		void	Update_ApplyGravity();		// 重力処理
		void	Update_ApplyMovement();		// 移動処理
		void	Draw_Grid();				// グリッド範囲の描写
		void	Update_Action();			// 行動処理

		/* 変数 */
		bool bMeleeFlg;	// 近接攻撃状態であるかのフラグ
		bool bMoveFlg;	// 移動を行ったかのフラグ
};
