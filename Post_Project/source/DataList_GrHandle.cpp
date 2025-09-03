/* �f�[�^���X�g"�摜�f�[�^�Ǘ�"�N���X�̒�` */

#include "DataList_GrHandle.h"

// �R���X�g���N�^
DataList_GrHandle::DataList_GrHandle() : DataList_Base("DataList_GrHandle")
{
	/* ������ */
	this->pGrHandleList.clear();	// �摜�f�[�^���X�g
}

// �f�X�g���N�^
DataList_GrHandle::~DataList_GrHandle()
{
	/* ���X�g���̉摜�n���h�����폜 */
	for (auto& list : this->pGrHandleList)
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
		this->pGrHandleList[cFileName] = GrHandle;
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
		this->pGrHandleList[cFileName] = GrHandle;
	}

	return;
}

// �摜�f�[�^�擾
int DataList_GrHandle::iGetGrhandle(std::string& cFileName)
{
	// ����
	// cFileName	: �摜�t�@�C����
	// �߂�l
	// int			: �摜�n���h��

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
	
	/* �Ώۂ̉摜�f�[�^��߂�l�ɐݒ� */
	iReturn = pGrHandleList[cFileName];

	return iReturn;
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
	if (this->pGrHandleList.count(cFileName) != 0)
	{
		// �o�^����Ă���ꍇ
		bReturn = true;
	}

	return bReturn;
}
