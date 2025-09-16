/* データリスト"オブジェクト管理"クラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "DataList_Object.h"
// 関連クラス
#include "Object_Base.h"
#include "Ground_Base.h"
#include "Actor_Base.h"
#include "Ground_Model.h"

// コンストラクタ
DataList_Object::DataList_Object() : DataList_Base("DataList_Object")
{

}

// デストラクタ
DataList_Object::~DataList_Object()
{

}

/* リスト内オブジェクト初期化 */
// すべてのオブジェクト
void DataList_Object::InitialSetup_All()
{
	InitialSetup_Ground();
	InitialSetup_Actor();
	InitialSetup_Building();
}

// 地形
void DataList_Object::InitialSetup_Ground()
{
	for (int iGridX = 0; iGridX < GRID_NUMBER_X; ++iGridX)
	{
		for (int iGridZ = 0; iGridZ < GRID_NUMBER_Z; ++iGridZ)
		{
			for (auto& GroundList : this->pGroundList[iGridX][iGridZ])
			{
				GroundList->InitialSetup();
			}
		}
	}
}

// アクタ
void DataList_Object::InitialSetup_Actor()
{
	for (auto& ActorList : this->pActorList)
	{
		ActorList->InitialSetup();
	}
}

// 建造物
void DataList_Object::InitialSetup_Building()
{
	for (auto& BuildingList : this->pBuildingList)
	{
		BuildingList->InitialSetup();
	}
}

/* オブジェクト更新 */
// すべてのオブジェクト
void DataList_Object::Update_All()
{
	Update_Ground();
	Update_Actor();
	Update_Building();
}

// 地形
void DataList_Object::Update_Ground()
{
	for (int iGridX = 0; iGridX < GRID_NUMBER_X; ++iGridX)
	{
		for (int iGridZ = 0; iGridZ < GRID_NUMBER_Z; ++iGridZ)
		{
			for (auto& GroundList : this->pGroundList[iGridX][iGridZ])
			{
				GroundList->Update();
			}
		}
	}
}

// アクター
void DataList_Object::Update_Actor()
{
	for (auto& ActorList : this->pActorList)
	{
		ActorList->Update();
	}
}

// 建造物
void DataList_Object::Update_Building()
{
	for (auto& BuildingList : this->pBuildingList)
	{
		BuildingList->Update();
	}
}

/* オブジェクト描画 */
// すべてのオブジェクト
void DataList_Object::Draw_All()
{
	Draw_Ground();
	Draw_Actor();
	Draw_Building();
}

// 地形
void DataList_Object::Draw_Ground()
{
	for (int iGridX = 0; iGridX < GRID_NUMBER_X; ++iGridX)
	{
		for (int iGridZ = 0; iGridZ < GRID_NUMBER_Z; ++iGridZ)
		{
			for (auto& GroundList : this->pGroundList[iGridX][iGridZ])
			{
				GroundList->Draw();
			}
		}
	}
}

// アクター
void DataList_Object::Draw_Actor()
{
	for (auto& ActorList : this->pActorList)
	{
		ActorList->Draw();
	}
}

// 建造物
void DataList_Object::Draw_Building()
{
	for (auto& BuildingList : this->pBuildingList)
	{
		BuildingList->Draw();
	}
}

// オブジェクト描写(シャドウマップ用)
// すべてのオブジェクト
void DataList_Object::Draw_All_Shadow()
{
	Draw_Ground_Shadow();
	Draw_Actor_Shadow();
	Draw_Building_Shadow();
}

// 地形
void DataList_Object::Draw_Ground_Shadow()
{
	for (int iGridX = 0; iGridX < GRID_NUMBER_X; ++iGridX)
	{
		for (int iGridZ = 0; iGridZ < GRID_NUMBER_Z; ++iGridZ)
		{
			for (auto& GroundList : this->pGroundList[iGridX][iGridZ])
			{
				GroundList->Draw_Shadow();
			}
		}
	}
}

