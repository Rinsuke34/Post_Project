/* シーン"ステージ作成"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_StageCreate.h"
// 関連クラス
#include "Scene_Stage.h"
#include "DataList_Object.h"
#include "DataList_StageCreate.h"
#include "Ground_Block.h"
#include "Ground_Model.h"
#include "Ground_Marker.h"
// 共通定義
#include "ConstantDefine.h"
#include "DataList_Image.h"
#include "DataList_Model.h"

// コンストラクタ
Scene_StageCreate::Scene_StageCreate() : Scene_Base("Scene_StageCreate", 100, false, false)
{
	/* データリスト作成 */
	gpDataListServer->AddDataList(std::make_shared<DataList_Object>());			// オブジェクト管理
	gpDataListServer->AddDataList(std::make_shared<DataList_StageCreate>());	// ステージクリエイト情報管理

	/* データリスト取得 */
	this->pDataList_StageCreate	= std::dynamic_pointer_cast<DataList_StageCreate>(gpDataListServer->GetDataList("DataList_StageCreate"));	// ステージクリエイト情報管理

	/* 初期化 */
	this->iNowPhase					= PHASE_SELECT_MAP;	// マップ選択フェーズから開始
	this->iSelectMapIndex			= 0;				// 選択中のマップのインデックス番号
	this->iSelectObjectTypeIndex	= 0;				// 選択中の追加オブジェクトの種類のインデックス番号
	this->iSelectObjectNameIndex	= 0;				// 選択中の追加オブジェクトの名前のインデックス番号
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
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_W] == TRUE)	{ vecSelectPos.z ++; }
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_S] == TRUE)	{ vecSelectPos.z --; }
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_D] == TRUE)	{ vecSelectPos.x ++; }
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_A] == TRUE)	{ vecSelectPos.x --; }
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_E] == TRUE)	{ vecSelectPos.y ++; }
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_Q] == TRUE)	{ vecSelectPos.y --; }

	/* 選択座標を更新 */
	this->pDataList_StageCreate->SetSelectPos(vecSelectPos);

	/* 追加オブジェクトの種類を変更 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_LEFT]		== TRUE)	{ this->iSelectObjectTypeIndex--; }
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_RIGHT]	== TRUE)	{ this->iSelectObjectTypeIndex++; }

	/* 追加オブジェクトの種類を範囲内に収める */
	if (this->iSelectObjectTypeIndex < 0)
	{
		this->iSelectObjectTypeIndex = 0;
		this->iSelectObjectNameIndex = 0;
	}
	if (this->iSelectObjectTypeIndex >= ADD_OBJECT_TYPE_MAX)
	{
		this->iSelectObjectTypeIndex = ADD_OBJECT_TYPE_MAX - 1;
		this->iSelectObjectNameIndex = 0;
	}

	/* オブジェクト名を取得 */
	std::vector<std::string>& ObjectNameList = this->pDataList_StageCreate->GetObjectNameList(this->iSelectObjectTypeIndex);

	/* 追加オブジェクト名を変更 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_UP]	== TRUE)	{ this->iSelectObjectNameIndex--; }
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_DOWN]	== TRUE)	{ this->iSelectObjectNameIndex++; }

	/* 追加オブジェクト名を範囲内に収める */
	if (this->iSelectObjectNameIndex < 0)
	{
		this->iSelectObjectNameIndex = 0;
	}
	if (this->iSelectObjectNameIndex > static_cast<int>(ObjectNameList.size() - 1))
	{
		this->iSelectObjectNameIndex = static_cast<int>(ObjectNameList.size() - 1);
	}

	/* 現在選択中のオブジェクトを配置 */
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_Z] == TRUE)
	{
		switch (this->iSelectObjectTypeIndex)
		{
			// ブロック
			case ADD_OBJECT_TYPE_BLOCK:
				Add_Block();
				break;

			// 3Dモデル
			case ADD_OBJECT_TYPE_MODEL:
				Add_Model();
				break;

			// マーカー
			case ADD_OBJECT_TYPE_MARKER:
				Add_Marker();
				break;
		}
	}

	/* 現在選択中のオブジェクトを削除 */
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_X] == TRUE)
	{
		/* 選択中の座標に登録されたオブジェクトを削除 */
		this->pDataList_StageCreate->DeleteGroundObject(this->pDataList_StageCreate->vecGetSelectPos());
	}

	/* ESCキーが入力(ステージシーンが削除)されたなら現時点での情報をJSON出力 */
	if (gstKeyboardInputData.cgInput[INPUT_REL][KEY_INPUT_ESCAPE] == TRUE)
	{
		/* Jsonに保存 */
		this->pDataList_StageCreate->Save_MapData(this->pDataList_StageCreate->GetMapDataList()[this->iSelectMapIndex].MapName);

		/* マップ選択フェーズへ遷移 */
		this->iNowPhase = PHASE_SELECT_MAP;
	}
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
	DrawFormatString(DRAW_MAPNAME_X, 0, GetColor(255, 255, 255), "選択中の座標 : (%d, %d, %d)", this->pDataList_StageCreate->vecGetSelectPos().x, this->pDataList_StageCreate->vecGetSelectPos().y, this->pDataList_StageCreate->vecGetSelectPos().z);

	/* 追加オブジェクトの種類を描写 */
	switch (this->iSelectObjectTypeIndex)
	{
		// ブロック
		case ADD_OBJECT_TYPE_BLOCK:
			DrawFormatString(DRAW_MAPNAME_X, 32, GetColor(255, 255, 255), "追加するオブジェクトの種類 : ブロック");
			break;

		// 3Dモデル
		case ADD_OBJECT_TYPE_MODEL:
			DrawFormatString(DRAW_MAPNAME_X, 32, GetColor(255, 255, 255), "追加するオブジェクトの種類 : 3Dモデル");
			break;

		// マーカー
		case ADD_OBJECT_TYPE_MARKER:
			DrawFormatString(DRAW_MAPNAME_X, 32, GetColor(255, 255, 255), "追加するオブジェクトの種類 : マーカー");
			break;
	}

	/* 追加オブジェクト名を描写 */
	std::vector<std::string>& ObjectNameList = this->pDataList_StageCreate->GetObjectNameList(this->iSelectObjectTypeIndex);
	DrawFormatString(DRAW_MAPNAME_X, 48, GetColor(255, 255, 255), "追加するオブジェクト名 : %s", ObjectNameList[this->iSelectObjectNameIndex].c_str());
}

