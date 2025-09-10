/* �n�`(�}�[�J�[)�N���X�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// ���N���X
#include "Ground_Base.h"

// �n�`(�}�[�J�[)�N���X
class Ground_Marker : public Ground_Base
{
	public:
		Ground_Marker();				// �R���X�g���N�^
		virtual ~Ground_Marker() {};	// �f�X�g���N�^

		/* �Z�b�^�[ */
		void SetMarkerName(const std::string& cMarkerName)	{ this->MarkerName			= cMarkerName; }	// �}�[�J�[����ݒ�
		void SetBoxCenter(VECTOR vecBoxCenter)				{ this->stBox.vecBoxCenter	= vecBoxCenter; }	// �R���W�����̒��S���W��ݒ�
		void SetRotation(VECTOR vecRotation)				{ this->vecRotation			= vecRotation; }	// ��]�ʂ�ݒ�

		/* �Q�b�^�[ */
		std::string GetMarkerName()		{ return this->MarkerName; }			// �}�[�J�[�����擾
		VECTOR		vecGetBoxCenter()	{ return this->stBox.vecBoxCenter; }	// �R���W�����̒��S���W���擾
		VECTOR		vecGetRotation()	{ return this->vecRotation; }			// ��]�ʂ��擾

	private:
		/* �ϐ� */
		std::string MarkerName;		// �}�[�J�[��
		VECTOR		vecRotation;	// ��]��
};
