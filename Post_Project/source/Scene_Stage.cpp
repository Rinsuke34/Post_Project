/* シーン"ステージ"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_Stage.h"
// 関連クラス
#include "DataList_Object.h"
#include "DataList_GameStatus.h"
// 共通定義
#include "ConstantDefine.h"

// コンストラクタ
Scene_Stage::Scene_Stage() : Scene_Base("Scene_Stage", 1, false, false)
{
	/* 画像データ作成 */
	// 画像
	this->iScreenHandle_Stage		= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	// シャドウマップ
	this->iScreenHandle_ShadowMap[SHADOWMAP_GROUND]	= MakeShadowMap(SHADOW_GROUND_MAP_SIZE_WIDE, SHADOW_GROUND_MAP_SIZE_HEIGHT);
	this->iScreenHandle_ShadowMap[SHADOWMAP_ACTOR]	= MakeShadowMap(SHADOW_ACTOR_MAP_SIZE_WIDE, SHADOW_ACTOR_MAP_SIZE_HEIGHT);

	/* データリスト取得 */
	this->pDataList_Object		= std::dynamic_pointer_cast<DataList_Object>(gpDataListServer->GetDataList("DataList_Object"));			// オブジェクト管理
	this->pDataList_GameStatus	= std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));	// ゲーム状態管理

	/* テクスチャ読み込み */
	JsonLoad_Texture();

	/* ワールドマップ(中央)読み込み */
	JsonLoad_WoldMap_Center();
}

// デストラクタ
Scene_Stage::~Scene_Stage()
{
	/* 画像データ削除 */
	// 画像
	DeleteGraph(this->iScreenHandle_Stage);
	// シャドウマップ
	DeleteShadowMap(this->iScreenHandle_ShadowMap[SHADOWMAP_GROUND]);
	DeleteShadowMap(this->iScreenHandle_ShadowMap[SHADOWMAP_ACTOR]);
}

// 更新
void Scene_Stage::Update()
{

}

