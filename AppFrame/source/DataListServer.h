/* �f�[�^���䏈���̊Ǘ����s���N���X�̐錾 */

#pragma once
#include "DataListBase.h"
#include <list>
#include <memory>

// �f�[�^���X�g�T�[�o�[�N���X
class DataListServer
{
	public:
		DataListServer() {};			// �R���X�g���N�^
		virtual ~DataListServer();		// �f�X�g���N�^

		void	DrawDataList();			// �f�[�^���X�g�`��(�f�o�b�O�p)

		void							AddDataList(std::shared_ptr<DataListBase> NewDataList);		// �f�[�^���X�g�ǉ�
		void							DeleteDataList(const std::string& cName);					// �w��f�[�^���X�g�폜
		std::shared_ptr<DataListBase>	GetDataList(const std::string& cName);						// �f�[�^���X�g�擾

	private:
		// �f�[�^���X�g�ꗗ
		std::list<std::shared_ptr<DataListBase>> pstDataList;

		/* �֐� */
		void	DeleteAllDataList();			// �f�[�^���X�g�폜(�f�[�^���X�g�ꗗ���̂��ׂẴf�[�^���X�g�ɑ΂���)

	protected:
};
