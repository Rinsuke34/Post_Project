/* �v���O�����N�����̏����̒�` */

#include <windows.h>
#include "AppFrame.h"
#include "Scene_Title.h"

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
		/* �f�[�^���X�g�T�[�o�[��"�v���C���[���͊Ǘ�"��ǉ� */
		//gpDataListServer->AddDataList(new DataList_Input());

		/* ���ǉ�����"�v���C���[���͊Ǘ�"���擾 */
		//gpDataList_Input = dynamic_cast<DataList_Input*>(gpDataListServer->GetDataList("DataList_Input"));
	}
}
