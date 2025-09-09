/* AppFrame�Ŏg�p����\���̂̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// �W�����C�u����
#include <vector>
#include <string>
// �O�����C�u����
#include <DxLib.h>
// ���ʒ�`
#include "AppConstantDefine.h"

// ���͊֘A
namespace Struct_Input
{
	struct PLAYER_INPUT_JOYPAD	// �v���C���[����(�W���C�p�b�h)
	{
		/* �W���C�p�b�h */
		char	cgInput[INPUT_MAX][16];						// �W���C�p�b�h����[0:�z�[���h�A1:�g���K�A2:�����[�X][���͓��e]
		bool	bgTrigger[INPUT_MAX][INPUT_DIRECTION];		// �W���C�p�b�h�̃g���K�[�̓���[0:�z�[���h�A1:�g���K�A2:�����[�X][0:���A1:�E]
		short	sAnalogStickX[INPUT_DIRECTION];				// X���A�i���O����[0:���A1:�E]
		short	sAnalogStickY[INPUT_DIRECTION];				// Y���A�i���O����[0:���A1:�E]
	};
	
	struct PLAYER_INPUT_KEYBOARD_MOUSE	// �v���C���[����(�L�[�{�[�h�A�}�E�X)
	{
		/* �L�[�{�[�h */
		char	cgInput[INPUT_MAX][256];	// �L�[����[0:�z�[���h�A1:�g���K�A2:�����[�X][���͓��e]

		/* �}�E�X */
		int	    igInput[INPUT_MAX];		// ����[0:�z�[���h�A1:�g���K�A2:�����[�X]

		int		iMouseX;		// �}�E�XX���W
		int		iMouseY;		// �}�E�XY���W
		int		iMouseMoveX;	// X�ړ���
		int		iMouseMoveY;	// Y�ړ���
	};
}

// �R���W�����֘A
namespace Struct_Collision
{
	struct COLLISION_CAPSULE	// �J�v�Z���R���W����
	{
		VECTOR	vecCapsuleTop;		// �J�v�Z���̏㕔
		VECTOR	vecCapsuleBottom;	// �J�v�Z���̉���
		float	fCapsuleRadius;		// �J�v�Z���̔��a
	};

	struct COLLISION_SQHERE		// ���̃R���W����
	{
		VECTOR	vecSqhere;			// ���̂̒��S
		float	fSqhereRadius;		// ���̂̔��a
	};

	struct COLLISION_LINE		// �����R���W����
	{
		VECTOR	vecLineStart;		// �����̎n�_
		VECTOR	vecLineEnd;			// �����̏I�_
	};

	struct COLLISION_BOX		// �{�b�N�X�R���W����
	{
		VECTOR	vecBoxCenter;		// ���̒��S
		VECTOR	vecBoxHalfSize;		// ���̃T�C�Y(�e���̔��a)
	};
};

// 2D�p�[�c�A�j���[�V�����֘A
namespace Struct_2DPartsAnim
{
	struct PARTS_ANIM_PARTS_IMAGE_DATA	// �e�p�[�c�̊�{���
	{
		std::string stPartsName;		// �p�[�c��
		std::string stPartsPath;		// �p�[�c�̉摜�t�@�C���p�X
		int			iPartsGrHandle;		// �p�[�c�̉摜�̃O���t�B�b�N�n���h��(LoadGraph�Ŏ擾�����l)
	};

	struct PARTS_ANIM_PARTS_FRAME_DATA // �t���[���ł̃p�[�c�̏��
	{
		std::string stPartsName;		// �p�[�c��
		float		fPartsX;			// �p�[�c��X���W
		float		fPartsY;			// �p�[�c��Y���W
		float		fPartsScaleX;		// �p�[�c��X�X�P�[��
		float		fPartsScaleY;		// �p�[�c��Y�X�P�[��
		float		fPartsAngle;		// �p�[�c�̊p�x(���W�A��)
		bool		bPartsFlipX;		// �p�[�c�̍��E���]�t���O(�L���ł���Ȃ�΃p�[�c�𔽓]����)
	};

	struct PARTS_ANIM_ANIM_DATA			// �p�[�c�A�j���[�V�����̏��
	{
		std::string													AnimName;			// �A�j���[�V������
		std::vector<std::vector<PARTS_ANIM_PARTS_FRAME_DATA>>		PartsAnimFrameData;	// �p�[�c�A�j���[�V�����̎��ԒP�ʂł̏��
	};

	struct PARTS_ANIM_DATA				// �p�[�c�A�j���[�V�����Q�̏��
	{
		std::string									FileName;		// �p�[�c�A�j���[�V�����Q�̖���(==�t�@�C����)
		std::vector<PARTS_ANIM_PARTS_IMAGE_DATA>	PartsImageData;	// �p�[�c�̉摜�f�[�^(�A�j���[�V�����p�p�[�c�̉摜�f�[�^)
		std::vector<PARTS_ANIM_ANIM_DATA>			PartsAnimData;	// �p�[�c�A�j���[�V�����̏��(�A�j���[�V�����̃t���[�����Ȃ�)
	};

}
