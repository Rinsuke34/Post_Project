/* �V�[��"�ėp2D�p�[�c�A�j���[�V�����c�[��"�̒�` */

#include "Scene_2DPartsAnimCreateTool.h"

#include "AppVariableDefine.h"
#include "AppFunctionDefine.h"

// �R���X�g���N�^
Scene_2DPartsAnimCreateTool::Scene_2DPartsAnimCreateTool() : SceneBase("Scene_2DPartsAnimCreateTool", 9999, true)
{
	/* �N�����_�ł̃}�E�X�֘A�̃t���O��ێ����A�e�t���O�𖳌��ɐݒ肷�� */
	this->bOldMouseCursorCenterFixedFlg = gbMouseCursorCenterFixedFlg;
	gbMouseCursorCenterFixedFlg			= false;
	this->bOldMouseCursorNotDepictedFlg = gbMouseCursorNotDepictedFlg;
	gbMouseCursorNotDepictedFlg			= false;

	/* UI�̍쐬 */
	paUI_Table[0] = std::make_shared<Scene_UI_Table>(400, 16, 16 * 5, "�p�[�c���X�g");					// 0:�p�[�c���X�g
	paUI_Table[1] = std::make_shared<Scene_UI_Table>(400, 16, 16 * 20, "�A�j���[�V�������X�g");			// 1:�A�j���[�V�������X�g
	paUI_Table[2] = std::make_shared<Scene_UI_Table>(400, 1500, 16 * 5, "�t���[�����X�g");				// 2:�t���[�����X�g
	paUI_Table[3] = std::make_shared<Scene_UI_Table>(400, 1500, 16 * 20, "�I���t���[���̃p�[�c���X�g");	// 3:�I���t���[���̃p�[�c���X�g

	// UI�̓o�^
	for (int i = 0; i < 4; ++i)
	{
		gpSceneServer->AddSceneReservation(paUI_Table[i]);
	}

}

// �f�X�g���N�^
Scene_2DPartsAnimCreateTool::~Scene_2DPartsAnimCreateTool()
{
	/* �c�[���I�����Ƀ}�E�X�֘A�̃t���O�����ɖ߂� */
	gbMouseCursorCenterFixedFlg = this->bOldMouseCursorCenterFixedFlg;
	gbMouseCursorNotDepictedFlg = this->bOldMouseCursorNotDepictedFlg;

	/* �쐬����UI�̍폜�t���O��L���� */
	for (int i = 0; i < 4; ++i)
	{
		paUI_Table[i]->SetDeleteFlg(true);
	}

	///* �I�������摜�̃O���t�B�b�N�n���h������� */
	//for (int iGrHandle : this->iSelectGrHandle)
	//{
	//	DeleteGraph(iGrHandle);
	//}
	//this->iSelectGrHandle.clear();
	//this->stSelectGrPath.clear();
}

