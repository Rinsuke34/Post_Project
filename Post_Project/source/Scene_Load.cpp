/* �V�[��"���[�h���"�̒�` */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// �w�b�_�t�@�C��
#include "Scene_Load.h"

// �R���X�g���N�^
Scene_Load::Scene_Load() : Scene_Base("Scene_Load", 99999, true, true)
{

}

// �f�X�g���N�^
Scene_Load::~Scene_Load()
{

}

// �X�V
void Scene_Load::Update()
{
	/* �񓯊��ǂݍ��ݒ��̏������������Ă��邩�m�F */
	if (GetASyncLoadNum() == 0)
	{
		// �������Ă���ꍇ
		/* �V�[���̍폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;

		return;
	}
}

// �`��
void Scene_Load::Draw()
{
	DrawString(16, 16, "Now Loading...", GetColor(255, 255, 255));
}
