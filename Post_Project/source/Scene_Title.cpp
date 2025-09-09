/* �V�[��"�^�C�g��"�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �w�b�_�t�@�C��
#include "Scene_Title.h"
// �֘A�N���X
#include "Scene_StageCreate.h"
#include "Scene_GameMain.h"
#include "Scene_Load.h"


// �R���X�g���N�^
Scene_Title::Scene_Title() : Scene_Base("Scene_Title", 0, false, false)
{

}

// �f�X�g���N�^
Scene_Title::~Scene_Title()
{

}

// �X�V
void Scene_Title::Update()
{
	/* ���͑҂� */
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_Z] == TRUE)
	{
		/* 2D�p�[�c�A�j���[�V�����쐬�c�[���֑J�� */
		PUBLIC_FUNCTION::Start2DPartsAnimCreateTool();
	}

	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_X] == TRUE)
	{
		/* "�X�e�[�W�쐬"�֑J�� */
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_StageCreate>());
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_Load>());

		/* �V�[���̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;
	}

	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_C] == TRUE)
	{
		/* �V�[��"�Q�[�����C��"�֑J�� */
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_GameMain>());
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_Load>());

		/* �V�[���̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;
	}
}

// �`��
void Scene_Title::Draw()
{
	/* �^�C�g����ʕ`�� */
	DrawString(SCREEN_SIZE_WIDE / 2, SCREEN_SIZE_HEIGHT / 2, "�^�C�g��", GetColor(255, 255, 255));
}
