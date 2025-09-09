/* �n�`�̃x�[�X�N���X�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// ���N���X
#include "Object_Base.h"
// ���ʒ�`
#include "AppFrame.h"

// �n�`�x�[�X�N���X
class Ground_Base : public Object_Base
{
	public:
		Ground_Base();					// �R���X�g���N�^
		virtual ~Ground_Base() {};		// �f�X�g���N�^

		/* �֐� */
		// �R���W�����ڐG����
		virtual bool HitCheck(Struct_Collision::COLLISION_SQHERE	stSqhere);	// ����
		virtual bool HitCheck(Struct_Collision::COLLISION_LINE		stLine);	// ����
		virtual bool HitCheck(Struct_Collision::COLLISION_BOX		stBox);		// �{�b�N�X
		// �Փ˓_�擾(���� - �u���b�N)
		virtual VECTOR HitPosition(Struct_Collision::COLLISION_LINE	stLine);	// ����

		/* �Z�b�^�[ */
		void SetBoxCollision(Struct_Collision::COLLISION_BOX stBox)	{ this->stBox = stBox; }	// �{�b�N�X�R���W�����̏���ݒ�

		/* �Q�b�^�[ */
		Struct_Collision::COLLISION_BOX GetBoxCollision()			{ return stBox; }			// �{�b�N�X�R���W�����̏����擾

	protected:
		Struct_Collision::COLLISION_BOX	stBox;							// �{�b�N�X�R���W�����̏��
};
