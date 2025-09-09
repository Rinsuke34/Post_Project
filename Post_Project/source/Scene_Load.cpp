/* シーン"ロード画面"の定義 */

#pragma once

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_Load.h"

// コンストラクタ
Scene_Load::Scene_Load() : Scene_Base("Scene_Load", 99999, true, true)
{

}

// デストラクタ
Scene_Load::~Scene_Load()
{

}

// 更新
void Scene_Load::Update()
{
	/* 非同期読み込み中の処理が完了しているか確認 */
	if (GetASyncLoadNum() == 0)
	{
		// 完了している場合
		/* シーンの削除フラグを有効にする */
		this->bDeleteFlg = true;

		return;
	}
}

// 描画
void Scene_Load::Draw()
{
	DrawString(16, 16, "Now Loading...", GetColor(255, 255, 255));
}
