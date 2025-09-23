/* シーン"ゲームメイン(建築モード)"の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"

/* 前方宣言 */
class DataList_GameStatus;
class DataList_Object;

// シーン"ゲームメイン(建築モード)"
class Scene_GameMain_Building : public Scene_Base
{
	public:
		Scene_GameMain_Building();			// コンストラクタ
		virtual ~Scene_GameMain_Building();	// デストラクタ

		/* 定数 */
		static const int BUILDING_MONUMENT_SOWRD	= 0;	// モニュメント(剣)
		static const int BUILDING_MONUMENT_ROD		= 1;	// モニュメント(杖)
		static const int BUILDING_NPCBASE_SLIME		= 2;	// NPC拠点(スライム)
		static const int BUILDING_NPCBASE_WISP		= 3;	// NPC拠点(ウィスプ)
		static const int BUILDING_MAX				= 4;	// 建築物の総数
		// UI用の座標
		static const int UI_BUILDING_POS_X			= 100;	// 建築物選択のX座標
		static const int UI_BUILDING_POS_Y			= 300;	// 建築物選択のY座標
		static const int UI_BUILDING_WIDE			= 500;	// 建築物選択の幅
		static const int UI_BUILDING_HEIGHT			= 80;	// 建築物選択の高さ
		static const int UI_BUILDING_BACK_WIDE		= 5;	// 背景の幅
		static const int UI_BUILDING_PRICE_WIDE_X	= 150;	// 建築物の値段の幅

		/* 関数 */
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描画

	private:
		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_GameStatus>	pDataList_GameStatus;			// ゲーム状態管理
		std::shared_ptr<DataList_Object>		pDataList_Object;				// オブジェクト管理
		// 選択状態
		int										iPlacementBuildingIndex;		// 配置予定の建築物の番号
		// 描画系
		std::shared_ptr<int>					piGrHandle_Coin;				// コインの画像
		// 状態系
		int										iBuildingPrice[BUILDING_MAX];	// 各建築物の値段

		/* 関数 */
		void Update_Change_SelectBuildingArea();	// 選択している建築エリアの変更
		void Update_BuildingPlacement();			// 建築物の配置
};