// �v�Z
void Scene_2DPartsAnimCreateTool::Process()
{
	/* �p�[�c�A�j���[�V�����Q�V�K�쐬 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_Z] == TRUE)
	{
		/* �p�[�c�A�j���[�V�����Q�̖��̂����(���p����) */
		char cAnimName[20];
		int iReturn = KeyInputSingleCharString(0, 0, 20, cAnimName, TRUE);
		if (iReturn == 1)
		{
			// ����ɓ��͂��ꂽ�ꍇ
			/* ���͂��ꂽ�p�[�c�A�j���[�V�����Q���ɐݒ� */
			this->stPartsAnimData.stAnimName = cAnimName; // �p�[�c�A�j���[�V�����Q����ݒ�

			/* ���݂̃A�j���[�V���������폜 */
			this->stPartsAnimData.vecPartsImageData.clear();
			this->stPartsAnimData.vecPartsAnimData.clear();
		}
	}

	/* �A�j���[�V�����p�p�[�c�ǉ� */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_X] == TRUE)
	{
		/* �_�C�A���O��\�� */
		std::string path = PUBLIC_FUNCTION::aOpenFileDialog(".png");

		/* �p�X���擾���ꂽ���m�F */
		if (!path.empty())
		{
			// �擾���ꂽ�ꍇ
			/* �摜�̃O���t�B�b�N�n���h�����擾 */
			int iGrHandle = LoadGraph(path.c_str());

			/* �p�[�c�������(���p����) */
			char cPartsName[20];
			int iReturn = KeyInputSingleCharString(0, 0, 20, cPartsName, TRUE);
			if (iGrHandle != -1 && iReturn == 1)
			{
				// �O���t�B�b�N�n���h�����擾�ł��A����ɖ��̂����͂��ꂽ�ꍇ
				/* �p�[�c�̉摜�f�[�^�ɓ��͂��ꂽ����ǉ����� */
				Struct_2DPartsAnim::PARTS_ANIM_PARTS_IMAGE_DATA stPartsImageData;
				stPartsImageData.stPartsName	= cPartsName;	// �p�[�c����ݒ�
				stPartsImageData.stPartsPath	= path;			// �p�[�c�̉摜�t�@�C���p�X��ݒ�
				stPartsImageData.iPartsGrHandle	= iGrHandle;	// �p�[�c�̉摜�̃O���t�B�b�N�n���h����ݒ�

				/* �p�[�c�̉摜�f�[�^���p�[�c�A�j���[�V�����Q�ɒǉ� */
				this->stPartsAnimData.vecPartsImageData.push_back(stPartsImageData);
			}
		}
	}

	/* �A�j���[�V�����ǉ� */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_C] == TRUE)
	{
		/* �A�j���[�V�����̖��̂����(���p����) */
		char cAnimName[20];
		int iReturn = KeyInputSingleCharString(0, 0, 20, cAnimName, TRUE);
		if (iReturn == 1)
		{
			// ����ɓ��͂��ꂽ�ꍇ
			/* �A�j���[�V������V�K�쐬 */
			Struct_2DPartsAnim::PARTS_ANIM_ANIM_DATA stAnimData;
			stAnimData.stAnimName	= cAnimName;
			this->stPartsAnimData.vecPartsAnimData.push_back(stAnimData);
		}
	}

	/* �I�𒆂̃A�j���[�V�����Ƀt���[���ǉ� */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_V] == TRUE)
	{

	}

	/* �I�𒆂̃A�j���[�V�����̃t���[���Ƀp�[�c�ǉ� */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_B] == TRUE)
	{

	}

	//if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_Z] == TRUE)
	//{
	//	/* �_�C�A���O��\�� */
	//	std::string path = PUBLIC_FUNCTION::aOpenFileDialog(".png");

	//	/* �p�X���擾���ꂽ���m�F */
	//	if (!path.empty())
	//	{
	//		// �擾���ꂽ�ꍇ
	//		/* �摜�̃O���t�B�b�N�n���h�����擾 */
	//		int iGrHandle = LoadGraph(path.c_str());

	//		/* �O���t�B�b�N�n���h�����擾�ł������m�F */
	//		if (iGrHandle != -1)
	//		{
	//			// �O���t�B�b�N�n���h�����擾�ł����ꍇ
	//			///* �I�������摜�̃O���t�B�b�N�n���h���ƃp�X��ۑ� */
	//			//this->iSelectGrHandle.push_back(iGrHandle);
	//			//this->stSelectGrPath.push_back(path);
	//		}
	//	}
	//}

	/* �e�[�u��UI�ւ̗v�f�ݒ� */
	// �p�[�c���X�g
	std::vector<std::string> partsNameList;
	for (const auto& part : this->stPartsAnimData.vecPartsImageData) {
		partsNameList.push_back(part.stPartsName);
	}
	paUI_Table[0]->SetElement(partsNameList);

	/* �A�j���[�V�������X�g */
	std::vector<std::string> animNameList;
	for (const auto& anim : this->stPartsAnimData.vecPartsAnimData) {
		animNameList.push_back(anim.stAnimName);
	}
	paUI_Table[1]->SetElement(animNameList);
}

