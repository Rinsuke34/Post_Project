/* シーン"タイトル"の宣言 */

#pragma once
#include "AppFrame.h"

// シーン"タイトル"
class Scene_Title : public SceneBase
{
	public:
		Scene_Title();				// コンストラクタ
		virtual ~Scene_Title();		// デストラクタ

		virtual void	Process()			override;	// 計算
		virtual void	Draw()				override;	// 描画
};
