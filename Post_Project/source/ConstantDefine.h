/* �v���W�F�N�g�Ŏg�p����萔�̐錾 */

#pragma once

/* �}�b�v�n */
// �u���b�N�T�C�Y
static const float MAP_BLOCK_SIZE_X = 64.f;		// X���̃}�b�v�^�C���̑傫��
static const float MAP_BLOCK_SIZE_Y = 32.f;		// Y���̃}�b�v�^�C���̑傫��
static const float MAP_BLOCK_SIZE_Z = 64.f;		// Z���̃}�b�v�^�C���̑傫��
// �G���A�T�C�Y
static const int AREA_SIZE_BLOCK_X = 64;	// X���̃G���A�̑傫��(�u���b�N���P��)
static const int AREA_SIZE_BLOCK_Y = 8;		// X���̃G���A�̑傫��(�u���b�N���P��)
static const int AREA_SIZE_BLOCK_Z = 64;	// X���̃G���A�̑傫��(�u���b�N���P��)
// �G���A���
// ���G���A��9�ō\�������(���S�G���A+����8�G���A)
// �G���A0 | �G���A1 | �G���A2
// �G���A3 | �G���A4 | �G���A5
// �G���A6 | �G���A7 | �G���A8
static const int AREA_NO_MAX	= 9;	// �G���A��
static const int AREA_NO_CENTER	= 4;	// ���S�G���A�̃C���f�b�N�X
// �e�G���A�̌��_
static const VECTOR AREA_ORIGIN_POS[AREA_NO_MAX] =
{
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 0.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 0.f},
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 1.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 0.f},
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 2.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 0.f},
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 0.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 1.f},
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 1.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 1.f},
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 2.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 1.f},
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 0.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 2.f},
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 1.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 2.f},
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 2.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 2.f}
};
// ���[���h�}�b�v�̎��
static const int WOLD_MAP_TYPE_CENTER	= 0;	// ���S�G���A
static const int WOLD_MAP_TYPE_SIDE		= 1;	// �T�C�h�G���A

/* �����蔻��n */
static float COLLISION_CHECK_DISTANCE			= 40000.f;	// �����蔻����s����������(���e���_�̓��̋�����������傫���Ȃ��ڐG�Ɣ��肷��)
static float COLLISION_CHECK_CEILING_PREVENTION = 20.f;		// �V�䂷��ʂ��h�~�p�̕␳�l
static float COLLISION_CHECK_FLOOR_MARGIN		= -20.f;	// �������ւ̈ړ����ɏ��ɑ΂���딻��h�~�p�̕␳�l
static float COLLISION_PUSH_MAX_LOOP			= 10;		// �����o������̍ő僋�[�v��(�������[�v�΍�)

/* �`�ʌn */
// �V���h�E�}�b�v�֘A
static const int SHADOW_GROUND_MAP_SIZE_WIDE	= 4096;		// �ÓI�I�u�W�F�N�g�̃V���h�E�}�b�v�̉���
static const int SHADOW_GROUND_MAP_SIZE_HEIGHT	= 4096;		// �ÓI�I�u�W�F�N�g�̃V���h�E�}�b�v�̏c��
static const int SHADOW_ACTOR_MAP_SIZE_WIDE		= 2048;		// ���I�I�u�W�F�N�g�̃V���h�E�}�b�v�̉���
static const int SHADOW_ACTOR_MAP_SIZE_HEIGHT	= 2048;		// ���I�I�u�W�F�N�g�̃V���h�E�}�b�v�̏c��
// 2D�A�j���[�V�����p�摜�֘A
static const int CHARACTER_PARTS_ANIM_DRAW_SIZE_WIDE	= 256;	// �L�����N�^�[�̃p�[�c�A�j���[�V�����p�摜�̉���
static const int CHARACTER_PARTS_ANIM_DRAW_SIZE_HEIGHT	= 256;	// �L�����N�^�[�̃p�[�c�A�j���[�V�����p�摜�̏c��
// �����낵���_�ł̂̂������
static const float TOPVIEW_LEAN_AMOUNT			= 150.f;	// �����낵���_�ł̂̂������
