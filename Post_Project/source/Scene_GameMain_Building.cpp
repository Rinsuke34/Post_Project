/* シーン"ゲームメイン(建築モード)"の提議 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_GameMain_Building.h"
// 関連クラス
#include "DataList_GameStatus.h"
#include "DataList_Object.h"
#include "Building_Monument_Sowrd.h"

// コンストラクタ
Scene_GameMain_Building::Scene_GameMain_Building() : Scene_Base("Scene_GameMain_Building", 1000, true, false)
{
	/* データリスト取得 */
	this->pDataList_GameStatus	= std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));		// ゲーム状態管理
	this->pDataList_Object		= std::dynamic_pointer_cast<DataList_Object>(gpDataListServer->GetDataList("DataList_Object"));				// オブジェクト管理

	/* 建築モードフラグを有効化 */
	this->pDataList_GameStatus->SetBuildModeFlg(true);
}

// デストラクタ
Scene_GameMain_Building::~Scene_GameMain_Building()
{
	/* 建築モードフラグを無効化 */
	this->pDataList_GameStatus->SetBuildModeFlg(false);
}

// 更新
void Scene_GameMain_Building::Update()
{	
	/* Escキーが入力されたならシーンを終了する */
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_ESCAPE] == TRUE)
	{
		/* シーンを削除(ゲームメインシーンに遷移) */
		this->bDeleteFlg = true;
		return;
	}

	/* 選択している建築エリアの変更 */
	Update_Change_SelectBuildingArea();

	/* 建築物の配置 */
	Update_BuildingPlacement();
}

// 描画
void Scene_GameMain_Building::Draw()
{
	/* 建築物一覧を描写 */
}

// 選択している建築エリアの変更
void Scene_GameMain_Building::Update_Change_SelectBuildingArea()
{
	/* 入力に応じて選択中の建築エリアを切り替える */
	// 現在のインデックス番号を取得
	int iNowIndex = this->pDataList_GameStatus->GetSelectedBuildingIndex();

	// 入力に応じてインデックス番号を変更
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_A] == TRUE)	{ iNowIndex--; }
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_D] == TRUE)	{ iNowIndex++; }

	// インデックス番号が範囲外の場合はループさせる
	if (iNowIndex < 0) { iNowIndex = static_cast<int>(this->pDataList_GameStatus->GetBuildAreaPositionList().size()) - 1; }
	if (iNowIndex >= static_cast<int>(this->pDataList_GameStatus->GetBuildAreaPositionList().size())) { iNowIndex = 0; }

	// インデックス番号を設定
	this->pDataList_GameStatus->SetSelectedBuildingIndex(iNowIndex);
}

// 建築物の配置
void Scene_GameMain_Building::Update_BuildingPlacement()
{
	/* 配置する建築物を切り替える */
	// 入力に応じてインデックス番号を変更
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_W] == TRUE) { this->iPlacementBuildingIndex--; }
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_S] == TRUE) { this->iPlacementBuildingIndex++; }

	// インデックス番号が範囲外の場合はループさせる
	if (this->iPlacementBuildingIndex < 0) { this->iPlacementBuildingIndex = BUILDING_MAX - 1; }
	if (this->iPlacementBuildingIndex >= BUILDING_MAX) { this->iPlacementBuildingIndex = 0; }

	/* 建築物の配置 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_SPACE] == TRUE)
	{
		// Spaceキーが押された場合
		/* 選択中の建築エリアに建造物がないか確認 */
		if (this->pDataList_GameStatus->GetBuildAreaPosition(this->pDataList_GameStatus->GetSelectedBuildingIndex()).pBuilding == nullptr)
		{
			// 建築物がない(建築可能である)場合
			/* 建築物を配置 */

			switch (this->iPlacementBuildingIndex)
			{
				case BUILDING_MONUMENT_SOWRD:	// モニュメント(剣)
				{
					/* 建築物を生成 */
					std::shared_ptr<Building_Monument_Sowrd> pBuilding = std::make_shared<Building_Monument_Sowrd>();
					pBuilding->SetPosition(this->pDataList_GameStatus->GetBuildAreaPosition(this->pDataList_GameStatus->GetSelectedBuildingIndex()).vecPosition);
					pBuilding->InitialSetup();

					/* 建造物をデータリストに設定 */
					// オブジェクト管理
					this->pDataList_Object->AddObject_Building(pBuilding);
					// ゲーム状態管理
					BUILDING_AREA_DATA AreaData	= this->pDataList_GameStatus->GetBuildAreaPosition(this->pDataList_GameStatus->GetSelectedBuildingIndex());
					AreaData.pBuilding			= pBuilding;
					this->pDataList_GameStatus->SetBuildAreaPosition(this->pDataList_GameStatus->GetSelectedBuildingIndex(), AreaData);
				}
				break;
			}
		}
	}
}
