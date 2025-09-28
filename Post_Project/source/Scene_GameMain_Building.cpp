/* シーン"ゲームメイン(建築モード)"の提議 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_GameMain_Building.h"
// 関連クラス
#include "DataList_Image.h"
#include "DataList_GameStatus.h"
#include "DataList_Object.h"
#include "DataList_Sound.h"
#include "Building_Monument.h"
#include "Building_NpcBase.h"

// コンストラクタ
Scene_GameMain_Building::Scene_GameMain_Building() : Scene_Base("Scene_GameMain_Building", 1000, true, false)
{
	/* データリスト取得 */
	this->pDataList_GameStatus						= std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));		// ゲーム状態管理
	this->pDataList_Object							= std::dynamic_pointer_cast<DataList_Object>(gpDataListServer->GetDataList("DataList_Object"));				// オブジェクト管理
	std::shared_ptr<DataList_Image>	pDataList_Image	= std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));				// 画像管理
	this->pDataList_Sound							= std::dynamic_pointer_cast<DataList_Sound>(gpDataListServer->GetDataList("DataList_Sound"));				// サウンド管理

	/* 建築モードフラグを有効化 */
	this->pDataList_GameStatus->SetBuildModeFlg(true);

	/* 初期化 */
	this->iPlacementBuildingIndex = 0;

	/* 使用する画像を設定 */
	// コインの画像
	std::string fileName = "ItemImage/Coin";
	this->piGrHandle_Coin = pDataList_Image->iGetGrhandle(fileName);
	// キーの画像
	fileName = "Key/E";
	this->piGrHandle_Key[KEY_E] = pDataList_Image->iGetGrhandle(fileName);
	fileName = "Key/Q";
	this->piGrHandle_Key[KEY_Q] = pDataList_Image->iGetGrhandle(fileName);
	fileName = "Key/W";
	this->piGrHandle_Key[KEY_W] = pDataList_Image->iGetGrhandle(fileName);
	fileName = "Key/A";
	this->piGrHandle_Key[KEY_A] = pDataList_Image->iGetGrhandle(fileName);
	fileName = "Key/S";
	this->piGrHandle_Key[KEY_S] = pDataList_Image->iGetGrhandle(fileName);
	fileName = "Key/D";
	this->piGrHandle_Key[KEY_D] = pDataList_Image->iGetGrhandle(fileName);

	/* 建築物のコスト設定 */	
	this->iBuildingPrice[BUILDING_MONUMENT_SOWRD]	= 3;	// モニュメント(剣)
	this->iBuildingPrice[BUILDING_MONUMENT_ROD]		= 3;	// モニュメント(杖)
	this->iBuildingPrice[BUILDING_NPCBASE_SLIME]	= 5;	// NPC拠点(スライム)
	this->iBuildingPrice[BUILDING_NPCBASE_WISP]		= 8;	// NPC拠点(ウィスプ)
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
	/* Qキーが入力されたならシーンを終了する */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_Q] == TRUE)
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
	/* 上方向と下方向の矢印、キーを描写 */
	// 上方向
	DrawTriangle(
		UI_TRIANGLE_CENTER_X, UI_BUILDING_POS_Y - UI_TRIANGLE_GAP - UI_TRIANGLE_HEIGHT,
		UI_TRIANGLE_CENTER_X - UI_TRIANGLE_WIDTH, UI_BUILDING_POS_Y - UI_TRIANGLE_GAP,
		UI_TRIANGLE_CENTER_X + UI_TRIANGLE_WIDTH, UI_BUILDING_POS_Y - UI_TRIANGLE_GAP,
		GetColor(255, 255, 0), TRUE);
	DrawExtendGraph(
		UI_TRIANGLE_CENTER_X + UI_TRIANGLE_WIDTH + UI_TRIANGLE_GAP,		UI_BUILDING_POS_Y - UI_TRIANGLE_GAP - UI_TRIANGLE_HEIGHT,
		UI_TRIANGLE_CENTER_X + UI_TRIANGLE_WIDTH + UI_TRIANGLE_GAP + UI_KEY_SIZE,	UI_BUILDING_POS_Y - UI_TRIANGLE_GAP,
		*(this->piGrHandle_Key[KEY_W]), TRUE);
	// 下方向
	DrawTriangle(
		UI_TRIANGLE_CENTER_X, UI_BUILDING_POS_Y + (BUILDING_MAX * UI_BUILDING_HEIGHT) + UI_TRIANGLE_GAP + UI_TRIANGLE_HEIGHT,
		UI_TRIANGLE_CENTER_X - UI_TRIANGLE_WIDTH, UI_BUILDING_POS_Y + (BUILDING_MAX * UI_BUILDING_HEIGHT) + UI_TRIANGLE_GAP,
		UI_TRIANGLE_CENTER_X + UI_TRIANGLE_WIDTH, UI_BUILDING_POS_Y + (BUILDING_MAX * UI_BUILDING_HEIGHT) + UI_TRIANGLE_GAP,
		GetColor(255, 255, 0), TRUE);
	DrawExtendGraph(
		UI_TRIANGLE_CENTER_X + UI_TRIANGLE_WIDTH + UI_TRIANGLE_GAP, UI_BUILDING_POS_Y + (BUILDING_MAX * UI_BUILDING_HEIGHT) + UI_TRIANGLE_GAP,
		UI_TRIANGLE_CENTER_X + UI_TRIANGLE_WIDTH + UI_TRIANGLE_GAP + UI_KEY_SIZE, UI_BUILDING_POS_Y + (BUILDING_MAX * UI_BUILDING_HEIGHT) + UI_TRIANGLE_GAP + UI_TRIANGLE_HEIGHT,
		*(this->piGrHandle_Key[KEY_S]), TRUE);

	/* 建築物一覧を描写 */
	for (int i = 0; i < BUILDING_MAX; i++)
	{
		/* 描写地点を取得 */
		int iPosX = UI_BUILDING_POS_X;
		int iPosY = UI_BUILDING_POS_Y + (i * UI_BUILDING_HEIGHT);

		/* オブジェクト名の背景描写 */
		// ※ 選択中の建築物であるならば黄色で描写
		DrawBox(iPosX, iPosY, iPosX + UI_BUILDING_WIDE, iPosY + UI_BUILDING_HEIGHT, GetColor(0, 0, 0), TRUE);
		int iFrameColor = GetColor(255, 255, 255);
		if (i == this->iPlacementBuildingIndex) { iFrameColor = GetColor(255, 255, 0); }
		DrawBox(iPosX + UI_BUILDING_BACK_WIDE, iPosY + UI_BUILDING_BACK_WIDE, iPosX + UI_BUILDING_WIDE - UI_BUILDING_BACK_WIDE, iPosY + UI_BUILDING_HEIGHT - UI_BUILDING_BACK_WIDE, iFrameColor, TRUE);

		/* オブジェクト名を描写 */
		std::string strBuildingName[BUILDING_MAX] =
		{
			"モニュメント(剣)",			// モニュメント(剣)
			"モニュメント(杖)",			// モニュメント(杖)
			"味方生成拠点(スライム)",	// NPC拠点(スライム)
			"味方生成拠点(ウィスプ)"	// NPC拠点(ウィスプ)
		};
		DrawFormatString(iPosX + 10, iPosY + 15, GetColor(0, 0, 0), "%s", strBuildingName[i].c_str());

		/* オブジェクトの値段の背景描写 */
		// ※選択中の建築物であるならば黄色で描写
		DrawBox(iPosX + UI_BUILDING_WIDE, iPosY, iPosX + UI_BUILDING_WIDE + UI_BUILDING_PRICE_WIDE_X, iPosY + UI_BUILDING_HEIGHT, GetColor(0, 0, 0), TRUE);
		iFrameColor = GetColor(255, 255, 255);
		if (i == this->iPlacementBuildingIndex) { iFrameColor = GetColor(255, 255, 0); }
		DrawBox(iPosX + UI_BUILDING_WIDE + UI_BUILDING_BACK_WIDE, iPosY + UI_BUILDING_BACK_WIDE, iPosX + UI_BUILDING_WIDE + UI_BUILDING_PRICE_WIDE_X - UI_BUILDING_BACK_WIDE, iPosY + UI_BUILDING_HEIGHT - UI_BUILDING_BACK_WIDE, iFrameColor, TRUE);

		/* オブジェクトの値段を描写 */
		DrawGraph(iPosX + UI_BUILDING_WIDE + 10, iPosY + 10, *(this->piGrHandle_Coin), TRUE);
		DrawFormatString(iPosX + UI_BUILDING_WIDE + 80, iPosY + 30, GetColor(0, 0, 0), "x %d", iBuildingPrice[i]);
	}

	/* 操作内容とキーを描写 */
	// Eキー : 決定
	DrawExtendGraph(UI_BUILDING_POS_X, UI_BUILDING_POS_Y + (BUILDING_MAX * UI_BUILDING_HEIGHT) + 100, UI_BUILDING_POS_X + UI_KEY_SIZE, UI_BUILDING_POS_Y + (BUILDING_MAX * UI_BUILDING_HEIGHT) + 100 + UI_KEY_SIZE, *(this->piGrHandle_Key[KEY_E]), TRUE);
	DrawFormatString(UI_BUILDING_POS_X + (UI_KEY_SIZE * 2) + 20, UI_BUILDING_POS_Y + (BUILDING_MAX * UI_BUILDING_HEIGHT) + 100, GetColor(255, 255, 255), "決定");

	// Qキー : 建築モード終了
	DrawExtendGraph(UI_BUILDING_POS_X, UI_BUILDING_POS_Y + (BUILDING_MAX * UI_BUILDING_HEIGHT) + 150, UI_BUILDING_POS_X + UI_KEY_SIZE, UI_BUILDING_POS_Y + (BUILDING_MAX * UI_BUILDING_HEIGHT) + 150 + UI_KEY_SIZE, *(this->piGrHandle_Key[KEY_Q]), TRUE);
	DrawFormatString(UI_BUILDING_POS_X + (UI_KEY_SIZE * 2) + 20, UI_BUILDING_POS_Y + (BUILDING_MAX * UI_BUILDING_HEIGHT) + 150, GetColor(255, 255, 255), "建築モード終了");

	// ADキー : 建築エリア選択
	DrawExtendGraph(UI_BUILDING_POS_X, UI_BUILDING_POS_Y + (BUILDING_MAX * UI_BUILDING_HEIGHT) + 200, UI_BUILDING_POS_X + UI_KEY_SIZE, UI_BUILDING_POS_Y + (BUILDING_MAX * UI_BUILDING_HEIGHT) + 200 + UI_KEY_SIZE, *(this->piGrHandle_Key[KEY_A]), TRUE);
	DrawExtendGraph(UI_BUILDING_POS_X + UI_KEY_SIZE + 10, UI_BUILDING_POS_Y + (BUILDING_MAX * UI_BUILDING_HEIGHT) + 200, UI_BUILDING_POS_X + (UI_KEY_SIZE * 2) + 10, UI_BUILDING_POS_Y + (BUILDING_MAX * UI_BUILDING_HEIGHT) + 200 + UI_KEY_SIZE, *(this->piGrHandle_Key[KEY_D]), TRUE);
	DrawFormatString(UI_BUILDING_POS_X + (UI_KEY_SIZE * 2) + 20, UI_BUILDING_POS_Y + (BUILDING_MAX * UI_BUILDING_HEIGHT) + 200, GetColor(255, 255, 255), "建築エリア選択");
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

	// 入力されたならSEを再生
	if (iNowIndex != this->pDataList_GameStatus->GetSelectedBuildingIndex())
	{
		this->pDataList_Sound->SE_Play("CursorMove");
	}

	// インデックス番号を設定
	this->pDataList_GameStatus->SetSelectedBuildingIndex(iNowIndex);
}

