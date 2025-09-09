/* データリスト"汎用2Dパーツアニメーションツール"クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "DataList_Base.h"
// 共通定義
#include "AppStructDefine.h"

// データリスト"汎用2Dパーツアニメーションツール"クラス
class DataList_2DPartsAnimCreateTool : public DataList_Base
{
	public:
		DataList_2DPartsAnimCreateTool();			// コンストラクタ
		virtual ~DataList_2DPartsAnimCreateTool();	// デストラクタ

		/* 定数 */
		static const int SCREEN_SIZE_WIDE	= 0;	// 描画用スクリーンの幅
		static const int SCREEN_SIZE_HEIGHT	= 1;	// 描画用スクリーンの高さ
		static const int SCREEN_SIZE_MAX	= 2;	// 描画用スクリーンのサイズの個数

		/* 関数 */
		void	DrawPartsAnim(std::string FileName, std::string AnimDame, int iFrame);		// パーツアニメーションの描画

		/* セッター */
		void	LoadPartsAnimData(std::string FileName);									// パーツアニメーションのデータ読み込み
		void	SetDrawScreenSize(int iWide, int iHeight);									// 描画用スクリーンのサイズ設定

		/* ゲッター */
		int		iGetPartsAnimMaxTime(std::string FileName, std::string AnimDame);			// パーツアニメーションの最大フレーム数取得

	private:
		/* 変数 */
		std::vector<Struct_2DPartsAnim::PARTS_ANIM_DATA>	PartsAnimDataList;					// パーツアニメーションの情報リスト
		int													iDrawScreenSize[SCREEN_SIZE_MAX];	// 描画用スクリーンのサイズ(0:幅, 1:高さ)
};
