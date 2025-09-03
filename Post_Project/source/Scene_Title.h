/* シーン"タイトル"の宣言 */

#pragma once
#include "AppFrame.h"

// シーン"タイトル"
class Scene_Title : public SceneBase
{
	public:
		Scene_Title();				// コンストラクタ
		virtual ~Scene_Title();		// デストラクタ

		/* 関数 */
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描画
};
