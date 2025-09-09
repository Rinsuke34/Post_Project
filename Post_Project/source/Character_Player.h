/* �v���C���[�N���X�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// ���N���X
#include "Character_Base.h"

/* �O���錾 */
class DataList_GameStatus;

// �v���C���[�N���X
class Character_Player : public Character_Base
{
	public:
		Character_Player();				// �R���X�g���N�^
		virtual ~Character_Player();	// �f�X�g���N�^

		/* �֐� */
		virtual void	Update()	override;	// �X�V
		virtual void	Draw()		override;	// �`��

	protected:
		/* �ϐ� */
		// �f�[�^���X�g�ւ̃|�C���^
		std::shared_ptr<DataList_GameStatus>			pDataList_GameStatus;				// �Q�[����ԊǗ�
		std::shared_ptr<DataList_2DPartsAnimCreateTool>	pDataList_2DPartsAnimCreateTool;	// 2D�p�[�c�A�j���[�V�����c�[��
		// �摜�f�[�^
		int iScreenHandle_Animation;	// �A�j���[�V�����`�ʗp
		// �A�j���[�V�����֌W
		std::string		AnimFileName;	// �A�j���[�V�����t�@�C����
		std::string		NowMotionName;	// ���݂̃��[�V������
		int				iMotionCount;	// ���[�V�����J�E���g

		/* �֐� */
		void	Update_ApplyGravity();		// �d�͏���
		void	Update_ApplyMovement();		// �ړ�����
		void	Update_Animation();			// �A�j���[�V�����X�V
		void	Draw_Animation();			// �A�j���[�V�����`��
};
