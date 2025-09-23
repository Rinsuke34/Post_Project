/* シーン"UI:ゲーム内リソース"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_GameMain_UI_Resource.h"
// 関連クラス
#include "DataList_GameStatus.h"
#include "DataList_Image.h"

// コンストラクタ
Scene_GameMain_UI_Resource::Scene_GameMain_UI_Resource() : Scene_Base("Scene_GameMain_UI_Resource", 100, false, false)
{
	/* データリスト取得 */
	this->pDataList_GameStatus						= std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));	// ゲーム状態管理
	std::shared_ptr<DataList_Image>	pDataList_Image	= std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));			// 画像管理

	/* 使用する画像を設定 */
	std::string fileName = "ItemImage/Coin";
	this->piGrHandle_Coin = pDataList_Image->iGetGrhandle(fileName);	// コインの画像
}

// 描画
void Scene_GameMain_UI_Resource::Draw()
{
	/* 建築モードであるか確認 */
	if (this->pDataList_GameStatus->GetBuildModeFlg())
	{
		// 建築モードである場合
		/* コインの画像を描写 */
		DrawGraph(UI_COIN_POS_X_BUILDING, UI_COIN_POS_Y_BUILDING, *(this->piGrHandle_Coin), TRUE);

		/* コイン枚数を描写 */
		DrawFormatString(UI_COIN_POS_X_BUILDING + 75, UI_COIN_POS_Y_BUILDING + 25, GetColor(255, 255, 255), "x %d", this->pDataList_GameStatus->GetHaveCoin());
	}
	else
	{
		// 建築モードでない場合
		/* コインの画像を描写 */
		DrawGraph(UI_COIN_POS_X, UI_COIN_POS_Y, *(this->piGrHandle_Coin), TRUE);

		/* コイン枚数を描写 */
		DrawFormatString(UI_COIN_POS_X + 75, UI_COIN_POS_Y + 25, GetColor(255, 255, 255), "x %d", this->pDataList_GameStatus->GetHaveCoin());

		/* 現在のスコアの背景を描写 */
		DrawBox(UI_SCORE_POS_X - UI_BACKGROUND_BACK_WIDE, UI_SCORE_POS_Y - UI_BACKGROUND_BACK_WIDE, UI_SCORE_POS_X + UI_BACKGROUND_BACK_WIDE + UI_BACKGROUND_WIDE, UI_SCORE_POS_Y + UI_BACKGROUND_BACK_WIDE + UI_BACKGROUND_HEIGHT, GetColor(0, 0, 0), TRUE);
		DrawBox(UI_SCORE_POS_X, UI_SCORE_POS_Y, UI_SCORE_POS_X + UI_BACKGROUND_WIDE, UI_SCORE_POS_Y + UI_BACKGROUND_HEIGHT, GetColor(128, 128, 128), TRUE);

		/* 現在のスコアを描写 */
		DrawFormatString(UI_SCORE_POS_X, UI_SCORE_POS_Y, GetColor(255, 255, 255), "Score : %d", this->pDataList_GameStatus->GetScore());

		/* 現在のウェーブの背景を描写 */
		DrawBox(UI_WAVE_POS_X - UI_BACKGROUND_BACK_WIDE, UI_WAVE_POS_Y - UI_BACKGROUND_BACK_WIDE, UI_WAVE_POS_X + UI_BACKGROUND_BACK_WIDE + UI_BACKGROUND_WIDE, UI_WAVE_POS_Y + UI_BACKGROUND_BACK_WIDE + UI_BACKGROUND_HEIGHT, GetColor(0, 0, 0), TRUE);
		DrawBox(UI_WAVE_POS_X, UI_WAVE_POS_Y, UI_WAVE_POS_X + UI_BACKGROUND_WIDE, UI_WAVE_POS_Y + UI_BACKGROUND_HEIGHT, GetColor(128, 128, 128), TRUE);

		/* 現在のウェーブ数を描写 */
		DrawFormatString(UI_WAVE_POS_X, UI_WAVE_POS_Y, GetColor(255, 255, 255), "Wave  : %d", this->pDataList_GameStatus->GetWave());
	}
}
