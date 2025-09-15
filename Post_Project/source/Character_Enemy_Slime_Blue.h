/* 青スライム(エネミー)クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Character_Base.h"

// 青スライム(エネミー)クラス
class Character_Enemy_Slime_Blue : public Character_Base
{
	public:
		Character_Enemy_Slime_Blue();			// コンストラクタ
		virtual ~Character_Enemy_Slime_Blue();	// デストラクタ

		/* 関数 */
		virtual void	InitialSetup()	override;	// 初期設定
		virtual void	Update()		override;	// 更新

	protected:
		/* 関数 */
		void	Update_Move();						// 移動処理
};
