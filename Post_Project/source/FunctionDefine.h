/* プロジェクトで使用する関数の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 標準ライブラリ
#include <thread>
#include <future>
// 外部ライブラリ
#include <DxLib.h>

/* マップ系 */
int	iGetGridIndexX(float fX);	// グリッドのXインデックスを取得
int iGetGridIndexZ(float fZ);	// グリッドのZインデックスを取得

/* 非同期読み込み系 */
bool bCheck_FutureReady(std::future<void>& future);	// 非同期処理が完了しているか確認
