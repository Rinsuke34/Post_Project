/* �V�[��"�X�e�[�W"�̐錾 */

#pragma once

/* �g�p����v�f�̃C���N���[�h */
// ���ʒ�`
#include "AppFrame.h"

/* �O���錾 */
class DataList_Object;
class DataList_GameStatus;
class DataList_StageCreate;

// �V�[��"�X�e�[�W"
class Scene_Stage : public Scene_Base
{
	public:
		Scene_Stage();				// �R���X�g���N�^
		virtual ~Scene_Stage();		// �f�X�g���N�^

		/* �N���X���Ŏg�p����萔 */
		// �V���h�E�}�b�v�̎��
		static const int SHADOWMAP_GROUND	= 0;	// �ÓI�I�u�W�F�N�g
		static const int SHADOWMAP_ACTOR	= 1;	// ���I�I�u�W�F�N�g
		static const int SHADOWMAP_MAX		= 2;	// �V���h�E�}�b�v�̎�ނ̌�

		/* �֐� */
		virtual void	Update()			override;	// �X�V
		virtual void	Draw()				override;	// �`��

	private:
		/* �֐� */
		// �ǂݍ��݊֌W
		void	JsonLoad_WoldMap_Center();	// ���[���h�}�b�v�ǂݍ���(����)
		void	JsonLoad_DungeonMap();		// �_���W�����}�b�v�ǂݍ���
		// �`�ʊ֌W
		void	DrawSetup_CameraPosition();		// �J�����ݒ�
		void	DrawSetup_ShadowMap();			// �V���h�E�}�b�v�쐬
		void	DrawSetup_Stage();				// �X�e�[�W�̕`��
		void	DrawSetup_Stage_StageCreate();	// �X�e�[�W�̕`��(�X�e�[�W�N���G�C�g�p)
		

		/* �ϐ� */
		// �f�[�^���X�g�ւ̃|�C���^
		std::shared_ptr<DataList_Object>		pDataList_Object;		// �I�u�W�F�N�g�Ǘ�
		std::shared_ptr<DataList_GameStatus>	pDataList_GameStatus;	// �Q�[����ԊǗ�
		std::shared_ptr<DataList_StageCreate>	pDataList_StageCreate;	// �X�e�[�W�N���G�C�g���Ǘ�
		// �摜�f�[�^
		int iScreenHandle_Stage;					// �X�e�[�W
		int iScreenHandle_ShadowMap[SHADOWMAP_MAX];	// �V���h�E�}�b�v(0:�ÓI�I�u�W�F�N�g/1:���I�I�u�W�F�N�g)
};
