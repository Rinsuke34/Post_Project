/* 建造物(神木(防衛対象))クラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Building_CoreTree.h"
// 関連クラス
#include "DataList_Object.h"
#include "DataList_GameStatus.h"

// コンストラクタ
Building_CoreTree::Building_CoreTree() : Ground_Model()
{
	/* データリスト取得 */
	this->pDataList_Object		= std::dynamic_pointer_cast<DataList_Object>(gpDataListServer->GetDataList("DataList_Object"));				// オブジェクト管理
	this->pDataList_GameStatus	= std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));		// ゲーム状態管理

	/* 初期化 */
	this->iHp		= 0;	// 体力
	this->iMaxHp	= 0;	// 最大体力
}

// デストラクタ
Building_CoreTree::~Building_CoreTree()
{

}

// 初期設定
void Building_CoreTree::InitialSetup()
{
	/* 体力設定 */
	this->iMaxHp	= 100;
	this->iHp		= this->iMaxHp;
	this->pDataList_GameStatus->SetMaxHp_CoreTree(this->iMaxHp);
	this->pDataList_GameStatus->SetHp_CoreTree(this->iHp);

	/* コリジョン設定 */
	this->stBox.vecBoxCenter	= VAdd(VGet(0.f, (CORETREE_SIZE_Y / 2.f) - 16.f, 0.f), this->GetPosition());
	this->stBox.vecBoxHalfSize	= VGet(CORETREE_SIZE_X / 2.f, CORETREE_SIZE_Y / 2.f, CORETREE_SIZE_Z / 2.f);

	/* ベースクラスの初期設定 */
	Ground_Model::InitialSetup();
}

// 更新
void Building_CoreTree::Update()
{

}

// 描画(当たり判定)
void Building_CoreTree::Draw_Collision()
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

// 体力を設定
// ※このオブジェクトのHPだけでなく、ゲーム状態管理データリストの神木のHPも更新する
void Building_CoreTree::SetHP(int iHP)
{
	this->iHp = iHP;
	this->pDataList_GameStatus->SetHp_CoreTree(this->iHp);
}
