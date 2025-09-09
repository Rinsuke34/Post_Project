/* �f�[�^���X�g"�ėp2D�p�[�c�A�j���[�V�����c�[��"�N���X�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �W�����C�u����
#include <filesystem>
#include <fstream>
// �O�����C�u����
#include <nlohmann/json.hpp>
// �w�b�_�t�@�C��
#include "DataList_2DPartsAnimCreateTool.h"
// ���ʒ�`
#include "AppFunctionDefine.h"

// �R���X�g���N�^
DataList_2DPartsAnimCreateTool::DataList_2DPartsAnimCreateTool() : DataList_Base("DataList_2DPartsAnimCreateTool")
{
	/* ������ */
	this->iDrawScreenSize[SCREEN_SIZE_WIDE]		= SCREEN_SIZE_WIDE;
	this->iDrawScreenSize[SCREEN_SIZE_HEIGHT]	= SCREEN_SIZE_HEIGHT;
}

// �f�X�g���N�^
DataList_2DPartsAnimCreateTool::~DataList_2DPartsAnimCreateTool()
{
	/* �e�p�[�c�̃O���t�B�b�N�n���h����������� */
	for (const auto& partAnim : this->PartsAnimDataList)
	{
		for (const auto& partImage : partAnim.PartsImageData)
		{
			DeleteGraph(partImage.iPartsGrHandle);
		}
	}
}

// �p�[�c�A�j���[�V�����̃f�[�^�ǂݍ���
void DataList_2DPartsAnimCreateTool::LoadPartsAnimData(std::string FileName)
{
	// ����
	// FileName	<- �p�[�c�A�j���[�V�����Q�̖���(==�t�@�C����)

	/* �w�肳�ꂽ�p�[�c�A�j���[�V�����Q���̃f�[�^�����ɑ��݂��邩�m�F */
	for (const auto& partAnim : this->PartsAnimDataList)
	{
		if (partAnim.FileName == FileName)
		{
			// ���ɑ��݂���ꍇ
			return;
		}
	}

	/* �p�[�c�A�j���[�V�����̏�� */
	Struct_2DPartsAnim::PARTS_ANIM_DATA PartsAnimData;

	/* �t�@�C������ݒ� */
	PartsAnimData.FileName = FileName;

	/* Json�t�@�C����ǂݍ��� */
	using json = nlohmann::json;

	/* AppData/AnimData�t�H���_�̐�΃p�X�擾 */
	std::filesystem::path currentDir	= std::filesystem::current_path();
	std::filesystem::path parentDir		= currentDir.parent_path();
	std::filesystem::path dataDir		= parentDir / "AppResource";
	std::filesystem::path jsonPath		= dataDir / "AnimData_Json" / (FileName + ".json");

	/* �t�@�C�����J�� */
	std::ifstream ifs(jsonPath);
	if (!ifs.is_open())
	{
		return;
	}

	json j;
	try
	{
		ifs >> j;
	}
	catch (...)
	{
		return;
	}
	ifs.close();

	/* �p�[�c�̉摜�f�[�^�̓ǂݍ��� */
	if (j.contains("ImagePath") && j["ImagePath"].is_array())
	{
		/* �p�[�c�̉摜�f�[�^ */
		std::vector<Struct_2DPartsAnim::PARTS_ANIM_PARTS_IMAGE_DATA> PartsImageData;

		for (const auto& part : j["ImagePath"])
		{
			/* �ǉ�����C���[�W�f�[�^ */
			Struct_2DPartsAnim::PARTS_ANIM_PARTS_IMAGE_DATA AddImageData;
			AddImageData.stPartsName		= part.value("Name", "");							// �p�[�c��
			std::filesystem::path filename	= part.value("Path", "");							// �摜�t�@�C����
			std::filesystem::path absPath	= dataDir / "AnimData_Resource" / filename;			// ��΃p�X + �摜�t�H���_�� +  �摜�t�@�C����
			AddImageData.stPartsPath		= absPath.generic_string();							// �p�[�c�̉摜�t�@�C���p�X
			AddImageData.iPartsGrHandle		= LoadGraph(AddImageData.stPartsPath.c_str());		// �p�[�c�̉摜�̃O���t�B�b�N�n���h��
			PartsImageData.push_back(AddImageData);												// �p�[�c�̉摜�f�[�^�ɒǉ�
		}

		/* �p�[�c�̉摜�f�[�^��ݒ� */
		PartsAnimData.PartsImageData = PartsImageData;
	}

	/* �A�j���[�V�����f�[�^�̓ǂݍ��� */
	if (j.contains("Animation") && j["Animation"].is_array())
	{
		/* �p�[�c�A�j���[�V�����̏�� */
		std::vector<Struct_2DPartsAnim::PARTS_ANIM_ANIM_DATA> AnimData;

		for (const auto& anim : j["Animation"])
		{
			/* �ǉ�����A�j���[�V�����f�[�^ */
			Struct_2DPartsAnim::PARTS_ANIM_ANIM_DATA AddAnimData;
			AddAnimData.AnimName			= anim.value("Name", "");	// �A�j���[�V������
			AddAnimData.PartsAnimFrameData.clear();

			if (anim.contains("Parts") && anim["Parts"].is_array())
			{
				for (const auto& frameArray : anim["Parts"])
				{
					/* �ǉ�����t���[���ł̃p�[�c���̃��X�g */
					std::vector<Struct_2DPartsAnim::PARTS_ANIM_PARTS_FRAME_DATA> AddAnimFrameData;
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
							AddAnimFrameData.push_back(AddFrameData);
						}
					
					}
					AddAnimData.PartsAnimFrameData.push_back(AddAnimFrameData);
				}
			}
			AnimData.push_back(AddAnimData);
		}

		/* �A�j���[�V�����f�[�^��ݒ� */
		PartsAnimData.PartsAnimData = AnimData;
	}

	/* �p�[�c�A�j���[�V�����̏���ݒ� */
	this->PartsAnimDataList.push_back(PartsAnimData);
}

