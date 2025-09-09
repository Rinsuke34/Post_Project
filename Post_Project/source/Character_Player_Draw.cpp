/* �v���C���[�N���X�̒�` */
// �� �`�ʕ����̂�

/* �g�p����v�f�̃C���N���[�h */
// �w�b�_�t�@�C��
#include "Character_Player.h"
// �֘A�N���X
#include "DataList_Object.h"
#include "Ground_Base.h"
// ���ʒ�`
#include "Test_ConstantDefine.h"
#include "ConstantDefine.h"

// �`��
void Character_Player::Draw()
{
	/* �A�j���[�V�����`�� */
	Draw_Animation();

	/* �ȉ��A�e�X�g�`�� */
	Draw_Collision();

	DrawLine3D(VAdd(this->vecBasePosition, VGet(100.f, 0.f, 0.f)), VAdd(this->vecBasePosition, VGet(-100.f, 0.f, 0.f)), GetColor(255, 0, 0));
	DrawLine3D(VAdd(this->vecBasePosition, VGet(0.f, 100.f, 0.f)), VAdd(this->vecBasePosition, VGet(0.f, -100.f, 0.f)), GetColor(0, 255, 0));
	DrawLine3D(VAdd(this->vecBasePosition, VGet(0.f, 0.f, 100.f)), VAdd(this->vecBasePosition, VGet(0.f, 0.f, -100.f)), GetColor(0, 0, 255));

	DrawTriangle3D(VAdd(this->vecBasePosition, VGet(0.f, 0.f, 0.f)), VAdd(this->vecBasePosition, VGet(50.f, 0.f, 0.f)), VAdd(this->vecBasePosition, VGet(0.f, 50.f, 0.f)), GetColor(255, 255, 0), TRUE);
}

// �A�j���[�V�����`��
void Character_Player::Draw_Animation()
{
	/* ���S���W����Ƃ����A�j���[�V������`�ʂ���p�l���̒��_���W���v�Z */
	float fHalfWide		= CHARACTER_PARTS_ANIM_DRAW_SIZE_WIDE / 2;
	float fHeight		= CHARACTER_PARTS_ANIM_DRAW_SIZE_HEIGHT;
	// �����`���ێ����邽�߂�Y+����Y���W�␳
	float fYLean		= sqrtf(fHeight * fHeight - TOPVIEW_LEAN_AMOUNT * TOPVIEW_LEAN_AMOUNT);

	VERTEX3D aVertex[4];
	aVertex[0].pos = VGet(this->vecBasePosition.x + fHalfWide, this->vecBasePosition.y + fYLean,	this->vecBasePosition.z + TOPVIEW_LEAN_AMOUNT);
	aVertex[1].pos = VGet(this->vecBasePosition.x + fHalfWide, this->vecBasePosition.y,				this->vecBasePosition.z);
	aVertex[2].pos = VGet(this->vecBasePosition.x - fHalfWide, this->vecBasePosition.y + fYLean,	this->vecBasePosition.z + TOPVIEW_LEAN_AMOUNT);
	aVertex[3].pos = VGet(this->vecBasePosition.x - fHalfWide, this->vecBasePosition.y,				this->vecBasePosition.z);

	// ���_�̏�����
	for (int i = 0; i < 4; ++i)
	{
		aVertex[i].dif = GetColorU8(255, 255, 255, 255);
		aVertex[i].spc = GetColorU8(0, 0, 0, 0);
		aVertex[i].su = 0.f;
		aVertex[i].sv = 0.f;
	}

	/* �e�ʂ̕`�� */
	// �C���f�b�N�X�f�[�^�i���ʂ�2�|���S���j
	unsigned short IndexBack[6] = { 3, 2, 1, 1, 2, 0 };

	// �@���x�N�g����ݒ�
	for (int i = 0; i < 4; ++i)
	{
		aVertex[i].norm = VGet(0.0f, 0.0f, -1.0f);
	}

	// uv���W��ݒ�
	// �E��
	aVertex[0].u = 1.f;
	aVertex[0].v = 0.f;
	// �E��
	aVertex[1].u = 1.f;
	aVertex[1].v = 1.f;
	// ����
	aVertex[2].u = 0.f;
	aVertex[2].v = 0.f;
	// ����
	aVertex[3].u = 0.f;
	aVertex[3].v = 1.f;

	// �l�p�`�i�|���S���j�̕`��
	DrawPolygonIndexed3D(aVertex, 8, IndexBack, 2, this->iScreenHandle_Animation, TRUE);
//	DrawPolygonIndexed3D(aVertex, 8, IndexBack, 2, this->iTestCg, TRUE);
}

// �A�j���[�V�����X�V
void Character_Player::Update_Animation()
{
	/* �A�j���[�V�����`�ʊJ�n */
	SetDrawScreen(this->iScreenHandle_Animation);

	/* ��ʃN���A */
	ClearDrawScreen();

	/* ��ʃT�C�Y��ݒ� */
	this->pDataList_2DPartsAnimCreateTool->SetDrawScreenSize(CHARACTER_PARTS_ANIM_DRAW_SIZE_WIDE, CHARACTER_PARTS_ANIM_DRAW_SIZE_HEIGHT);

	/* ���݃��[�V�����̃p�[�c�A�j���[�V�����̕`�� */
	this->pDataList_2DPartsAnimCreateTool->DrawPartsAnim(this->AnimFileName, this->NowMotionName, this->iMotionCount);

	/* �A�j���[�V�����`�ʏI�� */
	SetDrawScreen(DX_SCREEN_BACK);

	/* ���[�V�����J�E���g��i�߂� */
	++this->iMotionCount;

	/* ���݂̃��[�V�����̍ő�J�E���g�𒴂��Ă��邩�m�F */
	if (this->iMotionCount >= this->pDataList_2DPartsAnimCreateTool->iGetPartsAnimMaxTime(this->AnimFileName, this->NowMotionName))
	{
		// �����Ă���ꍇ
		/* ���[�V�����J�E���g�����Z�b�g */
		this->iMotionCount = 0;
	}
}
