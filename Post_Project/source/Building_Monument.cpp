/* 建造物(モニュメント)クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Building_Monument.h"
// 関連クラス
#include "DataList_Model.h"

// コンストラクタ
Building_Monument::Building_Monument() : Building_Base()
{

}

// 初期設定
void Building_Monument::InitialSetup()
{
	/* モデルデータ設定 */
	std::shared_ptr<DataList_Model>	pDataList_Model = std::dynamic_pointer_cast<DataList_Model>(gpDataListServer->GetDataList("DataList_Model"));
	std::string FileName = "Monument/" + MonumentName;
	this->SetModelHandle(pDataList_Model->iGetModel(FileName));

	/* 親クラスの初期化処理 */
	Building_Base::InitialSetup();
}
