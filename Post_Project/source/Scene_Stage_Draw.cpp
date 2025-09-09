/* �V�[��"�X�e�[�W"�̒�` */
// ���`�ʊ֘A�̊֐��̂�

/* �g�p����v�f�̃C���N���[�h */
// �w�b�_�t�@�C��
#include "Scene_Stage.h"
// �֘A�N���X
#include "DataList_Object.h"
#include "DataList_GameStatus.h"
// ���ʒ�`
#include "ConstantDefine.h"

// �`��
void Scene_Stage::Draw()
{
	/* �V���h�E�}�b�v�`�� */
	DrawSetup_ShadowMap();

	/* �X�e�[�W�`�� */
	DrawSetup_Stage();

	/* �X�e�[�W�摜��`�� */
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, this->iScreenHandle_Stage, FALSE);

	/* �J�����ݒ� */
	DrawSetup_CameraPosition();

	/* �V���h�E�}�b�v�`�� */
	TestDrawShadowMap(this->iScreenHandle_ShadowMap[0], 0, 0, 256, 256);
	TestDrawShadowMap(this->iScreenHandle_ShadowMap[1], 0, 256, 256, 512);
}

// �J�����ݒ�
void Scene_Stage::DrawSetup_CameraPosition()
{
	/* 3D��{�ݒ� */
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	/* �O���[�o���A���r�G���g���C�g�J���[��ԐF�ɐݒ� */
	// ���f�t�H���g�̍��F���ƈÂ�����̂ŐԐF�ɕύX
	SetGlobalAmbientLight(GetColorF(0.5f, 0.5f, 0.5f, 1.0f));

	/* �v���C���[���W���擾 */
	VECTOR vecPlayerPos = this->pDataList_GameStatus->GetPlayerPosition_WoldMap();

	///* �J�����̎�O�Ɖ��̃N���b�v������ݒ� */
	//// ���X�J�C�X�t�B�A���a(25000)����]�T���������������l�ɉ��ݒ�
	//SetCameraNearFar(INIT_CAMERA_NEAR, INIT_CAMERA_FAR);

	/* �J�����ݒ� */
	VECTOR vecCameraPosition	= VAdd(vecPlayerPos, VGet(0.f, 1000.f, -500.f));
	VECTOR vecCameraTarget		= VAdd(vecPlayerPos, VGet(0.f, 10.f, 0.f));
	SetCameraPositionAndTarget_UpVecY(vecCameraPosition, vecCameraTarget);

	///* 3D�T�E���h�̃��X�i�[�ʒu�ƃ��X�i�[�O���ʒu��ݒ� */
	//Set3DSoundListenerPosAndFrontPos_UpVecY(this->StageStatusList->vecGetCameraPosition(), this->StageStatusList->vecGetCameraTarget());
}

