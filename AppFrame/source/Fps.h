/* 2024.12.08 駒沢風助 ファイル作成 */

#pragma once
#include "DxLib.h"

/* フレームレート固定クラスの宣言 */

// フレームレート固定クラス
class Fps
{
	public:
		Fps();				// コンストラクタ
		virtual ~Fps() {};	// デストラクタ

		void	FpsAdjustment();		// フレームレート調整処理
		void	DrawFPS();				// フレームレート描画(デバッグ用)

	private:
		/* 関数 */
		void FpsUpdate();				// 時刻計算
		void FpsWait();					// フレームレート調整のため待機

		/* 変数 */
		int iStartTime;					// 測定開始時刻
		int iCount;						// カウンタ

};
