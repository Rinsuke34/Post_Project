/* データリスト"オブジェクト管理"クラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "DataList_Object.h"
// 関連クラス
#include "Object_Base.h"
#include "Ground_Base.h"
#include "Character_Base.h"
#include "Building_Base.h"
#include "Item_Base.h"
#include "Bullet_Base.h"

// コンストラクタ
DataList_Object::DataList_Object() : DataList_Base("DataList_Object")
{

}

/* リスト内オブジェクト初期化 */
// すべてのオブジェクト
void DataList_Object::InitialSetup_All()
{
	InitialSetup_Ground();
	InitialSetup_Character();
	InitialSetup_Building();
	InitialSetup_Item();
	InitialSetup_Bullet();
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

// キャラクター
void DataList_Object::InitialSetup_Character()
{
	for (auto& ActorList : this->pCharacterList)
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

// アイテム
void DataList_Object::InitialSetup_Item()
{
	for (auto& ItemList : this->pItemList)
	{
		ItemList->InitialSetup();
	}
}

// バレット
void DataList_Object::InitialSetup_Bullet()
{
	for (auto& BulletList : this->pBulletList)
	{
		BulletList->InitialSetup();
	}
}

/* オブジェクト更新 */
// すべてのオブジェクト
void DataList_Object::Update_All()
{
	Update_Ground();
	Update_Character();
	Update_Building();
	Update_Item();
	Update_Bullet();
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

// キャラクター
void DataList_Object::Update_Character()
{
	for (auto& ActorList : this->pCharacterList)
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

// アイテム
void DataList_Object::Update_Item()
{
	for (auto& ItemList : this->pItemList)
	{
		ItemList->Update();
	}
}

// バレット
void DataList_Object::Update_Bullet()
{
	for (auto& BulletList : this->pBulletList)
	{
		BulletList->Update();
	}
}

/* オブジェクト描画 */
// すべてのオブジェクト
void DataList_Object::Draw_All()
{
	Draw_Ground();
	Draw_Character();
	Draw_Building();
	Draw_Item();
	Draw_Bullet();
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

// キャラクター
void DataList_Object::Draw_Character()
{
	for (auto& ActorList : this->pCharacterList)
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

// アイテム
void DataList_Object::Draw_Item()
{
	for (auto& ItemList : this->pItemList)
	{
		ItemList->Draw();
	}
}

// バレット
void DataList_Object::Draw_Bullet()
{
	for (auto& BulletList : this->pBulletList)
	{
		BulletList->Draw();
	}
}

// オブジェクト描写(シャドウマップ用)
// すべてのオブジェクト
void DataList_Object::Draw_All_Shadow()
{
	Draw_Ground_Shadow();
	Draw_Character_Shadow();
	Draw_Building_Shadow();
	Draw_Item_Shadow();
	Draw_Bullet_Shadow();
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

// キャラクター
void DataList_Object::Draw_Character_Shadow()
{
	for (auto& ActorList : this->pCharacterList)
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

// アイテム
void DataList_Object::Draw_Item_Shadow()
{
	for (auto& ItemList : this->pItemList)
	{
		ItemList->Draw_Shadow();
	}
}

// バレット
void DataList_Object::Draw_Bullet_Shadow()
{
	for (auto& BulletList : this->pBulletList)
	{
		BulletList->Draw_Shadow();
	}
}


// オブジェクト描写(当たり判定)
// すべてのオブジェクト
void DataList_Object::Draw_All_Collision()
{
	Draw_Ground_Collision();
	Draw_Character_Collision();
	Draw_Building_Collision();
	Draw_Item_Collision();
	Draw_Bullet_Collision();
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

// キャラクター
void DataList_Object::Draw_Character_Collision()
{
	for (auto& ActorList : this->pCharacterList)
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

// アイテム
void DataList_Object::Draw_Item_Collision()
{
	for (auto& ItemList : this->pItemList)
	{
		ItemList->Draw_Collision();
	}
}

// バレット
void DataList_Object::Draw_Bullet_Collision()
{
	for (auto& BulletList : this->pBulletList)
	{
		BulletList->Draw_Collision();
	}
}

/* 削除フラグが有効なオブジェクト削除 */
// すべてのオブジェクト
void DataList_Object::DeleteFlagged_AllObject()
{
	DeleteFlagged_AllGround();
	DeleteFlagged_AllCharacter();
	DeleteFlagged_AllBuilding();
	DeleteFlagged_AllItem();
	DeleteFlagged_AllBullet();
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

// キャラクター
void DataList_Object::DeleteFlagged_AllCharacter()
{
	this->pCharacterList.erase(
		std::remove_if(
			pCharacterList.begin(),
			pCharacterList.end(),
			[](const std::shared_ptr<Actor_Base>& pActor)
			{
				// 削除フラグが有効であるか確認
				return pActor && pActor->bGetDeleteFlg();
			}
		),
		pCharacterList.end()
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

// アイテム
void DataList_Object::DeleteFlagged_AllItem()
{
	this->pItemList.erase(
		std::remove_if(
			pItemList.begin(),
			pItemList.end(),
			[](const std::shared_ptr<Item_Base>& pItem)
			{
				// 削除フラグが有効であるか確認
				return pItem && pItem->bGetDeleteFlg();
			}
		),
		pItemList.end()
	);
}

// バレット
void DataList_Object::DeleteFlagged_AllBullet()
{
	this->pBulletList.erase(
		std::remove_if(
			pBulletList.begin(),
			pBulletList.end(),
			[](const std::shared_ptr<Bullet_Base>& pBullet)
			{
				// 削除フラグが有効であるか確認
				return pBullet && pBullet->bGetDeleteFlg();
			}
		),
		pBulletList.end()
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
