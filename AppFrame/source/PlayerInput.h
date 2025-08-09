/* プレイヤーの入力を取得するクラスの宣言 */

#pragma once
#include <DxLib.h>
#include <cstring>

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
