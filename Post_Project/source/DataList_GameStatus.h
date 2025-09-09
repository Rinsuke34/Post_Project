/* データリスト"ゲーム状態管理"クラスの宣言 */

#pragma once
/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"

// データリスト"ゲーム状態管理"クラス
class DataList_GameStatus : public DataList_Base
{
	public:
		DataList_GameStatus();			// コンストラクタ
		virtual ~DataList_GameStatus();	// デストラクタ

		/* セッター */
		void SetPlayerPosition_WoldMap(VECTOR vecPosition)	{ this->vecPlayerPosition_WoldMap = vecPosition; }	// プレイヤーのワールドマップ座標の設定

		/* ゲッター */
		VECTOR GetPlayerPosition_WoldMap()					{ return this->vecPlayerPosition_WoldMap; }			// プレイヤーのワールドマップ座標の取得

	private:
		/* 変数 */
		VECTOR	vecPlayerPosition_WoldMap;	// プレイヤーのワールドマップ座標
};
