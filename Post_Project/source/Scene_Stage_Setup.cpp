/* シーン"ステージ"の定義 */
// ※セットアップ用の処理部分のみ

/* 使用する要素のインクルード */
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
			this->pDataList_GameStatus->SetBuildAreaPositionList(Marker->vecGetBoxCenter());
		}
		else if (MarkerName == "CoreTree")
		{
			/* 神木(防衛対象)マーカーの場合 */
			this->pDataList_GameStatus->SetCoreTreePosition(Marker->vecGetBoxCenter());
		}
	}
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
	this->pDataList_Object->AddObject_Actor(pPlayer);

	/* 防衛対象追加 */
	std::shared_ptr<Building_CoreTree> pCoreTree = std::make_shared<Building_CoreTree>();
	pCoreTree->SetModelHandle(pDataList_Model->iGetModel("CoreTree/CoreTree"));
	pCoreTree->SetPosition(this->pDataList_GameStatus->GetCoreTreePosition());
	pCoreTree->InitialSetup();
	this->pDataList_Object->AddObject_Building(pCoreTree);

	/* 建築エリア追加 */
	// 未実装
}

// オブジェクト配置(外側エリア)
void Scene_Stage::Setup_PlaceObject_SideArea()
{
	/* 平原エリアのスポーンポイントにスライムをセット(テスト処理) */
	for (const auto& SpawnPoint : this->pDataList_GameStatus->GetEnemySpawnPointList())
	{
		if (SpawnPoint.iPointType == ENEMY_SPAWN_POINT_TYPE_PLAIN)
		{
			// スライムを生成
			std::shared_ptr<Npc_Base> pSlime = std::make_shared<Npc_Base>();
			pSlime->SetPosition(SpawnPoint.vecPosition);
			pSlime->SetTeamTag("Enemy");
			pSlime->SetName("Slime_Blue");
			pSlime->InitialSetup();
			this->pDataList_Object->AddObject_Actor(pSlime);
			break;	// テストのため1体のみ生成
		}
	}
}
