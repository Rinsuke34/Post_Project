/* 地形のベースクラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Object_Base.h"
// 共通定義
#include "AppFrame.h"

// 地形ベースクラス
class Ground_Base : public Object_Base
{
	public:
		Ground_Base();					// コンストラクタ
		virtual ~Ground_Base() {};		// デストラクタ

		/* 関数 */
		// コリジョン接触判定
		virtual bool HitCheck(Struct_Collision::COLLISION_SQHERE	stSqhere);	// 球体
		virtual bool HitCheck(Struct_Collision::COLLISION_LINE		stLine);	// 線分
		virtual bool HitCheck(Struct_Collision::COLLISION_BOX		stBox);		// ボックス
		// 衝突点取得(線分 - ブロック)
		virtual VECTOR HitPosition(Struct_Collision::COLLISION_LINE	stLine);	// 線分

		/* セッター */
		void SetBoxCollision(Struct_Collision::COLLISION_BOX stBox)	{ this->stBox = stBox; }	// ボックスコリジョンの情報を設定

		/* ゲッター */
		Struct_Collision::COLLISION_BOX GetBoxCollision()			{ return stBox; }			// ボックスコリジョンの情報を取得

	protected:
		Struct_Collision::COLLISION_BOX	stBox;							// ボックスコリジョンの情報
};
