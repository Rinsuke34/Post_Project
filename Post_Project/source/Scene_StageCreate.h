/* シーン"ステージ作成"の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"

/* 前方宣言 */
class DataList_StageCreate;

// シーン"ステージ作成"
class Scene_StageCreate : public Scene_Base
{
	public:
		Scene_StageCreate();			// コンストラクタ
		virtual ~Scene_StageCreate();	// デストラクタ

		/* 定数 */
		// フェーズ
		static const int PHASE_SELECT_MAP	= 0;	// マップ選択フェーズ
		static const int PHASE_EDIT_MAP		= 1;	// マップ編集フェーズ
		// 描写座標
		static const int DRAW_MAPNAME_X		= 50;	// マップ名描写位置X
		static const int DRAW_MAPNAME_Y		= 200;	// マップ名描写位置Y

		/* 関数 */
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描画

	private:
		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_StageCreate>	pDataList_StageCreate;	// ステージクリエイト情報管理
		// その他
		int	iNowPhase;			// 現在のフェーズ
		int iSelectMapIndex;	// 選択中のマップのインデックス番号

		/* 関数 */
		void Update_SelectMap();	// マップ選択フェーズの更新
		void Update_EditMap();		// マップ編集フェーズの更新
		void Draw_SelectMap();		// マップ選択フェーズの描写
		void Draw_EditMap();		// マップ編集フェーズの描写
};
