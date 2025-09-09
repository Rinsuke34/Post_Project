/* データリスト"オブジェクト管理"クラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "DataList_Object.h"
// 関連クラス
#include "Object_Base.h"
#include "Ground_Base.h"
#include "Actor_Base.h"

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
}

// 地形
void DataList_Object::InitialSetup_Ground()
{
	for (int iAreaNo = 0; iAreaNo < AREA_NO_MAX; ++iAreaNo)
	{
		for (auto& GroundList : this->pGroundList[iAreaNo])
		{
			GroundList->InitialSetup();
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

/* オブジェクト更新 */
// すべてのオブジェクト
void DataList_Object::Update_All()
{
	Update_Ground();
	Update_Actor();
}

// 地形
void DataList_Object::Update_Ground()
{
	for (int iAreaNo = 0; iAreaNo < AREA_NO_MAX; ++iAreaNo)
	{
		for (auto& GroundList : this->pGroundList[iAreaNo])
		{
			GroundList->Update();
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

/* オブジェクト描画 */
// すべてのオブジェクト
void DataList_Object::Draw_All()
{
	Draw_Ground();
	Draw_Actor();
}

// 地形
void DataList_Object::Draw_Ground()
{
	for (int iAreaNo = 0; iAreaNo < AREA_NO_MAX; ++iAreaNo)
	{
		for (auto& GroundList : this->pGroundList[iAreaNo])
		{
			GroundList->Draw();
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

// オブジェクト描写(シャドウマップ用)
// すべてのオブジェクト
void DataList_Object::Draw_All_Shadow()
{
	Draw_Ground_Shadow();
	Draw_Actor_Shadow();
}

// 地形
void DataList_Object::Draw_Ground_Shadow()
{
	for (int iAreaNo = 0; iAreaNo < AREA_NO_MAX; ++iAreaNo)
	{
		for (auto& GroundList : this->pGroundList[iAreaNo])
		{
			GroundList->Draw_Shadow();
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

// オブジェクト描写(当たり判定)
// すべてのオブジェクト
void DataList_Object::Draw_All_Collision()
{
	Draw_Ground_Collision();
	Draw_Actor_Collision();
}

// 地形
void DataList_Object::Draw_Ground_Collision()
{
	for (int iAreaNo = 0; iAreaNo < AREA_NO_MAX; ++iAreaNo)
	{
		for (auto& GroundList : this->pGroundList[iAreaNo])
		{
			GroundList->Draw_Collision();
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

/* 削除フラグが有効なオブジェクト削除 */
// すべてのオブジェクト
void DataList_Object::DeleteFlagged_AllObject()
{
	DeleteFlagged_AllGround();
	DeleteFlagged_AllActor();
}

// 地形
void DataList_Object::DeleteFlagged_AllGround()
{
	for (int iAreaNo = 0; iAreaNo < AREA_NO_MAX; ++iAreaNo)
	{
		this->pGroundList[iAreaNo].erase(
			std::remove_if(
				pGroundList[iAreaNo].begin(),
				pGroundList[iAreaNo].end(),
				[](const std::shared_ptr<Ground_Base>& pGround)
				{
					// 削除フラグが有効であるか確認
					return pGround && pGround->bGetDeleteFlg();
				}
			),
			pGroundList[iAreaNo].end()
		);
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
