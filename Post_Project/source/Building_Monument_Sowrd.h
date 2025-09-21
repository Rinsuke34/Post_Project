/* 建造物(モニュメント(剣))クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Building_Base.h"

// 建造物(モニュメント(剣))クラス
class Building_Monument_Sowrd : public Building_Base
{
	public:
		Building_Monument_Sowrd();				// コンストラクタ
		virtual ~Building_Monument_Sowrd() {};	// デストラクタ

	private:
		/* 変数 */
		// 状態系
		int	iAddMeleeAttack;		// 追加近接攻撃力
};
