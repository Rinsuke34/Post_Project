/* シーン"UI:神木(防衛対象)の状態"の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"

/* 前方宣言 */
class DataList_GameStatus;

// シーン"UI:神木(防衛対象)の状態"
class Scene_GameMain_UI_Status_CoreTree : public Scene_Base
{
	public:
		Scene_GameMain_UI_Status_CoreTree();				// コンストラクタ
		virtual ~Scene_GameMain_UI_Status_CoreTree() {};	// デストラクタ

		/* 関数 */
		virtual void	Draw()				override;	// 描画

	private:
		/* 定数 */
		// UI用の座標
		static const int UI_HPBAR_POS_X		= 70;	// HPバーのX座標
		static const int UI_HPBAR_POS_Y		= 155;	// HPバーのY座標
		static const int UI_HPBAR_WIDE		= 500;	// HPバーの幅
		static const int UI_HPBAR_HEIGHT	= 60;	// HPバーの高さ
		static const int UI_HPBAR_BACK_WIDE	= 5;	// 背景の幅

		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_GameStatus>	pDataList_GameStatus;	// ゲーム状態管理		
		// 描画系
		std::shared_ptr<int>					piGrHandle_TreeImage;	// 木の画像
};
