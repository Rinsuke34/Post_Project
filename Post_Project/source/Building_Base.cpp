/* 建造物のベースクラスの提議 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Building_Base.h"
// 関連クラス
#include "DataList_GameStatus.h"
// 共通定義
#include "ConstantDefine.h"

// コンストラクタ
Building_Base::Building_Base() : Ground_Model()
{
	/* データリスト取得 */
	this->pDataList_GameStatus = std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));		// ゲーム状態管理
}

// 初期設定
void Building_Base::InitialSetup()
{
	/* 少し下に下げる */
	this->vecPosition = (VAdd(this->vecPosition, VGet(0.f, -(MAP_BLOCK_SIZE_Y / 2.f), 0.f)));
	/* コリジョン設定 */
	this->stBox.vecBoxCenter	= VAdd(VGet(0.f, (BUILDING_SIZE_Y / 2.f), 0.f), this->GetPosition());
	this->stBox.vecBoxHalfSize	= VGet(BUILDING_SIZE_X / 2.f, BUILDING_SIZE_Y / 2.f, BUILDING_SIZE_Z / 2.f);

	/* ベースクラスの初期設定 */
	Ground_Model::InitialSetup();
}

// 描画(当たり判定)
void Building_Base::Draw_Collision()
{
	/* 頂点を設定 */
	VECTOR aVertex[8];
	aVertex[0] = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[1] = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);
	aVertex[2] = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[3] = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);
	aVertex[4] = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[5] = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);
	aVertex[6] = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[7] = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);

	/* 線分を描画 */
	PUBLIC_FUNCTION::DrawCubeLine3D(aVertex, GetColor(255, 255, 255));
}
