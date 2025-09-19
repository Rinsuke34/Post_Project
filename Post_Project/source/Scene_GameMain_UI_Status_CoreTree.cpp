/* シーン"UI:神木(防衛対象)の状態"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_GameMain_UI_Status_CoreTree.h"
// 関連クラス
#include "DataList_GameStatus.h"

// コンストラクタ
Scene_GameMain_UI_Status_CoreTree::Scene_GameMain_UI_Status_CoreTree() : Scene_Base("Scene_GameMain_UI_Status_CoreTree", 100, false, false)
{
	/* データリスト取得 */
	this->pDataList_GameStatus = std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));	// ゲーム状態管理
}

// 更新
void Scene_GameMain_UI_Status_CoreTree::Update()
{

}

// 描画
void Scene_GameMain_UI_Status_CoreTree::Draw()
{
	DrawFormatString(50, 50, GetColor(255, 255, 255), "CoreTree HP : %d / %d", this->pDataList_GameStatus->GetHp_CoreTree(), this->pDataList_GameStatus->GetMaxHp_CoreTree());
}
