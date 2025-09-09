/* �A�N�^�̃x�[�X�N���X�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �w�b�_�t�@�C��
#include "Actor_Base.h"
// �֘A�N���X
#include "DataList_Object.h"
#include "Ground_Base.h"

// �R���X�g���N�^
Actor_Base::Actor_Base() : Object_Base()
{
	/* �f�[�^���X�g�擾 */
	this->pDataList_Object = std::dynamic_pointer_cast<DataList_Object>(gpDataListServer->GetDataList("DataList_Object"));			// �I�u�W�F�N�g�Ǘ�

	/* ������ */
	this->vecBasePosition		= VGet(0.0f, 0.0f, 0.0f);
	this->bEnableGravityFlg		= false;	// �d�͗L���t���O
	this->fGravityVelocity		= 0.f;		// �d�͂ɂ�闎�����x
	this->fGravityAcceleration	= 0.f;		// �d�͉����x
}

// �X�V
void Actor_Base::Update()
{
	/* �d�͏��� */
	if (this->bEnableGravityFlg)
	{
		Update_ApplyGravity_Simple();
	}
}

// �`�[���^�O�̊m�F
bool Actor_Base::bCheckTeamTag(std::string TeamTag)
{
	// ����
	// TeamTag	: �`�[���^�O��
	// �߂�l
	// bool		: ���̃`�[���^�O���������Ă���(true) / �������Ă��Ȃ�(false)

	return (std::find(this->TeamTag.begin(), this->TeamTag.end(), TeamTag) != this->TeamTag.end());
}

// ���݂̃G���A�ԍ����擾
int Actor_Base::iCheckCurrentAreaNo()
{
	// �߂�l
	// int	: ���݂̃G���A�ԍ�(���݂��Ȃ��ꍇ��-1)

	int col = static_cast<int>(this->vecBasePosition.x / (AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X));
	int row = static_cast<int>(this->vecBasePosition.z / (AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z));

	if (col < 0 || col > 2 || row < 0 || row > 2)
	{
		// �G���A�O
		return -1;
	}
	else
	{
		return col + row * 3;
	}
}


// �d�͏���(�Ȉ�)
// �� ����W�Əd�͂ɂ�闎�����x�݂̂��l�������ȈՓI�ȏ���
void Actor_Base::Update_ApplyGravity_Simple()
{
	/* �ړ��O�̍��W��ۑ� */
	VECTOR vecBasePosition = this->vecBasePosition;

	/* �d�͂ɂ�闎�����x�ƈړ���̍��W���Z�o */
	this->fGravityVelocity	+=	this->fGravityAcceleration;
	VECTOR vecNextPosition	=	VAdd(this->vecBasePosition, VGet(0.f, this->fGravityVelocity, 0.f));

	/* �ړ��O�ƈړ���̍��W����R���W�������쐬 */
	Struct_Collision::COLLISION_LINE stMovementLine;
	stMovementLine.vecLineStart	= vecBasePosition;
	stMovementLine.vecLineEnd	= vecNextPosition;

	/* ����Ƃ̓����蔻�菈�� */
	// �� �y�ʉ��̂��ߌ��݂̃G���A�̑���̂݊m�F
	// �� �G���A�O�̏ꍇ�͑���Ƃ̓����蔻����s��Ȃ�
	int iAreaNo = iCheckCurrentAreaNo();
	if (iAreaNo != -1)
	{
		for (auto& Ground : this->pDataList_Object->GetGroundList(iAreaNo))
		{
			// ����̃R���W�����ƐڐG���Ă��邩�m�F
			if (Ground->HitCheck(stMovementLine))
			{
				// �ڐG���Ă���ꍇ
				/* �Փ˓_���擾 */
				VECTOR vecHitPosition = Ground->HitPosition(stMovementLine);

				// �Փ˓_���ړ��O���W�ɂ��߂��ꍇ�݈̂ړ���̍��W���X�V
				float fDistCurrent = VSize(VSub(vecNextPosition, vecBasePosition));
				float fDistHit = VSize(VSub(vecHitPosition, vecBasePosition));
				if (fDistHit < fDistCurrent)
				{
					vecNextPosition = vecHitPosition;
				}

				/* �������x���X�V */
				this->fGravityVelocity = 0.f;
			}
		}
	}

	/* ����W���X�V */
	this->vecBasePosition = vecNextPosition;
}