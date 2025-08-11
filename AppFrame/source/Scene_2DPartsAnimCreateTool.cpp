/* シーン"汎用2Dパーツアニメーションツール"の定義 */

#include "Scene_2DPartsAnimCreateTool.h"

#include "AppVariableDefine.h"
#include "AppFunctionDefine.h"

// コンストラクタ
Scene_2DPartsAnimCreateTool::Scene_2DPartsAnimCreateTool() : SceneBase("Scene_2DPartsAnimCreateTool", 9999, true)
{

}

// デストラクタ
Scene_2DPartsAnimCreateTool::~Scene_2DPartsAnimCreateTool()
{

}

// 計算
void Scene_2DPartsAnimCreateTool::Process()
{
	/* 入力待ち */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_Z] == TRUE)
	{
		/* ダイアログを表示 */
		std::string path = PUBLIC_FUNCTION::aOpenFileDialog(".png");

		/* パスが取得されたか確認 */
		if (!path.empty())
		{
			// 取得された場合
			/* 画像のグラフィックハンドルを取得 */
			int iGrHandle = LoadGraph(path.c_str());

			/* グラフィックハンドルが取得できたか確認 */
			if (iGrHandle != -1)
			{
				// グラフィックハンドルが取得できた場合
				/* 選択した画像のグラフィックハンドルとパスを保存 */
				this->iSelectGrHandle.push_back(iGrHandle);
				this->stSelectGrPath.push_back(path);
			}
		}
	}
}

// 描画
void Scene_2DPartsAnimCreateTool::Draw()
{
	/* 選択した画像のグラフィックハンドルを描写 */
	for (int iIndex = 0; iIndex < this->iSelectGrHandle.size(); ++iIndex)
	{
		DrawString(iIndex * 100, 0, this->stSelectGrPath[iIndex].c_str(), GetColor(255, 255, 255));
		DrawGraph(iIndex * 100, 20, this->iSelectGrHandle[iIndex], FALSE);
	}
}


