/* �f�[�^���X�g"�I�u�W�F�N�g�Ǘ�"�N���X�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �w�b�_�t�@�C��
#include "DataList_Object.h"
// �֘A�N���X
#include "Object_Base.h"
#include "Ground_Base.h"
#include "Actor_Base.h"

// �R���X�g���N�^
DataList_Object::DataList_Object() : DataList_Base("DataList_Object")
{

}

// �f�X�g���N�^
DataList_Object::~DataList_Object()
{

}

/* ���X�g���I�u�W�F�N�g������ */
// ���ׂẴI�u�W�F�N�g
void DataList_Object::InitialSetup_All()
{
	InitialSetup_Ground();
	InitialSetup_Actor();
}

// �n�`
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

// �A�N�^
void DataList_Object::InitialSetup_Actor()
{
	for (auto& ActorList : this->pActorList)
	{
		ActorList->InitialSetup();
	}
}

/* �I�u�W�F�N�g�X�V */
// ���ׂẴI�u�W�F�N�g
void DataList_Object::Update_All()
{
	Update_Ground();
	Update_Actor();
}

// �n�`
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

// �A�N�^�[
void DataList_Object::Update_Actor()
{
	for (auto& ActorList : this->pActorList)
	{
		ActorList->Update();
	}
}

/* �I�u�W�F�N�g�`�� */
// ���ׂẴI�u�W�F�N�g
void DataList_Object::Draw_All()
{
	Draw_Ground();
	Draw_Actor();
}

// �n�`
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

// �A�N�^�[
void DataList_Object::Draw_Actor()
{
	for (auto& ActorList : this->pActorList)
	{
		ActorList->Draw();
	}
}

// �I�u�W�F�N�g�`��(�V���h�E�}�b�v�p)
// ���ׂẴI�u�W�F�N�g
void DataList_Object::Draw_All_Shadow()
{
	Draw_Ground_Shadow();
	Draw_Actor_Shadow();
}

// �n�`
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

// �A�N�^�[
void DataList_Object::Draw_Actor_Shadow()
{
	for (auto& ActorList : this->pActorList)
	{
		ActorList->Draw_Shadow();
	}
}

// �I�u�W�F�N�g�`��(�����蔻��)
// ���ׂẴI�u�W�F�N�g
void DataList_Object::Draw_All_Collision()
{
	Draw_Ground_Collision();
	Draw_Actor_Collision();
}

// �n�`
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

// �A�N�^�[
void DataList_Object::Draw_Actor_Collision()
{
	for (auto& ActorList : this->pActorList)
	{
		ActorList->Draw_Collision();
	}
}

/* �폜�t���O���L���ȃI�u�W�F�N�g�폜 */
// ���ׂẴI�u�W�F�N�g
void DataList_Object::DeleteFlagged_AllObject()
{
	DeleteFlagged_AllGround();
	DeleteFlagged_AllActor();
}

// �n�`
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
					// �폜�t���O���L���ł��邩�m�F
					return pGround && pGround->bGetDeleteFlg();
				}
			),
			pGroundList[iAreaNo].end()
		);
	}
}

// �A�N�^�[
void DataList_Object::DeleteFlagged_AllActor()
{
	this->pActorList.erase(
		std::remove_if(
			pActorList.begin(),
			pActorList.end(),
			[](const std::shared_ptr<Actor_Base>& pActor)
			{
				// �폜�t���O���L���ł��邩�m�F
				return pActor && pActor->bGetDeleteFlg();
			}
		),
		pActorList.end()
	);
}
