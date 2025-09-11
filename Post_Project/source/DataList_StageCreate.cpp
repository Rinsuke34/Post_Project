/* �f�[�^���X�g"�X�e�[�W�N���G�C�g���Ǘ�"�N���X�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �W�����C�u����
#include <fstream>
// �w�b�_�t�@�C��
#include "DataList_StageCreate.h"
// �֘A�N���X
#include "DataList_Model.h"
#include "DataList_Image.h"
#include "Ground_Block.h"
#include "Ground_Model.h"
#include "Ground_Marker.h"

// �R���X�g���N�^
DataList_StageCreate::DataList_StageCreate() : DataList_Base("DataList_StageCreate")
{
	/* ������ */
	this->vecSelectPos = { 0, 0, 0 };
	for (int x = 0; x < AREA_SIZE_BLOCK_X; ++x)
	{
		for (int y = 0; y < AREA_SIZE_BLOCK_Y; ++y)
		{
			for (int z = 0; z < AREA_SIZE_BLOCK_Z; ++z)
			{
				pGoundObject[x][y][z] = nullptr;
			}
		}
	}

	Reset_MapData();	

	/* ���[���h�}�b�v���X�g�ǂݍ��� */
	MapDataList.clear();
	Load_WoldMapList();
}

// ���[���h�}�b�v���X�g�ǂݍ���
void DataList_StageCreate::Load_WoldMapList()
{
	/* ���[���h�}�b�v�̃��X�g��ǂݍ��� */
	// ���o�^����Ă���}�b�v����ҏW����}�b�v�f�[�^��I������

	/* JSON�t�@�C���ǂݍ��� */
	std::string FilePath = "resource/MapData/MapData_Wold/WoldMapList.json";

	std::ifstream ifs(FilePath);
	if (!ifs) return;

	using json = nlohmann::json;
	json j;
	ifs >> j;

	/* �}�b�v���X�g�f�[�^���o */
	for (const auto& elem : j)
	{
		WOLD_MAP_DATA data;
		data.MapName	= elem.value("MapName", "");
		data.iMapType	= elem.value("MapType", 0);
		this->MapDataList.push_back(data);
	}
}

// ���[���h�}�b�v�f�[�^�ǂݍ���
void DataList_StageCreate::Load_MapData(std::string MapName)
{
	// ����
	// MapName		<- �ǂݍ��ރ}�b�v�f�[�^�̖��O

	/* ���݂̃}�b�v�f�[�^�������� */
	Reset_MapData();

	/* �f�[�^���X�g�擾 */
	// �摜�f�[�^�Ǘ�
	std::shared_ptr<DataList_Image>	pDataList_Image = std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));
	// 3D���f���f�[�^�Ǘ�
	std::shared_ptr<DataList_Model>	pDataList_Model = std::dynamic_pointer_cast<DataList_Model>(gpDataListServer->GetDataList("DataList_Model"));

	/* JSON�t�@�C���ǂݍ��� */
	std::string FilePath = "resource/MapData/MapData_Wold/" + MapName + ".json";

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
				/* �u���b�NID�ǂݍ��� */
				int BlockIndex = GroundBlock.at(iY).at(iZ).at(iX).get<int>();

				/* ��������̃u���b�N�����邩�m�F */
				if (BlockIndex == -1)
				{
					// �u���b�N���Ȃ��ꍇ
					continue;
				}

				/* �R���W���������쐬 */
				Struct_Collision::COLLISION_BOX stBox;
				stBox.vecBoxCenter = VGet(
					iX * MAP_BLOCK_SIZE_X + (MAP_BLOCK_SIZE_X / 2.f),
					iY * MAP_BLOCK_SIZE_Y + (MAP_BLOCK_SIZE_Y / 2.f),
					iZ * MAP_BLOCK_SIZE_Z + (MAP_BLOCK_SIZE_Z / 2.f));
				stBox.vecBoxHalfSize = VGet(MAP_BLOCK_SIZE_X / 2.f, MAP_BLOCK_SIZE_Y / 2.f, MAP_BLOCK_SIZE_Z / 2.f);

				/* �u���b�N�f�[�^���쐬 */
				std::shared_ptr<Ground_Block> pGroundBlock = std::make_shared<Ground_Block>();;
				pGroundBlock->SetBoxCollision(stBox);	// �R���W������ݒ�

				/* �e�N�X�`���ݒ� */
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
				// �� �}�b�v�쐬�̏ꍇ�͑S�ʂ�`�ʂ���悤�ɐݒ�
				for (int iDir = 0; iDir < Ground_Block::DIRECTION_MAX; ++iDir)
				{
					pGroundBlock->SetFaceDrawFlg(iDir, true);
				}

				/* �u���b�N�f�[�^��ۑ� */
				this->pGoundObject[iX][iY][iZ] = pGroundBlock;
			}
		}
	}

	/* 3D���f���f�[�^���o */
	auto& ModelList = j["Ground_Model"];
	for (const auto& elem : ModelList)
	{
		/* 3D���f�����擾 */
		MODEL_DATA data;
		data.ModelName	= elem.value("ModelName", "");
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
		std::shared_ptr<Ground_Model> pGroundModel = std::make_shared<Ground_Model>();;
		
		pGroundModel->SetModelHandle(pDataList_Model->iGetModel(data.ModelName));
		pGroundModel->SetPosition(vecPosition);
		pGroundModel->SetRotation(data.vecRotation);
		pGroundModel->SetScale(data.vecScale);
		pGroundModel->InitialSetup();

		/* 3D���f���f�[�^��ۑ� */
		this->pGoundObject[data.vecPosition.x][data.vecPosition.y][data.vecPosition.z] = pGroundModel;
	}

	/* �}�[�J�[��񒊏o */
	auto& MarkerList = j["Marker"];
	for (const auto& elem : MarkerList)
	{
		/* �}�[�J�[���擾 */
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
		std::shared_ptr<Ground_Marker> pGroundMarker = std::make_shared<Ground_Marker>();;
		pGroundMarker->SetMarkerName(data.MarkerName);
		pGroundMarker->SetBoxCenter(vecPosition);
		pGroundMarker->SetRotation(data.vecRotation);

		/* �}�[�J�[�f�[�^��ۑ� */
		this->pGoundObject[data.vecPosition.x][data.vecPosition.y][data.vecPosition.z] = pGroundMarker;
	}
}

// �n�`�I�u�W�F�N�g�`��
void DataList_StageCreate::Draw_GroundObject()
{
	for (int iX = 0; iX < AREA_SIZE_BLOCK_X; ++iX)
	{
		for (int iY = 0; iY < AREA_SIZE_BLOCK_Y; ++iY)
		{
			for (int iZ = 0; iZ < AREA_SIZE_BLOCK_Z; ++iZ)
			{
				if (this->pGoundObject[iX][iY][iZ] != nullptr)
				{
					// �n�`�I�u�W�F�N�g�����݂���ꍇ
					this->pGoundObject[iX][iY][iZ]->Draw();
				}
			}
		}
	}
}

// �}�b�v�f�[�^�̏�����
void DataList_StageCreate::Reset_MapData()
{
	for (int iX = 0; iX < AREA_SIZE_BLOCK_X; ++iX)
	{
		for (int iY = 0; iY < AREA_SIZE_BLOCK_Y; ++iY)
		{
			for (int iZ = 0; iZ < AREA_SIZE_BLOCK_Z; ++iZ)
			{
				this->pGoundObject[iX][iY][iZ] = nullptr;
			}
		}
	}
}
