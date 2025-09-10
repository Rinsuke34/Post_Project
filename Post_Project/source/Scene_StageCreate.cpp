/* �V�[��"�X�e�[�W�쐬"�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �w�b�_�t�@�C��
#include "Scene_StageCreate.h"
// �֘A�N���X
// �֘A�N���X
#include "Scene_Stage.h"
#include "DataList_Object.h"
#include "DataList_StageCreate.h"

// �R���X�g���N�^
Scene_StageCreate::Scene_StageCreate() : Scene_Base("Scene_StageCreate", 100, true, false)
{
	/* �f�[�^���X�g�쐬 */
	gpDataListServer->AddDataList(std::make_shared<DataList_Object>());			// �I�u�W�F�N�g�Ǘ�
	gpDataListServer->AddDataList(std::make_shared<DataList_StageCreate>());	// �X�e�[�W�N���G�C�g���Ǘ�

	/* �V�[���쐬 */
	gpSceneServer->AddSceneReservation(std::make_shared<Scene_Stage>());		// �X�e�[�W�V�[��

	/* �f�[�^���X�g�擾 */
	this->pDataList_StageCreate	= std::dynamic_pointer_cast<DataList_StageCreate>(gpDataListServer->GetDataList("DataList_StageCreate"));	// �X�e�[�W�N���G�C�g���Ǘ�

	this->pDataList_StageCreate->Load_MapData("AreaData_Front");
}

// �f�X�g���N�^
Scene_StageCreate::~Scene_StageCreate()
{
	/* �f�[�^���X�g�폜 */
	gpDataListServer->DeleteDataList("DataList_StageCreate");	// �X�e�[�W�N���G�C�g���Ǘ�
}

// �X�V
void Scene_StageCreate::Update()
{
	/* ���݂̑I�����W���擾 */
	VECTOR_INT vecSelectPos = this->pDataList_StageCreate->vecGetSelectPos();

	/* �I�����W��ύX */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_W] == TRUE)
	{
		vecSelectPos.z += 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_S] == TRUE)
	{
		vecSelectPos.z -= 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_D] == TRUE)
	{
		vecSelectPos.x += 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_A] == TRUE)
	{
		vecSelectPos.x -= 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_SPACE] == TRUE)
	{
		vecSelectPos.y += 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_LSHIFT] == TRUE)
	{
		vecSelectPos.y -= 1;
	}

	/* �I�����W���X�V */
	this->pDataList_StageCreate->SetSelectPos(vecSelectPos);
}

// �`��
void Scene_StageCreate::Draw()
{
	/* �X�e�[�W�쐬�Ɋ֘A�������`�� */
}
