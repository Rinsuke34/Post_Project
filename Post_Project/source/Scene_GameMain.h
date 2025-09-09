/* シーン"ゲームメイン"の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"

/* 前方宣言 */
class DataList_Object;
class DataList_GameStatus;

// シーン"ゲームメイン"
class Scene_GameMain : public Scene_Base
{
	public:
		Scene_GameMain();				// コンストラクタ
		virtual ~Scene_GameMain();		// デストラクタ

		/* 関数 */
		virtual void	Update()			override;	// 更新

	private:
		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_Object>		pDataList_Object;		// オブジェクト管理
		std::shared_ptr<DataList_GameStatus>	pDataList_GameStatus;	// ゲーム状態管理
};
