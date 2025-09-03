/* �f�[�^���X�g"3D���f���Ǘ�"�N���X�̐錾 */

#pragma once
#include "AppFrame.h"

// �f�[�^���X�g"3D���f���Ǘ�"�N���X
class DataList_Model : public DataList_Base
{
	public:
		DataList_Model();			// �R���X�g���N�^
		virtual ~DataList_Model();	// �f�X�g���N�^

		/* �֐� */
		void	LoadModel(std::string modelName);			// 3D���f�����[�h(���O�ǂݍ��ݗp)
		int		iGetModel(std::string modelName);			// 3D���f���擾

	private:
		/* �ϐ� */
		// ���X�g
		std::map<std::string, int>	pModelHandleList;		// 3D���f�����X�g

		/* �֐� */
		bool	bCheckModel(std::string modelName);			// �Y��3D���f�����݊m�F
};
