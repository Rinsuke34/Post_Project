/* 建造物(モニュメント)クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Building_Base.h"

// 建造物(モニュメント)クラス
class Building_Monument : public Building_Base
{
	public:
		Building_Monument();				// コンストラクタ
		virtual ~Building_Monument() {};	// デストラクタ

		/* 関数 */
		virtual void	InitialSetup()		override;	// 初期設定

		/* セッター */
		void SetMonumentName(const std::string& Name) { this->MonumentName = Name; }	// モニュメント名を設定

		/* ゲッター */
		std::string GetMonumentName() { return this->MonumentName; }			// モニュメント名を取得

	private:
		/* 変数 */
		std::string MonumentName;	// モニュメント名
};
