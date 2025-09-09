/* �V�[��"�Q�[�����C��"�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �w�b�_�t�@�C��
#include "Scene_GameMain.h"

// �֘A�N���X
#include "Scene_Stage.h"
#include "DataList_Object.h"
#include "DataList_GameStatus.h"

// �R���X�g���N�^
Scene_GameMain::Scene_GameMain() : Scene_Base("Scene_GameMain", 0, false, false)
{
	/* �f�[�^���X�g�쐬 */	
	gpDataListServer->AddDataList(std::make_shared<DataList_GameStatus>());		// �Q�[����ԊǗ�
	gpDataListServer->AddDataList(std::make_shared<DataList_Object>());			// �I�u�W�F�N�g�Ǘ�

	/* �V�[���쐬 */
	gpSceneServer->AddSceneReservation(std::make_shared<Scene_Stage>());		// �X�e�[�W�V�[��

	/* �f�[�^���X�g�擾 */
	this->pDataList_Object		= std::dynamic_pointer_cast<DataList_Object>(gpDataListServer->GetDataList("DataList_Object"));			// �I�u�W�F�N�g�Ǘ�
	this->pDataList_GameStatus	= std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));	// �Q�[����ԊǗ�
}

// �f�X�g���N�^
Scene_GameMain::~Scene_GameMain()
{

}

// �X�V
void Scene_GameMain::Update()
{
	/* �I�u�W�F�N�g�X�V */
	this->pDataList_Object->Update_All();

	/* �폜�t���O���L���ȃI�u�W�F�N�g�폜 */
	this->pDataList_Object->DeleteFlagged_AllObject();
}
