/* データリスト"ステージクリエイト情報管理"クラスの定義 */

/* 使用する要素のインクルード */
// 標準ライブラリ
#include <fstream>
// ヘッダファイル
#include "DataList_StageCreate.h"
// 関連クラス
#include "DataList_Model.h"
#include "DataList_Image.h"
#include "Ground_Block.h"
#include "Ground_Model.h"
#include "Ground_Marker.h"

// コンストラクタ
DataList_StageCreate::DataList_StageCreate() : DataList_Base("DataList_StageCreate")
{
	/* 初期化 */
	this->vecSelectPos = { 0, 0, 0 };
	for (int x = 0; x < AREA_SIZE_BLOCK_X; ++x)
	{
		for (int y = 0; y < AREA_SIZE_BLOCK_Y; ++y)
		{
			for (int z = 0; z < AREA_SIZE_BLOCK_Z; ++z)
			{
				pGoundObject[x][y][z] = nullptr;
			}
		}
	}

	Reset_MapData();	

	/* ワールドマップリスト読み込み */
	MapDataList.clear();
	Load_WoldMapList();
}

// ワールドマップリスト読み込み
void DataList_StageCreate::Load_WoldMapList()
{
	/* ワールドマップのリストを読み込む */
	// ※登録されているマップから編集するマップデータを選択する

	/* JSONファイル読み込み */
	std::string FilePath = "resource/MapData/MapData_Wold/WoldMapList.json";

	std::ifstream ifs(FilePath);
	if (!ifs) return;

	using json = nlohmann::json;
	json j;
	ifs >> j;

	/* マップリストデータ抽出 */
	for (const auto& elem : j)
	{
		WOLD_MAP_DATA data;
		data.MapName	= elem.value("MapName", "");
		data.iMapType	= elem.value("MapType", 0);
		this->MapDataList.push_back(data);
	}
}