// 建築物の配置
void Scene_GameMain_Building::Update_BuildingPlacement()
{
	/* 配置する建築物を切り替える */
	// 入力に応じてインデックス番号を変更
	int iOldPlacementBuildingIndex = this->iPlacementBuildingIndex;
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_W] == TRUE) { this->iPlacementBuildingIndex--; }
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_S] == TRUE) { this->iPlacementBuildingIndex++; }

	// インデックス番号が範囲外の場合はループさせる
	if (this->iPlacementBuildingIndex < 0) { this->iPlacementBuildingIndex = BUILDING_MAX - 1; }
	if (this->iPlacementBuildingIndex >= BUILDING_MAX) { this->iPlacementBuildingIndex = 0; }

	/* 入力されたならSEを再生 */
	if (iOldPlacementBuildingIndex != this->iPlacementBuildingIndex)
	{
		this->pDataList_Sound->SE_Play("CursorMove");
	}

	/* 建築物の配置 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_E] == TRUE)
	{
		// Eキーが押された場合
		/* 選択中の建築エリアに建造物がないか確認 */
		if (this->pDataList_GameStatus->GetBuildAreaPosition(this->pDataList_GameStatus->GetSelectedBuildingIndex()).pBuilding == nullptr)
		{
			// 建築物がない(建築可能である)場合
			/* 所持コインが足りているか確認 */
			if (this->pDataList_GameStatus->GetHaveCoin() < this->iBuildingPrice[this->iPlacementBuildingIndex])
			{
				// 所持コインが足りていない場合は処理を終了
				/* SEを再生 */
				this->pDataList_Sound->SE_Play("Select_Error");
				return;
			}
			else
			{
				// 所持コインが足りている場合はコインを減算
				this->pDataList_GameStatus->SetHaveCoin(this->pDataList_GameStatus->GetHaveCoin() - this->iBuildingPrice[this->iPlacementBuildingIndex]);

				/* SEを再生 */
				this->pDataList_Sound->SE_Play("Select_OK");
			}

			/* 建築物を配置 */
			switch (this->iPlacementBuildingIndex)
			{
				// モニュメント(剣)
				case BUILDING_MONUMENT_SOWRD:
				{
					/* 建築物を生成 */
					std::shared_ptr<Building_Monument> pBuilding = std::make_shared<Building_Monument>();
					pBuilding->SetPosition(this->pDataList_GameStatus->GetBuildAreaPosition(this->pDataList_GameStatus->GetSelectedBuildingIndex()).vecPosition);
					pBuilding->SetMonumentName("Monument_Sowrd");
					pBuilding->InitialSetup();

					/* 建造物をデータリストに設定 */
					// オブジェクト管理
					this->pDataList_Object->AddObject_Building(pBuilding);
					// ゲーム状態管理
					BUILDING_AREA_DATA AreaData	= this->pDataList_GameStatus->GetBuildAreaPosition(this->pDataList_GameStatus->GetSelectedBuildingIndex());
					AreaData.pBuilding			= pBuilding;
					this->pDataList_GameStatus->SetBuildAreaPosition(this->pDataList_GameStatus->GetSelectedBuildingIndex(), AreaData);

					/* 剣バフ量を加算 */
					int iSowrdBuff = this->pDataList_GameStatus->GetBuilldingBuff_Sword();
					iSowrdBuff++;
					this->pDataList_GameStatus->SetBuilldingBuff_Sword(iSowrdBuff);
				}
				break;

				// モニュメント(杖)
				case BUILDING_MONUMENT_ROD:
				{
					/* 建築物を生成 */
					std::shared_ptr<Building_Monument> pBuilding = std::make_shared<Building_Monument>();
					pBuilding->SetPosition(this->pDataList_GameStatus->GetBuildAreaPosition(this->pDataList_GameStatus->GetSelectedBuildingIndex()).vecPosition);
					pBuilding->SetMonumentName("Monument_Rod");
					pBuilding->InitialSetup();
					/* 建造物をデータリストに設定 */
					// オブジェクト管理
					this->pDataList_Object->AddObject_Building(pBuilding);
					// ゲーム状態管理
					BUILDING_AREA_DATA AreaData = this->pDataList_GameStatus->GetBuildAreaPosition(this->pDataList_GameStatus->GetSelectedBuildingIndex());
					AreaData.pBuilding = pBuilding;
					this->pDataList_GameStatus->SetBuildAreaPosition(this->pDataList_GameStatus->GetSelectedBuildingIndex(), AreaData);

					/* 杖バフ量を加算 */
					int iRodBuff = this->pDataList_GameStatus->GetBuilldingBuff_Rod();
					iRodBuff++;
					this->pDataList_GameStatus->SetBuilldingBuff_Rod(iRodBuff);
				}
				break;

				// NPC拠点(スライム)
				case BUILDING_NPCBASE_SLIME:
				{
					/* 建築物を生成 */
					std::shared_ptr<Building_NpcBase> pBuilding = std::make_shared<Building_NpcBase>();
					pBuilding->SetPosition(this->pDataList_GameStatus->GetBuildAreaPosition(this->pDataList_GameStatus->GetSelectedBuildingIndex()).vecPosition);
					pBuilding->SetNpcName("Slime_Green");
					pBuilding->InitialSetup();

					/* 建造物をデータリストに設定 */
					// オブジェクト管理
					this->pDataList_Object->AddObject_Building(pBuilding);
					// ゲーム状態管理
					BUILDING_AREA_DATA AreaData = this->pDataList_GameStatus->GetBuildAreaPosition(this->pDataList_GameStatus->GetSelectedBuildingIndex());
					AreaData.pBuilding = pBuilding;
					this->pDataList_GameStatus->SetBuildAreaPosition(this->pDataList_GameStatus->GetSelectedBuildingIndex(), AreaData);
				}
				break;

				// NPC拠点(ウィスプ)
				case BUILDING_NPCBASE_WISP:
				{
					/* 建築物を生成 */
					std::shared_ptr<Building_NpcBase> pBuilding = std::make_shared<Building_NpcBase>();
					pBuilding->SetPosition(this->pDataList_GameStatus->GetBuildAreaPosition(this->pDataList_GameStatus->GetSelectedBuildingIndex()).vecPosition);
					pBuilding->SetNpcName("Wisp_Green");
					pBuilding->InitialSetup();

					/* 建造物をデータリストに設定 */
					// オブジェクト管理
					this->pDataList_Object->AddObject_Building(pBuilding);
					// ゲーム状態管理
					BUILDING_AREA_DATA AreaData = this->pDataList_GameStatus->GetBuildAreaPosition(this->pDataList_GameStatus->GetSelectedBuildingIndex());
					AreaData.pBuilding = pBuilding;
					this->pDataList_GameStatus->SetBuildAreaPosition(this->pDataList_GameStatus->GetSelectedBuildingIndex(), AreaData);
				}
				break;
			}
		}
		else
		{
			// 建築物がある(建築不可である)場合
			/* SEを再生 */
			this->pDataList_Sound->SE_Play("Select_Error");
		}
	}
}
