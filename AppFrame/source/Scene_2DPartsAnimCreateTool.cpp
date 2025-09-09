/* �V�[��"�ėp2D�p�[�c�A�j���[�V�����c�[��"�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �W�����C�u����
#include <filesystem>
#include <fstream>
// �O�����C�u����
#include <nlohmann/json.hpp>
// �w�b�_�t�@�C��
#include "Scene_2DPartsAnimCreateTool.h"
// �֘A�N���X
#include "Scene_UI_Table.h"
#include "SceneServer.h"
// ���ʒ�`
#include "AppVariableDefine.h"
#include "AppFunctionDefine.h"

// �R���X�g���N�^
Scene_2DPartsAnimCreateTool::Scene_2DPartsAnimCreateTool() : Scene_Base("Scene_2DPartsAnimCreateTool", 9999, true, false)
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
	this->iSelectTime		= 0;
	this->iAnimMaxTime		= 0;
	this->bNameSelectedFlg	= false;
	this->bTimeSelectedFlg	= false;
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

	/* �p�[�c�A�j���[�V�����̉摜�f�[�^����� */
	for (const auto& partImage : this->PartsImageData)
	{
		DeleteGraph(partImage.iPartsGrHandle);
	}
}

// �X�V
void Scene_2DPartsAnimCreateTool::Update()
{
	/* ���N���b�N�ł̍��ڑI�� */
	if (gstKeyboardInputData.igInput[INPUT_TRG] & MOUSE_INPUT_LEFT)
	{
		/* �}�E�X�J�[�\�����t�@�C���������ɏd�Ȃ��Ă����Ԃł��邩�m�F */
		if (gstKeyboardInputData.iMouseX >= 16 && gstKeyboardInputData.iMouseX <= 400 &&
			gstKeyboardInputData.iMouseY >= 16 * 1 && gstKeyboardInputData.iMouseY <= 16 * 3)
		{
			// �}�E�X�J�[�\�����t�@�C���������ɏd�Ȃ��Ă���ꍇ
			this->bNameSelectedFlg = true;
			this->bTimeSelectedFlg = false;
		}
		else if (gstKeyboardInputData.iMouseX >= 16 && gstKeyboardInputData.iMouseX <= 1920 - 16 &&
			gstKeyboardInputData.iMouseY >= 1080 - 16 * 4 && gstKeyboardInputData.iMouseY <= 1080 - 16 * 2)
		{
			// �}�E�X�J�[�\�������ԕ����ɏd�Ȃ��Ă���ꍇ
			this->bNameSelectedFlg = false;
			this->bTimeSelectedFlg = true;
		}
		else
		{
			// �}�E�X�J�[�\�����ǂ���ɂ��d�Ȃ��Ă��Ȃ��ꍇ
			this->bNameSelectedFlg = false;
			this->bTimeSelectedFlg = false;
		}
	}

	/* �p�[�c�A�j���[�V�����t�@�C���V�K�쐬 */
	if (this->bNameSelectedFlg && (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_I] == TRUE))
	{
		NewPartsAnimFile();
	}

	/* �A�j���[�V�����p�p�[�c�ǉ� */
	if(paUI_Table[0]->bGetTableSelectedFlg() && (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_I] == TRUE))
	{
		AddAnimPaarts();
	}
	/* �A�j���[�V�����p�p�[�c�폜 */
	if (paUI_Table[0]->bGetTableSelectedFlg() && gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_K] == TRUE)
	{
		DeleteAnimPaarts();
	}

	/* �A�j���[�V�����ǉ� */
	if (paUI_Table[1]->bGetTableSelectedFlg() && gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_I] == TRUE)
	{
		AddAnim();
	}
	/* �A�j���[�V�����폜 */
	if (paUI_Table[1]->bGetTableSelectedFlg() && gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_K] == TRUE)
	{
		DeleteAnim();
	}

	/* �I�𒆂̃A�j���[�V�����̎w�莞�ԂɃp�[�c�ǉ� */
	if(paUI_Table[2]->bGetTableSelectedFlg() && gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_I] == TRUE)
	{
		AddPartsToAnim();
	}
	/* �I�𒆂̃A�j���[�V�����̎w�莞�ԂɃp�[�c�폜 */
	if (paUI_Table[2]->bGetTableSelectedFlg() && gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_K] == TRUE)
	{
		DeletePartsToAnim();
	}

	/* �I�𒆂̃p�[�c�̏�ԕύX(�ʒu���]��) */
	if (paUI_Table[2]->bGetTableSelectedFlg())
	{
		ChangeSelectPartsStatus();
	}

	/* �I�����Ԃ̕ύX */
	if (this->bTimeSelectedFlg)
	{
		ChangeSelectTime();
	}

	/* �Z�[�u */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_O] == TRUE)
	{
		// S�L�[�������ꂽ�ꍇ
		bSavePartsAnimData();
	}

	/* ���[�h */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_L] == TRUE)
	{
		// L�L�[�������ꂽ�ꍇ
		bLoadPartsAnimData();
	}

	/* �I��(�V�[���폜) */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_ESCAPE] == TRUE)
	{
		// ESC�L�[�������ꂽ�ꍇ
		this->bDeleteFlg = true;
	}

	/* �e�[�u��UI�ւ̗v�f�ݒ� */
	SetUiTableElement();
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
	static const int iStandardSize = 256;	// �W���̎l�p�`�̃T�C�Y
	DrawBox(SCREEN_SIZE_WIDE / 2 - iStandardSize / 2, SCREEN_SIZE_HEIGHT / 2 - iStandardSize / 2, SCREEN_SIZE_WIDE / 2 + iStandardSize / 2, SCREEN_SIZE_HEIGHT / 2 + iStandardSize / 2, GetColor(0, 255, 0), FALSE);

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
					DrawRotaGraph3(
						static_cast<int>(part.fPartsX + (SCREEN_SIZE_WIDE / 2)),		// �摜����]�`�ʂ����ʏ�ł̒��S���WX
						static_cast<int>(part.fPartsY + (SCREEN_SIZE_HEIGHT / 2)),		// �摜����]�`�ʂ����ʏ�ł̒��S���WY
						static_cast<int>(iGrSizeX / 2),									// �摜����]�`�ʂ���摜��ł̒��S���WX
						static_cast<int>(iGrSizeY / 2),									// �摜����]�`�ʂ���摜��ł̒��S���WY
						part.fPartsScaleX,												// �������̊g�嗦
						part.fPartsScaleY,												// �c�����̊g�嗦
						part.fPartsAngle,												// �摜�̉�]�p�x(���W�A��)
						iGrHandle,														// �`�ʂ���O���t�B�b�N�n���h��
						TRUE,															// �摜�̓����x��L���ɂ��邩�ǂ���
						part.bPartsFlipX);												// �摜�����E���]���ĕ`�ʂ��邩�ǂ���
				}
			}
		}
	}

	/* �t�@�C�����`�� */
	DrawBox(16, 16 * 1, 400, 16 * 2, GetColor(0, 0, 0), TRUE);
	DrawBox(16, 16 * 1, 400, 16 * 3, GetColor(0, 0, 0), FALSE);
	DrawString(16, 16 * 1, "�t�@�C����", GetColor(255, 255, 255));
	DrawString(16, 16 * 2, this->FileName.c_str(), GetColor(0, 0, 0));
	if (this->bNameSelectedFlg == true)
	{
		DrawBox(16, 16 * 1, 400, 16 * 3, GetColor(255, 0, 0), FALSE);
	}

	/* ���݂̃A�j���[�V�����̎��ԕ`�� */
	DrawBox(16, 1080 - 16 * 4, 1920 - 16, 1080 - 16 * 3, GetColor(0, 0, 0), TRUE);
	DrawString(16, 1080 - 16 * 4, "����", GetColor(255, 255, 255));
	DrawBox(16, 1080 - 16 * 3, 1920 - 16, 1080 - 16 * 2, GetColor(128, 128, 128), FALSE);
	// ���ԕ���
	DrawBox(16, 1080 - 16 * 3 + 4, 1920 - 16, 1080 - 16 * 2 - 4, GetColor(128, 128, 128), TRUE);
	// �ő厞�Ԃ�0�̏ꍇ�͐ԐF�o�[���\��
	if (iAnimMaxTime > 0)
	{
		// �����v�Z
		float rate = static_cast<float>(iSelectTime) / static_cast<float>(iAnimMaxTime);
		if (rate > 1.0f) rate = 1.0f;
		if (rate < 0.0f) rate = 0.0f;
		int barStartX = 16;
		int barEndX = static_cast<int>(16 + (1920 - 16 - 16) * rate);
		DrawBox(barStartX, 1080 - 16 * 3 + 4, barEndX, 1080 - 16 * 2 - 4, GetColor(255, 0, 0), TRUE);
	}
	if (this->bTimeSelectedFlg == true)
	{
		DrawBox(16, 1080 - 16 * 4, 1920 - 16, 1080 - 16 * 2, GetColor(255, 0, 0), FALSE);
	}
}

