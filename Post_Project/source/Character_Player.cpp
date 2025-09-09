/* �v���C���[�N���X�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �w�b�_�t�@�C��
#include "Character_Player.h"
// �֘A�N���X
#include "DataList_GameStatus.h"
// ���ʒ�`
#include "Test_ConstantDefine.h"
#include "ConstantDefine.h"

// �R���X�g���N�^
Character_Player::Character_Player() : Character_Base()
{
	// �f�[�^���X�g�擾
	this->pDataList_GameStatus				= std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));							// �Q�[����ԊǗ�
	this->pDataList_2DPartsAnimCreateTool	= std::dynamic_pointer_cast<DataList_2DPartsAnimCreateTool>(gpDataListServer->GetDataList("DataList_2DPartsAnimCreateTool"));	// 2D�p�[�c�A�j���[�V�����c�[��

	// �摜�f�[�^�쐬
	this->iScreenHandle_Animation	= MakeScreen(CHARACTER_PARTS_ANIM_DRAW_SIZE_WIDE, CHARACTER_PARTS_ANIM_DRAW_SIZE_HEIGHT, TRUE);

	/* ������ */
	this->AnimFileName	= "Test_Player";	// �A�j���[�V�����t�@�C����
	this->NowMotionName	= "Delay";			// ���݂̃��[�V������
	this->iMotionCount	= 0;

	// �p�[�c�A�j���[�V�����Z�b�g�A�b�v
	this->pDataList_2DPartsAnimCreateTool->LoadPartsAnimData(this->AnimFileName);
	
	/* �R���W�����ݒ� */
	// �����ݒ�
	this->stBox.vecBoxHalfSize	= VGet(64 / 2, 32 / 2, 64 / 2);

	/* �X�e�[�^�X�֌W */
	// �����ݒ�
	this->iSpeed = TEST_PLAYER_MOVE_SPEED;
}

// �f�X�g���N�^
Character_Player::~Character_Player()
{
	/* �摜�f�[�^�폜 */
	// �A�j���[�V�����p
	DeleteGraph(this->iScreenHandle_Animation);
}

// �X�V
void Character_Player::Update()
{
	/* �ړ��E�d�͏��� */
	Update_ApplyGravity();
	Update_ApplyMovement();	

	/* ���[���h�}�b�v��̍��W��ݒ� */
	this->pDataList_GameStatus->SetPlayerPosition_WoldMap(this->vecBasePosition);

	/* �x�[�X�N���X�̍X�V���� */
	Character_Base::Update();

	/* �A�j���[�V�����̍X�V */
	Update_Animation();
}
