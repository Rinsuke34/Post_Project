/* シーン"ステージ作成"の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"

// シーン"ステージ作成"
class Scene_StageCreate : public Scene_Base
{
	public:
		Scene_StageCreate();			// コンストラクタ
		virtual ~Scene_StageCreate();	// デストラクタ

		/* 関数 */
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描画
};
