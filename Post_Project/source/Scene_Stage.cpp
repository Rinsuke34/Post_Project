/* シーン"ステージ"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_Stage.h"
// 関連クラス
#include "DataList_Object.h"
#include "DataList_GameStatus.h"
#include "DataList_StageCreate.h"
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
	this->pDataList_Object		= std::dynamic_pointer_cast<DataList_Object>(gpDataListServer->GetDataList("DataList_Object"));				// オブジェクト管理
	this->pDataList_GameStatus	= std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));		// ゲーム状態管理
	this->pDataList_StageCreate = std::dynamic_pointer_cast<DataList_StageCreate>(gpDataListServer->GetDataList("DataList_StageCreate"));	// ステージクリエイト情報管理

	std::shared_ptr<DataList_StageCreate>	pDataList_StageCreate;	// ステージクリエイト情報管理

	/* ゲーム状態管理データリストが読み込まれているか確認 */
	if (this->pDataList_GameStatus != nullptr)
	{
		// 読み込まれている場合
		/* ワールドマップ(中央)読み込み */
		JsonLoad_WoldMap_Center();
	}
	/* ステージクリエイト情報管理データリストが読み込まれているか確認 */
	else if (this->pDataList_StageCreate != nullptr)
	{
		// 読み込まれている場合

	}	
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

