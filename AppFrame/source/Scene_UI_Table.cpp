/* �V�[��"UI(�e�[�u��)"�̒�` */

#include "Scene_UI_Table.h"

// �R���X�g���N�^
Scene_UI_Table::Scene_UI_Table(int iTableWidth, int iDrawPosX, int iDrawPosY, std::string TableName) : SceneBase("Scene_UI_Table", 10000, false)
{
	// ����
	// iTableWidth					<- �e�[�u��UI�̉���
	// iDrawPosX					<- �`�ʈʒuX
	// iDrawPosY					<- �`�ʈʒuY
	// TableName					<- �e�[�u����


	/* ������ */
	this->TableName				= TableName;	// �e�[�u����
	this->iTableWidth			= iTableWidth;	// �e�[�u���̕�
	this->iDrwawPosX			= iDrawPosX;	// �`��ʒuX
	this->iDrwawPosY			= iDrawPosY;	// �`��ʒuY
	this->iSelectElementIndex	= 0;			// �I�𒆂̗v�f�̔ԍ�
	this->bTableSelectedFlg		= false;		// ���̃e�[�u�����I����Ԃł��邩�̃t���O
	this->vecElement.clear();
}

// �f�X�g���N�^
Scene_UI_Table::~Scene_UI_Table()
{

}

// �X�V
void Scene_UI_Table::Update()
{
	/* ���N���b�N */
	if (gstKeyboardInputData.igInput[INPUT_TRG] & MOUSE_INPUT_LEFT)
	{
		/* �}�E�X�J�[�\��������UI�ɏd�Ȃ��Ă����Ԃł��邩�m�F */
		if (gstKeyboardInputData.iMouseX >= this->iDrwawPosX && gstKeyboardInputData.iMouseX <= this->iDrwawPosX + this->iTableWidth &&
			gstKeyboardInputData.iMouseY >= this->iDrwawPosY && gstKeyboardInputData.iMouseY <= this->iDrwawPosY + 16 * 10)
		{
			// �}�E�X�J�[�\��������UI�ɏd�Ȃ��Ă���ꍇ
			this->bTableSelectedFlg = true;
		}
		else
		{
			// �}�E�X�J�[�\��������UI�ɏd�Ȃ��Ă��Ȃ��ꍇ
			this->bTableSelectedFlg = false;
		}
	}

	/* �I��v�f�ύX */
	if (this->bTableSelectedFlg == true)
	{
		/* �㉺�L�[�őI�𒆂̗v�f��ύX */
		if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_UP] == TRUE)
		{
			// ��L�[�������ꂽ�ꍇ
			if (this->iSelectElementIndex > 0)
			{
				this->iSelectElementIndex--;
			}
		}
		else if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_DOWN] == TRUE)
		{
			// ���L�[�������ꂽ�ꍇ
			if (this->iSelectElementIndex + 1 < this->vecElement.size())
			{
				this->iSelectElementIndex++;
			}
		}
	}
}

// �`��
void Scene_UI_Table::Draw()
{
	const int STRING_SIZE = 16; // �����T�C�Y

	/* �t���[���`�� */
	DrawBox(this->iDrwawPosX, this->iDrwawPosY, this->iDrwawPosX + this->iTableWidth, this->iDrwawPosY + STRING_SIZE, GetColor(0, 0, 0), TRUE);
	DrawBox(this->iDrwawPosX, this->iDrwawPosY, this->iDrwawPosX + this->iTableWidth, this->iDrwawPosY + STRING_SIZE * 10, GetColor(0, 0, 0), FALSE);
	if (this->bTableSelectedFlg == true)
	{
		DrawBox(this->iDrwawPosX, this->iDrwawPosY, this->iDrwawPosX + this->iTableWidth, this->iDrwawPosY + STRING_SIZE * 10, GetColor(255, 0, 0), FALSE);
	}

	/* �e�[�u�����`�� */
	DrawString(this->iDrwawPosX, this->iDrwawPosY, this->TableName.c_str(), GetColor(255, 255, 255));

	/* �e�v�f�`�� */
	for (int iIndex = 0; iIndex < this->vecElement.size(); ++iIndex)
	{
		/* �I�𒆂̗v�f�͐ԐF�̘g��`�� */
		if (iIndex == this->iSelectElementIndex)
		{
			// �I�𒆂̗v�f�̕`��
			DrawBox(this->iDrwawPosX, this->iDrwawPosY + STRING_SIZE * (iIndex + 1), this->iDrwawPosX + this->iTableWidth, this->iDrwawPosY + STRING_SIZE * (iIndex + 2), GetColor(255, 0, 0), FALSE);
			DrawString(this->iDrwawPosX + 2, this->iDrwawPosY + STRING_SIZE * (iIndex + 1) + 2, this->vecElement[iIndex].c_str(), GetColor(0, 0, 0));
		}
		else
		{
			DrawString(this->iDrwawPosX + 2, this->iDrwawPosY + STRING_SIZE * (iIndex + 1) + 2, this->vecElement[iIndex].c_str(), GetColor(0, 0, 0));
		}
	}
}
