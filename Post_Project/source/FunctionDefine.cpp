/* プロジェクトで使用する関数の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "FunctionDefine.h"
// 共通定義
#include "ConstantDefine.h"

/* マップ系 */
// グリッドのXインデックスを取得
int	iGetGridIndexX(float fX)
{
    // 引数
	// fX	<- 位置X座標
	// 戻り値
	// int	<- グリッドのXインデックス

    int iGridX = static_cast<int>(fX / GRID_SIZE_WORLD_X);

    if (iGridX < 0)
    {
        iGridX = 0;
    }

    if (iGridX >= GRID_NUMBER_X)
    {
        iGridX = GRID_NUMBER_X - 1;
    }

    return iGridX;
}

// グリッドのZインデックスを取得
int iGetGridIndexZ(float fZ)
{
	// 引数
	// fZ	<- 位置Z座標
	// 戻り値
	// int	<- グリッドのZインデックス

    int iGridZ = static_cast<int>(fZ / GRID_SIZE_WORLD_X);

    if (iGridZ < 0)
    {
        iGridZ = 0;
    }

    if (iGridZ >= GRID_NUMBER_Z)
    {
        iGridZ = GRID_NUMBER_Z - 1;
    }

    return iGridZ;
}
