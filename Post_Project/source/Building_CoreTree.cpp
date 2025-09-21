/* 建造物(神木(防衛対象))クラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Building_CoreTree.h"
// 関連クラス
#include "DataList_GameStatus.h"
#include "DataList_Model.h"

// コンストラクタ
Building_CoreTree::Building_CoreTree() : Building_Base()
{
	/* 初期化 */
	this->iHp		= 0;	// 体力
	this->iMaxHp	= 0;	// 最大体力

	/* モデルデータ設定 */
	std::shared_ptr<DataList_Model>	pDataList_Model = std::dynamic_pointer_cast<DataList_Model>(gpDataListServer->GetDataList("DataList_Model"));
	this->SetModelHandle(pDataList_Model->iGetModel("CoreTree/CoreTree"));
}

// 初期設定
void Building_CoreTree::InitialSetup()
{
	/* 体力設定 */
	this->iMaxHp	= 100;
	this->iHp		= this->iMaxHp;
	this->pDataList_GameStatus->SetMaxHp_CoreTree(this->iMaxHp);
	this->pDataList_GameStatus->SetHp_CoreTree(this->iHp);

	/* ベースクラスの初期設定 */
	Building_Base::InitialSetup();
}

// 更新
void Building_CoreTree::Update()
{
	this->pDataList_GameStatus->SetMaxHp_CoreTree(this->iMaxHp);
	this->pDataList_GameStatus->SetHp_CoreTree(this->iHp);
}

// 体力を設定
// ※このオブジェクトのHPだけでなく、ゲーム状態管理データリストの神木のHPも更新する
void Building_CoreTree::SetHP(int iHP)
{
	this->iHp = iHP;
	this->pDataList_GameStatus->SetHp_CoreTree(this->iHp);
}
