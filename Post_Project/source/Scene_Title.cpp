/* シーン"タイトル"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_Title.h"
// 関連クラス
#include "Scene_StageCreate.h"
#include "Scene_GameMain.h"
#include "Scene_Load.h"


// コンストラクタ
Scene_Title::Scene_Title() : Scene_Base("Scene_Title", 0, false, false)
{

}

// デストラクタ
Scene_Title::~Scene_Title()
{

}

// 更新
void Scene_Title::Update()
{
	/* 入力待ち */
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_Z] == TRUE)
	{
		/* 2Dパーツアニメーション作成ツールへ遷移 */
		PUBLIC_FUNCTION::Start2DPartsAnimCreateTool();
	}

	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_X] == TRUE)
	{
		/* "ステージ作成"へ遷移 */
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_StageCreate>());
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_Load>());

		/* シーンの削除フラグを有効にする */
		this->bDeleteFlg = true;
	}

	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_C] == TRUE)
	{
		/* シーン"ゲームメイン"へ遷移 */
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_GameMain>());
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_Load>());

		/* シーンの削除フラグを有効にする */
		this->bDeleteFlg = true;
	}
}

// 描画
void Scene_Title::Draw()
{
	/* タイトル画面描写 */
	DrawString(SCREEN_SIZE_WIDE / 2, SCREEN_SIZE_HEIGHT / 2, "タイトル", GetColor(255, 255, 255));
}
