/* �L�����N�^�[�̃x�[�X�N���X�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �w�b�_�t�@�C��
#include "Character_Base.h"
// ���ʒ�`
#include "ConstantDefine.h"

// �R���X�g���N�^
Character_Base::Character_Base() : Actor_Base()
{
	/* ������ */
	// �X�e�[�^�X�n
	this->iHealth			= 0;		// �̗�
	this->iMaxHealth		= 0;		// �ő�̗�
	this->iSpeed			= 0;		// ���x
	// ��Ԍn
	this->bDeadFlg			= false;	// ���S�t���O
	this->iInvincibleTime	= 0;		// �c�薳�G����(�t���[����)
	// �R���W����
	this->stBox.vecBoxCenter	= VGet(0.0f, 0.0f, 0.0f);
	this->stBox.vecBoxHalfSize	= VGet(1.0f, 1.0f, 1.0f);
}

// �X�V
// �� ����W�̍X�V���������Ă�����s���邱��
void Character_Base::Update()
{
	/* HP���c���Ă��邩�m�F */
	if (this->iHealth <= 0)
	{
		// HP��0�ȉ��Ȃ玀�S�t���O�𗧂Ă�
		this->bDeadFlg = true;
	}

	/* ���G���Ԃ̍X�V */
	if (this->iInvincibleTime > 0)
	{
		--this->iInvincibleTime;
	}

	/* �R���W�����̍X�V */
	Update_Collision();
}

// �`��(�V���h�E�}�b�v�p)
void Character_Base::Draw_Shadow()
{
	/* �R���W�����̒��S���W�Ɣ��a���狅�̂��쐬���A�e�Ƃ��� */
	DrawSphere3D(this->stBox.vecBoxCenter, this->stBox.vecBoxHalfSize.x, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
}

// �R���W�����`��(�f�o�b�O�p)
void Character_Base::Draw_Collision()
{
	/* ���_��ݒ� */
	VECTOR aVertex[8];
	aVertex[0] = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[1] = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);
	aVertex[2] = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[3] = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);
	aVertex[4] = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[5] = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);
	aVertex[6] = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[7] = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);

	/* ������`�� */
	DrawLine3D(aVertex[0], aVertex[1], GetColor(255, 255, 255));
	DrawLine3D(aVertex[1], aVertex[5], GetColor(255, 255, 255));
	DrawLine3D(aVertex[5], aVertex[4], GetColor(255, 255, 255));
	DrawLine3D(aVertex[4], aVertex[0], GetColor(255, 255, 255));
	DrawLine3D(aVertex[2], aVertex[3], GetColor(255, 255, 255));
	DrawLine3D(aVertex[3], aVertex[7], GetColor(255, 255, 255));
	DrawLine3D(aVertex[7], aVertex[6], GetColor(255, 255, 255));
	DrawLine3D(aVertex[6], aVertex[2], GetColor(255, 255, 255));
	DrawLine3D(aVertex[0], aVertex[2], GetColor(255, 255, 255));
	DrawLine3D(aVertex[1], aVertex[3], GetColor(255, 255, 255));
	DrawLine3D(aVertex[4], aVertex[6], GetColor(255, 255, 255));
	DrawLine3D(aVertex[5], aVertex[7], GetColor(255, 255, 255));
}

// �R���W�����X�V
void Character_Base::Update_Collision()
{
	/* �R���W�����̒��S���W���X�V */
	// �� ���݂̊���W����R���W�����̒��S���W��ݒ�
	this->stBox.vecBoxCenter = VAdd(this->vecBasePosition, VGet(0.f, this->stBox.vecBoxHalfSize.y, 0.f));
}