// �p�[�c�A�j���[�V�����̕`��
// �� �`�ʗp�X�N���[���̃T�C�Y��ݒ肵�Ă�����s���邱��
void DataList_2DPartsAnimCreateTool::DrawPartsAnim(std::string FileName, std::string AnimDame, int iFrame)
{
	// ����
	// FileName	<- �p�[�c�A�j���[�V�����Q�̖���(==�t�@�C����)
	// AnimDame	<- �A�j���[�V������
	// iFrame	<- �t���[����(����)

	/* �w�肳�ꂽ�b���̃A�j���[�V������`�� */
	// �� X:0,Y:0����ʒu�Ƃ��ĕ`��
	// �� �`�ʂ���X�N���[���͎��O�ɐݒ肵�Ă�������

	for (const auto& partAnim : this->PartsAnimDataList)
	{
		/* �w�肳�ꂽ�p�[�c�A�j���[�V�����Q�ł��邩�m�F */
		if (partAnim.FileName == FileName)
		{
			/* �w�肳�ꂽ�A�j���[�V�������̃A�j���[�V������T�� */
			for (const auto& animData : partAnim.PartsAnimData)
			{
				if (animData.AnimName == AnimDame)
				{
					/* �w�肳�ꂽ�t���[�����̃p�[�c��񂪑��݂��邩�m�F */
					if (iFrame >= 0 && iFrame < animData.PartsAnimFrameData.size())
					{
						/* �w�肳�ꂽ�t���[�����̃p�[�c����`�� */
						for (const auto& partFrameData : animData.PartsAnimFrameData[iFrame])
						{
							/* �p�[�c������p�[�c�̉摜�f�[�^��T�� */
							for (const auto& partImageData : partAnim.PartsImageData)
							{
								if (partImageData.stPartsName == partFrameData.stPartsName)
								{
									// �p�[�c������v�����ꍇ
									/* �摜�̃T�C�Y���擾 */
									int iGrSizeX, iGrSizeY;
									GetGraphSize(partImageData.iPartsGrHandle, &iGrSizeX, &iGrSizeY);
									/* �p�[�c�̉摜��`�� */
									DrawRotaGraph3(
										static_cast<int>(partFrameData.fPartsX) + (this->iDrawScreenSize[SCREEN_SIZE_WIDE] / 2),	// �摜����]�`�ʂ����ʏ�ł̒��S���WX
										static_cast<int>(partFrameData.fPartsY) + (this->iDrawScreenSize[SCREEN_SIZE_HEIGHT] / 2),	// �摜����]�`�ʂ����ʏ�ł̒��S���WY
										static_cast<int>(iGrSizeX / 2),																// �摜����]�`�ʂ���摜��ł̒��S���WX
										static_cast<int>(iGrSizeY / 2),																// �摜����]�`�ʂ���摜��ł̒��S���WY
										partFrameData.fPartsScaleX,																	// �������̊g�嗦
										partFrameData.fPartsScaleY,																	// �c�����̊g�嗦
										partFrameData.fPartsAngle,																	// �摜�̉�]�p�x(���W�A��)
										partImageData.iPartsGrHandle,																// �`�ʂ���O���t�B�b�N�n���h��
										TRUE,																						// �摜�̓����x��L���ɂ��邩�ǂ���
										partFrameData.bPartsFlipX																	// �摜�����E���]���ĕ`�ʂ��邩�ǂ���
									);
									break;
								}
							}
						}
					}
					break;
				}
			}
			break;
		}
	}
}

// �p�[�c�A�j���[�V�����̍ő�t���[�����擾
int DataList_2DPartsAnimCreateTool::iGetPartsAnimMaxTime(std::string FileName, std::string AnimDame)
{
	// ����
	// FileName	<- �p�[�c�A�j���[�V�����Q�̖���(==�t�@�C����)
	// AnimDame	<- �A�j���[�V������
	// �߂�l
	// iMaxFrame <- �w�肳�ꂽ�A�j���[�V�����̍ő�t���[����(����)

	int iMaxFrame = 0; // �ő�t���[����(����)
	for (const auto& partAnim : this->PartsAnimDataList)
	{
		/* �w�肳�ꂽ�p�[�c�A�j���[�V�����Q�ł��邩�m�F */
		if (partAnim.FileName == FileName)
		{
			/* �w�肳�ꂽ�A�j���[�V�������̃A�j���[�V������T�� */
			for (const auto& animData : partAnim.PartsAnimData)
			{
				if (animData.AnimName == AnimDame)
				{
					/* �ő�t���[����(����)���擾 */
					iMaxFrame = static_cast<int>(animData.PartsAnimFrameData.size());
					break;
				}
			}
			break;
		}
	}
	return iMaxFrame;
}

// �`��p�X�N���[���̃T�C�Y�ݒ�
// �� ��ʒ�������Ƀp�[�c��`�ʂ���̂Ŏ��O�ɐݒ肷�邱��
void DataList_2DPartsAnimCreateTool::SetDrawScreenSize(int iWide, int iHeight)
{
	// ����
	// iWide	<- �`��p�X�N���[���̉���
	// iHeight	<- �`��p�X�N���[���̏c��

	iDrawScreenSize[SCREEN_SIZE_WIDE]	= iWide;
	iDrawScreenSize[SCREEN_SIZE_HEIGHT]	= iHeight;
}