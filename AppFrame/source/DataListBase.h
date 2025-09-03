/* すべてのデータリストのベースとなるクラスの宣言 */

#pragma once
#include <DxLib.h>
#include <string>

// データリストベースクラス
class DataListBase
{
	public:
		DataListBase(const std::string& cName);		// コンストラクタ
		virtual ~DataListBase() {};					// デストラクタ

		/* ゲッター */
		std::string	stGetDataListName()	{ return this->stDataListName; }	// データリスト名称を取得

	private:

		/* 変数 */
		// DataListServerでの管理用データ
		std::string		stDataListName;			// データリスト名称
};