// 地形オブジェクト追加(ブロック)
void Scene_StageCreate::Add_Block()
{
	/* データリスト取得 */
	// 画像データ管理
	std::shared_ptr<DataList_Image>	pDataList_Image = std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));

	/* 地形(ブロック)を作成 */
	std::shared_ptr<Ground_Block> pGroundBlock = std::make_shared<Ground_Block>();

	/* ブロックIDを取得 */
	int iBlockID = pDataList_Image->iGetBlockID(this->pDataList_StageCreate->GetObjectNameList(this->iSelectObjectTypeIndex)[this->iSelectObjectNameIndex].c_str());

	/* テクスチャ設定 */
	auto& TextureDataList = pDataList_Image->GetTextureDataList();
	for (auto& texData : TextureDataList)
	{
		if (texData.iBlockIndex == iBlockID)
		{
			// 上面
			if (!texData.aImageName[0].empty())
			{
				pGroundBlock->SetTextureHandle(Ground_Block::FACE_TYPE_TOP, pDataList_Image->iGetGrhandle(texData.aImageName[0]));
			}
			// 横面
			if (!texData.aImageName[1].empty())
			{
				pGroundBlock->SetTextureHandle(Ground_Block::FACE_TYPE_SIDE, pDataList_Image->iGetGrhandle(texData.aImageName[1]));
			}
			// 下面
			if (!texData.aImageName[2].empty())
			{
				pGroundBlock->SetTextureHandle(Ground_Block::FACE_TYPE_BOTTOM, pDataList_Image->iGetGrhandle(texData.aImageName[2]));
			}
			break;
		}
	}

	/* コリジョン設定 */
	Struct_Collision::COLLISION_BOX stBox;
	stBox.vecBoxCenter = VGet(
		this->pDataList_StageCreate->vecGetSelectPos().x * MAP_BLOCK_SIZE_X + (MAP_BLOCK_SIZE_X / 2.f),
		this->pDataList_StageCreate->vecGetSelectPos().y * MAP_BLOCK_SIZE_Y + (MAP_BLOCK_SIZE_Y / 2.f),
		this->pDataList_StageCreate->vecGetSelectPos().z * MAP_BLOCK_SIZE_Z + (MAP_BLOCK_SIZE_Z / 2.f)
	);
	stBox.vecBoxHalfSize = VGet(MAP_BLOCK_SIZE_X / 2.f, MAP_BLOCK_SIZE_Y / 2.f, MAP_BLOCK_SIZE_Z / 2.f);
	pGroundBlock->SetBoxCollision(stBox);

	/* ブロックの面の描写設定 */
	// ※ マップ作成の場合は全面を描写するように設定
	for (int iDir = 0; iDir < Ground_Block::DIRECTION_MAX; ++iDir)
	{
		pGroundBlock->SetFaceDrawFlg(iDir, true);
	}

	/* ブロックIDを登録 */
	pGroundBlock->SetBlockId(iBlockID);

	/* 初期設定 */
	pGroundBlock->InitialSetup();

	/* ブロックをマップのオブジェクトに追加 */
	this->pDataList_StageCreate->AddGroundObject(this->pDataList_StageCreate->vecGetSelectPos(), pGroundBlock);
}

