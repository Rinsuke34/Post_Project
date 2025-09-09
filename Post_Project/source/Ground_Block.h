/* �n�`(�u���b�N)�N���X�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// ���N���X
#include "Ground_Base.h"

// �n�`(�u���b�N)�N���X
class Ground_Block : public Ground_Base
{
	public:
		Ground_Block();					// �R���X�g���N�^
		virtual ~Ground_Block() {};		// �f�X�g���N�^

		/* �N���X���Ŏg�p����萔 */
		// �ʂ̎��
		static const int FACE_TYPE_TOP		= 0;	// �ʂ̎��:���
		static const int FACE_TYPE_SIDE		= 1;	// �ʂ̎��:����
		static const int FACE_TYPE_BOTTOM	= 2;	// �ʂ̎��:����
		// �ʂ̕���
		static const int DIRECTION_X_PLUS	= 0;	// +X����
		static const int DIRECTION_X_MINUS	= 1;	// -X����
		static const int DIRECTION_Y_PLUS	= 2;	// +Y����
		static const int DIRECTION_Y_MINUS	= 3;	// -Y����
		static const int DIRECTION_Z_PLUS	= 4;	// +Z����
		static const int DIRECTION_Z_MINUS	= 5;	// -Z����
		static const int DIRECTION_MAX		= 6;	// ������

		/* �֐� */
		virtual void	Draw();			// �`��

		/* �Z�b�^�[ */
		void SetBoxCollision(Struct_Collision::COLLISION_BOX stBox)				{ this->stBox						= stBox; }			// �{�b�N�X�R���W�����̏���ݒ�
		void SetTextureHandle(int iFaceType, std::shared_ptr<int> iGrhandle)	{ this->apiGrHandle[iFaceType]		= iGrhandle; };		// �ʂ̃e�N�X�`���n���h����ݒ�(0:���, 1:����, 2:����)
		void SetFaceDrawFlg(int iDirection, bool bFaceDrawFlg)					{ this->bFaceDrawFlg[iDirection]	= bFaceDrawFlg; };	// �ʂ̕`��t���O��ݒ�(0:+X, 1:-X, 2:+Y, 3:-Y, 4:+Z, 5:-Z)

		/* �Q�b�^�[ */
		Struct_Collision::COLLISION_BOX GetBoxCollision()				{ return stBox; }						// �{�b�N�X�R���W�����̏����擾
		bool							GetFaceDrawFlg(int iDirection)	{ return bFaceDrawFlg[iDirection]; }	// �ʂ̕`�ʃt���O���擾

	private:
		/* �ϐ� */
		std::shared_ptr<int>			apiGrHandle[3];					// �g�p����摜�̃n���h��(0:���, 1:����: 2,����)
		bool							bFaceDrawFlg[DIRECTION_MAX];	// �ʂ̕`��t���O
};
