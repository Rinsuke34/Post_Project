/* シーン"UI:ゲーム内リソース"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_GameMain_UI_Resource.h"
// 関連クラス
#include "DataList_GameStatus.h"

// コンストラクタ
Scene_GameMain_UI_Resource::Scene_GameMain_UI_Resource() : Scene_Base("Scene_GameMain_UI_Resource", 100, false, false)
{
	/* データリスト取得 */
	this->pDataList_GameStatus = std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));	// ゲーム状態管理
}

// 描画
void Scene_GameMain_UI_Resource::Draw()
{
	/* コイン枚数を描写 */
	DrawFormatString(1980 - 500, 1000, GetColor(255, 255, 255), "HaveCoin : %d", this->pDataList_GameStatus->GetHaveCoin());
}
