/* シーン"UI:プレイヤーの状態"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_GameMain_UI_Status_Player.h"
// 関連クラス
#include "DataList_GameStatus.h"

// コンストラクタ
Scene_GameMain_UI_Status_Player::Scene_GameMain_UI_Status_Player() : Scene_Base("Scene_GameMain_UI_Status_Player", 100, false, false)
{
	/* データリスト取得 */
	this->pDataList_GameStatus = std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));	// ゲーム状態管理
}

// 更新
void Scene_GameMain_UI_Status_Player::Update()
{

}

// 描画
void Scene_GameMain_UI_Status_Player::Draw()
{
	DrawFormatString(50, 500, GetColor(255, 255, 255), "Player HP : %d / %d", this->pDataList_GameStatus->GetHp_Player(), this->pDataList_GameStatus->GetMaxHp_Player());
}
