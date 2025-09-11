/* �n�`(3D���f��)�N���X�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// ���N���X
#include "Ground_Base.h"

// �n�`(3D���f��)�N���X
class Ground_Model : public Ground_Base
{
	public:
		Ground_Model();				// �R���X�g���N�^
		virtual ~Ground_Model();	// �f�X�g���N�^

		/* �֐� */
		virtual void	InitialSetup()	override;		// �����ݒ�
		virtual void	Draw()			override;		// �`��

		/* �Z�b�^�[ */
		void SetModelHandle(int iModelHandle)	{ this->iModelHandle	= iModelHandle; }	// ���f���n���h����ݒ�
		void SetPosition(VECTOR vecPosition)	{ this->vecPosition		= vecPosition; }	// �I�u�W�F�N�g�̍��W��ݒ�
		void SetRotation(VECTOR vecRotation)	{ this->vecRotation		= vecRotation; }	// �I�u�W�F�N�g�̉�]�ʂ�ݒ�
		void SetScale(VECTOR vecScale)			{ this->vecScale		= vecScale; }		// �I�u�W�F�N�g�̊g�嗦��ݒ�

		/* �Q�b�^�[ */
		int	GetModelHandle()					{ return this->iModelHandle; }			// ���f���n���h�����擾
		VECTOR	GetPosition()					{ return this->vecPosition; }			// �I�u�W�F�N�g�̍��W���擾
		VECTOR	GetRotation()					{ return this->vecRotation; }			// �I�u�W�F�N�g�̉�]�ʂ��擾
		VECTOR	GetScale()						{ return this->vecScale; }				// �I�u�W�F�N�g�̊g�嗦���擾

	private:
		/* �ϐ� */
		int iModelHandle;				// ���f���n���h��
		VECTOR	vecPosition;			// �I�u�W�F�N�g�̍��W
		VECTOR	vecRotation;			// �I�u�W�F�N�g�̉�]��
		VECTOR	vecScale;				// �I�u�W�F�N�g�̊g�嗦(x,y,z�������ꂼ��̊g��{��)

		/* �֐� */
		void SetUpCollision();			// �R���W�����̐ݒ�
};
