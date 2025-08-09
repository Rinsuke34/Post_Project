/* 2024.12.12 駒沢風助 ファイル作成 */

#pragma once
#include <DxLib.h>
#include <string>

/* すべてのデータ制御処理のベースとなるクラスの宣言 */

// データリストベースクラス
class DataListBase
{
	public:
		DataListBase(const std::string& cName);		// コンストラクタ
		virtual ~DataListBase() {};					// デストラクタ

		std::string	stGetDataListName()	{ return this->stDataListName; }	// データリスト名称を取得

	private:
	protected:

		/* 変数 */
		// DataListServerでの管理用データ
		std::string		stDataListName;			// データリスト名称
};
