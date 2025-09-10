/* �f�[�^���X�g"�摜�f�[�^�Ǘ�"�N���X�̐錾 */

#pragma once
/* �g�p����v�f�̃C���N���[�h */
// ���ʒ�`
#include "AppFrame.h"
#include "StructDefine.h"

// �f�[�^���X�g"�摜�f�[�^�Ǘ�"�N���X
class DataList_Image : public DataList_Base
{
	public:
		DataList_Image();			// �R���X�g���N�^
		virtual ~DataList_Image();	// �f�X�g���N�^

		/* �֐� */
		void					LoadGrHandle(std::string& cFileName);				// �摜�f�[�^�ǂݍ���
		std::shared_ptr<int>	iGetGrhandle(std::string& cFileName);				// �摜�f�[�^�擾

		/* �Z�b�^�[ */
		void	AddTexture(TEXTURE_DATA stTexture) { this->TextureDataList.push_back(stTexture); };	// �e�N�X�`���f�[�^�ǉ�

		/* �Q�b�^�[ */
		std::vector<TEXTURE_DATA>& GetTextureDataList() { return this->TextureDataList; }		// �e�N�X�`���f�[�^���X�g�擾

	private:
		/* �ϐ� */
		// ���X�g
		std::map<std::string, int>	GrHandleList;		// �摜�f�[�^���X�g
		std::vector<TEXTURE_DATA>	TextureDataList;	// �e�N�X�`�����X�g

		/* �֐� */
		bool	bCheckGrHandle(std::string& cFileName);	// �Y���摜�n���h���f�[�^���݊m�F
		void	JsonLoad_Texture();						// �e�N�X�`���ǂݍ���
};
