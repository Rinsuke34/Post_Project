/* �L��ϐ��̐錾 */

#pragma once
/* �g�p����v�f�̃C���N���[�h */
// �W�����C�u����
#include <vector>
#include <memory>
// ���ʒ�`
#include "AppStructDefine.h"

/* �O���錾 */
class Fps;
class PlayerInput;
class SceneServer;
class DataListServer;

/* �v���O������� */
extern bool gbEndFlg;	// �v���O�����I���t���O

/* �v���C���[�̓��͏�� */
extern Struct_Input::PLAYER_INPUT_JOYPAD			gstJoypadInputData;				// �W���C�p�b�h
extern Struct_Input::PLAYER_INPUT_KEYBOARD_MOUSE	gstKeyboardInputData;			// �L�[�{�[�h���}�E�X
extern unsigned char								gucTriggerThreshold;			// �g���K�[���͂�臒l
extern bool											gbMouseCursorCenterFixedFlg;	// �}�E�X�̒��S�Œ�t���O(�L���ł���Ȃ�΃}�E�X�J�[�\������ʒ����ɌŒ肷��)
extern bool											gbMouseCursorNotDepictedFlg;	// �}�E�X�J�[�\���`�ʖ����t���O(�L���ł���Ȃ�΃}�E�X�J�[�\����`�ʂ��Ȃ�)


/* ���s���N���X */
extern std::unique_ptr<Fps>				gpFps;					// fps�Œ�p�N���X
extern std::unique_ptr<PlayerInput>		gpPlayerInput;			// �v���C���[���͎擾�N���X
extern std::unique_ptr<SceneServer>		gpSceneServer;			// �V�[���T�[�o�[�N���X
extern std::unique_ptr<DataListServer>	gpDataListServer;		// �f�[�^���X�g�T�[�o�[�N���X

/* �t���[�����[�g�֘A */
extern int giNowFps;							// ���݂̃t���[�����[�g

/* �f�o�b�O�p�`�ʊǗ��t���O */
extern bool gbDrawSceneListFlg;					// �V�[�����X�g�̕`��
extern bool	gbDrawDatalistFlg;					// �v���C���[�X�e�[�^�X�̕`��
extern bool gbDrawFpsFlg;						// �t���[�����[�g�̕`��

