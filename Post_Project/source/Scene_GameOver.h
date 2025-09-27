/* シーン"ゲームオーバー"の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"

/* 前方宣言 */
class DataList_GameStatus;

// シーン"ゲームオーバー"
class Scene_GameOver : public Scene_Base
{
	public:
		Scene_GameOver();				// コンストラクタ
		virtual ~Scene_GameOver() {};	// デストラクタ

		/* 関数 */
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描画

	private:
		/* 定数 */
		static const int OFFSET_X = 100;	// 左右のオフセット値
		static const int OFFSET_Y = 100;	// 上下のオフセット値

		/* 変数 */
		std::shared_ptr<DataList_GameStatus>	pDataList_GameStatus;	// ゲーム状態管理
};
