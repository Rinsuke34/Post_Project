/* �V�[��"�X�e�[�W"�̒�` */
// ���`�ʊ֘A�̊֐��̂�

/* �g�p����v�f�̃C���N���[�h */
// �w�b�_�t�@�C��
#include "Scene_Stage.h"
// �֘A�N���X
#include "DataList_Object.h"
#include "DataList_GameStatus.h"
#include "DataList_StageCreate.h"
// ���ʒ�`
#include "ConstantDefine.h"

// �`��
void Scene_Stage::Draw()
{
	/* �Q�[����ԊǗ��f�[�^���X�g���ǂݍ��܂�Ă��邩�m�F */
	if (this->pDataList_GameStatus != nullptr)
	{
		// �ǂݍ��܂�Ă���ꍇ
		/* �V���h�E�}�b�v�`�� */
		DrawSetup_ShadowMap();

		/* �X�e�[�W�`�� */
		DrawSetup_Stage();

		///* �V���h�E�}�b�v�`�� */
		//TestDrawShadowMap(this->iScreenHandle_ShadowMap[0], 0, 0, 256, 256);
		//TestDrawShadowMap(this->iScreenHandle_ShadowMap[1], 0, 256, 256, 512);
	}
	/* �X�e�[�W�N���G�C�g���Ǘ��f�[�^���X�g���ǂݍ��܂�Ă��邩�m�F */
	else if (this->pDataList_StageCreate != nullptr)
	{
		// �ǂݍ��܂�Ă���ꍇ
		DrawSetup_Stage_StageCreate();
	}

	/* �X�e�[�W�摜��`�� */
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, this->iScreenHandle_Stage, FALSE);

	/* �J�����ݒ� */
	DrawSetup_CameraPosition();
}

// �J�����ݒ�
void Scene_Stage::DrawSetup_CameraPosition()
{
	/* �J�������W */
	VECTOR vecCameraPosition	= VGet(0.f, 0.f, 0.f);
	VECTOR vecCameraTarget		= VGet(0.f, 0.f, 0.f);

	/* 3D��{�ݒ� */
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	/* �O���[�o���A���r�G���g���C�g�J���[��ԐF�ɐݒ� */
	// ���f�t�H���g�̍��F���ƈÂ�����̂ŐԐF�ɕύX
	SetGlobalAmbientLight(GetColorF(0.5f, 0.5f, 0.5f, 1.0f));

	/* �Q�[����ԊǗ��f�[�^���X�g���ǂݍ��܂�Ă��邩�m�F */
	if (this->pDataList_GameStatus != nullptr)
	{
		// �ǂݍ��܂�Ă���ꍇ
		/* �v���C���[���W����J�����ݒ�����{ */
		VECTOR vecPlayerPos = this->pDataList_GameStatus->GetPlayerPosition_WoldMap();

		/* �J�����ݒ� */
		vecCameraTarget		= VAdd(vecPlayerPos,	VGet(0.f, 10.f, 0.f));
		vecCameraPosition	= VAdd(vecCameraTarget, VGet(0.f, 1000.f, -500.f));
	}
	/* �X�e�[�W�N���G�C�g���Ǘ��f�[�^���X�g���ǂݍ��܂�Ă��邩�m�F */
	else if (this->pDataList_StageCreate != nullptr)
	{
		// �ǂݍ��܂�Ă���ꍇ
		/* �I�𒆂̍��W����J�����̍��W���Z�o */
		vecCameraTarget.x = this->pDataList_StageCreate->vecGetSelectPos().x * MAP_BLOCK_SIZE_X + (MAP_BLOCK_SIZE_X / 2);
		vecCameraTarget.y = this->pDataList_StageCreate->vecGetSelectPos().y * MAP_BLOCK_SIZE_Y + (MAP_BLOCK_SIZE_Y / 2);
		vecCameraTarget.z = this->pDataList_StageCreate->vecGetSelectPos().z * MAP_BLOCK_SIZE_Z + (MAP_BLOCK_SIZE_Z / 2);
		vecCameraPosition = VAdd(vecCameraTarget, VGet(0.f, 1000.f, -500.f));
	}
	
	/* �J�����ݒ� */
	SetCameraPositionAndTarget_UpVecY(vecCameraPosition, vecCameraTarget);
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

// �X�e�[�W�̕`��(�X�e�[�W�N���G�C�g�p)
void Scene_Stage::DrawSetup_Stage_StageCreate()
{
	/* �X�e�[�W�`�ʊJ�n */
	SetDrawScreen(this->iScreenHandle_Stage);

	/* ��ʃN���A */
	ClearDrawScreen();

	/* �J�����ݒ� */
	DrawSetup_CameraPosition();

	/* �S�Ă̒n�`�I�u�W�F�N�g�̕`�� */
	this->pDataList_StageCreate->Draw_GroundObject();

	VECTOR_INT	vecSelectPos		= this->pDataList_StageCreate->vecGetSelectPos();
	/* �|�W�V���������[���h���W�ɕϊ� */
	VECTOR vecPosition;
	vecPosition.x = vecSelectPos.x * MAP_BLOCK_SIZE_X + (MAP_BLOCK_SIZE_X / 2);
	vecPosition.y = vecSelectPos.y * MAP_BLOCK_SIZE_Y + (MAP_BLOCK_SIZE_Y / 2);
	vecPosition.z = vecSelectPos.z * MAP_BLOCK_SIZE_Z + (MAP_BLOCK_SIZE_Z / 2);

	VECTOR		vecMapTileHarfSize	= VGet(MAP_BLOCK_SIZE_X / 2, MAP_BLOCK_SIZE_Y / 2, MAP_BLOCK_SIZE_Z / 2);

	/* �I�𒆂̍��W��`�� */
	// ���_��ݒ�
	VECTOR aVertex[8];
	aVertex[0] = VGet(vecPosition.x + vecMapTileHarfSize.x, vecPosition.y + vecMapTileHarfSize.y, vecPosition.z + vecMapTileHarfSize.z);
	aVertex[1] = VGet(vecPosition.x + vecMapTileHarfSize.x, vecPosition.y + vecMapTileHarfSize.y, vecPosition.z - vecMapTileHarfSize.z);
	aVertex[2] = VGet(vecPosition.x + vecMapTileHarfSize.x, vecPosition.y - vecMapTileHarfSize.y, vecPosition.z + vecMapTileHarfSize.z);
	aVertex[3] = VGet(vecPosition.x + vecMapTileHarfSize.x, vecPosition.y - vecMapTileHarfSize.y, vecPosition.z - vecMapTileHarfSize.z);
	aVertex[4] = VGet(vecPosition.x - vecMapTileHarfSize.x, vecPosition.y + vecMapTileHarfSize.y, vecPosition.z + vecMapTileHarfSize.z);
	aVertex[5] = VGet(vecPosition.x - vecMapTileHarfSize.x, vecPosition.y + vecMapTileHarfSize.y, vecPosition.z - vecMapTileHarfSize.z);
	aVertex[6] = VGet(vecPosition.x - vecMapTileHarfSize.x, vecPosition.y - vecMapTileHarfSize.y, vecPosition.z + vecMapTileHarfSize.z);
	aVertex[7] = VGet(vecPosition.x - vecMapTileHarfSize.x, vecPosition.y - vecMapTileHarfSize.y, vecPosition.z - vecMapTileHarfSize.z);

	// ������`��
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
	

	/* ���C����ʂւ̕`�ʂ��I�� */
	SetDrawScreen(DX_SCREEN_BACK);
}
