/* 2024.12.08 駒沢風助 ファイル作成 */

#include "DataListBase.h"

/* すべてのデータ制御処理のベースとなるクラスの定義 */

// コンストラクタ
DataListBase::DataListBase(const std::string& cName)
{
	// 引数
	// cName					<- データリストの名前

	/* 初期化処理 */
	// DataListServerでの管理用データ
	this->stDataListName	= cName;					// データリスト名を設定
}