// 地形オブジェクト追加(モデル)
void Scene_StageCreate::Add_Model()
{
	/* データリスト取得 */
	// 3Dモデルデータ管理
	std::shared_ptr<DataList_Model>	pDataList_Model = std::dynamic_pointer_cast<DataList_Model>(gpDataListServer->GetDataList("DataList_Model"));

	/* 地形(モデル)を作成 */
	std::shared_ptr<Ground_Model> pGroundModel = std::make_shared<Ground_Model>();

	/* 現在の選択ポジションをワールド座標に変換 */
	VECTOR vecPosition;
	vecPosition.x = this->pDataList_StageCreate->vecGetSelectPos().x * MAP_BLOCK_SIZE_X + (MAP_BLOCK_SIZE_X / 2);
	vecPosition.y = this->pDataList_StageCreate->vecGetSelectPos().y * MAP_BLOCK_SIZE_Y + (MAP_BLOCK_SIZE_Y / 2);
	vecPosition.z = this->pDataList_StageCreate->vecGetSelectPos().z * MAP_BLOCK_SIZE_Z + (MAP_BLOCK_SIZE_Z / 2);

	/* 各要素を設定 */
	pGroundModel->SetModelName(this->pDataList_StageCreate->GetObjectNameList(this->iSelectObjectTypeIndex)[this->iSelectObjectNameIndex].c_str());
	pGroundModel->SetModelHandle(pDataList_Model->iGetModel(this->pDataList_StageCreate->GetObjectNameList(this->iSelectObjectTypeIndex)[this->iSelectObjectNameIndex].c_str()));
	pGroundModel->SetPosition(vecPosition);
	pGroundModel->SetRotation(VGet(0.f, 0.f, 0.f));
	pGroundModel->SetScale(VGet(1.f, 1.f, 1.f));
	pGroundModel->InitialSetup();

	/* モデルをマップのオブジェクトに追加 */
	this->pDataList_StageCreate->AddGroundObject(this->pDataList_StageCreate->vecGetSelectPos(), pGroundModel);
}

// 地形オブジェクト追加(マーカー)
void Scene_StageCreate::Add_Marker()
{
	/* 地形(マーカー)を作成 */
	std::shared_ptr<Ground_Marker> pGroundMarker = std::make_shared<Ground_Marker>();

	/* 現在の選択ポジションをワールド座標に変換 */
	VECTOR vecPosition;
	vecPosition.x = this->pDataList_StageCreate->vecGetSelectPos().x * MAP_BLOCK_SIZE_X + (MAP_BLOCK_SIZE_X / 2);
	vecPosition.y = this->pDataList_StageCreate->vecGetSelectPos().y * MAP_BLOCK_SIZE_Y + (MAP_BLOCK_SIZE_Y / 2);
	vecPosition.z = this->pDataList_StageCreate->vecGetSelectPos().z * MAP_BLOCK_SIZE_Z + (MAP_BLOCK_SIZE_Z / 2);

	/* 各要素を設定 */
	pGroundMarker->SetMarkerName(this->pDataList_StageCreate->GetObjectNameList(this->iSelectObjectTypeIndex)[this->iSelectObjectNameIndex].c_str());
	pGroundMarker->SetBoxCenter(vecPosition);
	pGroundMarker->SetRotation(VGet(0.f, 0.f, 0.f));

	/* マーカーをマップのオブジェクトに追加 */
	this->pDataList_StageCreate->AddGroundObject(this->pDataList_StageCreate->vecGetSelectPos(), pGroundMarker);
}
