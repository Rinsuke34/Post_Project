/* シーン"UI:ゲーム内リソース"の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"

/* 前方宣言 */
class DataList_GameStatus;

// シーン"UI:プレイヤーの状態"
class Scene_GameMain_UI_Resource : public Scene_Base
{
	public:
		Scene_GameMain_UI_Resource();				// コンストラクタ
		virtual ~Scene_GameMain_UI_Resource() {};	// デストラクタ

		/* 関数 */
		virtual void	Draw()				override;	// 描画

	private:
		/* 定数 */
		// コイン描写
		static const int UI_COIN_POS_X			= 10;	// コインのX座標
		static const int UI_COIN_POS_Y			= 310;	// コインのY座標
		static const int UI_COIN_POS_X_BUILDING	= 100;	// 建築モード時のコインのX座標
		static const int UI_COIN_POS_Y_BUILDING	= 236;	// 建築モード時のコインのX座標
		// スコア描写
		static const int UI_SCORE_POS_X	= 1480;	// スコアのX座標
		static const int UI_SCORE_POS_Y	= 100;	// スコアのY座標
		// ウェーブ描写
		static const int UI_WAVE_POS_X	= 1480;	// ウェーブのX座標
		static const int UI_WAVE_POS_Y	= 150;	// ウェーブのY座標
		// スコア・ウェーブの背景
		static const int UI_BACKGROUND_WIDE			= 200;	// 背景部分の幅
		static const int UI_BACKGROUND_HEIGHT		= 32;	// 背景部分の高さ
		static const int UI_BACKGROUND_BACK_WIDE	= 5;	// 背景の幅

		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_GameStatus>	pDataList_GameStatus;	// ゲーム状態管理
		// 描画系
		std::shared_ptr<int>					piGrHandle_Coin;		// コインの画像
};
