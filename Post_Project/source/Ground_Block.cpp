/* 地形(ブロック)クラスの定義 */

/* 使用する要素のインクルード */
// 標準ライブラリ
#define NOMINMAX
#include <algorithm>
// ヘッダファイル
#include "Ground_Block.h"

// コンストラクタ
Ground_Block::Ground_Block() : Ground_Base()
{
	/* 初期化 */
	for (int iIndex = 0; iIndex < 3; ++iIndex)
	{
		this->apiGrHandle[iIndex] = nullptr;
	}
	this->stBox.vecBoxCenter	= VGet(0.0f, 0.0f, 0.0f);
	this->stBox.vecBoxHalfSize		= VGet(1.0f, 1.0f, 1.0f);

	for (int iIndex = 0; iIndex < DIRECTION_MAX; ++iIndex)
	{
		this->bFaceDrawFlg[iIndex] = false;
	}
}

// 描画
void Ground_Block::Draw()
{
	/* 中心座標を基準とした立方体の頂点座標を計算 */
	VERTEX3D aVertex[8];
	aVertex[0].pos = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[1].pos = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);
	aVertex[2].pos = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[3].pos = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);
	aVertex[4].pos = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[5].pos = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);
	aVertex[6].pos = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[7].pos = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);
	// 頂点の初期化
	for (int i = 0; i < 8; ++i)
	{
		aVertex[i].dif	= GetColorU8(255, 255, 255, 255);
		aVertex[i].spc	= GetColorU8(125, 125, 125, 255);
		aVertex[i].su	= 0.f;
		aVertex[i].sv	= 0.f;
	}

	/* 各面の描画 */
	// +X方向
	if (bFaceDrawFlg[DIRECTION_X_PLUS])
	{
		// インデックスデータ（右面の2ポリゴン）
		unsigned short IndexRight[6] = { 3, 1, 2, 2, 1, 0 };

		// 法線ベクトルを設定
		for (int i = 0; i < 8; ++i)
		{
			aVertex[i].norm = VGet(+1.0f, 0.0f, 0.0f);
		}

		// uv座標を設定
		aVertex[0].u = 0.f;
		aVertex[0].v = 0.f;
		aVertex[1].u = 1.f;
		aVertex[1].v = 0.f;
		aVertex[2].u = 0.f;
		aVertex[2].v = 1.f;
		aVertex[3].u = 1.f;
		aVertex[3].v = 1.f;

		// 四角形（板ポリゴン）の描画
		DrawPolygonIndexed3D(aVertex, 8, IndexRight, 2, *this->apiGrHandle[FACE_TYPE_SIDE], TRUE);
	}
	// -X方向
	if (bFaceDrawFlg[DIRECTION_X_MINUS])
	{
		// インデックスデータ（左面の2ポリゴン）
		unsigned short IndexLeft[6] = { 6, 4, 7, 7, 4, 5 };

		// 法線ベクトルを設定
		for (int i = 0; i < 8; ++i)
		{
			aVertex[i].norm = VGet(-1.0f, 0.0f, 0.0f);
		}

		// uv座標を設定
		aVertex[4].u = 0.f;
		aVertex[4].v = 0.f;
		aVertex[5].u = 1.f;
		aVertex[5].v = 0.f;
		aVertex[6].u = 0.f;
		aVertex[6].v = 1.f;
		aVertex[7].u = 1.f;
		aVertex[7].v = 1.f;

		// 四角形（板ポリゴン）の描画
		DrawPolygonIndexed3D(aVertex, 8, IndexLeft, 2, *this->apiGrHandle[FACE_TYPE_SIDE], TRUE);
	}
	// +Y方向
	if (bFaceDrawFlg[DIRECTION_Y_PLUS])
	{
		// インデックスデータ（上面の2ポリゴン）
		unsigned short IndexTop[6] = { 0, 1, 4, 4, 1, 5 };

		// 法線ベクトルを設定
		for (int i = 0; i < 8; ++i)
		{
			aVertex[i].norm = VGet(0.0f, 1.0f, 0.0f);
		}

		// uv座標を設定
		aVertex[0].u = 1.f;
		aVertex[0].v = 0.f;
		aVertex[1].u = 1.f;
		aVertex[1].v = 1.f;
		aVertex[4].u = 0.f;
		aVertex[4].v = 0.f;
		aVertex[5].u = 0.f;
		aVertex[5].v = 1.f;

		// 四角形（板ポリゴン）の描画
		DrawPolygonIndexed3D(aVertex, 8, IndexTop, 2, *this->apiGrHandle[FACE_TYPE_TOP], TRUE);
	}
	// -Y方向
	if (bFaceDrawFlg[DIRECTION_Y_MINUS])
	{
		// インデックスデータ（底面の2ポリゴン）
		unsigned short IndexBottom[6] = { 6, 3, 2, 7, 3, 6 };

		// 法線ベクトルを設定
		for (int i = 0; i < 8; ++i)
		{
			aVertex[i].norm = VGet(0.0f, -1.0f, 0.0f);
		}

		// uv座標を設定
		aVertex[2].u = 1.f;
		aVertex[2].v = 0.f;
		aVertex[3].u = 1.f;
		aVertex[3].v = 1.f;
		aVertex[6].u = 0.f;
		aVertex[6].v = 0.f;
		aVertex[7].u = 0.f;
		aVertex[7].v = 1.f;

		// 四角形（板ポリゴン）の描画
		DrawPolygonIndexed3D(aVertex, 8, IndexBottom, 2, *this->apiGrHandle[FACE_TYPE_BOTTOM], TRUE);
	}
	// +Z方向
	if (bFaceDrawFlg[DIRECTION_Z_PLUS])
	{
		// インデックスデータ（手前面の2ポリゴン）
		unsigned short IndexFront[6] = { 2, 0, 6, 6, 0, 4 };

		// 法線ベクトルを設定
		for (int i = 0; i < 8; ++i)
		{
			aVertex[i].norm = VGet(0.0f, 0.0f, +1.0f);
		}

		// uv座標を設定
		aVertex[0].u = 1.f;
		aVertex[0].v = 0.f;
		aVertex[2].u = 1.f;
		aVertex[2].v = 1.f;
		aVertex[4].u = 0.f;
		aVertex[4].v = 0.f;
		aVertex[6].u = 0.f;
		aVertex[6].v = 1.f;

		// 四角形（板ポリゴン）の描画
		DrawPolygonIndexed3D(aVertex, 8, IndexFront, 2, *this->apiGrHandle[FACE_TYPE_SIDE], TRUE);
	}
	// -Z方向
	if (bFaceDrawFlg[DIRECTION_Z_MINUS])
	{
		// インデックスデータ（奥面の2ポリゴン）
		unsigned short IndexBack[6] = { 7, 5, 3, 3, 5, 1 };

		// 法線ベクトルを設定
		for (int i = 0; i < 8; ++i)
		{
			aVertex[i].norm = VGet(0.0f, 0.0f, -1.0f);
		}

		// uv座標を設定
		aVertex[1].u = 1.f;
		aVertex[1].v = 0.f;
		aVertex[3].u = 1.f;
		aVertex[3].v = 1.f;
		aVertex[5].u = 0.f;
		aVertex[5].v = 0.f;
		aVertex[7].u = 0.f;
		aVertex[7].v = 1.f;

		// 四角形（板ポリゴン）の描画
		DrawPolygonIndexed3D(aVertex, 8, IndexBack, 2, *this->apiGrHandle[FACE_TYPE_SIDE], TRUE);
	}
}
