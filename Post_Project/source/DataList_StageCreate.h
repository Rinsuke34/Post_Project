/* �f�[�^���X�g"�X�e�[�W�N���G�C�g���Ǘ�"�N���X�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// ���ʒ�`
#include "AppFrame.h"
#include "ConstantDefine.h"
#include "StructDefine.h"

/* �O���錾 */
class Ground_Base;

// �f�[�^���X�g"�X�e�[�W�N���G�C�g���Ǘ�"�N���X
class DataList_StageCreate : public DataList_Base
{
	public:
		DataList_StageCreate();				// �R���X�g���N�^
		virtual ~DataList_StageCreate() {};	// �f�X�g���N�^

		/* �֐� */
		void Load_WoldMapList();				// ���[���h�}�b�v���X�g�ǂݍ���
		void Load_MapData(std::string MapName);	// ���[���h�}�b�v�f�[�^�ǂݍ���
		void Draw_GroundObject();				// �n�`�I�u�W�F�N�g�`��

		/* �Q�b�^�[ */
		VECTOR_INT	vecGetSelectPos()					{ return this->vecSelectPos; }	// �I�����W���擾
		std::vector<WOLD_MAP_DATA>& GetMapDataList()	{ return this->MapDataList; }	// �}�b�v���X�g���擾

		/* �Z�b�^�[ */
		void	SetSelectPos(VECTOR_INT vecSelectPos)	{ this->vecSelectPos = vecSelectPos; }	// �I�����W��ݒ�

	private:
		/* �ϐ� */
		// �}�b�v�̏��
		std::vector<WOLD_MAP_DATA>	MapDataList;															// �}�b�v���X�g
		// �}�b�v�̓��e
		std::shared_ptr<Ground_Base> pGoundObject[AREA_SIZE_BLOCK_X][AREA_SIZE_BLOCK_Y][AREA_SIZE_BLOCK_Z];	// �}�b�v�̃I�u�W�F�N�g���

		// ����p�ϐ�
		VECTOR_INT	vecSelectPos;	// �I�����W

		/* �֐� */
		void						Reset_MapData();	// �}�b�v�f�[�^�̏�����
};
