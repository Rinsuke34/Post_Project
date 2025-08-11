/* シーン"タイトル"の定義 */

#include "Scene_Title.h"

// コンストラクタ
Scene_Title::Scene_Title() : SceneBase("Scene_Title", 0, false)
{

}

// デストラクタ
Scene_Title::~Scene_Title()
{

}

// 計算
void Scene_Title::Process()
{
	/* 入力待ち */
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_Z] == TRUE)
	{
		/* シーン削除フラグを有効にする */
		this->bDeleteFlg = true;

		/* 2Dパーツアニメーション作成ツールを起動 */
		PUBLIC_FUNCTION::Start2DPartsAnimCreateTool();
	}
}

// 描画
void Scene_Title::Draw()
{
	/* タイトル画面描写 */
	DrawString(SCREEN_SIZE_WIDE / 2, SCREEN_SIZE_HEIGHT / 2, "タイトル", GetColor(255, 255, 255));
}
