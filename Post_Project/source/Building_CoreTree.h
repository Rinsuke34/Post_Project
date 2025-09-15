/* 建造物(神木(防衛対象))クラスの宣言 */
// ※ 建造物は押し出し判定を持つため、Ground_Modelクラスを継承して作成

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Ground_Model.h"

/* 前方宣言 */
class DataList_Object;
class DataList_GameStatus;

// 建造物(神木(防衛対象))クラス
class Building_CoreTree : public Ground_Model
{
	public:
		Building_CoreTree();			// コンストラクタ
		virtual ~Building_CoreTree();	// デストラクタ

		/* 定数 */
		static const int CORETREE_SIZE_X = 64 * 3;		// X軸の神木(防衛対象)の大きさ
		static const int CORETREE_SIZE_Y = 32 * 8;		// Y軸の神木(防衛対象)の大きさ
		static const int CORETREE_SIZE_Z = 64 * 3;		// Z軸の神木(防衛対象)の大きさ

		/* 関数 */
		virtual void	InitialSetup()		override;	// 初期設定
		virtual void	Update()			override;	// 更新
		virtual void	Draw_Collision()	override;	// 描画(当たり判定)

		/* セッター */
		void SetHP(int iHP);									// 体力を設定
		void SetMaxHP(int iMaxHp)	{ this->iMaxHp = iMaxHp; };	// 最大体力を設定

		/* ゲッター */
		int iGetHP()		{ return this->iHp; }		// 体力を取得
		int iGetMaxHP()		{ return this->iMaxHp; }	// 最大体力を取得

	private:
		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_Object>		pDataList_Object;		// オブジェクト管理
		std::shared_ptr<DataList_GameStatus>	pDataList_GameStatus;	// ゲーム状態管理
		// 状態系
		int										iHp;					// 体力
		int										iMaxHp;					// 最大体力
};
