/* シーン"UI:神木(防衛対象)の状態"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_GameMain_UI_Status_CoreTree.h"
// 関連クラス
#include "DataList_GameStatus.h"
#include "DataList_Image.h"
// 共通定義
#include "ConstantDefine.h"

// コンストラクタ
Scene_GameMain_UI_Status_CoreTree::Scene_GameMain_UI_Status_CoreTree() : Scene_Base("Scene_GameMain_UI_Status_CoreTree", 100, false, false)
{
	/* データリスト取得 */
	this->pDataList_GameStatus						= std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));	// ゲーム状態管理
	std::shared_ptr<DataList_Image>	pDataList_Image	= std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));			// 画像管理

	/* 使用する画像を設定 */
	std::string fileName		= "UI/Tree_Image";
	this->piGrHandle_TreeImage	= pDataList_Image->iGetGrhandle(fileName);	// 木の画像
}

// 描画
void Scene_GameMain_UI_Status_CoreTree::Draw()
{
	/* 建築モードであるなら描写を行わない */
	if (this->pDataList_GameStatus->GetBuildModeFlg()) { return; }

	/* 木の画像を描写 */
	DrawGraph(0, 0, *(this->piGrHandle_TreeImage), TRUE);

	/* HPを描写 */
	// HPバーの幅を計算
	int iHpBarWidth_Calc = (int)((float)UI_HPBAR_WIDE * ((float)this->pDataList_GameStatus->GetHp_CoreTree() / (float)this->pDataList_GameStatus->GetMaxHp_CoreTree()));

	// 背景部分の描写
	DrawBox(UI_HPBAR_POS_X - UI_HPBAR_BACK_WIDE, UI_HPBAR_POS_Y - UI_HPBAR_BACK_WIDE, UI_HPBAR_POS_X + UI_HPBAR_BACK_WIDE + UI_HPBAR_WIDE, UI_HPBAR_POS_Y + UI_HPBAR_BACK_WIDE + UI_HPBAR_HEIGHT, GetColor(0, 0, 0), TRUE);
	DrawBox(UI_HPBAR_POS_X, UI_HPBAR_POS_Y, UI_HPBAR_POS_X + UI_HPBAR_WIDE, UI_HPBAR_POS_Y + UI_HPBAR_HEIGHT, GetColor(255, 128, 128), TRUE);

	// HPバーの描写
	int iTextX = UI_HPBAR_POS_X + (UI_HPBAR_WIDE / 2) - 72;
	int iTextY = UI_HPBAR_POS_Y + (UI_HPBAR_HEIGHT / 2) - (BASE_FONT_SIZE / 2);
	DrawBox(UI_HPBAR_POS_X, UI_HPBAR_POS_Y, UI_HPBAR_POS_X + iHpBarWidth_Calc, UI_HPBAR_POS_Y + UI_HPBAR_HEIGHT, GetColor(255, 0, 0), TRUE);
	DrawFormatString(iTextX, iTextY, GetColor(255, 255, 255), "%d / %d", this->pDataList_GameStatus->GetHp_CoreTree(), this->pDataList_GameStatus->GetMaxHp_CoreTree());
}
