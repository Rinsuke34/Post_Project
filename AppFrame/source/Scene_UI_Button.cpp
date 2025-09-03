/* �V�[��"UI(�{�^��)"�̒�` */

#include "Scene_UI_Button.h"

// �R���X�g���N�^
Scene_UI_Button::Scene_UI_Button(int iButtonWidth, int iDrawPosX, int iDrawPosY, std::string ButtonName, int iInputType) : SceneBase("Scene_UI_Table", 10000, false)
{
	// ����
	// iButtonWidth					<- �{�^��UI�̉���
	// iDrawPosX					<- �`�ʈʒuX
	// iDrawPosY					<- �`�ʈʒuY
	// ButtonName					<- �e�[�u����
	// iInputType					<- ���̓^�C�v(0:�g�O��, 1:�g���K�[)

	/* ������ */
	this->iButtonWidth	= iButtonWidth;
	this->iDrwawPosX	= iDrawPosX;
	this->iDrwawPosY	= iDrawPosY;
	this->iInputType	= iInputType;
	this->ButtonName	= ButtonName;

	this->bSelectFlg	= false;
}

// �f�X�g���N�^
Scene_UI_Button::~Scene_UI_Button()
{

}

// �X�V
void Scene_UI_Button::Update()
{
	/* �g���K���͂ł���Ȃ���͂�OFF�ɐݒ肷�� */
	if (this->iInputType == INPUT_TYPE_TRIGGER)
	{
		this->bSelectFlg = false;
	}

	/* ���N���b�N */
	if (gstKeyboardInputData.igInput[INPUT_TRG] & MOUSE_INPUT_LEFT)
	{
		/* �}�E�X�J�[�\��������UI�ɏd�Ȃ��Ă����Ԃł��邩�m�F */
		if (gstKeyboardInputData.iMouseX >= this->iDrwawPosX && gstKeyboardInputData.iMouseX <= this->iDrwawPosX + this->iButtonWidth &&
			gstKeyboardInputData.iMouseY >= this->iDrwawPosY && gstKeyboardInputData.iMouseY <= this->iDrwawPosY + 16)
		{
			// �}�E�X�J�[�\��������UI�ɏd�Ȃ��Ă���ꍇ
			/* ���̓^�C�v�ɉ��������������{ */
			switch (this->iInputType)
			{
				// �g�O������
				case INPUT_TYPE_TOGGLE:
					this->bSelectFlg = !this->bSelectFlg;
					break;

				// �g���K����
				case INPUT_TYPE_TRIGGER:
					this->bSelectFlg = true;
					break;

				default:
					break;
			}
		}
	}
}

// �`��
void Scene_UI_Button::Draw()
{
	const int STRING_SIZE = 16; // �����T�C�Y

	/* �{�^���`�� */
	DrawBox(this->iDrwawPosX, this->iDrwawPosY, this->iDrwawPosX + this->iButtonWidth, this->iDrwawPosY + STRING_SIZE, GetColor(0, 0, 0), TRUE);

	/* �g�`�� */
	if (this->bSelectFlg)
	{
		// �I��
		DrawBox(this->iDrwawPosX, this->iDrwawPosY, this->iDrwawPosX + this->iButtonWidth, this->iDrwawPosY + STRING_SIZE, GetColor(255, 0, 0), FALSE);
	}
	else
	{
		// ��I��
		DrawBox(this->iDrwawPosX, this->iDrwawPosY, this->iDrwawPosX + this->iButtonWidth, this->iDrwawPosY + STRING_SIZE, GetColor(255, 255, 255), FALSE);
	}

	/* �{�^�����`�� */
	DrawString(this->iDrwawPosX, this->iDrwawPosY, this->ButtonName.c_str(), GetColor(255, 255, 255));
}
