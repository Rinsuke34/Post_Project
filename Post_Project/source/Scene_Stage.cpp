/* シーン"ステージ"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_Stage.h"
// 関連クラス
#include "DataList_Image.h"
#include "DataList_Object.h"
#include "DataList_GameStatus.h"
#include "DataList_StageCreate.h"
// 共通定義
#include "ConstantDefine.h"

// コンストラクタ
Scene_Stage::Scene_Stage() : Scene_Base("Scene_Stage", 1, false, false)
{
	/* 初期化 */
	this->iEnemySpawnTime = 0;

	/* データリスト取得 */
	this->pDataList_Object							= std::dynamic_pointer_cast<DataList_Object>(gpDataListServer->GetDataList("DataList_Object"));				// オブジェクト管理
	this->pDataList_GameStatus						= std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));		// ゲーム状態管理
	this->pDataList_StageCreate						= std::dynamic_pointer_cast<DataList_StageCreate>(gpDataListServer->GetDataList("DataList_StageCreate"));	// ステージクリエイト情報管理
	std::shared_ptr<DataList_Image>	pDataList_Image	= std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));				// 画像管理

	/* 画像データ作成 */
	// 画像
	this->iScreenHandle_Stage						= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, TRUE);
	// シャドウマップ
	this->iScreenHandle_ShadowMap[SHADOWMAP_GROUND]	= MakeShadowMap(SHADOW_GROUND_MAP_SIZE_WIDE, SHADOW_GROUND_MAP_SIZE_HEIGHT);
	this->iScreenHandle_ShadowMap[SHADOWMAP_ACTOR]	= MakeShadowMap(SHADOW_ACTOR_MAP_SIZE_WIDE, SHADOW_ACTOR_MAP_SIZE_HEIGHT);

	/* 使用する画像を設定 */
	// 空の画像
	std::string fileName = "Sky/Sky";
	this->piGrHandle_Sky = pDataList_Image->iGetGrhandle(fileName);

	/* ゲーム状態管理データリストが読み込まれているか確認 */
	// ※ゲーム状態管理データリストがある場合、ゲームメインから遷移してきたと判断
	if (this->pDataList_GameStatus != nullptr)
	{
		// 読み込まれている場合
		/* ワールドマップリスト読み込み */
		JsonLoad_WoldMapList();

		/* エネミーのスポーンテーブル読み込み */
		JsonLoad_EnemySpawnTable();

		/* ワールドマップ(中央)読み込み */
		JsonLoad_WoldMap(AREA_NO_CENTER, "AreaData_Front");

		/* ワールドマップ(外側)読み込み */
		Setup_WoldMap_SideArea();

		/* マーカー情報読み込み */
		Setup_LoadMarker_CenterArea();
		Setup_LoadMarker_SideArea();

		/* オブジェクト配置 */
		// ※中央エリア部分のみ先行して配置し、外側エリア部分はエネミースポーンのタイミングで配置する
		Setup_PlaceObject_CenterArea();
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
	/* ステージクリエイト情報管理データリストが読み込まれているか確認 */
	// ※ステージクリエイト情報管理データリストがある場合、ステージクリエイトから遷移してきたと判断
	if (this->pDataList_StageCreate != nullptr)
	{
		// 読み込まれている場合
		if (gstKeyboardInputData.cgInput[INPUT_REL][KEY_INPUT_ESCAPE] == TRUE)
		{
			/* シーンを削除(ステージ作成シーンに遷移) */
			this->bDeleteFlg = true;
		}
	}
	else
	{
		// 読み込まれていない場合
		/* エネミーのスポーン更新 */
		if (this->iEnemySpawnTime <= 0)
		{
			// カウントが0以下であるならば
			/* エネミーをスポーン */
			Setup_PlaceObject_SideArea();

			/* 次のエネミースポーンまでのカウントをリセット */
			this->iEnemySpawnTime = ENEMY_SPAWN_TIME_BASE;
		}
		else
		{
			// カウントが0以下でないならば
			this->iEnemySpawnTime--;
		}
	}
}
