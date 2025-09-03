/* プログラム起動時の処理の定義 */

#include <windows.h>
#include "AppFrame.h"
#include "Scene_Title.h"

#include "DataList_GrHandle.h"
#include "DataList_Model.h"

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
		/* データリストサーバーへの登録 */
		gpDataListServer->AddDataList(std::make_shared<DataList_GrHandle>());	// 画像データ管理
		gpDataListServer->AddDataList(std::make_shared<DataList_Model>());		// 3Dモデル管理
	}
}
