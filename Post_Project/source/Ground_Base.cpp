/* �n�`�̃x�[�X�N���X�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �W�����C�u����
#define NOMINMAX
#include <algorithm>
// �w�b�_�t�@�C��
#include "Ground_Base.h"
// ���ʒ�`
#include "ConstantDefine.h"

// �R���X�g���N�^
Ground_Base::Ground_Base() : Object_Base()
{

}

// �R���W�����ڐG����
// ���� - �{�b�N�X
bool Ground_Base::HitCheck(Struct_Collision::COLLISION_SQHERE stSqhere)
{
	// ����
	// stSqhere	: ���肷�鋅�̃R���W����
	// �߂�l
	// bool		: �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	bool bHitFlg = false;

	/* ������s���������ł��邩 */
	if (std::abs(VSquareSize(VSub(stSqhere.vecSqhere, this->stBox.vecBoxCenter))) > COLLISION_CHECK_DISTANCE)
	{
		// ������s�������O�ł���ꍇ�͐ڐG���Ă��Ȃ��Ƃ݂Ȃ�
		return bHitFlg;
	}

	/* �ڐG���� */
	// �{�b�N�X�̊e���̍ŏ��l�ƍő�l���擾
	float fBoxMinX = this->stBox.vecBoxCenter.x - (this->stBox.vecBoxHalfSize.x / 2.0f);
	float fBoxMaxX = this->stBox.vecBoxCenter.x + (this->stBox.vecBoxHalfSize.x / 2.0f);
	float fBoxMinY = this->stBox.vecBoxCenter.y - (this->stBox.vecBoxHalfSize.y / 2.0f);
	float fBoxMaxY = this->stBox.vecBoxCenter.y + (this->stBox.vecBoxHalfSize.y / 2.0f);
	float fBoxMinZ = this->stBox.vecBoxCenter.z - (this->stBox.vecBoxHalfSize.z / 2.0f);
	float fBoxMaxZ = this->stBox.vecBoxCenter.z + (this->stBox.vecBoxHalfSize.z / 2.0f);

	// ���̂̒��S���W���{�b�N�X�̊e���͈͓̔��Ɏ��߂�
	float fClosestX = PUBLIC_PROCESS::fClamp(stSqhere.vecSqhere.x, fBoxMaxX, fBoxMinX);
	float fClosestY = PUBLIC_PROCESS::fClamp(stSqhere.vecSqhere.y, fBoxMaxY, fBoxMinY);
	float fClosestZ = PUBLIC_PROCESS::fClamp(stSqhere.vecSqhere.z, fBoxMaxZ, fBoxMinZ);

	// ���̂̒��S�ƍł��߂��_�Ƃ̋������v�Z
	float fDistanceX = stSqhere.vecSqhere.x - fClosestX;
	float fDistanceY = stSqhere.vecSqhere.y - fClosestY;
	float fDistanceZ = stSqhere.vecSqhere.z - fClosestZ;
	float fDistanceSquared = (fDistanceX * fDistanceX) + (fDistanceY * fDistanceY) + (fDistanceZ * fDistanceZ);

	// �����̓�悪���̂̔��a�̓��ȉ��ł���ΐڐG���Ă���
	if (fDistanceSquared <= (stSqhere.fSqhereRadius * stSqhere.fSqhereRadius))
	{
		bHitFlg = true;
	}

	return bHitFlg;
}

// ���� - �{�b�N�X
bool Ground_Base::HitCheck(Struct_Collision::COLLISION_LINE stLine)
{
	// ����
	// stLine	: ���肷����R���W����
	// �߂�l
	// bool		: �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	// �{�b�N�X�̊e���̍ŏ��l�ƍő�l��z��Ŏ擾
	float boxCenter[3] = { this->stBox.vecBoxCenter.x, this->stBox.vecBoxCenter.y, this->stBox.vecBoxCenter.z };
	float boxSize[3] = { this->stBox.vecBoxHalfSize.x,   this->stBox.vecBoxHalfSize.y,   this->stBox.vecBoxHalfSize.z };
	float boxMin[3], boxMax[3];
	for (int i = 0; i < 3; ++i)
	{
		boxMin[i] = boxCenter[i] - boxSize[i] / 2.0f;
		boxMax[i] = boxCenter[i] + boxSize[i] / 2.0f;
	}

	// �����̎n�_�E�I�_�E�����x�N�g����z��Ŏ擾
	float start[3] = { stLine.vecLineStart.x, stLine.vecLineStart.y, stLine.vecLineStart.z };
	float end[3] = { stLine.vecLineEnd.x,   stLine.vecLineEnd.y,   stLine.vecLineEnd.z };
	float dir[3] = { end[0] - start[0], end[1] - start[1], end[2] - start[2] };

	float tmin = 0.0f;
	float tmax = 1.0f;

	/* �ڐG���� */
	// �e�����ƂɃX���u�@�Ŕ���
	for (int i = 0; i < 3; ++i)
	{
		if (fabs(dir[i]) < 1e-6f)
		{
			if (start[i] < boxMin[i] || start[i] > boxMax[i])
			{
				return false;
			}
		}
		else
		{
			float ood = 1.0f / dir[i];
			float t1 = (boxMin[i] - start[i]) * ood;
			float t2 = (boxMax[i] - start[i]) * ood;
			if (t1 > t2)
			{
				std::swap(t1, t2);
			}
			tmin = std::max(tmin, t1);
			tmax = std::min(tmax, t2);
			if (tmin > tmax)
			{
				return false;
			}
		}
	}

	// tmin <= tmax �Ȃ����
	return true;
}

