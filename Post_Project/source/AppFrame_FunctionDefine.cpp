/* AppFrame�Ŏg�p����֐��̒�` */

#include "AppFrame.h"

// �V�[���̐ݒ�
namespace SCENE_SET
{
	// �Q�[���N�����̃V�[�����Z�b�g
	void	SetFastScene()
	{
		//gpSceneServer->AddSceneReservation(new SceneTitle(), true);
	}

	// ���[�h�V�[�����Z�b�g
	void	SetLoadScene()
	{
		//gpSceneServer->AddSceneReservation(new SceneLoad(), false);
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
