/* シーン"ゲームオーバー(フェードアウト)"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_GameOver_Fadeout.h"
// 関連クラス
#include "Scene_GameOver.h"

// コンストラクタ
Scene_GameOver_Fadeout::Scene_GameOver_Fadeout() : Scene_Base("Scene_GameOver_Fadeout", 2000, true, false)
{
	/* 初期化 */
	this->iFadeAlpha = 0;
}

// 更新
void Scene_GameOver_Fadeout::Update()
{
	/* フェードアウト処理 */
	this->iFadeAlpha += 2;
	if (this->iFadeAlpha >= 255)
	{
		/* シーン"ゲームオーバー"を作成 */
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_GameOver>());

		return;
	}
}

// 描画
void Scene_GameOver_Fadeout::Draw()
{
	/* フェードアウト描写 */
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, this->iFadeAlpha);
	DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
