/* シーン"ステージ"の定義 */
// ※セットアップ用の処理部分のみ

/* 使用する要素のインクルード */
// 標準ライブラリ
#define NOMINMAX
#include <algorithm>
// ヘッダファイル
#include "Scene_Stage.h"
// 関連クラス
#include "DataList_GameStatus.h"
#include "DataList_Object.h"
#include "Character_Player.h"
#include "Ground_Marker.h"
#include "Building_CoreTree.h"
#include "DataList_Model.h"
#include "Ground_Model.h"
#include "Npc_Base.h"

// マーカー情報読み込み(中央エリア)
void Scene_Stage::Setup_LoadMarker_CenterArea()
{
	/* 中央エリアのマーカーの要素を取得 */
	for (auto& Marker : this->pDataList_Object->GetMarkerList(AREA_NO_CENTER))
	{
		/* マーカー名を取得 */
		std::string MarkerName = static_cast<Ground_Marker*>(Marker.get())->GetMarkerName();

		if (MarkerName == "PlayerStart")
		{
			/* プレイヤースタート位置マーカーの場合 */
			this->pDataList_GameStatus->SetPlayerStartPosition(Marker->vecGetBoxCenter());
		}
		else if (MarkerName == "Building")
		{
			/* 建築エリアマーカーの場合 */
			BUILDING_AREA_DATA AreaData;
			AreaData.pBuilding		= nullptr;
			AreaData.vecPosition	= Marker->vecGetBoxCenter();
			this->pDataList_GameStatus->SetBuildAreaPositionList(AreaData);

		}
		else if (MarkerName == "CoreTree")
		{
			/* 神木(防衛対象)マーカーの場合 */
			this->pDataList_GameStatus->SetCoreTreePosition(Marker->vecGetBoxCenter());
		}
	}

	/* 建築エリアの順番調整 */
	Setup_Building_Index();
}

// マーカー情報読み込み(外側エリア)
void Scene_Stage::Setup_LoadMarker_SideArea()
{
	/* 外側エリアのマーカーの要素を取得 */
	for (int iAreaNo = 0; iAreaNo < AREA_NO_MAX; ++iAreaNo)
	{
		if (iAreaNo == AREA_NO_CENTER)
		{
			// 中央エリアはスキップ
			continue;
		}
		for (auto& Marker : this->pDataList_Object->GetMarkerList(iAreaNo))
		{
			/* マーカー名を取得 */
			std::string MarkerName = static_cast<Ground_Marker*>(Marker.get())->GetMarkerName();

			if (MarkerName.starts_with("Enemy_Spawn_"))
			{
				/* 敵スポーンマーカーの場合 */
				/* マーカー情報を作成 */
				ENEMY_SPAWN_POINT_DATA SpawnPointData;
				SpawnPointData.vecPosition = Marker->vecGetBoxCenter();

				// マーカー名からスポーンポイントの種類を取得
				if (MarkerName == "Enemy_Spawn_Plain")
				{
					// 平原
					SpawnPointData.iPointType = ENEMY_SPAWN_POINT_TYPE_PLAIN;
				}
				else if (MarkerName == "Enemy_Spawn_Desert")
				{
					// 砂漠
					SpawnPointData.iPointType = ENEMY_SPAWN_POINT_TYPE_DESERT;
				}
				else if (MarkerName == "Enemy_Spawn_Rocky")
				{
					// 岩場
					SpawnPointData.iPointType = ENEMY_SPAWN_POINT_TYPE_ROCKY;
				}
				else
				{
					// 不明な場合は平地とする
					SpawnPointData.iPointType = ENEMY_SPAWN_POINT_TYPE_PLAIN;
				}

				// スポーンポイント情報を追加
				this->pDataList_GameStatus->SetEnemySpawnPoint(SpawnPointData);
			}
		}
	}
}

// ワールドマップ(外側エリア)設定
// ※ 中央エリアを除く外側のエリアをランダムに設定する
void Scene_Stage::Setup_WoldMap_SideArea()
{
	/* マップデータから外側マップの情報のみを抽出 */
	std::vector<std::string> sideMapNames;
	for (const auto& mapData : this->MapDataList)
	{
		if (mapData.iMapType == WOLD_MAP_TYPE_SIDE)
		{
			sideMapNames.push_back(mapData.MapName);
		}
	}

	// 候補がなければ何もしない
	if (sideMapNames.empty()) {
		return;
	}

	/* 中央エリア以外のエリアのマップ設定を行う */
	for (int iIndex = 0; iIndex < AREA_NO_MAX; ++iIndex)
	{
		/* 中央エリアであるならスキップ */
		if (iIndex == AREA_NO_CENTER) { continue; }

		/* ランダムに一つのエリア情報を取得する */
		int iRandomIndex = (sideMapNames.size() == 1) ? 0 : GetRand(static_cast<int>(sideMapNames.size()) - 1);
		std::string selectedMapName = sideMapNames[iRandomIndex];

		/* 取得したエリア情報からマップを制作する */
		JsonLoad_WoldMap(iIndex, selectedMapName);
	}
}

