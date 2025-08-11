/* 汎用的に使用できる機能の定義 */

#include "AppFunctionDefine.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdio>
#include <Windows.h>

// 指定ファイルを完全に削除するまで待機
void PUBLIC_FUNCTION::FileDeletesAndStand(const std::string& filename)
{
	// 引数
	// filename	<- 削除するファイル名

	/* 削除完了フラグ */
	bool bDeleteCompleteFlg = false;

	/* 指定ファイルを削除 */
	std::remove(filename.c_str());

	/* ファイルが削除されるまで待機 */
	while (bDeleteCompleteFlg == false)
	{
		/* ファイルが開けるか確認 */
		std::ifstream file(filename);
		if (file.is_open())
		{
			// ファイルが開ける場合
			/* 待機 */
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		else
		{
			// ファイルが開けない場合
			/* 削除完了フラグを立てる */
			bDeleteCompleteFlg = true;
		}
	}
}

// ファイル選択ダイアログを表示
std::string	PUBLIC_FUNCTION::aOpenFileDialog(std::string Filter)
{
	// 引数
	// Filter	<- ファイル選択ダイアログのフィルター文字列(例："*.png;*.jpg;*.bmp")
	// 戻り値
	// std::string	<- 選択されたファイルのパス(選択されなかった場合は空文字列)

	/* DXライブラリのウィンドウハンドルを取得 */
	HWND WindHwnd = GetMainWindowHandle();

	/* ダイアログ作成 */
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize		= sizeof(ofn);
	ofn.hwndOwner		= WindHwnd; // DXライブラリのウィンドウを親に設定
	ofn.lpstrFile		= new char[MAX_PATH];
	ofn.nMaxFile		= MAX_PATH;
	ofn.lpstrFilter		= Filter.c_str();
	ofn.nFilterIndex	= 1;
	ofn.lpstrFile[0]	= '\0'; // 初期化
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;

	/* ダイアログ表示 */
	if (GetOpenFileName(&ofn))
	{
		// ファイルが選択された場合
		std::string selectedFile = ofn.lpstrFile;
		delete[] ofn.lpstrFile;

		/* 選択されたファイルのパスを返す */
		return selectedFile;
	}

	return "";
}

#include "AppVariableDefine.h"
#include "Scene_2DPartsAnimCreateTool.h"

// 2Dパーツアニメーション作成ツールの起動
void PUBLIC_FUNCTION::Start2DPartsAnimCreateTool()
{
	// シーン"汎用2Dパーツアニメーションツール"を追加予約
	gpSceneServer->AddSceneReservation(std::make_shared<Scene_2DPartsAnimCreateTool>());
}
