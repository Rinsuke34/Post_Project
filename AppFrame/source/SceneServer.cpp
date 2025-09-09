/* �V�[���T�[�o�[�̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �w�b�_�t�@�C��
#include "SceneServer.h"
// �֘A�N���X
#include "Scene_Base.h"
// ���ʒ�`
#include "AppFunctionDefine.h"

// �R���X�g���N�^
SceneServer::SceneServer()
{
	/* ������ */
	this->bSceneDeleteFlg			= false;	// �V�[���폜�t���O
	this->bSceneAddFlg				= false;	// �V�[���ǉ��t���O
	this->bDeleteCurrentSceneFlg	= false;	// ���s�V�[���폜�t���O
}

// �f�X�g���N�^
SceneServer::~SceneServer()
{
	/* �I������ */
	// ���X�g���̂��ׂẴV�[�����폜
	DeleteAllScene();		// �V�[�����X�g
	DeleteAllAddScene();	// �ǉ��\��̃V�[�����X�g
}

// �V�[���v�Z����
void SceneServer::SceneProcess()
{
	/* ���C���[�����������V�[������v�Z���s�� */
	for (auto& Scene : pstSceneList)
	{
		/* �V�[���̍X�V���� */
		Scene->Update();

		/* �ΏۃV�[���̍폜�t���O�̊m�F */
		if (Scene->bGetDeleteFlg() == true)
		{
			// �ΏۃV�[���̍폜�t���O���L���ł���Ȃ�
			/* �V�[���폜�t���O��L���ɂ��� */
			this->bSceneDeleteFlg = true;
		}

		/* �ΏۃV�[���̉��w���C���[�v�Z��~�t���O�̊m�F */
		if (Scene->bGetLowerLayerUpdateStopFlg() == true)
		{
			// ���w���C���[�v�Z��~�t���O���L���ł���Ȃ�
			/* �V�[���v�Z�������I������ */
			break;
		}
	}

	/* �폜�t���O���L���ȃV�[�����폜 */
	DeleteUnnecessaryScene();

	/* �V�[���̒ǉ� */
	AddScene();
}

// �V�[���`�揈��
void SceneServer::SceneDraw()
{
	/* 3D�p�̊�{�ݒ��L���� */
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	/* ���C���[�������Ⴂ�V�[������`�ʂ��s�� */
	for (auto Scene = pstSceneList.rbegin(); Scene != pstSceneList.rend(); ++Scene)
	{
		Scene->get()->Draw();
	}
}

// �V�[���ǉ��\��
void SceneServer::AddSceneReservation(std::shared_ptr<Scene_Base> NewScene)
{
	// ���V�[���̒ǉ����̂�"AddScene"�֐��ōs��
	// ����
	// NewScene			<-	�V�����V�[���T�[�o�[�ɓo�^����V�[��

	/* �V�[���ǉ��t���O�̗L���� */
	this->bSceneAddFlg = true;

	/* �ǉ��\��̃V�[�����X�g�ɃV�[����ǉ����� */
	this->pstAddSceneList.push_back(NewScene);
}

// �V�[���擾
std::shared_ptr<Scene_Base> SceneServer::GetScene(const std::string& cName)
{
	// ����
	// cName		<-	�擾�������V�[���̖���

	/* �V�[���ꗗ����V�[�����擾���� */
	for (auto& Scene : pstSceneList)
	{
		/* �V�[���̖��̂���v���邩�m�F���� */
		if (Scene->stGetSceneName() == cName)
		{
			// �V�[���̖��̂���v����Ȃ��
			/* �V�[���̃C���X�^���X��Ԃ� */
			return Scene;
		}
	}

	// �V�[����������Ȃ������ꍇ
	/* nullptr��߂�l�Ƃ��ĕԂ� */
	return nullptr;
}


// �V�[�����X�g�ւ̃V�[���ǉ�
void SceneServer::AddScene()
{
	/* �V�[���ǉ��t���O���L���ł��邩�m�F */
	if (this->bSceneAddFlg == true)
	{
		// �V�[���ǉ��t���O���L���Ȃ��
		/* ���s�V�[���폜�t���O���L���ł��邩�m�F */
		if (this->bDeleteCurrentSceneFlg == true)
		{
			// ���s�V�[���폜�t���O���L���ł���Ȃ��
			/* �V�[�����X�g�̃V�[�������ׂč폜���� */
			DeleteAllScene();

			/* ���s�V�[���폜�t���O�̖����� */
			this->bDeleteCurrentSceneFlg = false;
		}

		/* �ǉ��\��̃V�[�����V�[�����X�g�ɒǉ����� */
		pstSceneList.splice(pstSceneList.end(), pstAddSceneList);

		/* �ǉ��\��̃V�[�����X�g�����ׂč폜���� */
		DeleteAllAddScene();

		/* ���C���[�������傫�����ɕ��ёւ��� */
		SceneSortLayerOrder();

		/* �V�[���ǉ��t���O�̖����� */
		this->bSceneAddFlg = false;
	}
}

