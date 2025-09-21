/* アイテム"コイン"クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Item_Base.h"

// アイテム"コイン"クラス
class Item_Coin : public Item_Base
{
	public:
		Item_Coin();				// コンストラクタ
		virtual ~Item_Coin() {};	// デストラクタ

	protected:
		/* 関数 */
		void	Update_ItemGet() override;	// アイテム取得時の更新処理
};
