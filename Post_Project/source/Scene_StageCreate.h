/* シーン"ステージ作成"の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"

/* 前方宣言 */
class DataList_Object;
class DataList_StageCreate;

// シーン"ステージ作成"
class Scene_StageCreate : public Scene_Base
{
	public:
		Scene_StageCreate();			// コンストラクタ
		virtual ~Scene_StageCreate();	// デストラクタ

		/* 関数 */
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描画

	private:
		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_Object>		pDataList_Object;		// オブジェクト管理
		std::shared_ptr<DataList_StageCreate>	pDataList_StageCreate;	// ステージクリエイト情報管理
};
