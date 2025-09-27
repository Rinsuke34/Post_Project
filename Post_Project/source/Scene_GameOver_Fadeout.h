/* シーン"ゲームオーバー(フェードアウト)"の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"

// シーン"ゲームオーバー(フェードアウト)"
// ※フェードアウト完了後、ゲームオーバー画面へ遷移
class Scene_GameOver_Fadeout : public Scene_Base
{
	public:
		Scene_GameOver_Fadeout();				// コンストラクタ
		virtual ~Scene_GameOver_Fadeout() {};	// デストラクタ

		/* 関数 */
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描画

	private:
		/* 変数 */
		int iFadeAlpha; // フェードアウトのアルファ値
};
