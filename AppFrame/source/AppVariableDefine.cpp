/* 2024.12.08 駒沢風助 ファイル作成 */

#include "AppVariableDefine.h"

/* 広域変数の初期化 */

/* プログラム状態 */
bool gbEndFlg	= false;	// プログラム終了フラグ

/* プレイヤーの入力情報 */
Struct_Input::PLAYER_INPUT_JOYPAD			gstJoypadInputData;					// ジョイパッド
Struct_Input::PLAYER_INPUT_KEYBOARD_MOUSE	gstKeyboardInputData;				// キーボード＆マウス
bool										gbUseMouseFlg			= true;	// マウス使用フラグ(有効であるならばカーソルを描写＆中心固定解除)
unsigned char								gucTriggerThreshold		= 0;		// トリガー入力の閾値

/* 実行中クラス */
std::unique_ptr<Fps>			gpFps				= nullptr;	// fps固定用クラス
std::unique_ptr<PlayerInput>	gpPlayerInput		= nullptr;	// プレイヤー入力取得クラス
std::unique_ptr<SceneServer>	gpSceneServer		= nullptr;	// シーンサーバークラス
std::unique_ptr<DataListServer> gpDataListServer	= nullptr;	// データリストサーバークラス

/* フレームレート関連 */
int	giNowFps	= 0;						// 現在のフレームレート

/* デバッグ用描写管理フラグ */
bool gbDrawSceneListFlg		= false;		// シーンリストの描写
bool gbDrawDatalistFlg		= false;		// データリストの描写
bool gbDrawFpsFlg			= true;			// フレームレートの描写
