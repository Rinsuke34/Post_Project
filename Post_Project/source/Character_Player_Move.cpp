/* �v���C���[�N���X�̒�` */
// �� �ړ������̂�

/* �g�p����v�f�̃C���N���[�h */
// �W�����C�u����
#define NOMINMAX
#include <algorithm>
// �w�b�_�t�@�C��
#include "Character_Player.h"
// �֘A�N���X
#include "DataList_Object.h"
#include "Ground_Base.h"
// ���ʒ�`
#include "Test_ConstantDefine.h"

// �d�͏���
void Character_Player::Update_ApplyGravity()
{
	// �e�X�g
	this->fGravityAcceleration = TEST_GRAVITY_ACCELERATION;	// �d�͉����x(���ݒ�)

	/* �W�����v���� */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_SPACE] == TRUE)
	{
		this->fGravityVelocity = TEST_JUMP_GRAVITY_VELOCITY;
	}

	/* �d�͉����x�����Z */
	this->fGravityVelocity -= this->fGravityAcceleration;
	 
	/* �ړ��O�̊���W��ۑ� */
	VECTOR vecPrevPosition	= this->vecBasePosition;

	/* �ړ���̊���W���Z�o */
	VECTOR vecMovePosition = VAdd(vecPrevPosition, VGet(0.f, this->fGravityVelocity, 0.f));

	/* �ړ���̍��W�ƈړ��O�̍��W����{�b�N�X�R���W�������쐬 */
	// �� ���S�_�𕽋ϒl�A�傫���͍�����(�ړ��� + ���a)�ɂ����2�_��ʂ�{�b�N�X�ɂȂ�̂ł������ɃR���W����������
	// �� �������ɂ͏����]�T����������(�ǂɐڐG������ԂŃW�����v���ł���悤�ɂ��邽��)
	Struct_Collision::COLLISION_BOX stMoveBox;
	stMoveBox.vecBoxCenter		= VGet(this->vecBasePosition.x, (vecMovePosition.y + this->vecBasePosition.y) / 2.f, this->vecBasePosition.z);
	stMoveBox.vecBoxHalfSize	= VGet(this->stBox.vecBoxHalfSize.x - COLLISION_CHECK_CEILING_PREVENTION, (fabsf(vecMovePosition.y - this->vecBasePosition.y) / 2) + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxHalfSize.z - COLLISION_CHECK_CEILING_PREVENTION);

	// �㏸���A���~�����ꂼ��̕␳
	if (this->fGravityVelocity > 0)
	{
		// �㏸��
		// �{�b�N�X�R���W�����̉������𔻒肵�Ȃ��悤�ɂ���(�W�����v����ɒ��n���肪�o�Ă��܂����΍�)
		stMoveBox.vecBoxCenter.y	+= COLLISION_CHECK_CEILING_PREVENTION / 2.f;
		stMoveBox.vecBoxHalfSize.y	-= COLLISION_CHECK_CEILING_PREVENTION;
	}
	else
	{
		// ���~��
		// �{�b�N�X�R���W�����̏㕔���𔻒肵�Ȃ��悤�ɂ���(�V��ɑ΂��Ē��n���肪�o�Ă��܂����΍�)
		stMoveBox.vecBoxCenter.y	-= COLLISION_CHECK_CEILING_PREVENTION / 2.f;
		stMoveBox.vecBoxHalfSize.y	-= COLLISION_CHECK_CEILING_PREVENTION;
	}

	/* �n�`�Ƃ̐ڒn���� */
	// �� �y�ʉ��̂��ߌ��݂̃G���A�̑���̂݊m�F
	// �� �G���A�O�̏ꍇ�͑���Ƃ̓����蔻����s��Ȃ�
	bool bGroundHit = false;	// �n�ʂɐڒn���Ă��邩
	int iAreaNo		= iCheckCurrentAreaNo();
	if (iAreaNo != -1)
	{
		for (auto& Ground : this->pDataList_Object->GetGroundList(iAreaNo))
		{
			/* �ڐG���Ă��邩�m�F */
			if (Ground->HitCheck(stMoveBox))
			{
				// �ڐG���Ă���ꍇ
				/* �ڒn���Ă���Ƃ݂Ȃ� */
				bGroundHit = true;

				/* �Ώۂ̃I�u�W�F�N�g�̃R���W���������擾 */
				Struct_Collision::COLLISION_BOX stGroundBoxCollision;

				stGroundBoxCollision = Ground->GetBoxCollision();

				/* �v���C���[���㏸���ł��邩���~���ł��邩���� */
				// �� �㏸���̏ꍇ�͉������ɉ����o���A���~���̏ꍇ�͏�����ɉ����o��
				if (this->fGravityVelocity > 0)
				{
					// �㏸��(�������։����o��)
					vecMovePosition.y = stGroundBoxCollision.vecBoxCenter.y - stGroundBoxCollision.vecBoxHalfSize.y;
				}
				else
				{
					// ���~��(������։����o��)
					vecMovePosition.y = stGroundBoxCollision.vecBoxCenter.y + stGroundBoxCollision.vecBoxHalfSize.y;
				}
				break;
			}
		}
	}

	/* �ڒn���Ă��邩�m�F */
	if (bGroundHit == true)
	{
		// �ڒn���Ă���ꍇ
		/* ����W���ړ���̍��W�ɐݒ� */
		this->vecBasePosition = vecMovePosition;

		/* �������x�����Z�b�g */
 		this->fGravityVelocity = 0.f;
	}
	else
	{
		// �ڒn���Ă��Ȃ��ꍇ
		/* ����W���ړ���̍��W�ɐݒ� */
		this->vecBasePosition = vecMovePosition;
	}
}

