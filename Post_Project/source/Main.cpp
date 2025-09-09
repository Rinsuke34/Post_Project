/* �v���O�����N�����̏����̒�` */

/* �g�p����v�f�̃C���N���[�h */
// �W�����C�u����
#include <windows.h>
// �O�����C�u����
#include "AppFrame.h"
// �֘A�N���X
#include "Scene_Title.h"
#include "DataList_Image.h"
#include "DataList_Model.h"

// ���C���v���O����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/* AppFrame�̃��C�����[�v�����s */
	Main::MainLoop();

	return 0;
};

// �ȉ��AAppFrame�Ő錾���ꂽ�֐��̒�`
// �V�[���̐ݒ�
namespace SCENE_SET
{
	// �Q�[���N�����̃V�[�����Z�b�g
	void	SetFastScene()
	{
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_Title>());
	}
}

// ������
namespace PROJECT_INIT
{
	// �v���W�F�N�g����������
	void	Init()
	{
		/* �f�[�^���X�g�T�[�o�[�ւ̓o�^ */
		gpDataListServer->AddDataList(std::make_shared<DataList_Image>());					// �摜�f�[�^�Ǘ�
		gpDataListServer->AddDataList(std::make_shared<DataList_Model>());					// 3D���f���Ǘ�
		gpDataListServer->AddDataList(std::make_shared<DataList_2DPartsAnimCreateTool>());	// 2D�p�[�c�A�j���[�V�����쐬�c�[��
	}
}
