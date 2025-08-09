/* プログラム起動時の処理の定義 */

#include <windows.h>
#include "AppFrame.h"
#include "Scene_Title.h"

// メインプログラム
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/* AppFrameのメインループを実行 */
	Main::MainLoop();

	return 0;
};

// 以下、AppFrameで宣言された関数の定義
// シーンの設定
namespace SCENE_SET
{
	// ゲーム起動時のシーンをセット
	void	SetFastScene()
	{
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_Title>());
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
