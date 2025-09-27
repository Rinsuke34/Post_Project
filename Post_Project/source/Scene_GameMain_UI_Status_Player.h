/* シーン"UI:プレイヤーの状態"の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"

/* 前方宣言 */
class DataList_GameStatus;

// シーン"UI:プレイヤーの状態"
class Scene_GameMain_UI_Status_Player : public Scene_Base
{
	public:
		Scene_GameMain_UI_Status_Player();				// コンストラクタ
		virtual ~Scene_GameMain_UI_Status_Player() {};	// デストラクタ

		/* 関数 */
		virtual void	Draw()				override;	// 描画

	private:
		/* 定数 */
		// 武器の種類
		static const int WEPON_SOWRD	= 0;	// 剣
		static const int WEPON_ROD		= 1;	// 杖
		static const int WEPON_MAX		= 2;	// 総数
		// キーの種類
		static const int KEY_E			= 0;
		static const int KEY_Q			= 1;
		static const int KEY_MAX		= 2;
		// UI用の座標
		// 現在の武器
		static const int UI_WEPON_NOW_POS_X			= 10;	// 現在の武器のX座標
		static const int UI_WEPON_NOW_POS_Y			= 878;	// 現在の武器のY座標
		static const int UI_WEPON_NOW_WIDE			= 192;	// 現在の武器の幅
		static const int UI_WEPON_NOW_HEIGHT		= 192;	// H現在の武器の高さ
		static const int UI_WEPON_NOW_BACK_WIDE		= 5;	// 背景の幅
		// 切り替え先の武器
		static const int UI_WEPON_NEXT_POS_X		= 10;	// 切り替え先の武器のX座標
		static const int UI_WEPON_NEXT_POS_Y		= 777;	// 切り替え先の武器のY座標
		static const int UI_WEPON_NEXT_WIDE			= 96;	// 切り替え先の武器の幅
		static const int UI_WEPON_NEXT_HEIGHT		= 96;	// 切り替え先の武器の高さ
		static const int UI_WEPON_NEXT_BACK_WIDE	= 5;	// 背景の幅
		// 建築モード
		static const int UI_BUILDING_POS_X			= 1782;	// 建築アイコンのX座標
		static const int UI_BUILDING_POS_Y			= 942;	// 建築アイコンのY座標
		static const int UI_BUILDING_WIDE			= 128;	// 建築アイコンの幅
		static const int UI_BUILDING_HEIGHT			= 128;	// 建築アイコンの高さ
		static const int UI_BUILDING_BACK_WIDE		= 5;	// 背景の幅
		// HP表示
		static const int UI_HPBAR_POS_X		= 212;	// HPバーのX座標
		static const int UI_HPBAR_POS_Y		= 944;	// HPバーのY座標
		static const int UI_HPBAR_WIDE		= 500;	// HPバーの幅
		static const int UI_HPBAR_HEIGHT	= 60;	// HPバーの高さ
		static const int UI_HPBAR_BACK_WIDE = 5;	// 背景の幅

		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_GameStatus>	pDataList_GameStatus;			// ゲーム状態管理		
		// 描画系
		std::shared_ptr<int>					piGrHandle_Wepon[WEPON_MAX];	// 武器の画像
		std::shared_ptr<int>					piGrHandle_Building;			// 建築アイコン
		std::shared_ptr<int>					piKey[KEY_MAX];					// キー
		std::shared_ptr<int>					piGrHandle_NG;					// NGアイコン
};
