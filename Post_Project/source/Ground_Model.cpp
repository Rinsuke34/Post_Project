/* �n�`(3D���f��)�N���X�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �w�b�_�t�@�C��
#include "Ground_Model.h"

// �R���X�g���N�^
Ground_Model::Ground_Model() : Ground_Base()
{
	/* ������ */
	this->iModelHandle		= -1;	// ���f���n���h��

	this->vecPosition		= VGet(0.f, 0.f, 0.f);		// �I�u�W�F�N�g�̍��W
	this->vecRotation		= VGet(0.f, 0.f, 0.f);		// �I�u�W�F�N�g�̉�]��
	this->vecScale			= VGet(0.f, 0.f, 0.f);		// �I�u�W�F�N�g�̊g�嗦(x,y,z�������ꂼ��̊g��{��)
}

// �f�X�g���N�^
Ground_Model::~Ground_Model()
{
	/* ���f���n���h���폜 */
	MV1DeleteModel(this->iModelHandle);
}

// �����ݒ�
// �����f���n���h���A���W�A��]�ʁA�g�嗦��ݒ肵����ɌĂяo������
void Ground_Model::InitialSetup()
{
	/* ���W�ݒ� */
	MV1TerminateCollInfo(this->iModelHandle);

	/* ��]�ʐݒ� */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotation);

	/* �g�嗦�ݒ� */
	MV1SetScale(this->iModelHandle, this->vecScale);

	/* �X�V(�R���W�������) */
	SetUpCollision();
}

// �`��
void Ground_Model::Draw()
{
	/* ���݂̃��f���̓����x�擾 */
	float OpacityRate = MV1GetOpacityRate(this->iModelHandle);

	/* �����x�m�F */
	if (OpacityRate > 0.f)
	{
		// ���S�ɓ����łȂ��ꍇ
		/* ���f���`�� */
		MV1DrawModel(this->iModelHandle);
	}
}

// �R���W�����̐ݒ�
void Ground_Model::SetUpCollision()
{
	this->stBox.vecBoxCenter	= { 0.f, 0.f, 0.f };
	this->stBox.vecBoxHalfSize	= { 0.f, 0.f, 0.f };
}
