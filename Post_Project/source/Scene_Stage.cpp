/* �V�[��"�X�e�[�W"�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �w�b�_�t�@�C��
#include "Scene_Stage.h"
// �֘A�N���X
#include "DataList_Object.h"
#include "DataList_GameStatus.h"
#include "DataList_StageCreate.h"
// ���ʒ�`
#include "ConstantDefine.h"

// �R���X�g���N�^
Scene_Stage::Scene_Stage() : Scene_Base("Scene_Stage", 1, false, false)
{
	/* �摜�f�[�^�쐬 */
	// �摜
	this->iScreenHandle_Stage		= MakeScreen(SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT);
	// �V���h�E�}�b�v
	this->iScreenHandle_ShadowMap[SHADOWMAP_GROUND]	= MakeShadowMap(SHADOW_GROUND_MAP_SIZE_WIDE, SHADOW_GROUND_MAP_SIZE_HEIGHT);
	this->iScreenHandle_ShadowMap[SHADOWMAP_ACTOR]	= MakeShadowMap(SHADOW_ACTOR_MAP_SIZE_WIDE, SHADOW_ACTOR_MAP_SIZE_HEIGHT);

	/* �f�[�^���X�g�擾 */
	this->pDataList_Object		= std::dynamic_pointer_cast<DataList_Object>(gpDataListServer->GetDataList("DataList_Object"));				// �I�u�W�F�N�g�Ǘ�
	this->pDataList_GameStatus	= std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));		// �Q�[����ԊǗ�
	this->pDataList_StageCreate = std::dynamic_pointer_cast<DataList_StageCreate>(gpDataListServer->GetDataList("DataList_StageCreate"));	// �X�e�[�W�N���G�C�g���Ǘ�

	std::shared_ptr<DataList_StageCreate>	pDataList_StageCreate;	// �X�e�[�W�N���G�C�g���Ǘ�

	/* �Q�[����ԊǗ��f�[�^���X�g���ǂݍ��܂�Ă��邩�m�F */
	if (this->pDataList_GameStatus != nullptr)
	{
		// �ǂݍ��܂�Ă���ꍇ
		/* ���[���h�}�b�v(����)�ǂݍ��� */
		JsonLoad_WoldMap_Center();
	}
	/* �X�e�[�W�N���G�C�g���Ǘ��f�[�^���X�g���ǂݍ��܂�Ă��邩�m�F */
	else if (this->pDataList_StageCreate != nullptr)
	{
		// �ǂݍ��܂�Ă���ꍇ

	}	
}

// �f�X�g���N�^
Scene_Stage::~Scene_Stage()
{
	/* �摜�f�[�^�폜 */
	// �摜
	DeleteGraph(this->iScreenHandle_Stage);
	// �V���h�E�}�b�v
	DeleteShadowMap(this->iScreenHandle_ShadowMap[SHADOWMAP_GROUND]);
	DeleteShadowMap(this->iScreenHandle_ShadowMap[SHADOWMAP_ACTOR]);
}

// �X�V
void Scene_Stage::Update()
{

}

