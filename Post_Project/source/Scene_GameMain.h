/* �V�[��"�Q�[�����C��"�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// ���ʒ�`
#include "AppFrame.h"

/* �O���錾 */
class DataList_Object;
class DataList_GameStatus;

// �V�[��"�Q�[�����C��"
class Scene_GameMain : public Scene_Base
{
	public:
		Scene_GameMain();				// �R���X�g���N�^
		virtual ~Scene_GameMain();		// �f�X�g���N�^

		/* �֐� */
		virtual void	Update()			override;	// �X�V

	private:
		/* �ϐ� */
		// �f�[�^���X�g�ւ̃|�C���^
		std::shared_ptr<DataList_Object>		pDataList_Object;		// �I�u�W�F�N�g�Ǘ�
		std::shared_ptr<DataList_GameStatus>	pDataList_GameStatus;	// �Q�[����ԊǗ�
};