// �p�[�c�A�j���[�V�����̃f�[�^�ǂݍ���
bool Scene_2DPartsAnimCreateTool::bLoadPartsAnimData()
{
	/* Json�t�@�C����ǂݍ��� */
	using json = nlohmann::json;

	/* �t�@�C���I���_�C�A���O��JSON�t�@�C���p�X���擾 */
	std::string jsonPathStr = PUBLIC_FUNCTION::aOpenFileDialog(".json");
	if (jsonPathStr.empty())
	{
		return false;
	}
	std::filesystem::path jsonPath = jsonPathStr;

	/* �t�@�C�����i�g���q�Ȃ��j��Shift-JIS�ɕϊ�����FileName�ɐݒ� */
	this->FileName = PUBLIC_PROCESS::aUtf8ToShiftJIS(jsonPath.stem().string());

	/* AppResource/AnimData_Resource�̐�΃p�X�擾 */
	std::filesystem::path currentDir	= std::filesystem::current_path();
	std::filesystem::path parentDir		= currentDir.parent_path();
	std::filesystem::path resourceDir	= parentDir / "AnimData_Resource";

	/* �t�@�C�����J�� */
	std::ifstream ifs(jsonPath);
	if (!ifs.is_open())
	{
		return false;
	}

	json j;
	try
	{
		ifs >> j;
	}
	catch (...)
	{
		return false;
	}
	ifs.close();

	/* �ǂݍ��ݐ��������ꍇ�A�����̃f�[�^���N���A */
	PartsImageData.clear();
	PartsAnimData.clear();

	/* �p�[�c�̉摜�f�[�^�̓ǂݍ��� */
	if (j.contains("ImagePath") && j["ImagePath"].is_array())
	{
		for (const auto& part : j["ImagePath"])
		{
			/* �ǉ�����C���[�W�f�[�^ */
			Struct_2DPartsAnim::PARTS_ANIM_PARTS_IMAGE_DATA AddImageData;
			AddImageData.stPartsName		= part.value("Name", "");							// �p�[�c��
			std::filesystem::path filename	= part.value("Path", "");							// �摜�t�@�C����
			std::filesystem::path absPath	= resourceDir / filename;							// ��΃p�X + �摜�t�@�C����
			AddImageData.stPartsPath		= absPath.generic_string();							// �p�[�c�̉摜�t�@�C���p�X
			AddImageData.iPartsGrHandle		= LoadGraph(AddImageData.stPartsPath.c_str());		// �p�[�c�̉摜�̃O���t�B�b�N�n���h��
			PartsImageData.push_back(AddImageData);												// �p�[�c�̉摜�f�[�^�ɒǉ�
		}
	}

	/* �A�j���[�V�����f�[�^�̓ǂݍ��� */
	if (j.contains("Animation") && j["Animation"].is_array())
	{
		for (const auto& anim : j["Animation"])
		{
			/* �ǉ�����A�j���[�V�����f�[�^ */
			Struct_2DPartsAnim::PARTS_ANIM_ANIM_DATA AddAnimData;
			AddAnimData.AnimName	= anim.value("Name", "");	// �A�j���[�V������
			AddAnimData.PartsAnimFrameData.clear();

			if (anim.contains("Parts") && anim["Parts"].is_array())
			{
				for (const auto& frameArray : anim["Parts"])
				{
					/* �ǉ�����t���[���ł̃p�[�c���̃��X�g */
					std::vector<Struct_2DPartsAnim::PARTS_ANIM_PARTS_FRAME_DATA> AddFrameList;
					if (frameArray.is_array())
					{
						for (const auto& frame : frameArray)
						{
							/* �ǉ�����t���[���ł̃p�[�c��� */
							Struct_2DPartsAnim::PARTS_ANIM_PARTS_FRAME_DATA AddFrameData;
							AddFrameData.stPartsName	= frame.value("Name", "");		// �p�[�c��
							AddFrameData.fPartsX		= frame.value("PosX", 0.0f);	// �p�[�c��X���W
							AddFrameData.fPartsY		= frame.value("PosY", 0.0f);	// �p�[�c��Y���W
							AddFrameData.fPartsScaleX	= frame.value("ScaleX", 1.0f);	// �p�[�c��X�X�P�[��
							AddFrameData.fPartsScaleY	= frame.value("ScaleY", 1.0f);	// �p�[�c��Y�X�P�[��
							AddFrameData.fPartsAngle	= frame.value("Angle", 0.0f);	// �p�[�c�̊p�x(���W�A��)
							AddFrameData.bPartsFlipX	= frame.value("FlipX", false);	// �p�[�c�̍��E���]�t���O
							AddFrameList.push_back(AddFrameData);
						}
					}
					AddAnimData.PartsAnimFrameData.push_back(AddFrameList);
				}
			}
			PartsAnimData.push_back(AddAnimData);
		}
	}

	return true;
}

