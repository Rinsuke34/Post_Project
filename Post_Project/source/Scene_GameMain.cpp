/* シーン"ゲームメイン"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_GameMain.h"

// 関連クラス
#include "Scene_Stage.h"
#include "DataList_Object.h"
#include "DataList_GameStatus.h"

// コンストラクタ
Scene_GameMain::Scene_GameMain() : Scene_Base("Scene_GameMain", 0, false, false)
{
	/* データリスト作成 */	
	gpDataListServer->AddDataList(std::make_shared<DataList_GameStatus>());		// ゲーム状態管理
	gpDataListServer->AddDataList(std::make_shared<DataList_Object>());			// オブジェクト管理

	/* シーン作成 */
	gpSceneServer->AddSceneReservation(std::make_shared<Scene_Stage>());		// ステージシーン

	/* データリスト取得 */
	this->pDataList_Object		= std::dynamic_pointer_cast<DataList_Object>(gpDataListServer->GetDataList("DataList_Object"));			// オブジェクト管理
	this->pDataList_GameStatus	= std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));	// ゲーム状態管理
}

// デストラクタ
Scene_GameMain::~Scene_GameMain()
{

}

// 更新
void Scene_GameMain::Update()
{
	/* オブジェクト更新 */
	this->pDataList_Object->Update_All();

	/* 削除フラグが有効なオブジェクト削除 */
	this->pDataList_Object->DeleteFlagged_AllObject();
}
