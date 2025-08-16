/* �V�[��"�ėp2D�p�[�c�A�j���[�V�����c�[��"�̒�` */

#include "Scene_2DPartsAnimCreateTool.h"

#include "AppVariableDefine.h"
#include "AppFunctionDefine.h"

#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>

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
	paUI_Table[2] = std::make_shared<Scene_UI_Table>(400, 16, 16 * 35, "�I�����Ԃł̃p�[�c���X�g");		// 2:�I�����Ԃł̃p�[�c���X�g

	// UI�̓o�^
	for (int i = 0; i < 3; ++i)
	{
		gpSceneServer->AddSceneReservation(paUI_Table[i]);
	}

	/* ������ */
	this->iSelectTime	= 0;
}

// �f�X�g���N�^
Scene_2DPartsAnimCreateTool::~Scene_2DPartsAnimCreateTool()
{
	/* �c�[���I�����Ƀ}�E�X�֘A�̃t���O�����ɖ߂� */
	gbMouseCursorCenterFixedFlg = this->bOldMouseCursorCenterFixedFlg;
	gbMouseCursorNotDepictedFlg = this->bOldMouseCursorNotDepictedFlg;

	/* �쐬����UI�̍폜�t���O��L���� */
	for (int i = 0; i < 3; ++i)
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
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_N] == TRUE)
	{
		/* �t�@�C���������(���p����) */
		char cAnimName[20];
		int iReturn = KeyInputSingleCharString(0, 0, 20, cAnimName, TRUE);
		if (iReturn == 1)
		{
			// ����ɓ��͂��ꂽ�ꍇ
			/* ���͂��ꂽ�p�[�c�A�j���[�V�����Q���ɐݒ� */
			this->FileName = cAnimName; // �p�[�c�A�j���[�V�����Q����ݒ�

			/* ���݂̃A�j���[�V�����̏����폜 */
			for (int i = 0; i < this->PartsImageData.size(); i++)
			{
				// �摜�n���h�������
				DeleteGraph(this->PartsImageData[i].iPartsGrHandle);
			}
			this->PartsImageData.clear();		// �p�[�c�̉摜�f�[�^���N���A
			this->PartsAnimData.clear();		// �p�[�c�A�j���[�V�����̏����N���A
		}
	}

	/* �A�j���[�V�����p�p�[�c�ǉ� */
	if(paUI_Table[0]->bGetTableSelectedFlg() && gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_A] == TRUE)
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
				this->PartsImageData.push_back(stPartsImageData);
			}
		}
	}

	/* �A�j���[�V�����ǉ� */
	if (paUI_Table[1]->bGetTableSelectedFlg() && gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_A] == TRUE)
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
			this->PartsAnimData.push_back(stAnimData); // �p�[�c�A�j���[�V�����̏��ɒǉ�
		}
	}

	/* �I�𒆂̃A�j���[�V�����̎w�莞�ԂɃp�[�c�ǉ� */
	if(paUI_Table[2]->bGetTableSelectedFlg() && gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_A] == TRUE)
	{
		// �I�𒆂̃A�j���[�V�����̃C���f�b�N�X
		int iSelectAnimIndex = paUI_Table[1]->iGetSelectElementIndex();
		// �I�𒆂̃p�[�c���X�g�̃C���f�b�N�X
		int iSelectPartsIndex = paUI_Table[0]->iGetSelectElementIndex();

		// �C���f�b�N�X�͈̓`�F�b�N
		if (iSelectAnimIndex >= 0 && iSelectAnimIndex < PartsAnimData.size() &&
			iSelectPartsIndex >= 0 && iSelectPartsIndex < PartsImageData.size())
		{
			// �I�𒆂̃A�j���[�V�����E���Ԃ̃t���[�������݂��Ȃ��ꍇ�͐V�K�쐬
			auto& animData = PartsAnimData[iSelectAnimIndex];
			if (iSelectTime >= animData.PartsAnimFrameData.size())
			{
				animData.PartsAnimFrameData.resize(iSelectTime + 1);
			}

			// �p�[�c�����擾
			const auto& srcPart = PartsImageData[iSelectPartsIndex];
			Struct_2DPartsAnim::PARTS_ANIM_PARTS_FRAME_DATA stPartsFrameData;
			stPartsFrameData.stPartsName	= srcPart.stPartsName;
			stPartsFrameData.fPartsX		= 0.0f;
			stPartsFrameData.fPartsY		= 0.0f;
			stPartsFrameData.fPartsScaleX	= 1.0f;
			stPartsFrameData.fPartsScaleY	= 1.0f;
			stPartsFrameData.fPartsAngle	= 0.0f;
			stPartsFrameData.bPartsFlipX	= false;

			// �I�𒆃A�j���[�V�����̎w�莞�Ԃɒǉ�
			animData.PartsAnimFrameData[iSelectTime].push_back(stPartsFrameData);
		}
	}

	/* �I�����Ԃ̕ύX */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_LEFT] == TRUE)
	{
		// ���L�[�������ꂽ�ꍇ
		if (this->iSelectTime > 0)
		{
			this->iSelectTime--;
		}
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_RIGHT] == TRUE)
	{
		// �E�L�[�������ꂽ�ꍇ
		this->iSelectTime++;
	}

	/* �e�[�u��UI�ւ̗v�f�ݒ� */
	int iSelectAnimIndex = 0; // �I�𒆂̃A�j���[�V�����̃C���f�b�N�X
	// �p�[�c���X�g
	std::vector<std::string> partsNameList;
	for (const auto& part : this->PartsImageData) {
		partsNameList.push_back(part.stPartsName);
	}
	paUI_Table[0]->SetElement(partsNameList);

	// �A�j���[�V�������X�g
	std::vector<std::string> animNameList;
	for (const auto& anim : this->PartsAnimData) {
		animNameList.push_back(anim.stAnimName);
	}
	paUI_Table[1]->SetElement(animNameList);
	iSelectAnimIndex = paUI_Table[1]->iGetSelectElementIndex();

	// �I���������Ԃł̃p�[�c���X�g
	std::vector<std::string> framePartsNameList;
	if (iSelectAnimIndex >= 0 && iSelectAnimIndex < PartsAnimData.size()) {
		const auto& animData = PartsAnimData[iSelectAnimIndex];
		if (iSelectTime >= 0 && iSelectTime < animData.PartsAnimFrameData.size()) {
			for (const auto& part : animData.PartsAnimFrameData[iSelectTime]) {
				framePartsNameList.push_back(part.stPartsName);
			}
		}
	}
	paUI_Table[2]->SetElement(framePartsNameList);
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

	/* ���݂̃A�j���[�V�����̑I�����Ԃɓo�^���ꂽ�p�[�c��`�� */
	int iSelectAnimIndex = paUI_Table[1]->iGetSelectElementIndex(); // �I�𒆂̃A�j���[�V�����̃C���f�b�N�X
	if (iSelectAnimIndex >= 0 && iSelectAnimIndex < PartsAnimData.size())
	{
		const auto& animData = PartsAnimData[iSelectAnimIndex];
		if (iSelectTime >= 0 && iSelectTime < animData.PartsAnimFrameData.size())
		{
			const auto& frameData = animData.PartsAnimFrameData[iSelectTime];
			for (const auto& part : frameData)
			{
				int iGrHandle = -1;
				for (const auto& image : PartsImageData)
				{
					if (image.stPartsName == part.stPartsName)
					{
						iGrHandle = image.iPartsGrHandle;
						break;
					}
				}
				if (iGrHandle != -1)
				{
					int iGrSizeX, iGrSizeY;
					GetGraphSize(iGrHandle, &iGrSizeX, &iGrSizeY);
					DrawRotaGraph3(part.fPartsX + (SCREEN_SIZE_WIDE / 2), part.fPartsY + (SCREEN_SIZE_HEIGHT / 2), iGrSizeX / 2, iGrSizeY / 2, part.fPartsScaleX, part.fPartsScaleY, part.fPartsAngle, iGrHandle, TRUE, part.bPartsFlipX);
				}
			}
		}
	}

	/* �t�@�C�����`�� */
	DrawBox(16, 16 * 1, 400, 16 * 2, GetColor(0, 0, 0), TRUE);
	DrawBox(16, 16 * 1, 400, 16 * 3, GetColor(0, 0, 0), FALSE);
	DrawString(16, 16 * 1, "�t�@�C����", GetColor(255, 255, 255));
	DrawString(16, 16 * 2, this->FileName.c_str(), GetColor(0, 0, 0));

	/* ���݂̃A�j���[�V�����̎��ԕ`�� */
	DrawBox(16, 1080 - 16 * 4, 1920 - 16, 1080 - 16 * 3, GetColor(0, 0, 0), TRUE);
	DrawString(16, 1080 - 16 * 4, "����", GetColor(255, 255, 255));
	DrawBox(16, 1080 - 16 * 3, 1920 - 16, 1080 - 16 * 2, GetColor(128, 128, 128), FALSE);
	// ���ԕ���
	DrawBox(16, 1080 - 16 * 3 + 4, 1920 - 16, 1080 - 16 * 2 - 4, GetColor(128, 128, 128), TRUE);
	DrawBox(16, 1080 - 16 * 3 + 4, 16 + this->iSelectTime * 25, 1080 - 16 * 2 - 4, GetColor(255, 0, 0), TRUE);
}

