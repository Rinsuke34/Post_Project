/* �f�[�^���X�g"�Q�[����ԊǗ�"�N���X�̐錾 */

#pragma once
/* �g�p����v�f�̃C���N���[�h */
// ���ʒ�`
#include "AppFrame.h"

// �f�[�^���X�g"�Q�[����ԊǗ�"�N���X
class DataList_GameStatus : public DataList_Base
{
	public:
		DataList_GameStatus();			// �R���X�g���N�^
		virtual ~DataList_GameStatus();	// �f�X�g���N�^

		/* �Z�b�^�[ */
		void SetPlayerPosition_WoldMap(VECTOR vecPosition)	{ this->vecPlayerPosition_WoldMap = vecPosition; }	// �v���C���[�̃��[���h�}�b�v���W�̐ݒ�

		/* �Q�b�^�[ */
		VECTOR GetPlayerPosition_WoldMap()					{ return this->vecPlayerPosition_WoldMap; }			// �v���C���[�̃��[���h�}�b�v���W�̎擾

	private:
		/* �ϐ� */
		VECTOR	vecPlayerPosition_WoldMap;	// �v���C���[�̃��[���h�}�b�v���W
};
