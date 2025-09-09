/* �I�u�W�F�N�g�̃x�[�X�N���X�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// �O�����C�u����
#include <DxLib.h>

// �I�u�W�F�N�g�x�[�X�N���X
class Object_Base
{
	public:
		Object_Base();					// �R���X�g���N�^
		virtual ~Object_Base() {};		// �f�X�g���N�^

		/* �֐� */
		virtual void	InitialSetup()		{};	// �����ݒ�
		virtual void	Update()			{};	// �X�V
		virtual void	Draw()				{};	// �`��
		virtual void	Draw_Shadow();			// �`��(�V���h�E�}�b�v�p)
		virtual void	Draw_Collision()	{};	// �`��(�����蔻��)
		
		/* �Z�b�^�[ */
		void	SetDeleteFlg(bool bDeleteFlg) { this->bDeleteFlg = bDeleteFlg; }	// �폜�t���O��ݒ�(�L���Ȃ�΃I�u�W�F�N�g���폜����)

		/* �Q�b�^�[ */
		bool	bGetDeleteFlg() { return this->bDeleteFlg; };			// �폜�t���O���擾

	protected:
		/* �ϐ� */
		bool	bDeleteFlg;		// �폜�t���O(�L���Ȃ�΃I�u�W�F�N�g���폜����)
};

