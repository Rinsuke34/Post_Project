/* �V�[��"�X�e�[�W�쐬"�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// ���ʒ�`
#include "AppFrame.h"

// �V�[��"�X�e�[�W�쐬"
class Scene_StageCreate : public Scene_Base
{
	public:
		Scene_StageCreate();			// �R���X�g���N�^
		virtual ~Scene_StageCreate();	// �f�X�g���N�^

		/* �֐� */
		virtual void	Update()			override;	// �X�V
		virtual void	Draw()				override;	// �`��
};