// �{�b�N�X - �{�b�N�X
bool Ground_Base::HitCheck(Struct_Collision::COLLISION_BOX stBox)
{
	// ����
	// stBox	: ���肷��{�b�N�X�R���W����
	// �߂�l
	// bool		: �ڐG���Ă���(true) / �ڐG���Ă��Ȃ�(false)

	/* ������s���������ł��邩 */
	if (std::abs(VSquareSize(VSub(stBox.vecBoxCenter, this->stBox.vecBoxCenter))) > COLLISION_CHECK_DISTANCE)
	{
		// ������s�������O�ł���ꍇ�͐ڐG���Ă��Ȃ��Ƃ݂Ȃ�
		return false;
	}

	// ���g�̃{�b�N�X�̍ŏ��E�ő���W���擾
	float afBox_Min_This[3] =
	{
		this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x,
		this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y,
		this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z
	};

	float afBox_Max_This[3] =
	{
		this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x,
		this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y,
		this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z
	};

	// ���肷��{�b�N�X�̍ŏ��E�ő���擾
	float afBox_Min[3] =
	{
		stBox.vecBoxCenter.x - stBox.vecBoxHalfSize.x,
		stBox.vecBoxCenter.y - stBox.vecBoxHalfSize.y,
		stBox.vecBoxCenter.z - stBox.vecBoxHalfSize.z
	};

	float afBox_Max[3] =
	{
		stBox.vecBoxCenter.x + stBox.vecBoxHalfSize.x,
		stBox.vecBoxCenter.y + stBox.vecBoxHalfSize.y,
		stBox.vecBoxCenter.z + stBox.vecBoxHalfSize.z
	};

	// �e���ŏd�Ȃ��Ă�������Ȃ��Ȃ�false��Ԃ�
	for (int i = 0; i < 3; ++i)
	{
		if (afBox_Max_This[i] < afBox_Min[i] || afBox_Min_This[i] > afBox_Max[i])
		{
			return false;
		}
	}

	// ���ׂĂ̎��ŏd�Ȃ肪�����true
	return true;
}

// �Փ˓_�擾
// ���� - �{�b�N�X
VECTOR Ground_Base::HitPosition(Struct_Collision::COLLISION_LINE stLine)
{
	// ����
	// stLine	: ���肷����R���W����
	// �߂�l
	// VECTOR	: �ڐG�������W(�ł�Start�ɋ߂��_) / �ڐG���Ă��Ȃ��ꍇ��End���W(�I�_)��Ԃ�

	// �{�b�N�X�̊e���̍ŏ��l�ƍő�l��z��Ŏ擾
	float boxCenter[3]	= { this->stBox.vecBoxCenter.x,		this->stBox.vecBoxCenter.y,		this->stBox.vecBoxCenter.z };
	float boxSize[3]	= { this->stBox.vecBoxHalfSize.x,	this->stBox.vecBoxHalfSize.y,	this->stBox.vecBoxHalfSize.z };
	float boxMin[3], boxMax[3];
	for (int i = 0; i < 3; ++i)
	{
		boxMin[i] = boxCenter[i] - boxSize[i] / 2.0f;
		boxMax[i] = boxCenter[i] + boxSize[i] / 2.0f;
	}

	// �����̎n�_�E�I�_�E�����x�N�g����z��Ŏ擾
	float start[3] = { stLine.vecLineStart.x, stLine.vecLineStart.y, stLine.vecLineStart.z };
	float end[3] = { stLine.vecLineEnd.x, stLine.vecLineEnd.y, stLine.vecLineEnd.z };
	float dir[3] = { end[0] - start[0], end[1] - start[1], end[2] - start[2] };

	float tmin = 0.0f;
	float tmax = 1.0f;

	// �X���u�@�Ō��������tmin�Z�o
	for (int i = 0; i < 3; ++i)
	{
		if (fabs(dir[i]) < 1e-6f)
		{
			if (start[i] < boxMin[i] || start[i] > boxMax[i])
			{
				// �������Ȃ�
				return stLine.vecLineStart;
			}
		}
		else
		{
			float ood = 1.0f / dir[i];
			float t1 = (boxMin[i] - start[i]) * ood;
			float t2 = (boxMax[i] - start[i]) * ood;
			if (t1 > t2)
			{
				std::swap(t1, t2);
			}
			tmin = std::max(tmin, t1);
			tmax = std::min(tmax, t2);
			if (tmin > tmax)
			{
				// �������Ȃ�
				return stLine.vecLineStart;
			}
		}
	}

	// tmin��0�`1�͈̔͂Ȃ��_����
	if (tmin >= 0.0f && tmin <= 1.0f)
	{
		VECTOR hitPos;
		hitPos.x = start[0] + dir[0] * tmin;
		hitPos.y = start[1] + dir[1] * tmin;
		hitPos.z = start[2] + dir[2] * tmin;
		return hitPos;
	}
	else
	{
		// �����͈͊O
		return stLine.vecLineStart;
	}
}
