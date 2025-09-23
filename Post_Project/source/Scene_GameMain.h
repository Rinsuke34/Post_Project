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
		/* 定数 */
		static const int SCORE_UPDATE_TIME		= 60;		// スコア更新時間(1秒/フレーム数)
		static const int WAVE_UPDATE_TIME		= 60 * 60;	// ウェーブ更新時間(1分/フレーム数)

		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_Object>		pDataList_Object;		// オブジェクト管理
		std::shared_ptr<DataList_GameStatus>	pDataList_GameStatus;	// ゲーム状態管理
		// ゲーム状態
		int iScoreUpdateTimer;	// スコア更新までのカウントダウン
		int iWaveUpdateTimer;	// ウェーブ更新までのカウントダウン
};
