/* ���ׂẴV�[���̃x�[�X�ƂȂ�N���X�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// �W�����C�u����
#include <string>
// �O�����C�u����
#include <DxLib.h>

// �V�[���x�[�X�N���X
class Scene_Base
{
	public:
		Scene_Base(const std::string& cName, const int iLayer, const bool bLowerLayerUpdataStopFlg, const bool bUpperLayerDrawStopFlg);	// �R���X�g���N�^
		virtual ~Scene_Base() {};	// �f�X�g���N�^

		/* �֐� */
		virtual void	Update()			{};	// �X�V
		virtual void	Draw()				{};	// �`��

		/* �Z�b�^�[ */
		void	SetDeleteFlg(bool bDeleteFlg)	{ this->bDeleteFlg = bDeleteFlg; }		// �폜�t���O��ݒ�(�L���Ȃ�΃V�[�����폜����)

		/* �Q�b�^�[ */
		bool	bGetDeleteFlg()					{ return this->bDeleteFlg; };				// �폜�t���O���擾
		int		iGetSceneLayerOrder()			{ return this->iLayerOrder; };				// ���C���[�������擾
		bool	bGetLowerLayerUpdateStopFlg()	{ return this->bLowerLayerUpdataStopFlg; }	// ���w���C���[�v�Z��~�t���O���擾
		bool	bGetUpperLayerDrawStopFlg()		{ return this->bUpperLayerDrawStopFlg; }	// ��w���C���[�`�ʒ�~�t���O���擾
		std::string	stGetSceneName()			{ return this->stSceneName; }				// �V�[�����̂��擾

	protected:
		/* �ϐ� */
		// SceneServer�ł̊Ǘ��p�f�[�^
		std::string		stSceneName;					// �V�[������
		int				iLayerOrder;					// ���C���[����(�l���傫���قǎ�O�ɕ`��)
		bool			bLowerLayerUpdataStopFlg;		// ���w���C���[�v�Z��~�t���O(�L���Ȃ牺�w���C���[�Ōv�Z���s��Ȃ�)
		bool			bUpperLayerDrawStopFlg;			// ��w���C���[�`�ʒ�~�t���O(�L���Ȃ��w���C���[�̕`����s��Ȃ�)
		bool			bDeleteFlg;						// �폜�t���O(�L���Ȃ�V�[�����폜)
};