// �p�[�c�A�j���[�V�����̃f�[�^�ۑ�
bool Scene_2DPartsAnimCreateTool::bSavePartsAnimData()
{
	using json = nlohmann::json;

	// AppResource/AnimData_Resource�̐�΃p�X�擾
	std::filesystem::path currentDir = std::filesystem::current_path();
	std::filesystem::path parentDir = currentDir.parent_path();
	std::filesystem::path resourceDir = parentDir / "AnimData_Resource";

	// JSON�I�u�W�F�N�g�쐬
	json j;

	// PartsImageData�̏o�́i�摜�p�X�̓t�@�C�����݂̂ŕۑ��j
	j["ImagePath"] = json::array();
	for (const auto& part : PartsImageData) {
		std::filesystem::path imagePath = std::filesystem::absolute(part.stPartsPath);
		std::filesystem::path filename = imagePath.filename(); // �t�@�C�����̂ݎ擾
		j["ImagePath"].push_back({
			{"Name", part.stPartsName},
			{"Path", filename.string()}
			});
	}

	// PartsAnimData�̏o�́i�]���ʂ�j
	j["Animation"] = json::array();
	for (const auto& anim : PartsAnimData) {
		json animObj;
		animObj["Name"] = anim.AnimName;
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

	// �ۑ���p�X�쐬�iAppResource/AnimData_Json�����ɏC���j
	std::filesystem::path saveDir = parentDir / "AnimData_Json";
	std::filesystem::create_directories(saveDir);
	std::filesystem::path savePath = saveDir / (this->FileName + ".json");

	// �t�@�C���ۑ�
	std::ofstream ofs(savePath);
	if (!ofs.is_open()) {
		return false;
	}
	ofs << j.dump(4);
	ofs.close();

	return true;
}

// �V�K�p�[�c�A�j���[�V�����t�@�C���쐬
void Scene_2DPartsAnimCreateTool::NewPartsAnimFile()
{
	/* �t�@�C���������(���p����) */
	char cAnimName[20];
	DrawBox(0, 0, 400, 16, GetColor(0, 0, 0), TRUE);
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

// �A�j���[�V�����p�p�[�c�ǉ�
void Scene_2DPartsAnimCreateTool::AddAnimPaarts()
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
		DrawBox(0, 0, 400, 16, GetColor(0, 0, 0), TRUE);
		int iReturn = KeyInputSingleCharString(0, 0, 20, cPartsName, TRUE);
		if (iGrHandle != -1 && iReturn == 1)
		{
			// �O���t�B�b�N�n���h�����擾�ł��A����ɖ��̂����͂��ꂽ�ꍇ
			/* �p�[�c�̉摜�f�[�^�ɓ��͂��ꂽ����ǉ����� */
			Struct_2DPartsAnim::PARTS_ANIM_PARTS_IMAGE_DATA stPartsImageData;
			stPartsImageData.stPartsName = cPartsName;	// �p�[�c����ݒ�
			stPartsImageData.stPartsPath = path;			// �p�[�c�̉摜�t�@�C���p�X��ݒ�
			stPartsImageData.iPartsGrHandle = iGrHandle;	// �p�[�c�̉摜�̃O���t�B�b�N�n���h����ݒ�

			/* �p�[�c�̉摜�f�[�^���p�[�c�A�j���[�V�����Q�ɒǉ� */
			this->PartsImageData.push_back(stPartsImageData);
		}
	}
}