// �ړ�����
void Character_Player::Update_ApplyMovement()
{
	/* �ړ��O�̍��W��ۑ� */
	VECTOR vecPrevPosition	= this->vecBasePosition;

	/* �ړ��������擾 */
	VECTOR vecMoveDirection = VGet(0.f, 0.f, 0.f);
	// ���͂���ړ��������擾
	bool bIsMoving = false;
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_W] == TRUE)
	{
		vecMoveDirection = VAdd(vecMoveDirection, VGet(0.f, 0.f, 1.f));
		bIsMoving = true;
	}
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_S] == TRUE)
	{
		vecMoveDirection = VAdd(vecMoveDirection, VGet(0.f, 0.f, -1.f));
		bIsMoving = true;
	}
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_A] == TRUE)
	{
		vecMoveDirection = VAdd(vecMoveDirection, VGet(-1.f, 0.f, 0.f));
		bIsMoving = true;
	}
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_D] == TRUE)
	{
		vecMoveDirection = VAdd(vecMoveDirection, VGet(1.f, 0.f, 0.f));
		bIsMoving = true;
	}

	// �ړ����Ă��Ȃ��ꍇ�͏����𔲂���
	if (!bIsMoving)
	{
		return;
	}

	/* �ړ����Ă���ꍇ�̏��� */
	// ���K�������x���f
	vecMoveDirection = VScale(VNorm(vecMoveDirection), static_cast<float>(this->iSpeed));

	/* �ړ���̊���W���Z�o */
	VECTOR vecMovePosition = VAdd(vecPrevPosition, vecMoveDirection);

	/* �ړ�����W�̃R���W�����쐬 */
	// �� �c�����ɂ͏����]�T����������(�n�`�̉��ʂɈ���������Ȃ��悤�ɂ��邽��)
	Struct_Collision::COLLISION_BOX stMoveBox;
	stMoveBox.vecBoxCenter		= VAdd(vecMovePosition, VGet(0.f, this->stBox.vecBoxHalfSize.y, 0.f));
	stMoveBox.vecBoxHalfSize	= this->stBox.vecBoxHalfSize;
	stMoveBox.vecBoxHalfSize.y += COLLISION_CHECK_FLOOR_MARGIN;

	/* �n�`�Ƃ̐ڒn���� */
	// �� �y�ʉ��̂��ߌ��݂̃G���A�̑���̂݊m�F
	// �� �G���A�O�̏ꍇ�͑���Ƃ̓����蔻����s��Ȃ�
	int iAreaNo = iCheckCurrentAreaNo();
	if (iAreaNo != -1)
	{
		/* �ڐG�����S�Ă̒n�`���L�^ */
		std::vector<Struct_Collision::COLLISION_BOX> hitGroundBoxes;
		for (auto& Ground : this->pDataList_Object->GetGroundList(iAreaNo))
		{
			/* �ڐG���Ă��邩�m�F */
			if (Ground->HitCheck(stMoveBox))
			{
				// �ڐG���Ă���ꍇ
				/* �ڐG�����n�`�̃R���W��������ۑ� */
				hitGroundBoxes.push_back(Ground->GetBoxCollision());
			}
		}

		/* �����o������������܂Ŕ�����J��Ԃ� */
		int		iLoopCount = 0;	// ���[�v��
		bool	bPushed;	// �����o��������������
		do
		{
			bPushed = false;
			for (const auto& stGroundBox : hitGroundBoxes)
			{
				/* �e���̍ŏ��E�ő���W���v�Z */
				float playerMinX = vecMovePosition.x - stMoveBox.vecBoxHalfSize.x;
				float playerMaxX = vecMovePosition.x + stMoveBox.vecBoxHalfSize.x;
				float playerMinZ = vecMovePosition.z - stMoveBox.vecBoxHalfSize.z;
				float playerMaxZ = vecMovePosition.z + stMoveBox.vecBoxHalfSize.z;

				float groundMinX = stGroundBox.vecBoxCenter.x - stGroundBox.vecBoxHalfSize.x;
				float groundMaxX = stGroundBox.vecBoxCenter.x + stGroundBox.vecBoxHalfSize.x;
				float groundMinZ = stGroundBox.vecBoxCenter.z - stGroundBox.vecBoxHalfSize.z;
				float groundMaxZ = stGroundBox.vecBoxCenter.z + stGroundBox.vecBoxHalfSize.z;

				// X���̏d�Ȃ��
				float overlapX = std::min(playerMaxX, groundMaxX) - std::max(playerMinX, groundMinX);
				// Z���̏d�Ȃ��
				float overlapZ = std::min(playerMaxZ, groundMaxZ) - std::max(playerMinZ, groundMinZ);

				// �ڐG���Ă��Ȃ���΃X�L�b�v
				if (overlapX <= 0.f || overlapZ <= 0.f) continue;

				// �ŏ��̏d�Ȃ�����ɉ����o��
				if (overlapX < overlapZ)
				{
					// X�������ɉ����o��
					if (vecPrevPosition.x < stGroundBox.vecBoxCenter.x)
					{
						vecMovePosition.x = groundMinX - stMoveBox.vecBoxHalfSize.x;
					}
					else
					{
						vecMovePosition.x = groundMaxX + stMoveBox.vecBoxHalfSize.x;
					}
				}
				else
				{
					// Z�������ɉ����o��
					if (vecPrevPosition.z < stGroundBox.vecBoxCenter.z)
					{
						vecMovePosition.z = groundMinZ - stMoveBox.vecBoxHalfSize.z;
					}
					else
					{
						vecMovePosition.z = groundMaxZ + stMoveBox.vecBoxHalfSize.z;
					}
				}
				// �����o�������������̂ōĔ���
				stMoveBox.vecBoxCenter = VAdd(vecMovePosition, VGet(0.f, this->stBox.vecBoxHalfSize.y, 0.f));
				bPushed = true;
			}

			/* �������[�v�h�~���� */
			iLoopCount++;
			if (iLoopCount > COLLISION_PUSH_MAX_LOOP)
			{
				// �ő僋�[�v�񐔂𒴂����ꍇ�͋����I��
				/* ���̍��W�ɖ߂� */
				vecMovePosition = vecPrevPosition;
				break;
			}
		} while (bPushed);
	}

	// �����o����̍��W������W�ɔ��f
	this->vecBasePosition = vecMovePosition;
}