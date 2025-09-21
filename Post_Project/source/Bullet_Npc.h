/* バレット(NPC)クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Bullet_Base.h"

// バレット(NPC)クラス
class Bullet_Npc : public Bullet_Base
{
	public:
		Bullet_Npc();				// コンストラクタ
		virtual ~Bullet_Npc() {};	// デストラクタ

		/* 関数 */
		virtual void	InitialSetup();	// 初期設定
};
