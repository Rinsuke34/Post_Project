/* �V�[��"�^�C�g��"�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// ���ʒ�`
#include "AppFrame.h"

// �V�[��"�^�C�g��"
class Scene_Title : public Scene_Base
{
	public:
		Scene_Title();				// �R���X�g���N�^
		virtual ~Scene_Title();		// �f�X�g���N�^

		/* �֐� */
		virtual void	Update()			override;	// �X�V
		virtual void	Draw()				override;	// �`��
};
