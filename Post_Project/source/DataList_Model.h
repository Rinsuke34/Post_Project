/* データリスト"3Dモデル管理"クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"

// データリスト"3Dモデル管理"クラス
class DataList_Model : public DataList_Base
{
	public:
		DataList_Model();			// コンストラクタ
		virtual ~DataList_Model();	// デストラクタ

		/* 関数 */
		void	LoadModel(std::string modelName);			// 3Dモデルロード(事前読み込み用)
		int		iGetModel(std::string modelName);			// 3Dモデル取得

	private:
		/* 変数 */
		// リスト
		std::map<std::string, int>	ModelHandleList;		// 3Dモデルリスト

		/* 関数 */
		bool	bCheckModel(std::string modelName);			// 該当3Dモデル存在確認
};
