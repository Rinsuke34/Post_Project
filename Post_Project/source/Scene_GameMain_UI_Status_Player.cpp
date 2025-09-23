/* シーン"UI:プレイヤーの状態"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_GameMain_UI_Status_Player.h"
// 関連クラス
#include "DataList_GameStatus.h"
#include "DataList_Image.h"
// 共通定義
#include "ConstantDefine.h"

// コンストラクタ
Scene_GameMain_UI_Status_Player::Scene_GameMain_UI_Status_Player() : Scene_Base("Scene_GameMain_UI_Status_Player", 100, false, false)
{
	/* データリスト取得 */
	this->pDataList_GameStatus						= std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));	// ゲーム状態管理
	std::shared_ptr<DataList_Image>	pDataList_Image	= std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));			// 画像管理

	/* 使用する画像を設定 */
	// 剣
	std::string fileName				= "UI/Wepon_Image_Sowrd";
	this->piGrHandle_Wepon[WEPON_SOWRD]	= pDataList_Image->iGetGrhandle(fileName);
	// 杖
	fileName							= "UI/Wepon_Image_Rod";
	this->piGrHandle_Wepon[WEPON_ROD]	= pDataList_Image->iGetGrhandle(fileName);
}

// 描画
void Scene_GameMain_UI_Status_Player::Draw()
{
	/* 建築モードであるなら描写を行わない */
	if (this->pDataList_GameStatus->GetBuildModeFlg()) { return; }

	/* 武器の状態に応じて描写する武器の種類を設定する。*/ 
	// 近接武器を使用中に設定
	int iWepon_Now	= WEPON_SOWRD;	// 現在の武器
	int iWepon_Next	= WEPON_ROD;	// 切り替え先の武器
	if (!this->pDataList_GameStatus->GetPlayerMeleeFlg())
	{
		// 遠距離武器使用中であるならば
		/* 遠距離武器を使用中に設定 */
		iWepon_Now	= WEPON_ROD;	// 現在の武器
		iWepon_Next	= WEPON_SOWRD;	// 切り替え先の武器
	}

	/* 切り替え先武器アイコン描写 */
	DrawBox(UI_WEPON_NEXT_POS_X, UI_WEPON_NEXT_POS_Y, UI_WEPON_NEXT_POS_X + UI_WEPON_NEXT_WIDE, UI_WEPON_NEXT_POS_Y + UI_WEPON_NEXT_HEIGHT, GetColor(0, 0, 0), TRUE);
	DrawBox(UI_WEPON_NEXT_POS_X + UI_WEPON_NEXT_BACK_WIDE, UI_WEPON_NEXT_POS_Y + UI_WEPON_NEXT_BACK_WIDE, UI_WEPON_NEXT_POS_X + UI_WEPON_NEXT_WIDE - UI_WEPON_NEXT_BACK_WIDE, UI_WEPON_NEXT_POS_Y + UI_WEPON_NEXT_HEIGHT - UI_WEPON_NEXT_BACK_WIDE, GetColor(128, 128, 128), TRUE);
	DrawExtendGraph(UI_WEPON_NEXT_POS_X, UI_WEPON_NEXT_POS_Y, UI_WEPON_NEXT_POS_X + UI_WEPON_NEXT_WIDE, UI_WEPON_NEXT_POS_Y + UI_WEPON_NEXT_HEIGHT, *this->piGrHandle_Wepon[iWepon_Next], TRUE);

	/* 現在の武器アイコン描写 */
	DrawBox(UI_WEPON_NOW_POS_X, UI_WEPON_NOW_POS_Y, UI_WEPON_NOW_POS_X + UI_WEPON_NOW_WIDE, UI_WEPON_NOW_POS_Y + UI_WEPON_NOW_HEIGHT, GetColor(0, 0, 0), TRUE);
	DrawBox(UI_WEPON_NOW_POS_X + UI_WEPON_NOW_BACK_WIDE, UI_WEPON_NOW_POS_Y + UI_WEPON_NOW_BACK_WIDE, UI_WEPON_NOW_POS_X + UI_WEPON_NOW_WIDE - UI_WEPON_NOW_BACK_WIDE, UI_WEPON_NOW_POS_Y + UI_WEPON_NOW_HEIGHT - UI_WEPON_NOW_BACK_WIDE, GetColor(128, 128, 128), TRUE);
	DrawExtendGraph(UI_WEPON_NOW_POS_X, UI_WEPON_NOW_POS_Y, UI_WEPON_NOW_POS_X + UI_WEPON_NOW_WIDE, UI_WEPON_NOW_POS_Y + UI_WEPON_NOW_HEIGHT, *this->piGrHandle_Wepon[iWepon_Now], TRUE);

	/* HP描写 */
	// HPバーの幅を計算
	int iHpBarWidth_Calc = (int)((float)UI_HPBAR_WIDE * ((float)this->pDataList_GameStatus->GetHp_Player() / (float)this->pDataList_GameStatus->GetMaxHp_Player()));
	// 背景部分の描写
	DrawBox(UI_HPBAR_POS_X - UI_HPBAR_BACK_WIDE, UI_HPBAR_POS_Y - UI_HPBAR_BACK_WIDE, UI_HPBAR_POS_X + UI_HPBAR_BACK_WIDE + UI_HPBAR_WIDE, UI_HPBAR_POS_Y + UI_HPBAR_BACK_WIDE + UI_HPBAR_HEIGHT, GetColor(0, 0, 0), TRUE);
	DrawBox(UI_HPBAR_POS_X, UI_HPBAR_POS_Y, UI_HPBAR_POS_X + UI_HPBAR_WIDE, UI_HPBAR_POS_Y + UI_HPBAR_HEIGHT, GetColor(255, 128, 128), TRUE);
	// HPバーの描写
	int iTextX = UI_HPBAR_POS_X + (UI_HPBAR_WIDE / 2) - 72;
	int iTextY = UI_HPBAR_POS_Y + (UI_HPBAR_HEIGHT / 2) - (BASE_FONT_SIZE / 2);
	DrawBox(UI_HPBAR_POS_X, UI_HPBAR_POS_Y, UI_HPBAR_POS_X + iHpBarWidth_Calc, UI_HPBAR_POS_Y + UI_HPBAR_HEIGHT, GetColor(255, 0, 0), TRUE);
	DrawFormatString(iTextX, iTextY, GetColor(255, 255, 255), "%d / %d", this->pDataList_GameStatus->GetHp_Player(), this->pDataList_GameStatus->GetMaxHp_Player());
}
