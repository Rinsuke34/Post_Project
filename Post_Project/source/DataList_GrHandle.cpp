/* �f�[�^���X�g"�摜�f�[�^�Ǘ�"�N���X�̒�` */

#include "DataList_GrHandle.h"

// �R���X�g���N�^
DataList_GrHandle::DataList_GrHandle() : DataList_Base("DataList_GrHandle")
{
	/* ������ */
	this->GrHandleList.clear();	// �摜�f�[�^���X�g
}

// �f�X�g���N�^
DataList_GrHandle::~DataList_GrHandle()
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
void DataList_GrHandle::LoadGrHandle(std::string& cFileName)
{
	// ����
	// cFileName		<-	�ǂݍ��މ摜�f�[�^�̃t�@�C����

	/* �Ώۂ̉摜�f�[�^���ǂݍ��܂�Ă��Ȃ����m�F */
	if (bCheckGrHandle(cFileName) == false)
	{
		// �ǂݍ��܂�Ă��Ȃ��ꍇ
		/* �摜�̃t�@�C���p�X���擾 */
		std::string FileName = "resource/ImageData/" + cFileName + ".mv1";

		/* �摜�f�[�^�ǂݍ��� */
		int GrHandle = LoadGraph(FileName.c_str());

		/* �摜�f�[�^�����X�g�ɒǉ� */
		this->GrHandleList[cFileName] = GrHandle;
	}

	return;
}

// �摜�f�[�^�ǂݍ���(2D�p�[�c�A�j���[�V�����p)
void DataList_GrHandle::LoadGrHandle_2DPartsAnim(std::string& cFileName)
{
	// ����
	// cFileName		<-	�ǂݍ��މ摜�f�[�^�̃t�@�C����

	/* �Ώۂ̉摜�f�[�^���ǂݍ��܂�Ă��Ȃ����m�F */
	if (bCheckGrHandle(cFileName) == false)
	{
		// �ǂݍ��܂�Ă��Ȃ��ꍇ
		/* �摜�̃t�@�C���p�X���擾 */
		std::filesystem::path currentDir	= std::filesystem::current_path();
		std::filesystem::path parentDir		= currentDir.parent_path();
		std::filesystem::path resourceDir	= parentDir / "AnimData_Resource";
		std::filesystem::path absPath		= resourceDir / (cFileName + ".png");

		/* �摜�f�[�^�ǂݍ��� */
		int GrHandle = LoadGraph(absPath.generic_string().c_str());

		/* �摜�f�[�^�����X�g�ɒǉ� */
		this->GrHandleList[cFileName] = GrHandle;
	}

	return;
}

// �摜�f�[�^�擾
std::shared_ptr<int> DataList_GrHandle::iGetGrhandle(std::string& cFileName)
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
bool DataList_GrHandle::bCheckGrHandle(std::string& cFileName)
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