// ワールドマップデータ読み込み
void DataList_StageCreate::Load_MapData(std::string MapName)
{
	// 引数
	// MapName		<- 読み込むマップデータの名前

	/* 現在のマップデータを初期化 */
	Reset_MapData();

	/* データリスト取得 */
	// 画像データ管理
	std::shared_ptr<DataList_Image>	pDataList_Image = std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));
	// 3Dモデルデータ管理
	std::shared_ptr<DataList_Model>	pDataList_Model = std::dynamic_pointer_cast<DataList_Model>(gpDataListServer->GetDataList("DataList_Model"));

	/* JSONファイル読み込み */
	std::string FilePath = "resource/MapData/MapData_Wold/" + MapName + ".json";

	std::ifstream ifs(FilePath);
	if (!ifs) return;

	using json = nlohmann::json;
	json j;
	ifs >> j;

	/* 地形(ブロック)データ抽出 */
	auto& GroundBlock = j["Ground_Block"];
	for (int iY = 0; iY < AREA_SIZE_BLOCK_Y; ++iY)
	{
		for (int iZ = 0; iZ < AREA_SIZE_BLOCK_Z; ++iZ)
		{
			for (int iX = 0; iX < AREA_SIZE_BLOCK_X; ++iX)
			{
				/* ブロックID読み込み */
				int BlockIndex = GroundBlock.at(iY).at(iZ).at(iX).get<int>();

				/* 何かしらのブロックがあるか確認 */
				if (BlockIndex == -1)
				{
					// ブロックがない場合
					continue;
				}

				/* コリジョン情報を作成 */
				Struct_Collision::COLLISION_BOX stBox;
				stBox.vecBoxCenter = VGet(
					iX * MAP_BLOCK_SIZE_X + (MAP_BLOCK_SIZE_X / 2.f),
					iY * MAP_BLOCK_SIZE_Y + (MAP_BLOCK_SIZE_Y / 2.f),
					iZ * MAP_BLOCK_SIZE_Z + (MAP_BLOCK_SIZE_Z / 2.f));
				stBox.vecBoxHalfSize = VGet(MAP_BLOCK_SIZE_X / 2.f, MAP_BLOCK_SIZE_Y / 2.f, MAP_BLOCK_SIZE_Z / 2.f);

				/* ブロックデータを作成 */
				std::shared_ptr<Ground_Block> pGroundBlock = std::make_shared<Ground_Block>();;
				pGroundBlock->SetBoxCollision(stBox);	// コリジョンを設定

				/* テクスチャ設定 */
				auto& TextureDataList = pDataList_Image->GetTextureDataList();
				for (auto& texData : TextureDataList)
				{
					if (texData.iBlockIndex == BlockIndex)
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

				/* ブロックの面の描写設定 */
				// ※ マップ作成の場合は全面を描写するように設定
				for (int iDir = 0; iDir < Ground_Block::DIRECTION_MAX; ++iDir)
				{
					pGroundBlock->SetFaceDrawFlg(iDir, true);
				}

				/* ブロックデータを保存 */
				this->pGoundObject[iX][iY][iZ] = pGroundBlock;
			}
		}
	}

	/* 3Dモデルデータ抽出 */
	auto& ModelList = j["Ground_Model"];
	for (const auto& elem : ModelList)
	{
		/* 3Dモデル情報取得 */
		MODEL_DATA data;
		data.ModelName	= elem.value("ModelName", "");
		elem.at("Position").at("x").get_to(data.vecPosition.x);
		elem.at("Position").at("y").get_to(data.vecPosition.y);
		elem.at("Position").at("z").get_to(data.vecPosition.z);
		elem.at("Rotation").at("x").get_to(data.vecRotation.x);
		elem.at("Rotation").at("y").get_to(data.vecRotation.y);
		elem.at("Rotation").at("z").get_to(data.vecRotation.z);
		elem.at("Scale").at("x").get_to(data.vecScale.x);
		elem.at("Scale").at("y").get_to(data.vecScale.y);
		elem.at("Scale").at("z").get_to(data.vecScale.z);

		/* ポジションをワールド座標に変換 */
		VECTOR vecPosition;
		vecPosition.x = data.vecPosition.x * MAP_BLOCK_SIZE_X + (MAP_BLOCK_SIZE_X / 2);
		vecPosition.y = data.vecPosition.y * MAP_BLOCK_SIZE_Y + (MAP_BLOCK_SIZE_Y / 2);
		vecPosition.z = data.vecPosition.z * MAP_BLOCK_SIZE_Z + (MAP_BLOCK_SIZE_Z / 2);

		/* 3Dモデルデータを作成 */
		std::shared_ptr<Ground_Model> pGroundModel = std::make_shared<Ground_Model>();;
		
		pGroundModel->SetModelHandle(pDataList_Model->iGetModel(data.ModelName));
		pGroundModel->SetPosition(vecPosition);
		pGroundModel->SetRotation(data.vecRotation);
		pGroundModel->SetScale(data.vecScale);
		pGroundModel->InitialSetup();

		/* 3Dモデルデータを保存 */
		this->pGoundObject[data.vecPosition.x][data.vecPosition.y][data.vecPosition.z] = pGroundModel;
	}

	/* マーカー情報抽出 */
	auto& MarkerList = j["Marker"];
	for (const auto& elem : MarkerList)
	{
		/* マーカー情報取得 */
		MARKER_DATA data;
		data.MarkerName = elem.value("MarkerName", "");
		elem.at("Position").at("x").get_to(data.vecPosition.x);
		elem.at("Position").at("y").get_to(data.vecPosition.y);
		elem.at("Position").at("z").get_to(data.vecPosition.z);
		elem.at("Rotation").at("x").get_to(data.vecRotation.x);
		elem.at("Rotation").at("y").get_to(data.vecRotation.y);
		elem.at("Rotation").at("z").get_to(data.vecRotation.z);

		/* ポジションをワールド座標に変換 */
		VECTOR vecPosition;
		vecPosition.x = data.vecPosition.x * MAP_BLOCK_SIZE_X + (MAP_BLOCK_SIZE_X / 2);
		vecPosition.y = data.vecPosition.y * MAP_BLOCK_SIZE_Y + (MAP_BLOCK_SIZE_Y / 2);
		vecPosition.z = data.vecPosition.z * MAP_BLOCK_SIZE_Z + (MAP_BLOCK_SIZE_Z / 2);

		/* マーカーデータを作成 */
		std::shared_ptr<Ground_Marker> pGroundMarker = std::make_shared<Ground_Marker>();;
		pGroundMarker->SetMarkerName(data.MarkerName);
		pGroundMarker->SetBoxCenter(vecPosition);
		pGroundMarker->SetRotation(data.vecRotation);

		/* マーカーデータを保存 */
		this->pGoundObject[data.vecPosition.x][data.vecPosition.y][data.vecPosition.z] = pGroundMarker;
	}
}

// 地形オブジェクト描画
void DataList_StageCreate::Draw_GroundObject()
{
	for (int iX = 0; iX < AREA_SIZE_BLOCK_X; ++iX)
	{
		for (int iY = 0; iY < AREA_SIZE_BLOCK_Y; ++iY)
		{
			for (int iZ = 0; iZ < AREA_SIZE_BLOCK_Z; ++iZ)
			{
				if (this->pGoundObject[iX][iY][iZ] != nullptr)
				{
					// 地形オブジェクトが存在する場合
					this->pGoundObject[iX][iY][iZ]->Draw();
				}
			}
		}
	}
}

// マップデータの初期化
void DataList_StageCreate::Reset_MapData()
{
	for (int iX = 0; iX < AREA_SIZE_BLOCK_X; ++iX)
	{
		for (int iY = 0; iY < AREA_SIZE_BLOCK_Y; ++iY)
		{
			for (int iZ = 0; iZ < AREA_SIZE_BLOCK_Z; ++iZ)
			{
				this->pGoundObject[iX][iY][iZ] = nullptr;
			}
		}
	}
}