void Scene_2DPartsAnimCreateTool::AddAnim()
{
	/* �A�j���[�V�����̖��̂����(���p����) */
	char cAnimName[20];
	DrawBox(0, 0, 400, 16, GetColor(0, 0, 0), TRUE);
	int iReturn = KeyInputSingleCharString(0, 0, 20, cAnimName, TRUE);
	if (iReturn == 1)
	{
		// ����ɓ��͂��ꂽ�ꍇ
		/* �A�j���[�V������V�K�쐬 */
		Struct_2DPartsAnim::PARTS_ANIM_ANIM_DATA stAnimData;
		stAnimData.AnimName = cAnimName;
		this->PartsAnimData.push_back(stAnimData); // �p�[�c�A�j���[�V�����̏��ɒǉ�
	}
}

// �I�𒆂̃A�j���[�V�����Ƀp�[�c��ǉ�
void Scene_2DPartsAnimCreateTool::AddPartsToAnim()
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

// �A�j���[�V�����p�p�[�c�폜
void Scene_2DPartsAnimCreateTool::DeleteAnimPaarts()
{
	// �I�𒆂̃p�[�c���X�g�̃C���f�b�N�X
	int iSelectPartsIndex = paUI_Table[2]->iGetSelectElementIndex();

	// �I�𒆂̃p�[�c��PartsImageData����폜
	if (iSelectPartsIndex >= 0 && iSelectPartsIndex < PartsImageData.size())
	{
		PartsImageData.erase(PartsImageData.begin() + iSelectPartsIndex);
	}
}