// �`��
void Scene_2DPartsAnimCreateTool::Draw()
{
	/* �����T�C�Y��16�ɐݒ� */
	SetFontSize(16);

	/* �w�i�`�� */
	DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(255, 255, 255), TRUE);
	DrawLine(SCREEN_SIZE_WIDE / 2, 0, SCREEN_SIZE_WIDE / 2, SCREEN_SIZE_HEIGHT, GetColor(255, 0, 0));
	DrawLine(0, SCREEN_SIZE_HEIGHT / 2, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT / 2, GetColor(0, 0, 255));

	///* �I�������摜�̃O���t�B�b�N�n���h����`�� */
	//for (int iIndex = 0; iIndex < this->iSelectGrHandle.size(); ++iIndex)
	//{
	//	DrawString(iIndex * 100, 0, this->stSelectGrPath[iIndex].c_str(), GetColor(255, 255, 255));
	//	DrawGraph(iIndex * 100, 20, this->iSelectGrHandle[iIndex], FALSE);
	//}

	/* ���݂̃A�j���[�V�����̖��̕`�� */
	DrawBox(16, 16 * 1, 400, 16 * 2, GetColor(0, 0, 0), TRUE);
	DrawBox(16, 16 * 1, 400, 16 * 3, GetColor(0, 0, 0), FALSE);
	DrawString(16, 16 * 1, "���݂̃A�j���[�V�����Q����", GetColor(255, 255, 255));
	DrawString(16, 16 * 2, this->stPartsAnimData.stAnimName.c_str(), GetColor(0, 0, 0));

	///* ���݂̃A�j���[�V�����̃p�[�c���X�g */
	//DrawBox(16, 16 * 5, 400, 16 * 6, GetColor(0, 0, 0), TRUE);
	//DrawString(16, 16 * 5, "���݂̃p�[�c���X�g", GetColor(255, 255, 255));
	//for (iIndex = 0; iIndex < this->stPartsAnimData.vecPartsImageData.size(); ++iIndex)
	//{
	//	const auto& imageData = this->stPartsAnimData.vecPartsImageData[iIndex];
	//	DrawString(16, 16 * (iIndex + 6), imageData.stPartsName.c_str(), GetColor(0, 0, 0));
	//}
	//DrawBox(16, 16 * 5, 400, 16 * 16, GetColor(0, 0, 0), FALSE);

	///* ���݂̃A�j���[�V�������X�g */
	//DrawBox(16, 16 * 15, 400, 16 * 16, GetColor(0, 0, 0), TRUE);
	//DrawString(16, 16 * 15, "���݂̃A�j���[�V�������X�g", GetColor(255, 255, 255));
	//for (iIndex = 0; iIndex < this->stPartsAnimData.vecPartsAnimData.size(); ++iIndex)
	//{
	//	const auto& animData = this->stPartsAnimData.vecPartsAnimData[iIndex];
	//	DrawString(16, 16 * (iIndex + 25), animData.stAnimName.c_str(), GetColor(0, 0, 0));
	//}
	//DrawBox(16, 16 * 15, 400, 16 * (iIndex + 25), GetColor(0, 0, 0), FALSE);

	/* �t���[���̃p�[�c���X�g�̌��ݑI�𒆂̃p�[�c�ڍ� */




}

// �p�[�c�A�j���[�V�����̃f�[�^�ǂݍ���
bool Scene_2DPartsAnimCreateTool::bLoadPartsAnimData()
{
	return false;
}

// �p�[�c�A�j���[�V�����̃f�[�^�ۑ�
bool Scene_2DPartsAnimCreateTool::bSavePartsAnimData()
{
	return false;
}

