/* シーン"ステージ"の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"

/* 前方宣言 */
class DataList_Object;
class DataList_GameStatus;
class DataList_StageCreate;

// シーン"ステージ"
class Scene_Stage : public Scene_Base
{
	public:
		Scene_Stage();				// コンストラクタ
		virtual ~Scene_Stage();		// デストラクタ

		/* クラス内で使用する定数 */
		// シャドウマップの種類
		static const int SHADOWMAP_GROUND	= 0;	// 静的オブジェクト
		static const int SHADOWMAP_ACTOR	= 1;	// 動的オブジェクト
		static const int SHADOWMAP_MAX		= 2;	// シャドウマップの種類の個数

		/* 関数 */
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描画

	private:
		/* 関数 */
		// 読み込み関係
		void	JsonLoad_WoldMap_Center();	// ワールドマップ読み込み(中央)
		void	JsonLoad_DungeonMap();		// ダンジョンマップ読み込み
		// 描写関係
		void	DrawSetup_CameraPosition();		// カメラ設定
		void	DrawSetup_ShadowMap();			// シャドウマップ作成
		void	DrawSetup_Stage();				// ステージの描写
		void	DrawSetup_Stage_StageCreate();	// ステージの描写(ステージクリエイト用)
		

		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_Object>		pDataList_Object;		// オブジェクト管理
		std::shared_ptr<DataList_GameStatus>	pDataList_GameStatus;	// ゲーム状態管理
		std::shared_ptr<DataList_StageCreate>	pDataList_StageCreate;	// ステージクリエイト情報管理
		// 画像データ
		int iScreenHandle_Stage;					// ステージ
		int iScreenHandle_ShadowMap[SHADOWMAP_MAX];	// シャドウマップ(0:静的オブジェクト/1:動的オブジェクト)
};
