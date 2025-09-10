/* 地形(マーカー)クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Ground_Base.h"

// 地形(マーカー)クラス
class Ground_Marker : public Ground_Base
{
	public:
		Ground_Marker();				// コンストラクタ
		virtual ~Ground_Marker() {};	// デストラクタ

		/* セッター */
		void SetMarkerName(const std::string& cMarkerName)	{ this->MarkerName			= cMarkerName; }	// マーカー名を設定
		void SetBoxCenter(VECTOR vecBoxCenter)				{ this->stBox.vecBoxCenter	= vecBoxCenter; }	// コリジョンの中心座標を設定
		void SetRotation(VECTOR vecRotation)				{ this->vecRotation			= vecRotation; }	// 回転量を設定

		/* ゲッター */
		std::string GetMarkerName()		{ return this->MarkerName; }			// マーカー名を取得
		VECTOR		vecGetBoxCenter()	{ return this->stBox.vecBoxCenter; }	// コリジョンの中心座標を取得
		VECTOR		vecGetRotation()	{ return this->vecRotation; }			// 回転量を取得

	private:
		/* 変数 */
		std::string MarkerName;		// マーカー名
		VECTOR		vecRotation;	// 回転量
};