// �A�j���[�V�����폜
void Scene_2DPartsAnimCreateTool::DeleteAnim()
{
	// �I�𒆂̃A�j���[�V�����̃C���f�b�N�X
	int iSelectAnimIndex = paUI_Table[1]->iGetSelectElementIndex();

	// �I�𒆂̃A�j���[�V������PartsAnimData����폜
	if (iSelectAnimIndex >= 0 && iSelectAnimIndex < PartsAnimData.size())
	{
		PartsAnimData.erase(PartsAnimData.begin() + iSelectAnimIndex);
	}
}

// �I�𒆂̃A�j���[�V�����Ƀp�[�c��ǉ�
void Scene_2DPartsAnimCreateTool::DeletePartsToAnim()
{
	// �I�𒆂̃A�j���[�V�����̃C���f�b�N�X
	int iSelectAnimIndex = paUI_Table[1]->iGetSelectElementIndex();
	// �I�𒆂̃p�[�c���X�g�̃C���f�b�N�X
	int iSelectPartsIndex = paUI_Table[2]->iGetSelectElementIndex();

	// �I�𒆃A�j���[�V�����̃p�[�c���X�g����I�𒆃p�[�c���폜
	if (iSelectAnimIndex >= 0 && iSelectAnimIndex < PartsAnimData.size())
	{
		auto& anim = PartsAnimData[iSelectAnimIndex];
		if (iSelectPartsIndex >= 0 && iSelectPartsIndex < anim.PartsAnimFrameData.size())
		{
			anim.PartsAnimFrameData.erase(anim.PartsAnimFrameData.begin() + iSelectPartsIndex);
		}
	}
}

