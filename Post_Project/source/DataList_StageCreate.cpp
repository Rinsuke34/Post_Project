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

	/* オブジェクトデータ読み込み */
	Load_ObjectData();
}

// オブジェクトデータ読み込み
void DataList_StageCreate::Load_ObjectData()
{
	/* オブジェクトデータを読み込む */
	// ※ブロック、3Dモデル、マーカの種類を読み込む

	/* JSONファイル読み込み */
	std::string FilePath = "resource/MapData/Object_Data.json";

	std::ifstream ifs(FilePath);
	if (!ifs) return;

	using json = nlohmann::json;
	json j;
	ifs >> j;

	/* ブロック名リスト抽出 */
	if (j.contains("Block") && j["Block"].is_array())
	{
		for (const auto& name : j["Block"])
		{
			this->ObjectNameList[OBJECT_TYPE_BLOCK].push_back(name.get<std::string>());
		}
	}

	/* モデル名リスト抽出 */
	if (j.contains("Model") && j["Model"].is_array())
	{
		for (const auto& name : j["Model"])
		{
			this->ObjectNameList[OBJECT_TYPE_MODEL].push_back(name.get<std::string>());
		}
	}

	/* マーカー名リスト抽出 */
	if (j.contains("Marker") && j["Marker"].is_array())
	{
		for (const auto& name : j["Marker"])
		{
			this->ObjectNameList[OBJECT_TYPE_MARKER].push_back(name.get<std::string>());
		}
	}
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
				int iBlockIndex = -1;
				try
				{
					// 要素があるなら読み込む
					iBlockIndex = GroundBlock.at(iY).at(iZ).at(iX).get<int>();
				}
				catch (...)
				{
					// 要素がないならブロックを無しに設定
					iBlockIndex = -1;
				}

				/* 何かしらのブロックがあるか確認 */
				if (iBlockIndex == -1)
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
					if (texData.iBlockIndex == iBlockIndex)
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

				/* ブロックIDを登録 */
				pGroundBlock->SetBlockId(iBlockIndex);

				/* 初期化処理 */
				pGroundBlock->InitialSetup();

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

		/* 3Dモデル名を保存 */
		pGroundModel->SetModelName(data.ModelName);

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

// ワールドマップデータ保存
void DataList_StageCreate::Save_MapData(std::string MapName)
{
	// 引数
	// MapName		<- 保存するマップデータの名前

	/* 保存するファイル名を設定 */
	std::string FilePath = "resource/MapData/MapData_Wold/" + MapName + ".json";

	using json = nlohmann::json;
	json j;

	/* 地形(ブロック)の情報を保存 */
	j["Ground_Block"] = json::array();
	for (int iY = 0; iY < AREA_SIZE_BLOCK_Y; ++iY)
	{
		json arrY = json::array();
		for (int iZ = 0; iZ < AREA_SIZE_BLOCK_Z; ++iZ)
		{
			json arrZ = json::array();
			for (int iX = 0; iX < AREA_SIZE_BLOCK_X; ++iX)
			{
				int blockIndex = -1;
				auto pObj = this->pGoundObject[iX][iY][iZ];
				
				if (pObj != nullptr)
				{
					/* ブロックIDを取得 */
					auto pBlock = std::dynamic_pointer_cast<Ground_Block>(pObj);
					if (pBlock)
					{
						// ブロックであるなら
						/* ブロックIDを出力 */
						blockIndex = pBlock->iGetBlockId();
					}
				}
				arrZ.push_back(blockIndex);
			}
			arrY.push_back(arrZ);
		}
		j["Ground_Block"].push_back(arrY);
	}

	/* 地形(モデル)の情報を保存 */
	j["Ground_Model"] = json::array();
	for (int iX = 0; iX < AREA_SIZE_BLOCK_X; ++iX)
	{
		for (int iY = 0; iY < AREA_SIZE_BLOCK_Y; ++iY)
		{
			for (int iZ = 0; iZ < AREA_SIZE_BLOCK_Z; ++iZ)
			{
				auto pObj = this->pGoundObject[iX][iY][iZ];
				if (pObj != nullptr)
				{
					/* 3Dモデルの情報を取得 */
					auto pModel = std::dynamic_pointer_cast<Ground_Model>(pObj);
					if (pModel)
					{
						json modelObj;
						modelObj["ModelName"] = pModel->GetModelName();
						// 配列インデックス座標を保存
						modelObj["Position"] = { {"x", iX}, {"y", iY}, {"z", iZ} };
						// 回転・スケール
						VECTOR rot = pModel->GetRotation();
						VECTOR scl = pModel->GetScale();
						modelObj["Rotation"] = { {"x", rot.x}, {"y", rot.y}, {"z", rot.z} };
						modelObj["Scale"] = { {"x", scl.x}, {"y", scl.y}, {"z", scl.z} };
						j["Ground_Model"].push_back(modelObj);
					}
				}
			}
		}
	}

	/* 地形(マーカー)の情報を保存 */
	j["Marker"] = json::array();
	for (int iX = 0; iX < AREA_SIZE_BLOCK_X; ++iX)
	{
		for (int iY = 0; iY < AREA_SIZE_BLOCK_Y; ++iY)
		{
			for (int iZ = 0; iZ < AREA_SIZE_BLOCK_Z; ++iZ)
			{
				auto pObj = this->pGoundObject[iX][iY][iZ];
				if (pObj != nullptr)
				{
					/* マーカーの情報を取得 */
					auto pMarker = std::dynamic_pointer_cast<Ground_Marker>(pObj);
					if (pMarker)
					{
						json markerObj;
						markerObj["MarkerName"] = pMarker->GetMarkerName();
						// 配列インデックス座標を保存
						markerObj["Position"] = { {"x", iX}, {"y", iY}, {"z", iZ} };
						VECTOR rot = pMarker->vecGetRotation();
						markerObj["Rotation"] = { {"x", rot.x}, {"y", rot.y}, {"z", rot.z} };
						j["Marker"].push_back(markerObj);
					}
				}
			}
		}
	}

	/* Jsonファイル出力 */
	std::ofstream ofs(FilePath);
	if (ofs.is_open())
	{
		ofs << j.dump(4);
		ofs.close();
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

// オブジェクトを削除
void DataList_StageCreate::AddGroundObject(VECTOR_INT AddPos, std::shared_ptr<Ground_Base> AddObject)
{
	// 引数
	// AddPos		<- 追加する座標(ブロック単位)
	// AddObject	<- 追加するオブジェクト

	/* 座標が範囲内か確認 */
	if (AddPos.x < 0 || AddPos.x >= AREA_SIZE_BLOCK_X ||
		AddPos.y < 0 || AddPos.y >= AREA_SIZE_BLOCK_Y ||
		AddPos.z < 0 || AddPos.z >= AREA_SIZE_BLOCK_Z)
	{
		// 範囲外の場合
		return;
	}

	/* 既にオブジェクトがある場合は削除 */
	if (this->pGoundObject[AddPos.x][AddPos.y][AddPos.z] != nullptr)
	{
		this->pGoundObject[AddPos.x][AddPos.y][AddPos.z] = nullptr;
	}

	/* オブジェクトを追加 */
	this->pGoundObject[AddPos.x][AddPos.y][AddPos.z] = AddObject;
}

// オブジェクトを削除
void DataList_StageCreate::DeleteGroundObject(VECTOR_INT DeletePos)
{
	// 引数
	// DeletePos	<- 削除する座標(ブロック単位)

	/* 座標が範囲内か確認 */
	if (DeletePos.x < 0 || DeletePos.x >= AREA_SIZE_BLOCK_X ||
		DeletePos.y < 0 || DeletePos.y >= AREA_SIZE_BLOCK_Y ||
		DeletePos.z < 0 || DeletePos.z >= AREA_SIZE_BLOCK_Z)
	{
		// 範囲外の場合
		return;
	}
	/* オブジェクトを削除 */
	this->pGoundObject[DeletePos.x][DeletePos.y][DeletePos.z] = nullptr;
}
