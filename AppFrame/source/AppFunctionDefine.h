/* AppFrameで使用する関数の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 標準ライブラリ
#include <string>
// 外部ライブラリ
#include <DxLib.h>
// 共通定義
#include "AppConstantDefine.h"

// シーンの設定
namespace SCENE_SET
{
	// ※この関数は各プログラム毎に内容を変更する必要があるため、AppFrameでは宣言のみ行い各プロジェクトで定義する
	void	SetFastScene();		// ゲーム起動時のシーンをセット
}

// 初期化
namespace PROJECT_INIT
{
	void	Init();				// プロジェクト初期化処理
}

// 汎用計算系
namespace PUBLIC_PROCESS
{
	float		fClamp(float fValue, float fMax, float fMin);																			// 値を範囲内に収める
	bool		bCheckAboveThreshold(unsigned char ucValue, unsigned char ucThreshold);													// 閾値を超えているか確認
	float		fAnalogStickNorm(short sMouseMove);																						// アナログスティックの入力を正規化(±1)
	bool		bCheckInputDeadzone(float fInput, float fDeadzone);																		// 入力値がデッドゾーンの範囲内であるか確認
	VECTOR		vecGetLineCrossPoint(VECTOR vecLineAStart, VECTOR vecLineADirection, VECTOR vecLineBStart, VECTOR vecLineBDirection);	// 2つの線分の交点を取得
	COLOR_F		stAddCollorF(COLOR_F vecColorF_A, COLOR_F vecColorF_B);																	// 2つの色(COLOR_F型)を合成
	std::string	aUtf8ToShiftJIS(std::string Utf8);																						// UTF-8 → Shift-JIS 変換
	std::string	aShiftJisToUtf8(std::string ShiftJis);																					// Shift-JIS → UTF-8 変換
	std::string	aCutShitfJisString(std::string ShiftJis, int iLength);																	// Shift-JIS文字列を指定文字数でカット
	std::string aInsertNewLine(std::string ShiftJis, int iLength);																		// Shift-JIS文字列を指定文字数で改行
}

// 汎用機能系
namespace PUBLIC_FUNCTION
{
	void		FileDeletesAndStand(const std::string& filename);																		// 指定ファイルを完全に削除するまで待機
	std::string	aOpenFileDialog(std::string Filter);																					// ファイル選択ダイアログを表示
	void		Start2DPartsAnimCreateTool();																							// 2Dパーツアニメーション作成ツールを起動
}
