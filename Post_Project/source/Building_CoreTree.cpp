/* 建造物(神木(防衛対象))クラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Building_CoreTree.h"
// 関連クラス
#include "DataList_GameStatus.h"
#include "DataList_Model.h"
#include "DataList_Sound.h"

// コンストラクタ
Building_CoreTree::Building_CoreTree() : Building_Base()
{
	/* データリストを取得 */
	this->pDataList_Sound							= std::dynamic_pointer_cast<DataList_Sound>(gpDataListServer->GetDataList("DataList_Sound"));	// サウンド管理
	std::shared_ptr<DataList_Model>	pDataList_Model = std::dynamic_pointer_cast<DataList_Model>(gpDataListServer->GetDataList("DataList_Model"));	// モデル管理

	/* 初期化 */
	this->iHpPrevFrame		= 0;
	this->iSECooldownTimer	= 0;

	/* モデルデータ設定 */
	this->SetModelHandle(pDataList_Model->iGetModel("CoreTree/CoreTree"));
}

// 初期設定
void Building_CoreTree::InitialSetup()
{
	/* 体力設定 */
	this->pDataList_GameStatus->SetMaxHp_CoreTree(MAX_HP);
	this->pDataList_GameStatus->SetHp_CoreTree(MAX_HP);
	this->iHpPrevFrame	= MAX_HP;

	/* ベースクラスの初期設定 */
	Building_Base::InitialSetup();
}

// 更新
void Building_CoreTree::Update()
{
	/* 現在のHPを取得 */
	int iNowHp = this->pDataList_GameStatus->GetHp_CoreTree();

	/* HPが減少しているか確認 */
	if (iNowHp < this->iHpPrevFrame)
	{
		// 減少している場合
		/* ダメージ音を再生 */
		if (this->iSECooldownTimer <= 0)
		{
			pDataList_Sound->SE_Play("Tree_Damage", this->vecPosition);
			this->iSECooldownTimer = SE_COOLDOWN_TIME;	// クールダウンタイムを設定
		}
	}

	/* SEクールダウンタイム更新 */
	if (this->iSECooldownTimer > 0)
	{
		this->iSECooldownTimer--;
	}

	/* 現在のHPを設定 */
	this->iHpPrevFrame = iNowHp;
}
