/* ���ׂẴf�[�^���X�g�̃x�[�X�ƂȂ�N���X�̐錾 */

#pragma once
#include <DxLib.h>
#include <string>

// �f�[�^���X�g�x�[�X�N���X
class DataListBase
{
	public:
		DataListBase(const std::string& cName);		// �R���X�g���N�^
		virtual ~DataListBase() {};					// �f�X�g���N�^

		/* �Q�b�^�[ */
		std::string	stGetDataListName()	{ return this->stDataListName; }	// �f�[�^���X�g���̂��擾

	private:

		/* �ϐ� */
		// DataListServer�ł̊Ǘ��p�f�[�^
		std::string		stDataListName;			// �f�[�^���X�g����
};
