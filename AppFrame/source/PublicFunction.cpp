/* �ėp�I�Ɏg�p�ł���@�\�̒�` */

#include "AppFunctionDefine.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdio>
#include <Windows.h>

// �w��t�@�C�������S�ɍ폜����܂őҋ@
void PUBLIC_FUNCTION::FileDeletesAndStand(const std::string& filename)
{
	// ����
	// filename	<- �폜����t�@�C����

	/* �폜�����t���O */
	bool bDeleteCompleteFlg = false;

	/* �w��t�@�C�����폜 */
	std::remove(filename.c_str());

	/* �t�@�C�����폜�����܂őҋ@ */
	while (bDeleteCompleteFlg == false)
	{
		/* �t�@�C�����J���邩�m�F */
		std::ifstream file(filename);
		if (file.is_open())
		{
			// �t�@�C�����J����ꍇ
			/* �ҋ@ */
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		else
		{
			// �t�@�C�����J���Ȃ��ꍇ
			/* �폜�����t���O�𗧂Ă� */
			bDeleteCompleteFlg = true;
		}
	}
}

// �t�@�C���I���_�C�A���O��\��
std::string	PUBLIC_FUNCTION::aOpenFileDialog(std::string Filter)
{
	// ����
	// Filter	<- �t�@�C���I���_�C�A���O�̃t�B���^�[������(��F"*.png;*.jpg;*.bmp")
	// �߂�l
	// std::string	<- �I�����ꂽ�t�@�C���̃p�X(�I������Ȃ������ꍇ�͋󕶎���)

	/* DX���C�u�����̃E�B���h�E�n���h�����擾 */
	HWND WindHwnd = GetMainWindowHandle();

	/* �_�C�A���O�쐬 */
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize		= sizeof(ofn);
	ofn.hwndOwner		= WindHwnd; // DX���C�u�����̃E�B���h�E��e�ɐݒ�
	ofn.lpstrFile		= new char[MAX_PATH];
	ofn.nMaxFile		= MAX_PATH;
	ofn.lpstrFilter		= Filter.c_str();
	ofn.nFilterIndex	= 1;
	ofn.lpstrFile[0]	= '\0'; // ������
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;

	/* �_�C�A���O�\�� */
	if (GetOpenFileName(&ofn))
	{
		// �t�@�C�����I�����ꂽ�ꍇ
		std::string selectedFile = ofn.lpstrFile;
		delete[] ofn.lpstrFile;

		/* �I�����ꂽ�t�@�C���̃p�X��Ԃ� */
		return selectedFile;
	}

	return "";
}

#include "AppVariableDefine.h"
#include "Scene_2DPartsAnimCreateTool.h"

// 2D�p�[�c�A�j���[�V�����쐬�c�[���̋N��
void PUBLIC_FUNCTION::Start2DPartsAnimCreateTool()
{
	// �V�[��"�ėp2D�p�[�c�A�j���[�V�����c�[��"��ǉ��\��
	gpSceneServer->AddSceneReservation(std::make_shared<Scene_2DPartsAnimCreateTool>());
}
