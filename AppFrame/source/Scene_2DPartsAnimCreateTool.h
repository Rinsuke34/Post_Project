/* �V�[��"�ėp2D�p�[�c�A�j���[�V�����c�[��"�̐錾 */

#pragma once
#include "SceneBase.h"
#include "AppStructDefine.h"
#include "Scene_UI_Table.h"
#include <memory>

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
		bool	bLoadPartsAnimData();			// �p�[�c�A�j���[�V�����̃f�[�^�ǂݍ���
		bool	bSavePartsAnimData();			// �p�[�c�A�j���[�V�����̃f�[�^�ۑ�

		/* �ϐ� */
		bool								bOldMouseCursorCenterFixedFlg;	// �c�[���N�����̃}�E�X�̒��S�Œ�t���O
		bool								bOldMouseCursorNotDepictedFlg;	// �c�[���N�����̃}�E�X�J�[�\���`�ʖ����t���O

		Struct_2DPartsAnim::PARTS_ANIM_DATA	stPartsAnimData;				// �p�[�c�A�j���[�V�����̃f�[�^

		std::shared_ptr<Scene_UI_Table> 	paUI_Table[4];					// �e�[�u��UI(0:�p�[�c���X�g, 1:�A�j���[�V�������X�g, 2:�t���[�����X�g, 3:�I���t���[���̃p�[�c���X�g)
};