// �V�[�����X�g�̕��ёւ�(���C���[�����̑傫����)
void SceneServer::SceneSortLayerOrder()
{
	/* �e���C���[����������"���C���[����"���傫�����ɕ��ёւ��� */
	pstSceneList.sort([](std::shared_ptr<Scene_Base> SceneA, std::shared_ptr<Scene_Base> SceneB)
	{
		return SceneA->iGetSceneLayerOrder() > SceneB->iGetSceneLayerOrder();
	});
}


// �V�[���폜(�폜�t���O���L���ȃV�[���ɑ΂���)
void SceneServer::DeleteUnnecessaryScene()
{
	/* �폜�Ώۂ̃V�[�����폜���� */
	// �폜�t���O���L��(�����ꂩ�̃V�[�����폜�ҋ@���)�ł��邩
	if (this->bSceneDeleteFlg == true)
	{
		/* �폜�t���O���L���ȃV�[�������폜 */
		pstSceneList.erase( std::remove_if(pstSceneList.begin(), pstSceneList.end(), [](std::shared_ptr<Scene_Base> pScene)
		{
			/* �폜�t���O���L���ł��邩�m�F�@*/
			if (pScene->bGetDeleteFlg() == true)
			{
				// �L���ł���ꍇ
				/* ��������������� */
				pScene.reset();
				return true;
			}
			else
			{
				// �����ł���ꍇ
				return false;
			}
		}), pstSceneList.end());

		// �V�[���폜�t���O�����ɖ߂�
		this->bSceneDeleteFlg = false;
	}
}

// �V�[���폜(�V�[�����X�g���̂��ׂẴV�[���ɑ΂���)
void SceneServer::DeleteAllScene()
{
	/* �V�[�����X�g���̂��ׂẴV�[�����폜���� */
	// �V�[�����X�g�ɓo�^����Ă��邷�ׂẴV�[�����폜����
	for (auto& Scene : pstSceneList)
	{
		/* ��������������� */
		Scene.reset();
	}

	/* �V�[�����X�g�̃N���A���s�� */
	pstSceneList.clear();
}

// �V�[���폜(�ǉ��\��̃V�[�����X�g���̂��ׂẴV�[���ɑ΂���)
void SceneServer::DeleteAllAddScene()
{
	/* �ǉ��\��̃V�[�����X�g���̂��ׂẴV�[�����폜���� */
	// �ǉ��\��̃V�[�����X�g�ɓo�^����Ă��邷�ׂẴV�[�����폜����
	for (auto& Scene : pstAddSceneList)
	{
		/* ��������������� */
		Scene.reset();
	}

	/* �ǉ��\��̃V�[�����X�g�̃N���A���s�� */
	pstAddSceneList.clear();
}

// �f�[�^���X�g�`��(�f�o�b�O�p)
void SceneServer::DrawSceneList()
{
	/* �V�[�����X�g�ɓo�^����Ă���V�[�����̂̕`�� */
	int iIndex = 0;

	DrawBox(0, iIndex * 20, 400, iIndex * 20 + 20, GetColor(0, 255, 0), TRUE);
	DrawString(0, 0, "�V�[����", GetColor(255, 255, 255));
	DrawString(200, 0, "���C���[", GetColor(255, 255, 255));
	iIndex++;
	
	/* �V�[�����X�g�ɓo�^����Ă��邷�ׂẴV�[����`�� */
	for (auto& Scene : pstSceneList)
	{
		DrawBox(0, iIndex * 20, 400, iIndex * 20 + 20, GetColor(0, 255, 0), TRUE);

		/* �V�[�����̂̕`�� */
		DrawString(0, iIndex * 20, Scene->stGetSceneName().c_str(), GetColor(255, 255, 255));

		/* �V�[�����C���[�̕`�� */
		int i = Scene->iGetSceneLayerOrder();
		DrawFormatString(200, iIndex * 20, GetColor(255, 255, 255), "%d", i);

		iIndex++;
	}
};

