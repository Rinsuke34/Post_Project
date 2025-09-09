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
#include "DataList_Image.h"
#include "DataList_Object.h"
#include "Ground_Block.h"
#include "Character_Player.h"
// ���ʒ�`
#include "ConstantDefine.h"
#include "StructDefine.h"

// �e�N�X�`���ǂݍ���
void Scene_Stage::JsonLoad_Texture()
{
	/* �e�N�X�`���f�[�^��ǂݍ��݁A�e�N�X�`���f�[�^���X�g�ɓo�^���� */
	// ���e�N�X�`���ǂݍ��݂����������Ă���}�b�v�f�[�^�̓ǂݍ��݂͍s������

	// Json�t�@�C���ǂݍ���
	std::string FilePath = "resource/MapData/Texture_Data.json";

	std::ifstream ifs(FilePath);
	if (!ifs) return;

	using json = nlohmann::json;
	json j;
	ifs >> j;

	// �e�N�X�`���f�[�^���X�g�ւ̐ݒ�
	for (const auto& elem : j)
	{
		TEXTURE_DATA data;
		data.BlockName		= elem.value("BlockName", "");
		data.iBlockIndex	= elem.value("BlockIndex", -1);
		data.aImageName[0]	= elem.value("ImageName_Upper", "");
		data.aImageName[1]	= elem.value("ImageName_Side", "");
		data.aImageName[2]	= elem.value("ImageName_Under", "");

		this->pDataList_Object->AddTexture(data);
	}

	// �f�[�^���X�g"�摜�f�[�^�Ǘ�"�փe�N�X�`���̓o�^
	std::shared_ptr<DataList_Image>	pDataList_Image	= std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));
	for (auto& texData : this->pDataList_Object->GetTextureDataList())
	{
		// ���
		if (!texData.aImageName[0].empty())
		{
			pDataList_Image->LoadGrHandle(texData.aImageName[0]);
		}
		// ����
		if (!texData.aImageName[1].empty())
		{
			pDataList_Image->LoadGrHandle(texData.aImageName[1]);
		}
		// ����
		if (!texData.aImageName[2].empty())
		{
			pDataList_Image->LoadGrHandle(texData.aImageName[2]);
		}
	}
}

// ���[���h�}�b�v�ǂݍ���(����)
void Scene_Stage::JsonLoad_WoldMap_Center()
{
	/* �}�b�v�f�[�^�ǂݍ��� */
	// ���e�N�X�`���ǂݍ��݂��������Ă����ԂŎ��s���邱��

	/* �f�[�^���X�g"�摜�f�[�^�Ǘ�"�擾 */
	std::shared_ptr<DataList_Image>	pDataList_Image = std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));

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
					auto& TextureDataList = this->pDataList_Object->GetTextureDataList();
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

	/* �v���C���[�ǉ�(��) */
	std::shared_ptr<Character_Player> pPlayer = std::make_shared<Character_Player>();
	pPlayer->SetPosition(VGet(6144.f, 300.f, 6144.f));
	this->pDataList_Object->AddObject_Actor(pPlayer);
}

// �_���W�����}�b�v�ǂݍ���
void Scene_Stage::JsonLoad_DungeonMap()
{

}
