/* �I�u�W�F�N�g�̃x�[�X�N���X�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �w�b�_�t�@�C��
#include "Object_Base.h"

// �R���X�g���N�^
Object_Base::Object_Base()
{
	/* ������ */
	this->bDeleteFlg = false;	// �폜�t���O
}

// �`��(�V���h�E�}�b�v�p)
void Object_Base::Draw_Shadow()
{
	// ����{�I�ɒʏ�̕`�ʂƓ����ŗǂ����A�I�u�W�F�N�g�̌`�Ɖe�̌`���قȂ�ꍇ�͂��̊֐����I�[�o�[���C�h���Ē���
	Draw();
}
