/* �v���W�F�N�g�Ŏg�p����\���̂̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// �W�����C�u����
#include <string>

// �x�N�g��(INT�^)
struct VECTOR_INT
{
	int x;
	int y;
	int z;
};

// �e�N�X�`�����
struct TEXTURE_DATA
{
	std::string BlockName;		// �u���b�N��
	int			iBlockIndex;	// �u���b�N�̃C���f�b�N�X�ԍ�
	std::string aImageName[3];	// �摜��(0:���, 1:����, 2:����)
};

// ���f�����
struct MODEL_DATA
{
	std::string ModelName;		// ���f����
	VECTOR_INT	vecPosition;	// ���W
	VECTOR		vecRotation;	// ��]
	VECTOR		vecScale;		// �g�k
};

// �}�[�J�[���
struct MARKER_DATA
{
	std::string MarkerName;		// �}�[�J�[��
	VECTOR_INT	vecPosition;	// ���W
	VECTOR		vecRotation;	// ��]
};

// ���[���h�}�b�v�Ǘ��p���
struct WOLD_MAP_DATA
{
	std::string MapName;		// �}�b�v��
	int			iMapType;		// �}�b�v�̎��(0:�����A1:�O��)
};


