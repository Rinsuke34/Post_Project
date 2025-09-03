/* �n�`(3D���f��)�N���X�̒�` */

#include "Ground_Model.h"

// �R���X�g���N�^
Ground_Model::Ground_Model() : Ground_Base()
{
	/* ������ */
	this->iModelHandle		= -1;	// ���f���n���h��
	this->iCollisionFrameNo	= -1;	// �R���W�����p�̃t���[���ԍ�

	this->vecPosition		= VGet(0.f, 0.f, 0.f);		// �I�u�W�F�N�g�̍��W
	this->vecRotation		= VGet(0.f, 0.f, 0.f);		// �I�u�W�F�N�g�̉�]��
	this->vecScale			= VGet(0.f, 0.f, 0.f);		// �I�u�W�F�N�g�̊g�嗦(x,y,z�������ꂼ��̊g��{��)
}

// �f�X�g���N�^
Ground_Model::~Ground_Model()
{

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
	Update_Collision();
}

// �X�V
void Ground_Model::Update()
{

}

// �`��
void Ground_Model::Draw()
{

}

// �X�V(�R���W�������)
void Ground_Model::Update_Collision()
{
	/* �R���W�����t���[���ԍ��擾 */
	this->iCollisionFrameNo	=	MV1SearchFrame(this->iModelHandle, "Collision");

	/* �R���W�����t���[���ԍ��̎擾�𐬌��������̊m�F */
	if (this->iCollisionFrameNo >= 0)
	{
		// �R���W�����t���[���ԍ��̎擾�ɐ��������ꍇ
		/* �R���W�����̐ݒ肳�ꂽ�t���[���̃R���W�������\�z */
		MV1SetupCollInfo(this->iModelHandle, this->iCollisionFrameNo, 1, 1, 1);

		/* �R���W�����̐ݒ肳�ꂽ�t���[����`�ʂ��Ȃ��悤�ɐݒ� */
		MV1SetFrameVisible(this->iModelHandle, this->iCollisionFrameNo, FALSE);
	}
}

// �R���W�����ڐG����
// ���f�� - �J�v�Z��
bool Ground_Model::HitCheck(Struct_Collision::COLLISION_CAPSULE	stCapsule)
{
	// ����
	// stCapsule	: ���肷��J�v�Z���R���W����
	// �߂�l
	// bool : �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	/* �R���W�����t���[�������݂��Ȃ����m�F */
	if (this->iCollisionFrameNo < 0)
	{
		// ���݂��Ȃ��ꍇ
		/* ��ڐG�Ƃ��Ĕ��肷�� */
		return false;
	}

	/* �|���S���Ƃ̐ڐG��� */
	MV1_COLL_RESULT_POLY_DIM stHitPolyDim;

	/* �v���b�g�t�H�[���̃��f���ƑΏۂ̃J�v�Z���R���W�������ڐG���Ă��邩�̏��擾 */
	stHitPolyDim = MV1CollCheck_Capsule(
		/* ���̃I�u�W�F�N�g�̃R���W���� */
		this->iModelHandle, this->iCollisionFrameNo,
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		stCapsule.vecCapsuleTop, stCapsule.vecCapsuleBottom, stCapsule.fCapsuleRadius);

	/* �ڐG�����擾 */
	if (stHitPolyDim.HitNum > 0)
	{
		// �ڐG���Ă���ꍇ
		return true;
	}
	//�ڐG���Ă��Ȃ��ꍇ
	return false;
}

// ���f�� - ����
bool Ground_Model::HitCheck(Struct_Collision::COLLISION_SQHERE	stSqhere)
{
	// ����
	// stCapsule	: ���肷�鋅�̃R���W����
	// �߂�l
	// bool			: �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	/* �R���W�����t���[�������݂��Ȃ����m�F */
	if (this->iCollisionFrameNo < 0)
	{
		// ���݂��Ȃ��ꍇ
		/* ��ڐG�Ƃ��Ĕ��肷�� */
		return false;
	}

	/* �|���S���Ƃ̐ڐG��� */
	MV1_COLL_RESULT_POLY_DIM stHitPolyDim;

	/* �v���b�g�t�H�[���̃��f���ƑΏۂ̋��̃R���W�������ڐG���Ă��邩�̏��擾 */
	stHitPolyDim = MV1CollCheck_Capsule(
		/* ���̃I�u�W�F�N�g�̃R���W���� */
		this->iModelHandle, this->iCollisionFrameNo,
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		stSqhere.vecSqhere, stSqhere.vecSqhere, stSqhere.fSqhereRadius);

	/* �ڐG�����擾 */
	if (stHitPolyDim.HitNum > 0)
	{
		// �ڐG���Ă���ꍇ
		return true;
	}
	// �ڐG���Ă��Ȃ��ꍇ
	return false;
}

// ���f�� - ����
bool Ground_Model::HitCheck(Struct_Collision::COLLISION_LINE	stLine)
{
	// ����
	// stLine	: ���肷������R���W����
	// �߂�l
	// bool		: �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	/* �R���W�����t���[�������݂��Ȃ����m�F */
	if (this->iCollisionFrameNo < 0)
	{
		// ���݂��Ȃ��ꍇ
		/* ��ڐG�Ƃ��Ĕ��肷�� */
		return false;
	}

	/* �|���S���Ƃ̐ڐG��� */
	MV1_COLL_RESULT_POLY stHitPolyDim;

	/* �v���b�g�t�H�[���̃��f���ƑΏۂ̐����R���W�������ڐG���Ă��邩�̏��擾 */
	stHitPolyDim = MV1CollCheck_Line(
		/* ���̃I�u�W�F�N�g�̃R���W���� */
		this->iModelHandle, this->iCollisionFrameNo,
		/* ���肷��I�u�W�F�N�g�̃R���W���� */
		stLine.vecLineStart, stLine.vecLineEnd);

	/* �ڐG�������m�F */
	if (stHitPolyDim.HitFlag == 1)
	{
		// �ڐG���Ă���ꍇ
		return true;
	}

	// �ڐG���Ă��Ȃ��ꍇ
	return false;
}
