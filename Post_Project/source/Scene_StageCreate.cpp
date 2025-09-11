/* �V�[��"�X�e�[�W�쐬"�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �w�b�_�t�@�C��
#include "Scene_StageCreate.h"
// �֘A�N���X
// �֘A�N���X
#include "Scene_Stage.h"
#include "DataList_Object.h"
#include "DataList_StageCreate.h"

// �R���X�g���N�^
Scene_StageCreate::Scene_StageCreate() : Scene_Base("Scene_StageCreate", 100, false, false)
{
	/* �f�[�^���X�g�쐬 */
	gpDataListServer->AddDataList(std::make_shared<DataList_Object>());			// �I�u�W�F�N�g�Ǘ�
	gpDataListServer->AddDataList(std::make_shared<DataList_StageCreate>());	// �X�e�[�W�N���G�C�g���Ǘ�

	/* �f�[�^���X�g�擾 */
	this->pDataList_StageCreate	= std::dynamic_pointer_cast<DataList_StageCreate>(gpDataListServer->GetDataList("DataList_StageCreate"));	// �X�e�[�W�N���G�C�g���Ǘ�

	/* ������ */
	this->iNowPhase			= PHASE_SELECT_MAP;	// �}�b�v�I���t�F�[�Y����J�n
	this->iSelectMapIndex	= 0;				// �I�𒆂̃}�b�v�̃C���f�b�N�X�ԍ�
}

// �f�X�g���N�^
Scene_StageCreate::~Scene_StageCreate()
{
	/* �f�[�^���X�g�폜 */
	gpDataListServer->DeleteDataList("DataList_StageCreate");	// �X�e�[�W�N���G�C�g���Ǘ�
}

// �X�V
void Scene_StageCreate::Update()
{
	/* �t�F�[�Y���Ƃ̏��� */
	switch (this->iNowPhase)
	{
		// �}�b�v�I���t�F�[�Y
		case PHASE_SELECT_MAP:
			Update_SelectMap();
			break;

		// �}�b�v�ҏW�t�F�[�Y
		case PHASE_EDIT_MAP:
			Update_EditMap();
			break;
	}
}

// �`��
void Scene_StageCreate::Draw()
{
	/* �t�F�[�Y���Ƃ̏��� */
	switch (this->iNowPhase)
	{
		// �}�b�v�I���t�F�[�Y
		case PHASE_SELECT_MAP:
			Draw_SelectMap();
			break;

		// �}�b�v�ҏW�t�F�[�Y
		case PHASE_EDIT_MAP:
			Draw_EditMap();
			break;
	}
}

// �}�b�v�I���t�F�[�Y�̍X�V
void Scene_StageCreate::Update_SelectMap()
{
	/* �}�b�v�����擾 */
	std::vector<WOLD_MAP_DATA>& MapDataList = this->pDataList_StageCreate->GetMapDataList();

	/* �I���}�b�v�ύX */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_UP] == TRUE)
	{
		this->iSelectMapIndex--;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_DOWN] == TRUE)
	{
		this->iSelectMapIndex++;
	}

	/* �I���}�b�v�̃C���f�b�N�X�ԍ���͈͓��Ɏ��߂� */
	int iMapListSize = static_cast<int>(MapDataList.size());
	if (this->iSelectMapIndex < 0)
	{
		this->iSelectMapIndex = 0;
	}
	if (this->iSelectMapIndex >= iMapListSize)
	{
		this->iSelectMapIndex = iMapListSize - 1;
	}

	/* ����L�[�Ń}�b�v��ǂݍ��݁A�}�b�v�ҏW�t�F�[�Y�ֈڍs */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_Z] == TRUE)
	{
		/* �t�F�[�Y�ύX */
		this->iNowPhase = PHASE_EDIT_MAP;

		/* �I�𒆂̃}�b�v�f�[�^��ǂݍ��� */
		this->pDataList_StageCreate->Load_MapData(MapDataList[this->iSelectMapIndex].MapName);

		/* �X�e�[�W�V�[���쐬 */
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_Stage>());

		return;
	}
}

// �}�b�v�ҏW�t�F�[�Y�̍X�V
void Scene_StageCreate::Update_EditMap()
{
	/* ���݂̑I�����W���擾 */
	VECTOR_INT vecSelectPos = this->pDataList_StageCreate->vecGetSelectPos();

	/* �I�����W��ύX */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_W] == TRUE)
	{
		vecSelectPos.z += 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_S] == TRUE)
	{
		vecSelectPos.z -= 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_D] == TRUE)
	{
		vecSelectPos.x += 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_A] == TRUE)
	{
		vecSelectPos.x -= 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_Q] == TRUE)
	{
		vecSelectPos.y += 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_E] == TRUE)
	{
		vecSelectPos.y -= 1;
	}

	/* �I�����W���X�V */
	this->pDataList_StageCreate->SetSelectPos(vecSelectPos);
}

// �}�b�v�I���t�F�[�Y�̕`��
void Scene_StageCreate::Draw_SelectMap()
{
	/* �}�b�v�����擾 */
	std::vector<WOLD_MAP_DATA>& MapDataList = this->pDataList_StageCreate->GetMapDataList();

	/* �}�b�v���X�g��`�� */
	for (int i = 0; i < MapDataList.size(); ++i)
	{
		if (i == this->iSelectMapIndex)
		{
			// �I�𒆂̃}�b�v�̏ꍇ
			DrawFormatString(DRAW_MAPNAME_X, DRAW_MAPNAME_Y + (16 * i), GetColor(255, 255, 0), "> %s", MapDataList[i].MapName.c_str());
		}
		else
		{
			// �I�𒆂łȂ��}�b�v�̏ꍇ
			DrawFormatString(DRAW_MAPNAME_X, DRAW_MAPNAME_Y + (16 * i), GetColor(255, 255, 255), "  %s", MapDataList[i].MapName.c_str());
		}
	}
}

// �}�b�v�ҏW�t�F�[�Y�̕`��
void Scene_StageCreate::Draw_EditMap()
{
	/* �I�𒆂̍��W��`�� */
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�I�𒆂̍��W : (%d, %d, %d)", this->pDataList_StageCreate->vecGetSelectPos().x, this->pDataList_StageCreate->vecGetSelectPos().y, this->pDataList_StageCreate->vecGetSelectPos().z);
}
