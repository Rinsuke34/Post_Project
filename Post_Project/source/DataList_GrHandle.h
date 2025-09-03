/* �f�[�^���X�g"�摜�f�[�^�Ǘ�"�N���X�̐錾 */

#pragma once
#include "AppFrame.h"

// �f�[�^���X�g"�摜�f�[�^�Ǘ�"�N���X
class DataList_GrHandle : public DataList_Base
{
	public:
		DataList_GrHandle();			// �R���X�g���N�^
		virtual ~DataList_GrHandle();	// �f�X�g���N�^

		/* �֐� */
		void	LoadGrHandle(std::string& cFileName);				// �摜�f�[�^�ǂݍ���
		void	LoadGrHandle_2DPartsAnim(std::string& cFileName);	// �摜�f�[�^�ǂݍ���(2D�p�[�c�A�j���[�V�����p)
		int		iGetGrhandle(std::string& cFileName);				// �摜�f�[�^�擾

	private:
		/* �ϐ� */
		// ���X�g
		std::map<std::string, int> pGrHandleList;		// �摜�f�[�^���X�g

		/* �֐� */
		bool	bCheckGrHandle(std::string& cFileName);	// �Y���摜�n���h���f�[�^���݊m�F
};
