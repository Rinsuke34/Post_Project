/* �V�[��"UI(�{�^��)"�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// �W�����C�u����
#include <vector>
// ���N���X
#include "Scene_Base.h"
// ���ʒ�`
#include "AppVariableDefine.h"

// �V�[��"UI(�{�^��)"
class Scene_UI_Button : public Scene_Base
{
	public:
		Scene_UI_Button(int iButtonWidth, int iDrawPosX, int iDrawPosY, std::string ButtonName, int iInputType);	// �R���X�g���N�^
		virtual ~Scene_UI_Button();		// �f�X�g���N�^

		/* �N���X���Ŏg�p����萔 */
		static const int INPUT_TYPE_TOGGLE	= 0;	// ���̓^�C�v:�g�O��
		static const int INPUT_TYPE_TRIGGER	= 1;	// ���̓^�C�v:�g���K�[

		/* �֐� */
		virtual void	Update()			override;	// �X�V
		virtual void	Draw()				override;	// �`��

		/* �Q�b�^�[ */
		bool	bGetSelectFlg()				{ return this->bSelectFlg; }	// �I����Ԃł��邩�̃t���O���擾

	private:
		/* �ϐ� */
		int			iButtonWidth;		// �e�[�u���̕�
		int			iDrwawPosX;			// �`��ʒuX
		int			iDrwawPosY;			// �`��ʒuY
		bool		bSelectFlg;			// �I����Ԃł��邩�̃t���O
		int			iInputType;			// ���̓^�C�v(0:�g�O��, 1:�g���K�[)
		std::string	ButtonName;			// �{�^����
};
