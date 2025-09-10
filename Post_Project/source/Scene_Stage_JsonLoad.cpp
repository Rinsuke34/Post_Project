/* �V�[��"�X�e�[�W"�̒�` */
// ��Json�t�@�C���̓ǂݍ��ݕ����̂�

/* �g�p����v�f�̃C���N���[�h */
// �W�����C�u����
#include <fstream>
// �O�����C�u����
#include <nlohmann/json.hpp>
// �w�b�_�t�@�C��
#include "Scene_Stage.h"
// �֘A�N���X
#include "DataList_Model.h"
#include "DataList_Image.h"
#include "DataList_Object.h"
#include "Ground_Block.h"
#include "Ground_Model.h"
#include "Ground_Marker.h"
#include "Character_Player.h"
// ���ʒ�`
#include "ConstantDefine.h"
#include "StructDefine.h"

// ���[���h�}�b�v�ǂݍ���(����)
void Scene_Stage::JsonLoad_WoldMap_Center()
{
	/* �}�b�v�f�[�^�ǂݍ��� */
	// ���e�N�X�`���ǂݍ��݂��������Ă����ԂŎ��s���邱��

		/* �f�[�^���X�g�擾 */
	// �摜�f�[�^�Ǘ�
	std::shared_ptr<DataList_Image>	pDataList_Image = std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));
	// 3D���f���f�[�^�Ǘ�
	std::shared_ptr<DataList_Model>	pDataList_Model = std::dynamic_pointer_cast<DataList_Model>(gpDataListServer->GetDataList("DataList_Model"));

	/* Json�t�@�C���ǂݍ��� */
	std::string FilePath = "resource/MapData/MapData_Wold/AreaData_Front.json";

	std::ifstream ifs(FilePath);
	if (!ifs) return;

	using json = nlohmann::json;
	json j;
	ifs >> j;

	/* �n�`(�u���b�N)�f�[�^���o */
	auto& GroundBlock = j["Ground_Block"];
	
	for (int iY = 0; iY < AREA_SIZE_BLOCK_Y; ++iY)
	{
		for (int iZ = 0; iZ < AREA_SIZE_BLOCK_Z; ++iZ)
		{
			for (int iX = 0; iX < AREA_SIZE_BLOCK_X; ++iX)
			{
				int BlockIndex = GroundBlock.at(iY).at(iZ).at(iX).get<int>();
				if (BlockIndex != -1)
				{
					// �u���b�N�����݂���ꍇ
					/* �u���b�N���� */
					std::shared_ptr<Ground_Block> pGroundBlock = std::make_shared<Ground_Block>();

					// �R���W�����ݒ�
					Struct_Collision::COLLISION_BOX stBox;
					stBox.vecBoxCenter = VGet(
						AREA_ORIGIN_POS[AREA_NO_CENTER].x + iX * MAP_BLOCK_SIZE_X + MAP_BLOCK_SIZE_X / 2.f,
						AREA_ORIGIN_POS[AREA_NO_CENTER].y + iY * MAP_BLOCK_SIZE_Y + MAP_BLOCK_SIZE_Y / 2.f,
						AREA_ORIGIN_POS[AREA_NO_CENTER].z + iZ * MAP_BLOCK_SIZE_Z + MAP_BLOCK_SIZE_Z / 2.f
					);
					stBox.vecBoxHalfSize = VGet(MAP_BLOCK_SIZE_X / 2.f , MAP_BLOCK_SIZE_Y / 2.f, MAP_BLOCK_SIZE_Z / 2.f);
					pGroundBlock->SetBoxCollision(stBox);

					// �e�N�X�`���ݒ�
					auto& TextureDataList = pDataList_Image->GetTextureDataList();
					for (auto& texData : TextureDataList)
					{
						if (texData.iBlockIndex == BlockIndex)
						{
							// ���
							if (!texData.aImageName[0].empty())
							{
								pGroundBlock->SetTextureHandle(Ground_Block::FACE_TYPE_TOP, pDataList_Image->iGetGrhandle(texData.aImageName[0]));
							}
							// ����
							if (!texData.aImageName[1].empty())
							{
								pGroundBlock->SetTextureHandle(Ground_Block::FACE_TYPE_SIDE, pDataList_Image->iGetGrhandle(texData.aImageName[1]));
							}
							// ����
							if (!texData.aImageName[2].empty())
							{
								pGroundBlock->SetTextureHandle(Ground_Block::FACE_TYPE_BOTTOM, pDataList_Image->iGetGrhandle(texData.aImageName[2]));
							}
							break;
						}
					}

					/* �u���b�N�̖ʂ̕`�ʐݒ� */
					// �� �אڂ���u���b�N������ꍇ�A���̖ʂ͕`�ʂ��Ȃ�
					// �� �e�����̋��E�ʂ͕K���`�ʂ���
					static const int aiDirOffset[Ground_Block::DIRECTION_MAX][3] = {
						{+1,  0,  0}, // +X
						{-1,  0,  0}, // -X
						{ 0, +1,  0}, // +Y
						{ 0, -1,  0}, // -Y
						{ 0,  0, +1}, // +Z
						{ 0,  0, -1}  // -Z
					};

					for (int iDir = 0; iDir < Ground_Block::DIRECTION_MAX; ++iDir) {
						int nx = iX + aiDirOffset[iDir][0];
						int ny = iY + aiDirOffset[iDir][1];
						int nz = iZ + aiDirOffset[iDir][2];

						// ���E�ʂł��邩
						if (nx < 0 || nx >= AREA_SIZE_BLOCK_X ||
							ny < 0 || ny >= AREA_SIZE_BLOCK_Y ||
							nz < 0 || nz >= AREA_SIZE_BLOCK_Z)
						{
							// ���E�ʂł���Ȃ�Ε`�ʂ�L���ɐݒ�
							pGroundBlock->SetFaceDrawFlg(iDir, true);
						}
						else
						{
							// ���E�ʂłȂ��Ȃ�Ηאڂ���u���b�N�̑��݂��m�F
							int NeighborBlockIndex = GroundBlock.at(ny).at(nz).at(nx).get<int>();
							if (NeighborBlockIndex == -1)
							{
								// �אڂ���u���b�N���Ȃ��Ȃ�`�ʂ�L���ɐݒ�
								pGroundBlock->SetFaceDrawFlg(iDir, true);
							}
						}
					}

					// �I�u�W�F�N�g���X�g�ɓo�^
					this->pDataList_Object->AddObject_Ground(pGroundBlock, AREA_NO_CENTER);
				}
			}
		}
	}

	/* �n�`(3D���f��)�f�[�^���o */
	auto& GroundModel = j["Ground_Model"];
	for (const auto& elem : GroundModel)
	{
		/* 3D���f�����擾 */
		MODEL_DATA data;
		data.ModelName = elem.value("ModelName", "");
		elem.at("Position").at("x").get_to(data.vecPosition.x);
		elem.at("Position").at("y").get_to(data.vecPosition.y);
		elem.at("Position").at("z").get_to(data.vecPosition.z);
		elem.at("Rotation").at("x").get_to(data.vecRotation.x);
		elem.at("Rotation").at("y").get_to(data.vecRotation.y);
		elem.at("Rotation").at("z").get_to(data.vecRotation.z);
		elem.at("Scale").at("x").get_to(data.vecScale.x);
		elem.at("Scale").at("y").get_to(data.vecScale.y);
		elem.at("Scale").at("z").get_to(data.vecScale.z);

		/* �|�W�V���������[���h���W�ɕϊ� */
		VECTOR vecPosition;
		vecPosition.x = data.vecPosition.x * MAP_BLOCK_SIZE_X + (MAP_BLOCK_SIZE_X / 2);
		vecPosition.y = data.vecPosition.y * MAP_BLOCK_SIZE_Y + (MAP_BLOCK_SIZE_Y / 2);
		vecPosition.z = data.vecPosition.z * MAP_BLOCK_SIZE_Z + (MAP_BLOCK_SIZE_Z / 2);

		/* 3D���f���f�[�^���쐬 */
		std::shared_ptr<Ground_Model> pGroundModel = std::make_shared<Ground_Model>();

		pGroundModel->SetModelHandle(pDataList_Model->iGetModel(data.ModelName));
		pGroundModel->SetPosition(vecPosition);
		pGroundModel->SetRotation(data.vecRotation);
		pGroundModel->SetScale(data.vecScale);
		pGroundModel->InitialSetup();

		/* �I�u�W�F�N�g���X�g�ɓo�^ */
		this->pDataList_Object->AddObject_Ground(pGroundModel, AREA_NO_CENTER);
	}

	/* �}�[�J�[��񒊏o */
	auto& MarkerList = j["Marker"];
	for (const auto& elem : MarkerList)
	{
		/* �}�[�J�[���쐬 */
		MARKER_DATA data;
		data.MarkerName = elem.value("MarkerName", "");
		elem.at("Position").at("x").get_to(data.vecPosition.x);
		elem.at("Position").at("y").get_to(data.vecPosition.y);
		elem.at("Position").at("z").get_to(data.vecPosition.z);
		elem.at("Rotation").at("x").get_to(data.vecRotation.x);
		elem.at("Rotation").at("y").get_to(data.vecRotation.y);
		elem.at("Rotation").at("z").get_to(data.vecRotation.z);

		/* �|�W�V���������[���h���W�ɕϊ� */
		VECTOR vecPosition;
		vecPosition.x = data.vecPosition.x * MAP_BLOCK_SIZE_X + (MAP_BLOCK_SIZE_X / 2);
		vecPosition.y = data.vecPosition.y * MAP_BLOCK_SIZE_Y + (MAP_BLOCK_SIZE_Y / 2);
		vecPosition.z = data.vecPosition.z * MAP_BLOCK_SIZE_Z + (MAP_BLOCK_SIZE_Z / 2);

		/* �}�[�J�[�f�[�^���쐬 */
		std::shared_ptr<Ground_Marker> pMarker = std::make_shared<Ground_Marker>();
		pMarker->SetMarkerName(data.MarkerName);
		pMarker->SetBoxCenter(vecPosition);
		pMarker->SetRotation(data.vecRotation);

		/* �}�[�J�[����ۑ� */
		this->pDataList_Object->AddObject_Marker(pMarker, AREA_NO_CENTER);
	}

	/* �v���C���[�ǉ�(��) */
	std::shared_ptr<Character_Player> pPlayer = std::make_shared<Character_Player>();
	pPlayer->SetPosition(VGet(6144.f, 300.f, 6144.f));
	this->pDataList_Object->AddObject_Actor(pPlayer);
}

// �_���W�����}�b�v�ǂݍ���
void Scene_Stage::JsonLoad_DungeonMap()
{

}
