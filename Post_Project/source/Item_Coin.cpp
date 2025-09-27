/* アイテム"コイン"クラスの提議 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Item_Coin.h"
// 関連クラス
#include "DataList_GameStatus.h"
#include "DataList_Image.h"
#include "DataList_Sound.h"

// コンストラクタ
Item_Coin::Item_Coin() : Item_Base()
{
	/* データリスト取得 */
	this->pDataList_Sound							= std::dynamic_pointer_cast<DataList_Sound>(gpDataListServer->GetDataList("DataList_Sound"));	// サウンド管理
	std::shared_ptr<DataList_Image>	pDataList_Image	= std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));	// 画像データ管理

	/* 使用する画像を設定 */
	std::string fileName = "ItemImage/Coin";
	this->piGrHandle = pDataList_Image->iGetGrhandle(fileName);
}

// アイテム取得時の更新処理
void Item_Coin::Update_ItemGet()
{
	/* コインの枚数を加算する */
	int iHaveCoin = this->pDataList_GameStatus->GetHaveCoin();
	iHaveCoin++;
	this->pDataList_GameStatus->SetHaveCoin(iHaveCoin);

	/* コイン取得音を再生 */
	this->pDataList_Sound->SE_Play("GetCoin");
}
