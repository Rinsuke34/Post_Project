/* シーン"タイトル"の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"

// シーン"タイトル"
class Scene_Title : public Scene_Base
{
	public:
		Scene_Title();				// コンストラクタ
		virtual ~Scene_Title() {};	// デストラクタ

		/* 関数 */
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描画

	private:
		/* 定数 */
		// キーの種類
		static const int KEY_E		= 0;
		static const int KEY_Q		= 1;
		static const int KEY_W		= 2;
		static const int KEY_A		= 3;
		static const int KEY_S		= 4;
		static const int KEY_D		= 5;
		static const int KEY_MAX	= 6;
		// 選択肢
		static const int SELECT_START_GAME_MAIN					= 0;	// ゲーム開始
		static const int SELECT_START_STAGE_CREATE				= 1;	// ステージ作成
		static const int SELECT_START_2D_PARTS_ANIM_CREATE_TOOL	= 2;	// 2Dパーツアニメーション作成ツール
		static const int SELECT_END								= 3;	// ゲーム終了
		static const int SELECT_MAX								= 4;	// 選択肢の数
		static const int SELECT_POSITION_X						= (SCREEN_SIZE_WIDE / 2) + 200;		// 選択肢の描画位置X
		static const int SELECT_POSITION_Y						= (SCREEN_SIZE_HEIGHT / 2);			// 選択肢の描画位置Y
		
		/* 変数 */
		// 画像
		std::shared_ptr<int>	piGrHandle_Sky;				// 空の画像
		std::shared_ptr<int>	piGrHandle_Title;			// タイトルの画像
		std::shared_ptr<int>	piGrHandle_Tree;			// 木の画像
		std::shared_ptr<int>	piGrHandle_Key[KEY_MAX];	// キーの画像
		// 状態
		int						iSelectIndex;				// 選択中のインデックス
};
