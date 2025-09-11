/* �n�`(�}�[�J�[)�N���X�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �w�b�_�t�@�C��
#include "Ground_Marker.h"
// ���ʒ�`
#include "ConstantDefine.h"

// �R���X�g���N�^
Ground_Marker::Ground_Marker() : Ground_Base()
{
	/* ������ */
	this->MarkerName	= "";
	this->vecRotation	= VGet(0.f, 0.f, 0.f);
}

// �`��
void Ground_Marker::Draw()
{
	/* ���S�_�`�� */
	DrawLine3D(VAdd(this->stBox.vecBoxCenter, VGet(+MARKER_CENTER_SIZE_HALF, 0.f, 0.f)), VAdd(this->stBox.vecBoxCenter, VGet(-MARKER_CENTER_SIZE_HALF, 0.f, 0.f)), GetColor(255, 0, 0));
	DrawLine3D(VAdd(this->stBox.vecBoxCenter, VGet(0.f, +MARKER_CENTER_SIZE_HALF, 0.f)), VAdd(this->stBox.vecBoxCenter, VGet(0.f, -MARKER_CENTER_SIZE_HALF, 0.f)), GetColor(255, 0, 0));
	DrawLine3D(VAdd(this->stBox.vecBoxCenter, VGet(0.f, 0.f, +MARKER_CENTER_SIZE_HALF)), VAdd(this->stBox.vecBoxCenter, VGet(0.f, 0.f, -MARKER_CENTER_SIZE_HALF)), GetColor(255, 0, 0));
}