// �p�[�c�A�j���[�V�����̃f�[�^�ǂݍ���
bool Scene_2DPartsAnimCreateTool::bLoadPartsAnimData()
{
	return false;
}

// �p�[�c�A�j���[�V�����̃f�[�^�ۑ�
bool Scene_2DPartsAnimCreateTool::bSavePartsAnimData()
{

	using json = nlohmann::json;

	// JSON�I�u�W�F�N�g�쐬
	json j;

	// PartsImageData�̏o��
	j["ImagePath"] = json::array();
	for (const auto& part : PartsImageData) {
		j["ImagePath"].push_back({
			{"Name", part.stPartsName},
			{"Path", part.stPartsPath}
			});
	}

	// PartsAnimData�̏o��
	j["Animation"] = json::array();
	for (const auto& anim : PartsAnimData) {
		json animObj;
		animObj["Name"] = anim.stAnimName;
		animObj["Parts"] = json::array();

		for (const auto& frameList : anim.PartsAnimFrameData) {
			json frameArray = json::array();
			for (const auto& frame : frameList) {
				frameArray.push_back({
					{"Name", frame.stPartsName},
					{"PosX", frame.fPartsX},
					{"PosY", frame.fPartsY},
					{"ScaleX", frame.fPartsScaleX},
					{"ScaleY", frame.fPartsScaleY},
					{"Angle", frame.fPartsAngle},
					{"FlipX", frame.bPartsFlipX}
					});
			}
			animObj["Parts"].push_back(frameArray);
		}
		j["Animation"].push_back(animObj);
	}

	// �ۑ���p�X�쐬
	std::filesystem::path currentDir = std::filesystem::current_path();
	std::filesystem::path parentDir = currentDir.parent_path();
	std::filesystem::path saveDir = parentDir / "AppResource" / "AnimData_Json";
	std::filesystem::create_directories(saveDir); // �t�H���_���Ȃ���΍쐬

	std::filesystem::path savePath = saveDir / (FileName + ".json");

	// �t�@�C���ۑ�
	std::ofstream ofs(savePath);
	if (!ofs.is_open()) {
		return false;
	}
	ofs << j.dump(4); // �C���f���g4�ŏo��
	ofs.close();

	return true;
}

