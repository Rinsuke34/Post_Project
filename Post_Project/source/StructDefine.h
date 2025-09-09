/* プロジェクトで使用する構造体の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 標準ライブラリ
#include <string>

// テクスチャデータ
struct TEXTURE_DATA
{
	std::string BlockName;		// ブロック名
	int			iBlockIndex;	// ブロックのインデックス番号
	std::string aImageName[3];	// 画像名(0:上面, 1:横面, 2:下面)
};
