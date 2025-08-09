/* データリストのベースとなるクラスの定義 */

#include "DataListBase.h"

// コンストラクタ
DataListBase::DataListBase(const std::string& cName)
{
	// 引数
	// cName					<- データリストの名前

	/* 初期化処理 */
	// DataListServerでの管理用データ
	this->stDataListName	= cName;					// データリスト名を設定
}
