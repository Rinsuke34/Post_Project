/* シーン"ステージ作成"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_StageCreate.h"
// 関連クラス
// 関連クラス
#include "Scene_Stage.h"
#include "DataList_Object.h"
#include "DataList_StageCreate.h"

// コンストラクタ
Scene_StageCreate::Scene_StageCreate() : Scene_Base("Scene_StageCreate", 100, false, false)
{
	/* データリスト作成 */
	gpDataListServer->AddDataList(std::make_shared<DataList_Object>());			// オブジェクト管理
	gpDataListServer->AddDataList(std::make_shared<DataList_StageCreate>());	// ステージクリエイト情報管理

	/* データリスト取得 */
	this->pDataList_StageCreate	= std::dynamic_pointer_cast<DataList_StageCreate>(gpDataListServer->GetDataList("DataList_StageCreate"));	// ステージクリエイト情報管理

	/* 初期化 */
	this->iNowPhase			= PHASE_SELECT_MAP;	// マップ選択フェーズから開始
	this->iSelectMapIndex	= 0;				// 選択中のマップのインデックス番号
}

// デストラクタ
Scene_StageCreate::~Scene_StageCreate()
{
	/* データリスト削除 */
	gpDataListServer->DeleteDataList("DataList_StageCreate");	// ステージクリエイト情報管理
}

// 更新
void Scene_StageCreate::Update()
{
	/* フェーズごとの処理 */
	switch (this->iNowPhase)
	{
		// マップ選択フェーズ
		case PHASE_SELECT_MAP:
			Update_SelectMap();
			break;

		// マップ編集フェーズ
		case PHASE_EDIT_MAP:
			Update_EditMap();
			break;
	}
}

// 描画
void Scene_StageCreate::Draw()
{
	/* フェーズごとの処理 */
	switch (this->iNowPhase)
	{
		// マップ選択フェーズ
		case PHASE_SELECT_MAP:
			Draw_SelectMap();
			break;

		// マップ編集フェーズ
		case PHASE_EDIT_MAP:
			Draw_EditMap();
			break;
	}
}

// マップ選択フェーズの更新
void Scene_StageCreate::Update_SelectMap()
{
	/* マップ情報を取得 */
	std::vector<WOLD_MAP_DATA>& MapDataList = this->pDataList_StageCreate->GetMapDataList();

	/* 選択マップ変更 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_UP] == TRUE)
	{
		this->iSelectMapIndex--;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_DOWN] == TRUE)
	{
		this->iSelectMapIndex++;
	}

	/* 選択マップのインデックス番号を範囲内に収める */
	int iMapListSize = static_cast<int>(MapDataList.size());
	if (this->iSelectMapIndex < 0)
	{
		this->iSelectMapIndex = 0;
	}
	if (this->iSelectMapIndex >= iMapListSize)
	{
		this->iSelectMapIndex = iMapListSize - 1;
	}

	/* 決定キーでマップを読み込み、マップ編集フェーズへ移行 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_Z] == TRUE)
	{
		/* フェーズ変更 */
		this->iNowPhase = PHASE_EDIT_MAP;

		/* 選択中のマップデータを読み込み */
		this->pDataList_StageCreate->Load_MapData(MapDataList[this->iSelectMapIndex].MapName);

		/* ステージシーン作成 */
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_Stage>());

		return;
	}
}

// マップ編集フェーズの更新
void Scene_StageCreate::Update_EditMap()
{
	/* 現在の選択座標を取得 */
	VECTOR_INT vecSelectPos = this->pDataList_StageCreate->vecGetSelectPos();

	/* 選択座標を変更 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_W] == TRUE)
	{
		vecSelectPos.z += 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_S] == TRUE)
	{
		vecSelectPos.z -= 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_D] == TRUE)
	{
		vecSelectPos.x += 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_A] == TRUE)
	{
		vecSelectPos.x -= 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_Q] == TRUE)
	{
		vecSelectPos.y += 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_E] == TRUE)
	{
		vecSelectPos.y -= 1;
	}

	/* 選択座標を更新 */
	this->pDataList_StageCreate->SetSelectPos(vecSelectPos);
}

// マップ選択フェーズの描写
void Scene_StageCreate::Draw_SelectMap()
{
	/* マップ情報を取得 */
	std::vector<WOLD_MAP_DATA>& MapDataList = this->pDataList_StageCreate->GetMapDataList();

	/* マップリストを描写 */
	for (int i = 0; i < MapDataList.size(); ++i)
	{
		if (i == this->iSelectMapIndex)
		{
			// 選択中のマップの場合
			DrawFormatString(DRAW_MAPNAME_X, DRAW_MAPNAME_Y + (16 * i), GetColor(255, 255, 0), "> %s", MapDataList[i].MapName.c_str());
		}
		else
		{
			// 選択中でないマップの場合
			DrawFormatString(DRAW_MAPNAME_X, DRAW_MAPNAME_Y + (16 * i), GetColor(255, 255, 255), "  %s", MapDataList[i].MapName.c_str());
		}
	}
}

// マップ編集フェーズの描写
void Scene_StageCreate::Draw_EditMap()
{
	/* 選択中の座標を描写 */
	DrawFormatString(0, 0, GetColor(255, 255, 255), "選択中の座標 : (%d, %d, %d)", this->pDataList_StageCreate->vecGetSelectPos().x, this->pDataList_StageCreate->vecGetSelectPos().y, this->pDataList_StageCreate->vecGetSelectPos().z);
}
