/* �v���C���[�̓��͂��擾����N���X�̐錾 */

#pragma once
/* �g�p����v�f�̃C���N���[�h */
// �W�����C�u����
#include <cstring>
// �O�����C�u����
#include <DxLib.h>

// ���͎擾�N���X
class PlayerInput
{
	public:
		PlayerInput();					// �R���X�g���N�^
		virtual ~PlayerInput() {};		// �f�X�g���N�^

		/* �֐� */
		void	Input();				// �v���C���[�̓��͎擾

	private:
		/* �֐� */
		void	InputJoypad();			// �W���C�p�b�h
		void	InputKeyboard();		// �L�[�{�[�h���}�E�X

	protected:
};
