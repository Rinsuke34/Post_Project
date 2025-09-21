/* 建造物(モニュメント(剣))クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Building_Monument_Sowrd.h"
// 関連クラス
#include "DataList_Model.h"

// コンストラクタ
Building_Monument_Sowrd::Building_Monument_Sowrd() : Building_Base()
{
	/* 初期化 */
	this->iAddMeleeAttack = 1;	// 追加近接攻撃力

	/* モデルデータ設定 */
	std::shared_ptr<DataList_Model>	pDataList_Model = std::dynamic_pointer_cast<DataList_Model>(gpDataListServer->GetDataList("DataList_Model"));
	this->SetModelHandle(pDataList_Model->iGetModel("Monument_Sowrd/Monument_Sowrd"));
}
