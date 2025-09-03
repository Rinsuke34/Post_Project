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
	this->piGrHandle = nullptr;
}

// �`��
void Ground_Plane::Draw()
{
	/* ���_���W��ݒ� */
	VERTEX3D aVertex[4];
	for (int iIndex = 0; iIndex < 4; ++iIndex)
	{
		aVertex[iIndex].pos		= this->avecVertex[iIndex];			// ���_���W
		aVertex[iIndex].norm	= this->vecNormal;					// �@���x�N�g��
		aVertex[iIndex].dif		= GetColorU8(255, 255, 255, 255);	// �g�U����
		aVertex[iIndex].spc		= GetColorU8(0, 0, 0, 0);			// ���ʌ��̐F
		// ���_�̃e�N�X�`�����W
		switch (iIndex)
		{
			case 0: aVertex[iIndex].u = 0.0f; aVertex[iIndex].v = 0.0f; break;
			case 1: aVertex[iIndex].u = 1.0f; aVertex[iIndex].v = 0.0f; break;
			case 2: aVertex[iIndex].u = 1.0f; aVertex[iIndex].v = 1.0f; break;
			case 3: aVertex[iIndex].u = 0.0f; aVertex[iIndex].v = 1.0f; break;
		}
	}

	/* ���_�C���f�b�N�X��ݒ� */
	// ���l�p�`���̎O�p�`�ɕ�������
	unsigned short IndexTop[6] = { 0, 1, 2, 0, 2, 3 };

	/* �l�p�`�i�|���S���j�̕`�� */
	DrawPolygonIndexed3D(aVertex, 4, IndexTop, 2, *this->piGrHandle, TRUE);
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
