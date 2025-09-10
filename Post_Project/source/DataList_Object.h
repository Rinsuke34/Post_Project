/* �f�[�^���X�g"�I�u�W�F�N�g�Ǘ�"�N���X�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// ���ʒ�`
#include "AppFrame.h"
#include "ConstantDefine.h"
#include "StructDefine.h"

/* �O���錾 */
class Ground_Base;
class Ground_Marker;
class Actor_Base;

// �f�[�^���X�g"�I�u�W�F�N�g�Ǘ�"�N���X
class DataList_Object : public DataList_Base
{
	public:
		DataList_Object();				// �R���X�g���N�^
		virtual ~DataList_Object();		// �f�X�g���N�^

		/* �֐� */
		// ���X�g���I�u�W�F�N�g������
		void	InitialSetup_All();		// ���ׂẴI�u�W�F�N�g
		void	InitialSetup_Ground();	// �n�`
		void	InitialSetup_Actor();	// �A�N�^�[

		// �I�u�W�F�N�g�X�V
		void	Update_All();			// ���ׂẴI�u�W�F�N�g
		void	Update_Ground();		// �n�`
		void	Update_Actor();			// �A�N�^�[

		// �I�u�W�F�N�g�`��
		void	Draw_All();				// ���ׂẴI�u�W�F�N�g
		void	Draw_Ground();			// �n�`
		void	Draw_Actor();			// �A�N�^�[

		// �I�u�W�F�N�g�`��(�V���h�E�}�b�v�p)
		void	Draw_All_Shadow();		// ���ׂẴI�u�W�F�N�g
		void	Draw_Ground_Shadow();	// �n�`
		void	Draw_Actor_Shadow();	// �A�N�^�[

		// �I�u�W�F�N�g�`��(�����蔻��)
		void	Draw_All_Collision();		// ���ׂẴI�u�W�F�N�g
		void	Draw_Ground_Collision();	// �n�`
		void	Draw_Actor_Collision();		// �A�N�^�[

		// �폜�t���O���L���ȃI�u�W�F�N�g�폜
		void	DeleteFlagged_AllObject();		// ���ׂẴI�u�W�F�N�g
		void	DeleteFlagged_AllGround();		// �n�`
		void	DeleteFlagged_AllActor();		// �A�N�^�[

		/* �Z�b�^�[ */
		void	AddObject_Ground(std::shared_ptr<Ground_Base> pGround, int iAreaNo)		{ this->pGroundList[iAreaNo].push_back(pGround); };	// �w��G���A�̒n�`�ǉ�
		void	AddObject_Marker(std::shared_ptr<Ground_Marker> pMarker, int iAreaNo)	{ this->pMarkerList[iAreaNo].push_back(pMarker); };	// �w��G���A�̃}�[�J�[�ǉ�
		void	AddObject_Actor(std::shared_ptr<Actor_Base> pActor)						{ this->pActorList.push_back(pActor); };			// �A�N�^�[�ǉ�

		/* �Q�b�^�[ */
		std::vector<std::shared_ptr<Ground_Base>>&		GetGroundList(int iAreaNo)	{ return this->pGroundList[iAreaNo]; }	// �w��G���A�̒n�`���X�g�擾
		std::vector<std::shared_ptr<Ground_Marker>>&	GetMarkerList(int iAreaNo)	{ return this->pMarkerList[iAreaNo]; }	// �w��G���A�̃}�[�J�[���X�g�擾
		std::vector<std::shared_ptr<Actor_Base>>&		GetActorList()				{ return this->pActorList; }			// �A�N�^���X�g�擾

	private:
		/* �ϐ� */
		// ���X�g
		std::vector<std::shared_ptr<Ground_Base>>	pGroundList[AREA_NO_MAX];		// �n�`���X�g[�G���A�ԍ�]
		std::vector<std::shared_ptr<Ground_Marker>> pMarkerList[AREA_NO_MAX];		// �}�[�J�[���X�g
		std::vector<std::shared_ptr<Actor_Base>>	pActorList;						// �A�N�^�[���X�g
};
