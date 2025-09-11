/* 地形(マーカー)クラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Ground_Marker.h"
// 共通定義
#include "ConstantDefine.h"

// コンストラクタ
Ground_Marker::Ground_Marker() : Ground_Base()
{
	/* 初期化 */
	this->MarkerName	= "";
	this->vecRotation	= VGet(0.f, 0.f, 0.f);
}

// 描画
void Ground_Marker::Draw()
{
	/* 中心点描写 */
	DrawLine3D(VAdd(this->stBox.vecBoxCenter, VGet(+MARKER_CENTER_SIZE_HALF, 0.f, 0.f)), VAdd(this->stBox.vecBoxCenter, VGet(-MARKER_CENTER_SIZE_HALF, 0.f, 0.f)), GetColor(255, 0, 0));
	DrawLine3D(VAdd(this->stBox.vecBoxCenter, VGet(0.f, +MARKER_CENTER_SIZE_HALF, 0.f)), VAdd(this->stBox.vecBoxCenter, VGet(0.f, -MARKER_CENTER_SIZE_HALF, 0.f)), GetColor(255, 0, 0));
	DrawLine3D(VAdd(this->stBox.vecBoxCenter, VGet(0.f, 0.f, +MARKER_CENTER_SIZE_HALF)), VAdd(this->stBox.vecBoxCenter, VGet(0.f, 0.f, -MARKER_CENTER_SIZE_HALF)), GetColor(255, 0, 0));
}
