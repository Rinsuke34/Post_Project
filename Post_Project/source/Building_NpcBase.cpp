/* 建造物(NPC拠点)クラスの提議 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Building_NpcBase.h"
// 関連クラス
#include "DataList_Model.h"
#include "DataList_Object.h"
#include "Npc_Base.h"

// コンストラクタ
Building_NpcBase::Building_NpcBase() : Building_Base()
{
	/* データリスト取得 */
	this->pDataList_Object = std::dynamic_pointer_cast<DataList_Object>(gpDataListServer->GetDataList("DataList_Object"));	// オブジェクト管理

	/* 初期化 */
	this->iRespawnTime = RESPAWN_TIME_DEFAULT;

	/* モデルデータ設定 */
	std::shared_ptr<DataList_Model>	pDataList_Model = std::dynamic_pointer_cast<DataList_Model>(gpDataListServer->GetDataList("DataList_Model"));
	this->SetModelHandle(pDataList_Model->iGetModel("NpcBase/Npc_Base"));
}

// 初期設定
void Building_NpcBase::InitialSetup()
{
	/* 親クラスの初期化処理 */
	Building_Base::InitialSetup();

	/* コリジョン設定 */
	this->stBox.vecBoxCenter = this->vecPosition;
	this->stBox.vecBoxHalfSize.x = BUILDING_SIZE_X	/ 2.f;
	this->stBox.vecBoxHalfSize.y = MAP_BLOCK_SIZE_Y	/ 2.f;
	this->stBox.vecBoxHalfSize.z = BUILDING_SIZE_Z	/ 2.f;
}

// 更新
void Building_NpcBase::Update()
{
	/* タイマーの更新 */
	this->iRespawnTime--;

	/* タイマーが完了しているならNPCを生成する */
	if (this->iRespawnTime <= 0)
	{
		/* Npcを生成 */
		std::shared_ptr<Npc_Base> pNpc_Wisp = std::make_shared<Npc_Base>();
		pNpc_Wisp->SetName(this->NpcName);
		pNpc_Wisp->SetPosition(VAdd(this->GetPosition(), VGet(0.f, MAP_BLOCK_SIZE_Y / 2.f, 0.f)));
		pNpc_Wisp->InitialSetup();
		this->pDataList_Object->AddObject_Character(pNpc_Wisp);

		/* タイマーをリセット */
		this->iRespawnTime = RESPAWN_TIME_DEFAULT;
	}
}