// �I�����Ԃ̕ύX
void Scene_2DPartsAnimCreateTool::ChangeSelectTime()
{
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
		/* ���Ԃ�V�K�쐬����ꍇ�A�ł��Ō�̎��Ԃ̃p�[�c���������p�� */
		int iSelectAnimIndex = paUI_Table[1]->iGetSelectElementIndex();
		if (iSelectAnimIndex >= 0 && iSelectAnimIndex < PartsAnimData.size())
		{
			auto& animData = PartsAnimData[iSelectAnimIndex];
			this->iSelectTime++;

			// �V�K���ԁi�t���[���j��ǉ�����ꍇ
			if (this->iSelectTime >= animData.PartsAnimFrameData.size())
			{
				// ���O�̃t���[�������݂���ꍇ�͕���
				if (!animData.PartsAnimFrameData.empty())
				{
					animData.PartsAnimFrameData.push_back(animData.PartsAnimFrameData.back());
				}
				else
				{
					// �ŏ��̃t���[���̏ꍇ�͋�Œǉ�
					animData.PartsAnimFrameData.push_back({});
				}
			}
		}
		else
		{
			this->iSelectTime++;
		}
	}
}

// �e�[�u��UI�ւ̗v�f�ݒ�
void Scene_2DPartsAnimCreateTool::SetUiTableElement()
{
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
		animNameList.push_back(anim.AnimName);
	}
	paUI_Table[1]->SetElement(animNameList);
	iSelectAnimIndex = paUI_Table[1]->iGetSelectElementIndex();

	// �ő厞�ԁi�t���[�����j�𖈃t���[���X�V
	if (iSelectAnimIndex >= 0 && iSelectAnimIndex < PartsAnimData.size())
	{
		this->iAnimMaxTime = static_cast<int>(PartsAnimData[iSelectAnimIndex].PartsAnimFrameData.size());
	}
	else
	{
		this->iAnimMaxTime = 0;
	}

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

// �I�𒆂̃p�[�c�̏�ԕύX
void Scene_2DPartsAnimCreateTool::ChangeSelectPartsStatus()
{
	// �I�𒆂̃A�j���[�V�����̃C���f�b�N�X
	int iSelectAnimIndex = paUI_Table[1]->iGetSelectElementIndex();
	// �I�𒆂̃p�[�c���X�g�̃C���f�b�N�X
	int iSelectPartsIndex = paUI_Table[2]->iGetSelectElementIndex();
	// �C���f�b�N�X�͈̓`�F�b�N
	if (iSelectAnimIndex >= 0 && iSelectAnimIndex < PartsAnimData.size() &&
		iSelectPartsIndex >= 0)
	{
		auto& animData = PartsAnimData[iSelectAnimIndex];
		if (iSelectTime >= 0 && iSelectTime < animData.PartsAnimFrameData.size() &&
			iSelectPartsIndex < animData.PartsAnimFrameData[iSelectTime].size())
		{
			auto& partData = animData.PartsAnimFrameData[iSelectTime][iSelectPartsIndex];
			// �ʒu�ύX
			if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_W] == TRUE)
			{
				partData.fPartsY -= 1.0f;
			}
			if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_S] == TRUE)
			{
				partData.fPartsY += 1.0f;
			}
			if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_A] == TRUE)
			{
				partData.fPartsX -= 1.0f;
			}
			if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_D] == TRUE)
			{
				partData.fPartsX += 1.0f;
			}
			// ��]�ύX
			if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_Q] == TRUE)
			{
				partData.fPartsAngle -= 0.1f;
				if (partData.fPartsAngle < 0.0f) partData.fPartsAngle += 360.0f;
			}
			if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_E] == TRUE)
			{
				partData.fPartsAngle += 0.1f;
				if (partData.fPartsAngle >= 360.0f) partData.fPartsAngle -= 360.0f;
			}
			// �g��k���ύX
			if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_R] == TRUE)
			{
				partData.fPartsScaleX += 0.01f;
				partData.fPartsScaleY += 0.01f;
				if (partData.fPartsScaleX > 10.0f) partData.fPartsScaleX = 10.0f;
				if (partData.fPartsScaleY > 10.0f) partData.fPartsScaleY = 10.0f;
			}
			if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_F] == TRUE)
			{
				partData.fPartsScaleX -= 0.01f;
				partData.fPartsScaleY -= 0.01f;
				if (partData.fPartsScaleX < 0.1f) partData.fPartsScaleX = 0.1f;
				if (partData.fPartsScaleY < 0.1f) partData.fPartsScaleY = 0.1f;
			}
		}
	}
}