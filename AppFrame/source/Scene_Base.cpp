/* �V�[���̃x�[�X�ƂȂ�N���X�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �W�����C�u����
#include <cstring>
// �w�b�_�t�@�C��
#include "Scene_Base.h"
// ���ʒ�`
#include "AppVariableDefine.h"

// �R���X�g���N�^
Scene_Base::Scene_Base(const std::string& cName, const int iLayer, const bool bLowerLayerUpdataStopFlg, const bool bUpperLayerDrawStopFlg)
{
	// ����
	// iLayer					<- �V�[���̃��C���[
	// cName					<- �V�[���̖��O
	// bLowerLayerUpdataStopFlg	<- ���w���C���[�̌v�Z��~�t���O(�L���ł��`�ʂ͂���܂�)
	// bUpperLayerDrawStopFlg	<- ��w���C���[�̕`�ʒ�~�t���O

	/* ���������� */
	// SceneServer�ł̊Ǘ��p�f�[�^
	this->stSceneName				= cName;						// �V�[������ݒ�
	this->iLayerOrder				= iLayer;						// ���C���[������ݒ�
	this->bDeleteFlg				= false;						// �폜�t���O�𖳌���
	this->bLowerLayerUpdataStopFlg	= bLowerLayerUpdataStopFlg;		// ���ʃ��C���[�̌v�Z��~�t���O��ݒ�
	this->bUpperLayerDrawStopFlg	= bUpperLayerDrawStopFlg;		// ��ʃ��C���[�̕`�ʒ�~�t���O�𖳌���
}