// �V���h�E�}�b�v�쐬
void Scene_Stage::DrawSetup_ShadowMap()
{
	/* �v���C���[���W���擾 */
	VECTOR vecPlayerPos = this->pDataList_GameStatus->GetPlayerPosition_WoldMap();

	/* �����x�Ɋ֌W�Ȃ��`�ʂ���悤�ݒ�@*/
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_ALWAYS);

	/* ���I�I�u�W�F�N�g�̃V���h�E�}�b�v */
	{
		/* ���C�g�����ݒ� */
		// �� ���C�g�̕����͐^���Ƃ���
		SetShadowMapLightDirection(this->iScreenHandle_ShadowMap[SHADOWMAP_ACTOR], VGet(0.f, -1.f, 0.f));

		/* �V���h�E�}�b�v�͈͎̔w�� */
		// �� �v���C���[���W�𒆐S�ɐݒ�
		SetShadowMapDrawArea(this->iScreenHandle_ShadowMap[SHADOWMAP_ACTOR],
			VAdd(vecPlayerPos, VGet(-SHADOW_ACTOR_MAP_SIZE_WIDE, -SHADOW_ACTOR_MAP_SIZE_HEIGHT, -SHADOW_ACTOR_MAP_SIZE_WIDE)),
			VAdd(vecPlayerPos, VGet(+SHADOW_ACTOR_MAP_SIZE_WIDE, +SHADOW_ACTOR_MAP_SIZE_HEIGHT, +SHADOW_ACTOR_MAP_SIZE_WIDE)));

		/* �V���h�E�}�b�v�`�ʊJ�n */
		ShadowMap_DrawSetup(this->iScreenHandle_ShadowMap[SHADOWMAP_ACTOR]);

		/* �S�Ă̓��I�I�u�W�F�N�g�̕`�� */
		this->pDataList_Object->Draw_Actor_Shadow();

		/* �V���h�E�}�b�v�`�ʏI�� */
		ShadowMap_DrawEnd();
	}

	/* ���I�I�u�W�F�N�g�̃V���h�E�}�b�v */
	{
		/* ���C�g�����ݒ� */
		// �� ���C�g�̕����͏������Ƃ���
		SetShadowMapLightDirection(this->iScreenHandle_ShadowMap[SHADOWMAP_GROUND], VNorm(VGet(0.f, -1.f, 1.f)));

		/* �V���h�E�}�b�v�͈͎̔w�� */
		// �� �v���C���[���W�𒆐S�ɐݒ�
		SetShadowMapDrawArea(this->iScreenHandle_ShadowMap[SHADOWMAP_GROUND],
			VAdd(vecPlayerPos, VGet(-SHADOW_GROUND_MAP_SIZE_WIDE, -SHADOW_GROUND_MAP_SIZE_HEIGHT, -SHADOW_GROUND_MAP_SIZE_WIDE)),
			VAdd(vecPlayerPos, VGet(+SHADOW_GROUND_MAP_SIZE_WIDE, +SHADOW_GROUND_MAP_SIZE_HEIGHT, +SHADOW_GROUND_MAP_SIZE_WIDE)));

		/* �V���h�E�}�b�v�`�ʊJ�n */
		ShadowMap_DrawSetup(this->iScreenHandle_ShadowMap[SHADOWMAP_GROUND]);

		/* �S�Ă̐ÓI�I�u�W�F�N�g�̕`�� */
		this->pDataList_Object->Draw_Ground_Shadow();

		/* �V���h�E�}�b�v�`�ʏI�� */
		ShadowMap_DrawEnd();
	}
}

// �X�e�[�W�̕`��
void Scene_Stage::DrawSetup_Stage()
{
	/* �X�e�[�W�`�ʊJ�n */
	SetDrawScreen(this->iScreenHandle_Stage);

	/* ��ʃN���A */
	ClearDrawScreen();

	/* �J�����ݒ� */
	DrawSetup_CameraPosition();

	/* �`�ʂɎg�p����V���h�E�}�b�v�̐ݒ� */
	SetUseShadowMap(0, this->iScreenHandle_ShadowMap[SHADOWMAP_ACTOR]);
	SetUseShadowMap(1, this->iScreenHandle_ShadowMap[SHADOWMAP_GROUND]);

	/* ������������`�ʂ��Ȃ��悤�ݒ� */
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_NOT_SEMITRANS_ONLY);

	/* �I�u�W�F�N�g�`��(����������������) */
	this->pDataList_Object->Draw_All();

	/* �`�ʂɎg�p����V���h�E�}�b�v�̐ݒ������ */
	SetUseShadowMap(0, -1);
	SetUseShadowMap(1, -1);

	/* �����������̂ݕ`�ʂ���悤�ɐݒ� */
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_SEMITRANS_ONLY);

	/* �I�u�W�F�N�g�`��(�����������̂�) */
	// �� �n�`��`�ʂ��Ă��܂��ƃV���h�E�}�b�v���K�p����Ȃ��Ȃ�̂ŕ`�ʂ��Ȃ�
	this->pDataList_Object->Draw_Actor();

	/* ���C����ʂւ̕`�ʂ��I�� */
	SetDrawScreen(DX_SCREEN_BACK);
}