// アクター
void DataList_Object::Draw_Actor_Shadow()
{
	for (auto& ActorList : this->pActorList)
	{
		ActorList->Draw_Shadow();
	}
}

// 建造物
void DataList_Object::Draw_Building_Shadow()
{
	for (auto& BuildingList : this->pBuildingList)
	{
		BuildingList->Draw_Shadow();
	}
}

// オブジェクト描写(当たり判定)
// すべてのオブジェクト
void DataList_Object::Draw_All_Collision()
{
	Draw_Ground_Collision();
	Draw_Actor_Collision();
	Draw_Building_Collision();
}

// 地形
void DataList_Object::Draw_Ground_Collision()
{
	for (int iGridX = 0; iGridX < GRID_NUMBER_X; ++iGridX)
	{
		for (int iGridZ = 0; iGridZ < GRID_NUMBER_Z; ++iGridZ)
		{
			for (auto& GroundList : this->pGroundList[iGridX][iGridZ])
			{
				GroundList->Draw_Collision();
			}
		}
	}
}

// アクター
void DataList_Object::Draw_Actor_Collision()
{
	for (auto& ActorList : this->pActorList)
	{
		ActorList->Draw_Collision();
	}
}

// 建造物
void DataList_Object::Draw_Building_Collision()
{
	for (auto& BuildingList : this->pBuildingList)
	{
		BuildingList->Draw_Collision();
	}
}

/* 削除フラグが有効なオブジェクト削除 */
// すべてのオブジェクト
void DataList_Object::DeleteFlagged_AllObject()
{
	DeleteFlagged_AllGround();
	DeleteFlagged_AllActor();
	DeleteFlagged_AllBuilding();
}

// 地形
void DataList_Object::DeleteFlagged_AllGround()
{
	for (int iGridX = 0; iGridX < GRID_NUMBER_X; ++iGridX)
	{
		for (int iGridZ = 0; iGridZ < GRID_NUMBER_Z; ++iGridZ)
		{
			this->pGroundList[iGridX][iGridZ].erase(
				std::remove_if(
					pGroundList[iGridX][iGridZ].begin(),
					pGroundList[iGridX][iGridZ].end(),
					[](const std::shared_ptr<Ground_Base>& pGround)
					{
						// 削除フラグが有効であるか確認
						return pGround && pGround->bGetDeleteFlg();
					}
				),
				pGroundList[iGridX][iGridZ].end()
			);
		}
	}
}

// アクター
void DataList_Object::DeleteFlagged_AllActor()
{
	this->pActorList.erase(
		std::remove_if(
			pActorList.begin(),
			pActorList.end(),
			[](const std::shared_ptr<Actor_Base>& pActor)
			{
				// 削除フラグが有効であるか確認
				return pActor && pActor->bGetDeleteFlg();
			}
		),
		pActorList.end()
	);
}

// 建造物
void DataList_Object::DeleteFlagged_AllBuilding()
{
	this->pBuildingList.erase(
		std::remove_if(
			pBuildingList.begin(),
			pBuildingList.end(),
			[](const std::shared_ptr<Ground_Model>& pBuilding)
			{
				// 削除フラグが有効であるか確認
				return pBuilding && pBuilding->bGetDeleteFlg();
			}
		),
		pBuildingList.end()
	);
}

/* ゲッター */
std::vector<std::shared_ptr<Ground_Base>>& DataList_Object::GetGroundList(int iGridX, int iGridY)
{
	// 引数
	// iGridX	<- X軸のグリッド番号
	// iGridZ	<- Z軸のグリッド番号
	// 戻り値
	// リスト	<- 対象のグリッドに登録されたオブジェクトのリスト

	/* グリッドが範囲内であるか確認 */
	if (iGridX < 0 || iGridX >= GRID_NUMBER_X ||
		iGridY < 0 || iGridY >= GRID_NUMBER_Z)
	{
		// 範囲外である場合
		/* 要素のないダミーリストを作成し、戻り値として返す */
		static std::vector<std::shared_ptr<Ground_Base>> DummyList;
		return DummyList;
	}
	return pGroundList[iGridX][iGridY];
}
