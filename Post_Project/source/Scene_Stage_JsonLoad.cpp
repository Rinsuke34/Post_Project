/* シーン"ステージ"の定義 */
// ※Jsonファイルの読み込み部分のみ

/* 使用する要素のインクルード */
// 標準ライブラリ
#include <fstream>
// 外部ライブラリ
#include <nlohmann/json.hpp>
// ヘッダファイル
#include "Scene_Stage.h"
// 関連クラス
#include "DataList_Model.h"
#include "DataList_Image.h"
#include "DataList_Object.h"
#include "Ground_Block.h"
#include "Ground_Model.h"
#include "Ground_Marker.h"
#include "Character_Player.h"
// 共通定義
#include "ConstantDefine.h"
#include "StructDefine.h"
#include "FunctionDefine.h"

// ワールドマップリスト読み込み
void Scene_Stage::JsonLoad_WoldMapList()
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
		data.MapName = elem.value("MapName", "");
		data.iMapType = elem.value("MapType", 0);
		this->MapDataList.push_back(data);
	}
}

// ワールドマップを読み込む
void Scene_Stage::JsonLoad_WoldMap(int iAreaNo, std::string MapName)
{
	// 引数
	// iAreaNo		<- 読み込むエリア番号(AREA_NO_CENTERなど)
	// MapName		<- 読み込むマップデータの名前


	/* マップデータ読み込み */
	// ※テクスチャ読み込みが完了している状態で実行すること

	/* データリスト取得 */
	// 画像データ管理
	std::shared_ptr<DataList_Image>	pDataList_Image = std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));
	// 3Dモデルデータ管理
	std::shared_ptr<DataList_Model>	pDataList_Model = std::dynamic_pointer_cast<DataList_Model>(gpDataListServer->GetDataList("DataList_Model"));

	/* Jsonファイル読み込み */
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
				int BlockIndex = GroundBlock.at(iY).at(iZ).at(iX).get<int>();
				if (BlockIndex != -1)
				{
					// ブロックが存在する場合
					/* ブロック生成 */
					std::shared_ptr<Ground_Block> pGroundBlock = std::make_shared<Ground_Block>();

					// コリジョン設定
					Struct_Collision::COLLISION_BOX stBox;
					stBox.vecBoxCenter = VGet(
						AREA_ORIGIN_POS[iAreaNo].x + iX * MAP_BLOCK_SIZE_X + MAP_BLOCK_SIZE_X / 2.f,
						AREA_ORIGIN_POS[iAreaNo].y + iY * MAP_BLOCK_SIZE_Y + MAP_BLOCK_SIZE_Y / 2.f,
						AREA_ORIGIN_POS[iAreaNo].z + iZ * MAP_BLOCK_SIZE_Z + MAP_BLOCK_SIZE_Z / 2.f
					);
					stBox.vecBoxHalfSize = VGet(MAP_BLOCK_SIZE_X / 2.f, MAP_BLOCK_SIZE_Y / 2.f, MAP_BLOCK_SIZE_Z / 2.f);
					pGroundBlock->SetBoxCollision(stBox);

					// テクスチャ設定
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
					// ※ 隣接するブロックがある場合、その面は描写しない
					// ※ 各方向の境界面は必ず描写する
					// ※ +Zと-Y方向はカメラの向きの関係で描写しない
					static const int aiDirOffset[Ground_Block::DIRECTION_MAX][3] = {
						{+1,  0,  0}, // +X
						{-1,  0,  0}, // -X
						{ 0, +1,  0}, // +Y
						{ 0,  0, -1}  // -Z
					};

					for (int iDir = 0; iDir < Ground_Block::DIRECTION_MAX; ++iDir) {
						int nx = iX + aiDirOffset[iDir][0];
						int ny = iY + aiDirOffset[iDir][1];
						int nz = iZ + aiDirOffset[iDir][2];

						// 境界面であるか
						if (nx < 0 || nx >= AREA_SIZE_BLOCK_X ||
							ny < 0 || ny >= AREA_SIZE_BLOCK_Y ||
							nz < 0 || nz >= AREA_SIZE_BLOCK_Z)
						{
							// 境界面であるならば描写を有効に設定
							pGroundBlock->SetFaceDrawFlg(iDir, true);
						}
						else
						{
							// 境界面でないならば隣接するブロックの存在を確認
							int NeighborBlockIndex = GroundBlock.at(ny).at(nz).at(nx).get<int>();
							if (NeighborBlockIndex == -1)
							{
								// 隣接するブロックがないなら描写を有効に設定
								pGroundBlock->SetFaceDrawFlg(iDir, true);
							}
						}
					}

					/* 初期化処理 */
					pGroundBlock->InitialSetup();

					/* 対象のグリッドに読み込んだオブジェクトを登録 */
					int iGridX = iGetGridIndexX(stBox.vecBoxCenter.x);
					int iGridZ = iGetGridIndexZ(stBox.vecBoxCenter.z);
					this->pDataList_Object->AddObject_Ground(pGroundBlock, iGridX, iGridZ);
				}
			}
		}
	}

	/* 地形(3Dモデル)データ抽出 */
	auto& GroundModel = j["Ground_Model"];
	for (const auto& elem : GroundModel)
	{
		/* 3Dモデル情報取得 */
		MODEL_DATA data;
		data.ModelName = elem.value("ModelName", "");
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
		vecPosition.x = data.vecPosition.x * MAP_BLOCK_SIZE_X + (MAP_BLOCK_SIZE_X / 2) + AREA_ORIGIN_POS[iAreaNo].x;
		vecPosition.y = data.vecPosition.y * MAP_BLOCK_SIZE_Y + (MAP_BLOCK_SIZE_Y / 2) + AREA_ORIGIN_POS[iAreaNo].y;
		vecPosition.z = data.vecPosition.z * MAP_BLOCK_SIZE_Z + (MAP_BLOCK_SIZE_Z / 2) + AREA_ORIGIN_POS[iAreaNo].z;

		/* 3Dモデルデータを作成 */
		std::shared_ptr<Ground_Model> pGroundModel = std::make_shared<Ground_Model>();

		pGroundModel->SetModelHandle(pDataList_Model->iGetModel(data.ModelName));
		pGroundModel->SetPosition(vecPosition);
		pGroundModel->SetRotation(data.vecRotation);
		pGroundModel->SetScale(data.vecScale);
		pGroundModel->InitialSetup();

		/* 対象のグリッドに読み込んだオブジェクトを登録 */
		int iGridX = iGetGridIndexX(vecPosition.x);
		int iGridZ = iGetGridIndexZ(vecPosition.z);
		this->pDataList_Object->AddObject_Ground(pGroundModel, iGridX, iGridZ);
	}

	/* マーカー情報抽出 */
	auto& MarkerList = j["Marker"];
	for (const auto& elem : MarkerList)
	{
		/* マーカー情報作成 */
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
		vecPosition.x = data.vecPosition.x * MAP_BLOCK_SIZE_X + (MAP_BLOCK_SIZE_X / 2) + AREA_ORIGIN_POS[iAreaNo].x;
		vecPosition.y = data.vecPosition.y * MAP_BLOCK_SIZE_Y + (MAP_BLOCK_SIZE_Y / 2) + AREA_ORIGIN_POS[iAreaNo].y;
		vecPosition.z = data.vecPosition.z * MAP_BLOCK_SIZE_Z + (MAP_BLOCK_SIZE_Z / 2) + AREA_ORIGIN_POS[iAreaNo].z;

		/* マーカーデータを作成 */
		std::shared_ptr<Ground_Marker> pMarker = std::make_shared<Ground_Marker>();
		pMarker->SetMarkerName(data.MarkerName);
		pMarker->SetBoxCenter(vecPosition);
		pMarker->SetRotation(data.vecRotation);

		/* マーカー情報を保存 */
		this->pDataList_Object->AddObject_Marker(pMarker, iAreaNo);
	}
}