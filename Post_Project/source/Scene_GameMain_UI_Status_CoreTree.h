/* シーン"UI:神木(防衛対象)の状態"の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"

/* 前方宣言 */
class DataList_GameStatus;

// シーン"UI:神木(防衛対象)の状態"
class Scene_GameMain_UI_Status_CoreTree : public Scene_Base
{
	public:
		Scene_GameMain_UI_Status_CoreTree();				// コンストラクタ
		virtual ~Scene_GameMain_UI_Status_CoreTree() {};	// デストラクタ

		/* 関数 */
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描画

	private:
		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_GameStatus>	pDataList_GameStatus;	// ゲーム状態管理		
};
