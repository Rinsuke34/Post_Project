/* �A�N�^�̃x�[�X�N���X�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// ���N���X
#include "Object_Base.h"
// ���ʒ�`
#include "AppFrame.h"

/* �O���錾 */
class DataList_Object;

// �A�N�^�x�[�X�N���X
class Actor_Base : public Object_Base
{
	public:
		Actor_Base();					// �R���X�g���N�^
		virtual ~Actor_Base() {};		// �f�X�g���N�^

		/* �֐� */
		virtual void	Update() override;	// �X�V

		bool	bCheckTeamTag(std::string TeamTag);	// �`�[���^�O�̊m�F
		int		iCheckCurrentAreaNo();				// ���݂̃G���A�ԍ����擾

		/* �Z�b�^�[ */
		void SetPosition(VECTOR vecPosition)				{ this->vecBasePosition			= vecPosition; }	// ����W�̐ݒ�
		void SetTeamTag(std::string TeamTag)				{ this->TeamTag.push_back(TeamTag); }				// �`�[���^�O�̐ݒ�
		void SetEnableGravityFlg(bool bEnable)				{ this->bEnableGravityFlg		= bEnable; }		// �d�͗L���t���O�̐ݒ�
		void SetGravityVelocity(float fVelocity)			{ this->fGravityVelocity		= fVelocity; }		// �d�͂ɂ�闎�����x�̐ݒ�
		void SetGravityAcceleration(float fAcceleration)	{ this->fGravityAcceleration	= fAcceleration; }	// �d�͉����x�̐ݒ�

		/* �Q�b�^�[ */
		VECTOR						GetPosition()				{ return this->vecBasePosition; }		// ����W�̎擾
		std::vector<std::string>&	GetTeamTag()				{ return this->TeamTag; }				// �`�[���^�O�̎擾
		bool						GetEnableGravityFlg()		{ return this->bEnableGravityFlg; }		// �d�͗L���t���O�̎擾
		float						GetGravityVelocity()		{ return this->fGravityVelocity; }		// �d�͂ɂ�闎�����x�̎擾
		float						GetGravityAcceleration()	{ return this->fGravityAcceleration; }	// �d�͉����x�̎擾

	protected:
		/* �ϐ� */
		// �f�[�^���X�g�ւ̃|�C���^
		std::shared_ptr<DataList_Object>		pDataList_Object;		// �I�u�W�F�N�g�Ǘ�
		// ��Ԍn
		VECTOR						vecBasePosition;		// ����W(�����̈ʒu)
		std::vector<std::string>	TeamTag;				// �`�[���^�O
		bool						bEnableGravityFlg;		// �d�͗L���t���O
		float						fGravityVelocity;		// �d�͂ɂ�闎�����x
		float						fGravityAcceleration;	// �d�͉����x

		/* �֐� */
		void Update_ApplyGravity_Simple();	// �d�͏���(�Ȉ�)
};
