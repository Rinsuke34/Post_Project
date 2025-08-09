/* AppFrameで使用する関数の定義 */

#include "AppFrame.h"

// シーンの設定
namespace SCENE_SET
{
	// ゲーム起動時のシーンをセット
	void	SetFastScene()
	{
		//gpSceneServer->AddSceneReservation(new SceneTitle(), true);
	}

	// ロードシーンをセット
	void	SetLoadScene()
	{
		//gpSceneServer->AddSceneReservation(new SceneLoad(), false);
	}
}

// 初期化
namespace PROJECT_INIT
{
	// プロジェクト初期化処理
	void	Init()
	{
		/* データリストサーバーに"プレイヤー入力管理"を追加 */
		//gpDataListServer->AddDataList(new DataList_Input());

		/* 今追加した"プレイヤー入力管理"を取得 */
		//gpDataList_Input = dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));
	}
}