// オブジェクト配置(中央エリア)
void Scene_Stage::Setup_PlaceObject_CenterArea()
{
	/* データリスト取得 */
	// 3Dモデルデータ管理
	std::shared_ptr<DataList_Model>	pDataList_Model = std::dynamic_pointer_cast<DataList_Model>(gpDataListServer->GetDataList("DataList_Model"));

	/* プレイヤー追加 */
	std::shared_ptr<Character_Player> pPlayer = std::make_shared<Character_Player>();
	pPlayer->SetPosition(this->pDataList_GameStatus->GetPlayerStartPosition());
	pPlayer->InitialSetup();
	this->pDataList_Object->AddObject_Character(pPlayer);

	/* 防衛対象追加 */
	std::shared_ptr<Building_CoreTree> pCoreTree = std::make_shared<Building_CoreTree>();
	pCoreTree->SetPosition(this->pDataList_GameStatus->GetCoreTreePosition());
	pCoreTree->InitialSetup();
	this->pDataList_Object->AddObject_Building(pCoreTree);
}

// オブジェクト配置(外側エリア)
// ※ この関数が呼ばれるたびにランダムな敵がスポーンする
void Scene_Stage::Setup_PlaceObject_SideArea()
{
	/* ランダムなスポーンポイントを決める */
	const auto& spawnList	= this->pDataList_GameStatus->GetEnemySpawnPointList();
	int spawnCount			= static_cast<int>(spawnList.size());
	if (spawnCount == 0) { return; }
	int iRandomIndex = (spawnCount == 1) ? 0 : GetRand(spawnCount - 1);
	ENEMY_SPAWN_POINT_DATA SpawnPoint = spawnList[iRandomIndex];

	/* エネミーのスポーン処理 */
	std::shared_ptr<Npc_Base> pEnemyNpc = std::make_shared<Npc_Base>();
	pEnemyNpc->SetPosition(SpawnPoint.vecPosition);
	pEnemyNpc->SetTeamTag("Enemy");

	/* 現在のスポーンポイントの種類に合致する敵の名前を設定 */
	// ※ 複数の名前が登録されている場合はランダムに選択する
	for (const auto& Table : this->pDataList_GameStatus->GetEnemySpawnTableList())
	{
		if (Table.iPointType == SpawnPoint.iPointType)
		{
			int nameCount = static_cast<int>(Table.EnemyNameList.size());
			if (nameCount > 0)
			{
				int iRandomEnemyIndex = (nameCount == 1) ? 0 : GetRand(nameCount - 1);
				pEnemyNpc->SetName(Table.EnemyNameList[iRandomEnemyIndex]);
				break;
			}
		}
	}

	pEnemyNpc->InitialSetup();
	this->pDataList_Object->AddObject_Character(pEnemyNpc);
}

// 建築エリアの順番調整 
// ※建築エリアの順番を、最も近いエリア同士が連続するように並べ替える
void Scene_Stage::Setup_Building_Index()
{
	/* 建築エリアリストを取得 */
	std::vector<BUILDING_AREA_DATA> BuildingAreaList = this->pDataList_GameStatus->GetBuildAreaPositionList();
	if (BuildingAreaList.size() <= 1) return;

	/* 最初の要素はそのまま、2番以降を並べ替える */
	std::vector<BUILDING_AREA_DATA> sortedList;
	std::vector<bool> used(BuildingAreaList.size(), false);

	/* 0番を追加 */
	sortedList.push_back(BuildingAreaList[0]);
	used[0] = true;

	/* 2番以降を最も近いエリア同士が連続するように並べ替え */
	int currentIdx = 0;
	for (size_t i = 1; i < BuildingAreaList.size(); ++i)
	{
		float minDistSq = std::numeric_limits<float>::max();
		int nearestIdx = -1;
		for (size_t j = 1; j < BuildingAreaList.size(); ++j)
		{
			if (used[j]) continue;
			float dx = BuildingAreaList[currentIdx].vecPosition.x - BuildingAreaList[j].vecPosition.x;
			float dy = BuildingAreaList[currentIdx].vecPosition.y - BuildingAreaList[j].vecPosition.y;
			float dz = BuildingAreaList[currentIdx].vecPosition.z - BuildingAreaList[j].vecPosition.z;
			float distSq = dx * dx + dy * dy + dz * dz;
			if (distSq < minDistSq)
			{
				minDistSq = distSq;
				nearestIdx = static_cast<int>(j);
			}
		}
		if (nearestIdx != -1)
		{
			sortedList.push_back(BuildingAreaList[nearestIdx]);
			used[nearestIdx] = true;
			currentIdx = nearestIdx;
		}
	}

	/* 並べ替えたリストで上書き */
	for (size_t i = 0; i < sortedList.size(); ++i)
	{
		this->pDataList_GameStatus->SetBuildAreaPosition(static_cast<int>(i), sortedList[i]);
	}
}
