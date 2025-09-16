/* NPC(エネミー)クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Npc_Base.h"

// NPC(エネミー)のベースクラスの宣言
class Npc_Enemy : public Npc_Base
{
	public:
		Npc_Enemy();			// コンストラクタ
		virtual ~Npc_Enemy();	// デストラクタ

		/* 関数 */
		virtual void	InitialSetup()	override;	// 初期設定
		virtual void	Update()		override;	// 更新

	private:
		/* 変数 */


		/* 関数 */
		void	Update_Move();						// 移動処理
};
