/* データリスト"ゲーム状態管理"クラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "DataList_GameStatus.h"

// コンストラクタ
DataList_GameStatus::DataList_GameStatus() : DataList_Base("DataList_GameStatus")
{
	/* 初期化 */
	this->vecPlayerPosition_WoldMap = VGet(0.0f, 0.0f, 0.0f);
}

// デストラクタ
DataList_GameStatus::~DataList_GameStatus()
{

}
