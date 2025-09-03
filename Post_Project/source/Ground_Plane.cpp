/* �n�`(����)�N���X�̒�` */

#include "Ground_Plane.h"


// �R���X�g���N�^
Ground_Plane::Ground_Plane() : Ground_Base()
{
	/* ������ */
	this->vecNormal = VGet(0.0f, 1.0f, 0.0f);
	for(int iIndex = 0; iIndex < 4; ++iIndex)
	{
		this->avecVertex[iIndex] = VGet(0.0f, 0.0f, 0.0f);
	}
}

// �X�V
void Ground_Plane::Update()
{

}

// �`��
void Ground_Plane::Draw()
{

}

// �R���W�����ڐG����
// ���� - �J�v�Z��
bool Ground_Plane::HitCheck(Struct_Collision::COLLISION_CAPSULE	stCapsule)
{
	// ����
	// stCapsule		<-	�J�v�Z���̏��
	// �߂�l
	// bool				<-	�ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	bool bHitFlg = false;

	/* �ڐG���� */
	// ���ʂ��̎O�p�`�ɕ������āA�e�O�p�`�ƃJ�v�Z���̓����蔻����s��
	// �O�p�`1: [0,1,2]
	if (HitCheck_Capsule_Triangle(
		stCapsule.vecCapsuleTop,
		stCapsule.vecCapsuleBottom,
		stCapsule.fCapsuleRadius,
		this->avecVertex[0],
		this->avecVertex[1],
		this->avecVertex[2]) == TRUE)
	{
		bHitFlg = true;
	}

	// �O�p�`2: [0,2,3]
	if (HitCheck_Capsule_Triangle(
		stCapsule.vecCapsuleTop,
		stCapsule.vecCapsuleBottom,
		stCapsule.fCapsuleRadius,
		this->avecVertex[0],
		this->avecVertex[2],
		this->avecVertex[3]) == TRUE)
	{
		bHitFlg = true;
	}

	return bHitFlg;
}

// ���� - ����
bool Ground_Plane::HitCheck(Struct_Collision::COLLISION_SQHERE	stSqhere)
{
	// ����
	// stSqhere		<-	���̂̏��
	// �߂�l
	// bool			<-	�ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	bool bHitFlg = false;

	/* �ڐG���� */
	// ���ʂ��̎O�p�`�ɕ������āA�e�O�p�`�Ƌ��̂̓����蔻����s��
	// �O�p�`1: [0,1,2]
	if (HitCheck_Sphere_Triangle(
		stSqhere.vecSqhere,
		stSqhere.fSqhereRadius,
		this->avecVertex[0],
		this->avecVertex[1],
		this->avecVertex[2]) == TRUE)
	{
		bHitFlg = true;
	}

	// �O�p�`2: [0,2,3]
	if (HitCheck_Sphere_Triangle(
		stSqhere.vecSqhere,
		stSqhere.fSqhereRadius,
		this->avecVertex[0],
		this->avecVertex[2],
		this->avecVertex[3]) == TRUE)
	{
		bHitFlg = true;
	}

	return bHitFlg;
}

// ���� - ����
bool Ground_Plane::HitCheck(Struct_Collision::COLLISION_LINE	stLine)
{
	// ����
	// stLine		<-	�����̏��
	// �߂�l
	// bool			<-	�ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	bool bHitFlg = false;

	/* �ڐG���� */
	// ���ʂ��̎O�p�`�ɕ������āA�e�O�p�`�Ɛ����̓����蔻����s��
	// �O�p�`1: [0,1,2]
	if (HitCheck_Line_Triangle(
		stLine.vecLineStart,
		stLine.vecLineEnd,
		this->avecVertex[0],
		this->avecVertex[1],
		this->avecVertex[2]).HitFlag == TRUE)
	{
		bHitFlg = true;
	}

	// �O�p�`2: [0,2,3]
	if (HitCheck_Line_Triangle(
		stLine.vecLineStart,
		stLine.vecLineEnd,
		this->avecVertex[0],
		this->avecVertex[1],
		this->avecVertex[2]).HitFlag == TRUE)
	{
		bHitFlg = true;
	}

	return bHitFlg;
}
