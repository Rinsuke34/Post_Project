/* �V�[��"UI(�e�[�u��)"�̐錾 */

#pragma once
#include <vector>
#include "SceneBase.h"
#include "AppVariableDefine.h"

// �V�[��"UI(�e�[�u��)"
class Scene_UI_Table : public SceneBase
{
	public:
		Scene_UI_Table(int iTableWidth, int iDrawPosX, int iDrawPosY, std::string TableName);	// �R���X�g���N�^
		virtual ~Scene_UI_Table();		// �f�X�g���N�^

		/* �֐� */
		virtual void	Update()			override;	// �X�V
		virtual void	Draw()				override;	// �`��

		/* �Z�b�^�[ */
		void SetElement(std::vector<std::string> vecElement) { this->vecElement = vecElement; }	// �v�f��ݒ�

		/* �Q�b�^�[ */
		int		iGetSelectElementIndex()	const { return this->iSelectElementIndex; }	// �I�𒆂̗v�f�̔ԍ����擾
		bool	bGetTableSelectedFlg()		const { return this->bTableSelectedFlg; }	// �e�[�u�����I����Ԃł��邩�̃t���O���擾

	private:
		/* �ϐ� */
		int		iTableWidth;				// �e�[�u���̕�
		int		iDrwawPosX;					// �`��ʒuX
		int		iDrwawPosY;					// �`��ʒuY
		int		iSelectElementIndex;		// �I�𒆂̗v�f�̔ԍ�
		bool	bTableSelectedFlg;			// ���̃e�[�u�����I����Ԃł��邩�̃t���O

		std::string					TableName;		// �e�[�u����
		std::vector<std::string>	vecElement;		// �e�[�u���̗v�f
};
