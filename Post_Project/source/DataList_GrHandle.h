/* データリスト"画像データ管理"クラスの宣言 */

#pragma once
#include "AppFrame.h"

// データリスト"画像データ管理"クラス
class DataList_GrHandle : public DataList_Base
{
	public:
		DataList_GrHandle();			// コンストラクタ
		virtual ~DataList_GrHandle();	// デストラクタ

		/* 関数 */
		void	LoadGrHandle(std::string& cFileName);				// 画像データ読み込み
		void	LoadGrHandle_2DPartsAnim(std::string& cFileName);	// 画像データ読み込み(2Dパーツアニメーション用)
		int		iGetGrhandle(std::string& cFileName);				// 画像データ取得

	private:
		/* 変数 */
		// リスト
		std::map<std::string, int> pGrHandleList;		// 画像データリスト

		/* 関数 */
		bool	bCheckGrHandle(std::string& cFileName);	// 該当画像ハンドルデータ存在確認
};
