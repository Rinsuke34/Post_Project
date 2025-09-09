/* �f�[�^���X�g"�ėp2D�p�[�c�A�j���[�V�����c�[��"�N���X�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// ���N���X
#include "DataList_Base.h"
// ���ʒ�`
#include "AppStructDefine.h"

// �f�[�^���X�g"�ėp2D�p�[�c�A�j���[�V�����c�[��"�N���X
class DataList_2DPartsAnimCreateTool : public DataList_Base
{
	public:
		DataList_2DPartsAnimCreateTool();			// �R���X�g���N�^
		virtual ~DataList_2DPartsAnimCreateTool();	// �f�X�g���N�^

		/* �萔 */
		static const int SCREEN_SIZE_WIDE	= 0;	// �`��p�X�N���[���̕�
		static const int SCREEN_SIZE_HEIGHT	= 1;	// �`��p�X�N���[���̍���
		static const int SCREEN_SIZE_MAX	= 2;	// �`��p�X�N���[���̃T�C�Y�̌�

		/* �֐� */
		void	DrawPartsAnim(std::string FileName, std::string AnimDame, int iFrame);		// �p�[�c�A�j���[�V�����̕`��

		/* �Z�b�^�[ */
		void	LoadPartsAnimData(std::string FileName);									// �p�[�c�A�j���[�V�����̃f�[�^�ǂݍ���
		void	SetDrawScreenSize(int iWide, int iHeight);									// �`��p�X�N���[���̃T�C�Y�ݒ�

		/* �Q�b�^�[ */
		int		iGetPartsAnimMaxTime(std::string FileName, std::string AnimDame);			// �p�[�c�A�j���[�V�����̍ő�t���[�����擾

	private:
		/* �ϐ� */
		std::vector<Struct_2DPartsAnim::PARTS_ANIM_DATA>	PartsAnimDataList;					// �p�[�c�A�j���[�V�����̏�񃊃X�g
		int													iDrawScreenSize[SCREEN_SIZE_MAX];	// �`��p�X�N���[���̃T�C�Y(0:��, 1:����)
};
