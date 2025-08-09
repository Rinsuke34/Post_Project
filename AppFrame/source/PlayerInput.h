/* 2024.12.08 駒沢風助 ファイル作成 */

#pragma once
#include <DxLib.h>
#include <cstring>

/* プレイヤーの入力を取得するクラスの宣言 */

// 入力取得クラス
class PlayerInput
{
	public:
		PlayerInput();					// コンストラクタ
		virtual ~PlayerInput() {};		// デストラクタ

		void	Input();				// プレイヤーの入力取得

	private:
		/* プレイヤー入力取得系 */
		void	InputJoypad();			// ジョイパッド
		void	InputKeyboard();		// キーボード＆マウス

	protected:
};
