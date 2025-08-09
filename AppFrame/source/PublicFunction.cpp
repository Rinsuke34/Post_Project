/* 2025.03.25 駒沢風助 ファイル作成 */

#include "AppFunctionDefine.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdio>

/* 汎用的に使用できる機能の定義 */
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
