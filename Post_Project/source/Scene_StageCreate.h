/* �V�[��"�X�e�[�W�쐬"�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// ���ʒ�`
#include "AppFrame.h"

/* �O���錾 */
class DataList_Object;
class DataList_StageCreate;

// �V�[��"�X�e�[�W�쐬"
class Scene_StageCreate : public Scene_Base
{
	public:
		Scene_StageCreate();			// �R���X�g���N�^
		virtual ~Scene_StageCreate();	// �f�X�g���N�^

		/* �֐� */
		virtual void	Update()			override;	// �X�V
		virtual void	Draw()				override;	// �`��

	private:
		/* �ϐ� */
		// �f�[�^���X�g�ւ̃|�C���^
		std::shared_ptr<DataList_Object>		pDataList_Object;		// �I�u�W�F�N�g�Ǘ�
		std::shared_ptr<DataList_StageCreate>	pDataList_StageCreate;	// �X�e�[�W�N���G�C�g���Ǘ�
};
