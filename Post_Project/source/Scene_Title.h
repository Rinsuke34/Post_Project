/* �V�[��"�^�C�g��"�̐錾 */

#pragma once
#include "AppFrame.h"

// �V�[��"�^�C�g��"
class Scene_Title : public SceneBase
{
	public:
		Scene_Title();				// �R���X�g���N�^
		virtual ~Scene_Title();		// �f�X�g���N�^

		virtual void	Process()			override;	// �v�Z
		virtual void	Draw()				override;	// �`��
};
