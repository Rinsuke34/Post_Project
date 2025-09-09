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
#include "DataList_Image.h"
#include "DataList_Object.h"
#include "Ground_Block.h"
#include "Character_Player.h"
// 共通定義
#include "ConstantDefine.h"
#include "StructDefine.h"

// テクスチャ読み込み
void Scene_Stage::JsonLoad_Texture()
{
	/* テクスチャデータを読み込み、テクスチャデータリストに登録する */
	// ※テクスチャ読み込みを完了させてからマップデータの読み込みは行うこと

	// Jsonファイル読み込み
	std::string FilePath = "resource/MapData/Texture_Data.json";

	std::ifstream ifs(FilePath);
	if (!ifs) return;

	using json = nlohmann::json;
	json j;
	ifs >> j;

	// テクスチャデータリストへの設定
	for (const auto& elem : j)
	{
		TEXTURE_DATA data;
		data.BlockName		= elem.value("BlockName", "");
		data.iBlockIndex	= elem.value("BlockIndex", -1);
		data.aImageName[0]	= elem.value("ImageName_Upper", "");
		data.aImageName[1]	= elem.value("ImageName_Side", "");
		data.aImageName[2]	= elem.value("ImageName_Under", "");

		this->pDataList_Object->AddTexture(data);
	}

	// データリスト"画像データ管理"へテクスチャの登録
	std::shared_ptr<DataList_Image>	pDataList_Image	= std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));
	for (auto& texData : this->pDataList_Object->GetTextureDataList())
	{
		// 上面
		if (!texData.aImageName[0].empty())
		{
			pDataList_Image->LoadGrHandle(texData.aImageName[0]);
		}
		// 横面
		if (!texData.aImageName[1].empty())
		{
			pDataList_Image->LoadGrHandle(texData.aImageName[1]);
		}
		// 下面
		if (!texData.aImageName[2].empty())
		{
			pDataList_Image->LoadGrHandle(texData.aImageName[2]);
		}
	}
}

// ワールドマップ読み込み(中央)
void Scene_Stage::JsonLoad_WoldMap_Center()
{
	/* マップデータ読み込み */
	// ※テクスチャ読み込みが完了している状態で実行すること

	/* データリスト"画像データ管理"取得 */
	std::shared_ptr<DataList_Image>	pDataList_Image = std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));

	/* Jsonファイル読み込み */
	std::string FilePath = "resource/MapData/MapData_Wold/AreaData_Front.json";

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
						AREA_ORIGIN_POS[AREA_NO_CENTER].x + iX * MAP_BLOCK_SIZE_X + MAP_BLOCK_SIZE_X / 2.f,
						AREA_ORIGIN_POS[AREA_NO_CENTER].y + iY * MAP_BLOCK_SIZE_Y + MAP_BLOCK_SIZE_Y / 2.f,
						AREA_ORIGIN_POS[AREA_NO_CENTER].z + iZ * MAP_BLOCK_SIZE_Z + MAP_BLOCK_SIZE_Z / 2.f
					);
					stBox.vecBoxHalfSize = VGet(MAP_BLOCK_SIZE_X / 2.f , MAP_BLOCK_SIZE_Y / 2.f, MAP_BLOCK_SIZE_Z / 2.f);
					pGroundBlock->SetBoxCollision(stBox);

					// テクスチャ設定
					auto& TextureDataList = this->pDataList_Object->GetTextureDataList();
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
					static const int aiDirOffset[Ground_Block::DIRECTION_MAX][3] = {
						{+1,  0,  0}, // +X
						{-1,  0,  0}, // -X
						{ 0, +1,  0}, // +Y
						{ 0, -1,  0}, // -Y
						{ 0,  0, +1}, // +Z
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

					// オブジェクトリストに登録
					this->pDataList_Object->AddObject_Ground(pGroundBlock, AREA_NO_CENTER);
				}
			}
		}
	}

	/* 地形(3Dモデル)データ抽出 */

	/* プレイヤー追加(仮) */
	std::shared_ptr<Character_Player> pPlayer = std::make_shared<Character_Player>();
	pPlayer->SetPosition(VGet(6144.f, 300.f, 6144.f));
	this->pDataList_Object->AddObject_Actor(pPlayer);
}

// ダンジョンマップ読み込み
void Scene_Stage::JsonLoad_DungeonMap()
{

}
