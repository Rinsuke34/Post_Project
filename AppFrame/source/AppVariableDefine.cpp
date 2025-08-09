/* �L��ϐ��̏����� */

#include "AppVariableDefine.h"

/* �v���O������� */
bool gbEndFlg	= false;	// �v���O�����I���t���O

/* �v���C���[�̓��͏�� */
Struct_Input::PLAYER_INPUT_JOYPAD			gstJoypadInputData;						// �W���C�p�b�h
Struct_Input::PLAYER_INPUT_KEYBOARD_MOUSE	gstKeyboardInputData;					// �L�[�{�[�h���}�E�X
unsigned char								gucTriggerThreshold			= 0;		// �g���K�[���͂�臒l
bool										gbMouseCursorCenterFixedFlg	= false;	// �}�E�X�̒��S�Œ�t���O(�L���ł���Ȃ�΃}�E�X�J�[�\������ʒ����ɌŒ肷��)
bool										gbMouseCursorNotDepictedFlg	= false;	// �}�E�X�J�[�\���`�ʖ����t���O(�L���ł���Ȃ�΃}�E�X�J�[�\����`�ʂ��Ȃ�)

/* ���s���N���X */
std::unique_ptr<Fps>			gpFps				= nullptr;	// fps�Œ�p�N���X
std::unique_ptr<PlayerInput>	gpPlayerInput		= nullptr;	// �v���C���[���͎擾�N���X
std::unique_ptr<SceneServer>	gpSceneServer		= nullptr;	// �V�[���T�[�o�[�N���X
std::unique_ptr<DataListServer> gpDataListServer	= nullptr;	// �f�[�^���X�g�T�[�o�[�N���X

/* �t���[�����[�g�֘A */
int	giNowFps	= 0;						// ���݂̃t���[�����[�g

/* �f�o�b�O�p�`�ʊǗ��t���O */
bool gbDrawSceneListFlg		= false;		// �V�[�����X�g�̕`��
bool gbDrawDatalistFlg		= false;		// �f�[�^���X�g�̕`��
bool gbDrawFpsFlg			= true;			// �t���[�����[�g�̕`��
