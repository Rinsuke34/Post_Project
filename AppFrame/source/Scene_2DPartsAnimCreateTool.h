/* シーン"汎用2Dパーツアニメーションツール"の宣言 */

#pragma once
#include "SceneBase.h"
#include <vector>

// シーン"汎用2Dパーツアニメーションツール"
class Scene_2DPartsAnimCreateTool : public SceneBase
{
	public:
		Scene_2DPartsAnimCreateTool();				// コンストラクタ
		virtual ~Scene_2DPartsAnimCreateTool();		// デストラクタ

		virtual void	Process()			override;	// 計算
		virtual void	Draw()				override;	// 描画

	private:
		/* 関数 */

		/* 変数 */
		std::vector<int> iSelectGrHandle;	// 選択した画像のグラフィックハンドル
		std::vector<std::string> stSelectGrPath;
};
