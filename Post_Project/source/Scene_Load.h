/* �V�[��"���[�h���"�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// ���ʒ�`
#include "AppFrame.h"

// �V�[��"���[�h���"
class Scene_Load : public Scene_Base
{
	public:
		Scene_Load();				// �R���X�g���N�^
		virtual ~Scene_Load();		// �f�X�g���N�^

		/* �֐� */
		virtual void	Update()			override;	// �X�V
		virtual void	Draw()				override;	// �`��
};
