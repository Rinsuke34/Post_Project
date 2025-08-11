/* �V�[��"�ėp2D�p�[�c�A�j���[�V�����c�[��"�̒�` */

#include "Scene_2DPartsAnimCreateTool.h"

#include "AppVariableDefine.h"
#include "AppFunctionDefine.h"

// �R���X�g���N�^
Scene_2DPartsAnimCreateTool::Scene_2DPartsAnimCreateTool() : SceneBase("Scene_2DPartsAnimCreateTool", 9999, true)
{

}

// �f�X�g���N�^
Scene_2DPartsAnimCreateTool::~Scene_2DPartsAnimCreateTool()
{

}

// �v�Z
void Scene_2DPartsAnimCreateTool::Process()
{
	/* ���͑҂� */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_Z] == TRUE)
	{
		/* �_�C�A���O��\�� */
		std::string path = PUBLIC_FUNCTION::aOpenFileDialog(".png");

		/* �p�X���擾���ꂽ���m�F */
		if (!path.empty())
		{
			// �擾���ꂽ�ꍇ
			/* �摜�̃O���t�B�b�N�n���h�����擾 */
			int iGrHandle = LoadGraph(path.c_str());

			/* �O���t�B�b�N�n���h�����擾�ł������m�F */
			if (iGrHandle != -1)
			{
				// �O���t�B�b�N�n���h�����擾�ł����ꍇ
				/* �I�������摜�̃O���t�B�b�N�n���h���ƃp�X��ۑ� */
				this->iSelectGrHandle.push_back(iGrHandle);
				this->stSelectGrPath.push_back(path);
			}
		}
	}
}

// �`��
void Scene_2DPartsAnimCreateTool::Draw()
{
	/* �I�������摜�̃O���t�B�b�N�n���h����`�� */
	for (int iIndex = 0; iIndex < this->iSelectGrHandle.size(); ++iIndex)
	{
		DrawString(iIndex * 100, 0, this->stSelectGrPath[iIndex].c_str(), GetColor(255, 255, 255));
		DrawGraph(iIndex * 100, 20, this->iSelectGrHandle[iIndex], FALSE);
	}
}


