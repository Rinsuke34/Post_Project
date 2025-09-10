/* �V�[��"�ėp2D�p�[�c�A�j���[�V�����c�[��"�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// �W�����C�u����
#include <memory>
// ���N���X
#include "Scene_Base.h"
// ���ʒ�`
#include "AppStructDefine.h"

/* �O���錾 */
class Scene_UI_Table;

// �V�[��"�ėp2D�p�[�c�A�j���[�V�����c�[��"
class Scene_2DPartsAnimCreateTool : public Scene_Base
{
	public:
		Scene_2DPartsAnimCreateTool();				// �R���X�g���N�^
		virtual ~Scene_2DPartsAnimCreateTool();		// �f�X�g���N�^

		/* �萔 */
		static const int FONT_SIZE			= 16;		// �t�H���g�T�C�Y
		static const int TABLE_SIZE_W		= 400;		// �e�[�u���̉���
		static const int STANDARD_SIZE		= 256;		// �W���p�̎l�p�`�̃T�C�Y
		static const int MAX_INPUT_NUMBER	= 20;		// ���͉\�ȍő啶����(���̓��͗p)

		/* �֐� */
		virtual void	Update()			override;	// �X�V
		virtual void	Draw()				override;	// �`��

	private:
		/* �֐� */
		bool	bLoadPartsAnimData();				// �p�[�c�A�j���[�V�����̃f�[�^�ǂݍ���
		bool	bSavePartsAnimData();				// �p�[�c�A�j���[�V�����̃f�[�^�ۑ�

		void	NewPartsAnimFile();					// �V�K�p�[�c�A�j���[�V�����t�@�C���쐬
		void	AddAnimPaarts();					// �A�j���[�V�����p�p�[�c�ǉ�
		void	AddAnim();							// �A�j���[�V�����ǉ�
		void	AddPartsToAnim();					// �I�𒆂̃A�j���[�V�����Ƀp�[�c��ǉ�
		void	DeleteAnimPaarts();					// �A�j���[�V�����p�p�[�c�폜
		void	DeleteAnim();						// �A�j���[�V�����폜
		void	DeletePartsToAnim();				// �I�𒆂̃A�j���[�V�����Ƀp�[�c���폜
		void	ChangeSelectTime();					// �I�����Ԃ̕ύX
		void	SetUiTableElement();				// �e�[�u��UI�ւ̗v�f�ݒ�
		void	ChangeSelectPartsStatus();			// �I�𒆂̃p�[�c�̏�ԕύX

		void	Draw_BackGround();					// �w�i�`��		
		void	Draw_CurrentPartsAtSelectTime();	// ���݂̃A�j���[�V�����̑I�����Ԃɓo�^���ꂽ�p�[�c��`��
		void	Draw_SelectFileName();				// �t�@�C�����`��
		void	Draw_SelectTime();					// �I�𒆂̎��ԕ`��
		void	Draw_PartsStatus();					// �I�𒆂̃p�[�c�̏�ԕ`��

		/* �ϐ� */
		bool								bOldMouseCursorCenterFixedFlg;	// �c�[���N�����̃}�E�X�̒��S�Œ�t���O
		bool								bOldMouseCursorNotDepictedFlg;	// �c�[���N�����̃}�E�X�J�[�\���`�ʖ����t���O

		bool								bNameSelectedFlg;				// �t�@�C�����I�𒆃t���O
		bool								bTimeSelectedFlg;				// ���ԑI�𒆃t���O
		int									iSelectTime;					// �w�蒆�̃A�j���[�V�����̎���
		int									iAnimMaxTime;					// �A�j���[�V�����̍ő厞��

		std::string														FileName;		// �p�[�c�A�j���[�V�����Q�̖���(==�t�@�C����)
		std::vector<Struct_2DPartsAnim::PARTS_ANIM_PARTS_IMAGE_DATA>	PartsImageData;	// �p�[�c�̉摜�f�[�^(�A�j���[�V�����p�p�[�c�̉摜�f�[�^)
		std::vector<Struct_2DPartsAnim::PARTS_ANIM_ANIM_DATA>			PartsAnimData;	// �p�[�c�A�j���[�V�����̏��(�A�j���[�V�����̃t���[�����Ȃ�)

		std::shared_ptr<Scene_UI_Table> 	paUI_Table[3];					// �e�[�u��UI(0:�p�[�c���X�g, 1:�A�j���[�V�������X�g, 2:�I�����Ԃł̃p�[�c���X�g)
};
