/* �V�[���̃x�[�X�ƂȂ�N���X�̒�` */

#include <cstring>
#include "SceneBase.h"
#include "AppVariableDefine.h"

// �R���X�g���N�^
SceneBase::SceneBase(const std::string& cName, const int iLayer, const bool bLowerLayerStopFlg)
{
	// ����
	// iLayer					<- �V�[���̃��C���[
	// cName					<- �V�[���̖��O
	// bLowerLayerProcessFlg	<- ���w���C���[�̌v�Z��~�t���O(�L���ł��`�ʂ͂���܂�)

	/* ���������� */
	// SceneServer�ł̊Ǘ��p�f�[�^
	this->stSceneName			= cName;					// �V�[������ݒ�
	this->iLayerOrder			= iLayer;					// ���C���[������ݒ�
	this->bDeleteFlg			= false;					// �폜�t���O�𖳌���
	this->bLowerLayerStopFlg	= bLowerLayerStopFlg;		// ���ʃ��C���[�̌v�Z��~�t���O��ݒ�
}
