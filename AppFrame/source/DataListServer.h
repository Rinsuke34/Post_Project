/* 2024.12.12 駒沢風助 ファイル作成 */

#pragma once
#include "DataListBase.h"
#include <list>

/* データ制御処理の管理を行うクラスの宣言 */

// データリストサーバークラス
class DataListServer
{
	public:
		DataListServer();				// コンストラクタ
		virtual ~DataListServer();		// デストラクタ

		void	DrawDataList();			// データリスト描画(デバッグ用)

		void			AddDataList(DataListBase* NewDataList);		// データリスト追加
		void			DeleteDataList(const std::string& cName);	// 指定データリスト削除
		DataListBase*	GetDataList(const std::string& cName);		// データリスト取得

	private:
		// データリスト一覧
		std::list<DataListBase*> pstDataList;

		/* 関数 */
		void	DeleteAllDataList();			// データリスト削除(データリスト一覧内のすべてのデータリストに対して)

	protected:
};
