/* 建造物(神木(防衛対象))クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Building_Base.h"

/* 前方宣言 */
class DataList_Object;

// 建造物(神木(防衛対象))クラス
class Building_CoreTree : public Building_Base
{
	public:
		Building_CoreTree();				// コンストラクタ
		virtual ~Building_CoreTree() {};	// デストラクタ

		/* 関数 */
		virtual void	InitialSetup()		override;	// 初期設定
		virtual void	Update()			override;	// 更新

		/* セッター */
		void SetHP(int iHP);									// 体力を設定
		void SetMaxHP(int iMaxHp)	{ this->iMaxHp = iMaxHp; };	// 最大体力を設定

		/* ゲッター */
		int iGetHP()		{ return this->iHp; }		// 体力を取得
		int iGetMaxHP()		{ return this->iMaxHp; }	// 最大体力を取得

	private:
		/* 変数 */
		// 状態系
		int										iHp;					// 体力
		int										iMaxHp;					// 最大体力
};
