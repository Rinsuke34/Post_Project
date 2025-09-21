/* バレット(プレイヤー)クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Bullet_Base.h"

// バレット(プレイヤー)クラス
class Bullet_Player : public Bullet_Base
{
	public:
		Bullet_Player();				// コンストラクタ
		virtual ~Bullet_Player() {};	// デストラクタ
};
