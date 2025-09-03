/* ���s���̃V�[���̊Ǘ����s���N���X�̐錾 */

#pragma once
#include "SceneBase.h"
#include <list>
#include <memory>

// �V�[���T�[�o�[�N���X
class SceneServer
{
	public:
		SceneServer();				// �R���X�g���N�^
		virtual ~SceneServer();		// �f�X�g���N�^

		/* �֐� */
		void	SceneProcess();		// �V�[���v�Z����
		void	SceneDraw();		// �V�[���`�揈��
		void	DrawSceneList();	// �f�[�^���X�g�`��(�f�o�b�O�p)

		/* �Z�b�^�[ */
		void	AddSceneReservation(std::shared_ptr<SceneBase> NewScene);															// �V�[���ǉ��\��
		void	SetDeleteCurrentSceneFlg(bool bDeleteCurrentSceneFlg) { this->bDeleteCurrentSceneFlg = bDeleteCurrentSceneFlg; };	// �V�[���ǉ����̌��s�V�[���폜�t���O�ݒ�

		/* �Q�b�^�[ */
		std::shared_ptr<SceneBase>	GetScene(const std::string& cName);		// �V�[���擾
		
	private:
		/* �V�[�����X�g */
		std::list<std::shared_ptr<SceneBase>> pstSceneList;

		/* �ǉ��\��̃V�[�����X�g */
		std::list<std::shared_ptr<SceneBase>> pstAddSceneList;

		/* �֐� */
		void	AddScene();						// �V�[�����X�g�ւ̃V�[���ǉ�
		void	SceneSortLayerOrder();			// �V�[�����X�g�̕��ёւ�(���C���[�����̑傫����)
		void	DeleteUnnecessaryScene();		// �V�[���폜(�폜�t���O���L���ȃV�[���ɑ΂���)
		void	DeleteAllScene();				// �V�[���폜(�V�[�����X�g���̂��ׂẴV�[���ɑ΂���)
		void	DeleteAllAddScene();			// �V�[���폜(�ǉ��\��̃V�[�����X�g���̂��ׂẴV�[���ɑ΂���)

		/* �ϐ� */
		bool	bSceneDeleteFlg;			// �V�[���폜�t���O(�폜�\��̃V�[��������Ȃ�ΗL���ɂ���)
		bool	bSceneAddFlg;				// �V�[���ǉ��t���O(�ǉ��\��̃V�[��������Ȃ�ΗL���ɂ���)
		bool	bDeleteCurrentSceneFlg;		// ���s�V�[���폜�t���O(�V�[�����X�g���̂��ׂẴV�[�����폜���邩�̃t���O)
};
