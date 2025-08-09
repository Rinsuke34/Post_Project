/* 2024.12.08 駒沢風助 ファイル作成 */

#pragma once
#include <vector>
#include <memory>

#include "AppStructDefine.h"
#include "Fps.h"
#include "PlayerInput.h"
#include "SceneServer.h"
#include "DataListServer.h"

/* 広域変数の宣言 */

/* プログラム状態 */
extern bool gbEndFlg;	// プログラム終了フラグ

/* プレイヤーの入力情報 */
extern Struct_Input::PLAYER_INPUT_JOYPAD			gstJoypadInputData;			// ジョイパッド
extern Struct_Input::PLAYER_INPUT_KEYBOARD_MOUSE	gstKeyboardInputData;		// キーボード＆マウス
extern bool											gbUseMouseFlg;				// マウス使用フラグ(有効であるならばカーソルを描写＆中心固定解除)
extern unsigned char								gucTriggerThreshold;		// トリガー入力の閾値

/* 実行中クラス */
extern std::unique_ptr<Fps>				gpFps;					// fps固定用クラス
extern std::unique_ptr<PlayerInput>		gpPlayerInput;			// プレイヤー入力取得クラス
extern std::unique_ptr<SceneServer>		gpSceneServer;			// シーンサーバークラス
extern std::unique_ptr<DataListServer>	gpDataListServer;		// データリストサーバークラス

/* フレームレート関連 */
extern int giNowFps;							// 現在のフレームレート

/* デバッグ用描写管理フラグ */
extern bool gbDrawSceneListFlg;					// シーンリストの描写
extern bool	gbDrawDatalistFlg;					// プレイヤーステータスの描写
extern bool gbDrawFpsFlg;						// フレームレートの描写

