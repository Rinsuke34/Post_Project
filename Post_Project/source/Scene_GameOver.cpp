/* シーン"ゲームオーバー"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_GameOver.h"
// 関連クラス
#include "DataList_GameStatus.h"
#include "Scene_Title.h"
#include "Scene_Load.h"

// コンストラクタ
Scene_GameOver::Scene_GameOver() : Scene_Base("Scene_GameOver", 2001, true, false)
{
	/* データリスト取得 */
	this->pDataList_GameStatus = std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));		// ゲーム状態管理
}

// 更新
void Scene_GameOver::Update()
{
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_Z] == TRUE)
	{
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_Title>());
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_Load>());
		gpSceneServer->SetDeleteCurrentSceneFlg(true);

		/* シーンの削除フラグを有効にする */
		this->bDeleteFlg = true;
	}
}

// 描画
void Scene_GameOver::Draw()
{
	/* ゲームオーバー画面描写 */
	// ゲームオーバー（中央上側）
	DrawString((SCREEN_SIZE_WIDE / 2) - OFFSET_X, (SCREEN_SIZE_HEIGHT / 2) - OFFSET_Y, "ゲームオーバー", GetColor(255, 255, 255));
	// スコア（中央下側）
	std::string scoreText = "スコア: " + std::to_string(this->pDataList_GameStatus->GetScore());
	DrawString((SCREEN_SIZE_WIDE / 2) - OFFSET_X, (SCREEN_SIZE_HEIGHT / 2) + OFFSET_Y, scoreText.c_str(), GetColor(255, 255, 255));

}
