/* �V�[��"�^�C�g��"�̒�` */

#include "Scene_Title.h"

// �R���X�g���N�^
Scene_Title::Scene_Title() : SceneBase("Scene_Title", 0, false)
{

}

// �f�X�g���N�^
Scene_Title::~Scene_Title()
{

}

// �v�Z
void Scene_Title::Process()
{
	/* ���͑҂� */
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_Z] == TRUE)
	{
		/* �V�[���폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;

		/* 2D�p�[�c�A�j���[�V�����쐬�c�[�����N�� */
		PUBLIC_FUNCTION::Start2DPartsAnimCreateTool();
	}
}

// �`��
void Scene_Title::Draw()
{
	/* �^�C�g����ʕ`�� */
	DrawString(SCREEN_SIZE_WIDE / 2, SCREEN_SIZE_HEIGHT / 2, "�^�C�g��", GetColor(255, 255, 255));
}
