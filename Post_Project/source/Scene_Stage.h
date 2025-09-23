/* シーン"ステージ"の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"
#include "StructDefine.h"

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
		// エネミーのスポーン頻度
		static const int ENEMY_SPAWN_TIME_BASE = 60 * 10;	// 基本のスポーン頻度(10秒/フレーム数)

		/* 関数 */
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描画

	private:
		/* 関数 */
		// 読み込み関係
		void	JsonLoad_WoldMapList();								// ワールドマップリスト読み込み
		void	JsonLoad_WoldMap(int iAreaNo, std::string MapName);	// ワールドマップを読み込む
		void	JsonLoad_EnemySpawnTable();							// エネミーのスポーンテーブル読み込み
		// 描写関係
		void	DrawSetup_CameraPosition();		// カメラ設定
		void	DrawSetup_ShadowMap();			// シャドウマップ作成
		void	DrawSetup_Stage();				// ステージの描写
		void	DrawSetup_Stage_StageCreate();	// ステージの描写(ステージクリエイト用)
		// 設定関係
		void	Setup_LoadMarker_CenterArea();	// マーカー情報読み込み(中央エリア)
		void	Setup_LoadMarker_SideArea();	// マーカー情報読み込み(外側エリア)
		void	Setup_WoldMap_SideArea();		// ワールドマップ(外側エリア)設定
		void	Setup_PlaceObject_CenterArea();	// オブジェクト配置(中央エリア)
		void	Setup_PlaceObject_SideArea();	// オブジェクト配置(外側エリア)
		
		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_Object>		pDataList_Object;		// オブジェクト管理
		std::shared_ptr<DataList_GameStatus>	pDataList_GameStatus;	// ゲーム状態管理
		std::shared_ptr<DataList_StageCreate>	pDataList_StageCreate;	// ステージクリエイト情報管理
		// 画像データ
		int iScreenHandle_Stage;					// ステージ
		int iScreenHandle_ShadowMap[SHADOWMAP_MAX];	// シャドウマップ(0:静的オブジェクト/1:動的オブジェクト)
		// マップの情報
		std::vector<WOLD_MAP_DATA>	MapDataList;	// マップ情報リスト
		// その他
		int iEnemySpawnTime;	// エネミーのスポーンまでの待機時間
};
