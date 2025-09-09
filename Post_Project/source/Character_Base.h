/* �L�����N�^�[�̃x�[�X�N���X�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// ���N���X
#include "Actor_Base.h"
// ���ʒ�`
#include "AppFrame.h"

// �L�����N�^�[�x�[�X�N���X
class Character_Base : public Actor_Base
{
	public:
		Character_Base();					// �R���X�g���N�^
		virtual ~Character_Base() {};		// �f�X�g���N�^

		/* �֐� */
		virtual void	Update()			override;	// �X�V
		virtual void	Draw_Shadow()		override;	// �`��(�V���h�E�}�b�v�p)
		virtual void	Draw_Collision()	override;	// �`��(�����蔻��)

		/* �Z�b�^�[ */
		// �X�e�[�^�X�n
		void SetHealth(int iHealth)					{ this->iHealth			=	std::clamp(iHealth, 0, this->iMaxHealth); }	// �̗͂̐ݒ�
		void HelthChange(int iHelthChange)			{ this->iMaxHealth		+=	iHelthChange; }								// �����̒l���̗͂�ϓ�
		void SetMaxHelth(int iMaxHelth)				{ this->iMaxHealth		= iMaxHelth; }									// �ő�̗͂̐ݒ�
		void SetSpeed(int iSpeed)					{ this->iSpeed			= iSpeed; }										// ���x�̐ݒ�
		// ��Ԍn
		void SetDeadFlg(bool bDeadFlg)				{ this->bDeadFlg		= bDeadFlg; }									// ���S�t���O�̐ݒ�
		void SetInvicibleTime(int iInvicibleTime)	{ this->iInvincibleTime = iInvicibleTime; }								// ���G���Ԃ̐ݒ�

		/* �Q�b�^�[ */
		// �X�e�[�^�X�n
		int		iGetHealth()		{ return this->iHealth; }			// �̗͂̎擾
		int		iGetMaxHealth()		{ return this->iMaxHealth; }		// �ő�̗͂̎擾
		int		iGetSpeed()			{ return this->iSpeed; }			// ���x�̎擾
		// ��Ԍn
		bool	bGetDeadFlg()		{ return this->bDeadFlg; }			// ���S�t���O�̎擾
		int		GetInvincibleTime() { return this->iInvincibleTime; }	// ���G���Ԃ̎擾

	protected:
		/* �ϐ� */
		// �X�e�[�^�X�n
		int	iHealth;			// �̗�
		int	iMaxHealth;			// �ő�̗�
		int iSpeed;				// ���x
		// ��Ԍn
		bool bDeadFlg;			// ���S�t���O
		int iInvincibleTime;	// �c�薳�G����(�t���[����)
		// �R���W����
		Struct_Collision::COLLISION_BOX	stBox;

		/* �֐� */
		void Update_Collision();	// �R���W�����X�V
};
