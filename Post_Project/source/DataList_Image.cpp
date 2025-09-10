/* �f�[�^���X�g"�摜�f�[�^�Ǘ�"�N���X�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �W�����C�u����
#include <fstream>
// �w�b�_�t�@�C��
#include "DataList_Image.h"
// ���ʒ�`
#include "StructDefine.h"

// �R���X�g���N�^
DataList_Image::DataList_Image() : DataList_Base("DataList_Image")
{
	/* ������ */
	this->GrHandleList.clear();	// �摜�f�[�^���X�g

	/* �e�N�X�`���ǂݍ��� */
	JsonLoad_Texture();
}

// �f�X�g���N�^
DataList_Image::~DataList_Image()
{
	/* ���X�g���̉摜�n���h�����폜 */
	for (auto& list : this->GrHandleList)
	{
		/* �摜���폜 */
		DeleteGraph(list.second);
		list.second = -1;
	}
}

// �摜�f�[�^�ǂݍ���
void DataList_Image::LoadGrHandle(std::string& cFileName)
{
	// ����
	// cFileName		<-	�ǂݍ��މ摜�f�[�^�̃t�@�C����

	/* �Ώۂ̉摜�f�[�^���ǂݍ��܂�Ă��Ȃ����m�F */
	if (bCheckGrHandle(cFileName) == false)
	{
		// �ǂݍ��܂�Ă��Ȃ��ꍇ
		/* �摜�̃t�@�C���p�X���擾 */
		std::string FileName = "resource/ImageData/" + cFileName + ".png";

		/* �摜�f�[�^�ǂݍ��� */
		int GrHandle = LoadGraph(FileName.c_str());

		/* �摜�f�[�^�����X�g�ɒǉ� */
		this->GrHandleList[cFileName] = GrHandle;
	}

	return;
}

// �摜�f�[�^�擾
std::shared_ptr<int> DataList_Image::iGetGrhandle(std::string& cFileName)
{
	// ����
	// cFileName			: �摜�t�@�C����
	// �߂�l
	// std::shared_ptr<int>	: �摜�n���h���̃|�C���^

	int iReturn = 0;

	/* �Ώۂ̉摜���擾���� */
	// ���ǂݍ��܂�Ă��Ȃ��Ȃ�ǂݍ���

	/* �Ώۂ̉摜�f�[�^���ǂݍ��܂�Ă��Ȃ����m�F */
	if (bCheckGrHandle(cFileName) == false)
	{
		// �ǂݍ��܂�Ă��Ȃ��ꍇ
		/* �摜�f�[�^��ǂݍ��� */
		LoadGrHandle(cFileName);
	}
	
	/* �摜�n���h���̃|�C���^���X�}�[�g�|�C���^�ŕԂ� */
	auto list = GrHandleList.find(cFileName);
	if (list != GrHandleList.end())
	{
		/* �Ώۂ̉摜�n���h���̃|�C���^��߂�l�ŕԋp */
		return std::make_shared<int>(list->second);
	}

	/* ������Ȃ������ꍇ��nullptr��Ԃ� */
	// ���ʏ�͂����ɗ��邱�Ƃ͂Ȃ��z��
	return nullptr;
}

// �Y���摜�n���h���f�[�^���݊m�F
bool DataList_Image::bCheckGrHandle(std::string& cFileName)
{
	// ����
	// cFileName	: �ǂݍ��މ摜�f�[�^�̃t�@�C����
	// �߂�l
	// bool			: �摜�f�[�^���o�^����Ă��邩(true:�o�^����Ă��� / false:�o�^����Ă��Ȃ�)

	/* �Ώۂ̉摜�����X�g�ɓo�^����Ă��邩�m�F */

	bool bReturn = false;

	/* �Ώۂ�3D���f�����o�^����Ă��邩 */
	if (this->GrHandleList.count(cFileName) != 0)
	{
		// �o�^����Ă���ꍇ
		bReturn = true;
	}

	return bReturn;
}

// �e�N�X�`���ǂݍ���
void DataList_Image::JsonLoad_Texture()
{
	/* �e�N�X�`���f�[�^��ǂݍ��݁A�e�N�X�`���f�[�^���X�g�ɓo�^���� */

	/* Json�t�@�C���ǂݍ��� */
	std::string FilePath = "resource/MapData/Texture_Data.json";

	std::ifstream ifs(FilePath);
	if (!ifs) return;

	using json = nlohmann::json;
	json j;
	ifs >> j;

	/* �e�N�X�`���f�[�^���X�g�ւ̐ݒ� */
	for (const auto& elem : j)
	{
		TEXTURE_DATA data;
		data.BlockName		= elem.value("BlockName", "");
		data.iBlockIndex	= elem.value("BlockIndex", -1);
		data.aImageName[0]	= elem.value("ImageName_Upper", "");
		data.aImageName[1]	= elem.value("ImageName_Side", "");
		data.aImageName[2]	= elem.value("ImageName_Under", "");

		this->AddTexture(data);
	}

	/* �f�[�^���X�g"�摜�f�[�^�Ǘ�"�փe�N�X�`���摜�̓o�^ */
	for (auto& texData : this->GetTextureDataList())
	{
		// ���
		if (!texData.aImageName[0].empty())
		{
			this->LoadGrHandle(texData.aImageName[0]);
		}
		// ����
		if (!texData.aImageName[1].empty())
		{
			this->LoadGrHandle(texData.aImageName[1]);
		}
		// ����
		if (!texData.aImageName[2].empty())
		{
			this->LoadGrHandle(texData.aImageName[2]);
		}
	}
}
