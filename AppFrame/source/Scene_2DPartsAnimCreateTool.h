/* �V�[��"�ėp2D�p�[�c�A�j���[�V�����c�[��"�̐錾 */

#pragma once
#include "SceneBase.h"
#include <vector>

// �V�[��"�ėp2D�p�[�c�A�j���[�V�����c�[��"
class Scene_2DPartsAnimCreateTool : public SceneBase
{
	public:
		Scene_2DPartsAnimCreateTool();				// �R���X�g���N�^
		virtual ~Scene_2DPartsAnimCreateTool();		// �f�X�g���N�^

		virtual void	Process()			override;	// �v�Z
		virtual void	Draw()				override;	// �`��

	private:
		/* �֐� */

		/* �ϐ� */
		std::vector<int> iSelectGrHandle;	// �I�������摜�̃O���t�B�b�N�n���h��
		std::vector<std::string> stSelectGrPath;
};
