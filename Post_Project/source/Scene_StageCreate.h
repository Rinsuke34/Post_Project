/* �V�[��"�X�e�[�W�쐬"�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// ���ʒ�`
#include "AppFrame.h"

/* �O���錾 */
class DataList_StageCreate;

// �V�[��"�X�e�[�W�쐬"
class Scene_StageCreate : public Scene_Base
{
	public:
		Scene_StageCreate();			// �R���X�g���N�^
		virtual ~Scene_StageCreate();	// �f�X�g���N�^

		/* �萔 */
		// �t�F�[�Y
		static const int PHASE_SELECT_MAP	= 0;	// �}�b�v�I���t�F�[�Y
		static const int PHASE_EDIT_MAP		= 1;	// �}�b�v�ҏW�t�F�[�Y
		// �`�ʍ��W
		static const int DRAW_MAPNAME_X		= 50;	// �}�b�v���`�ʈʒuX
		static const int DRAW_MAPNAME_Y		= 200;	// �}�b�v���`�ʈʒuY

		/* �֐� */
		virtual void	Update()			override;	// �X�V
		virtual void	Draw()				override;	// �`��

	private:
		/* �ϐ� */
		// �f�[�^���X�g�ւ̃|�C���^
		std::shared_ptr<DataList_StageCreate>	pDataList_StageCreate;	// �X�e�[�W�N���G�C�g���Ǘ�
		// ���̑�
		int	iNowPhase;			// ���݂̃t�F�[�Y
		int iSelectMapIndex;	// �I�𒆂̃}�b�v�̃C���f�b�N�X�ԍ�

		/* �֐� */
		void Update_SelectMap();	// �}�b�v�I���t�F�[�Y�̍X�V
		void Update_EditMap();		// �}�b�v�ҏW�t�F�[�Y�̍X�V
		void Draw_SelectMap();		// �}�b�v�I���t�F�[�Y�̕`��
		void Draw_EditMap();		// �}�b�v�ҏW�t�F�[�Y�̕`��
};
