/* シーン"タイトル"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_Title.h"
// 関連クラス
#include "DataList_Sound.h"
#include "DataList_Image.h"
#include "Scene_StageCreate.h"
#include "Scene_GameMain.h"
#include "Scene_Load.h"
// 共通定義
#include "ConstantDefine.h"

// コンストラクタ
Scene_Title::Scene_Title() : Scene_Base("Scene_Title", 0, false, false)
{
	/* 初期化 */
	this->iSelectIndex = 0;

	/* フォントサイズを変更 */
	SetFontSize(BASE_FONT_SIZE);

	/* データリストを取得 */
	std::shared_ptr<DataList_Sound>	pDataList_Sound = std::dynamic_pointer_cast<DataList_Sound>(gpDataListServer->GetDataList("DataList_Sound"));	// サウンド管理
	std::shared_ptr<DataList_Image>	pDataList_Image = std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));	// 画像管理

	/* BGMを設定 */
	pDataList_Sound->BGM_Play("fantasyX");

	/* 使用する画像を設定 */
	// 空の画像
	std::string fileName = "Sky/Sky";
	this->piGrHandle_Sky		= pDataList_Image->iGetGrhandle(fileName);
	// タイトルの画像
	fileName = "Title/Title";
	this->piGrHandle_Title		= pDataList_Image->iGetGrhandle(fileName);
	// 木の画像
	fileName = "UI/Tree_Image";
	this->piGrHandle_Tree		= pDataList_Image->iGetGrhandle(fileName);
	// キーの画像
	fileName = "Key/E";
	this->piGrHandle_Key[KEY_E] = pDataList_Image->iGetGrhandle(fileName);
	fileName = "Key/Q";
	this->piGrHandle_Key[KEY_Q] = pDataList_Image->iGetGrhandle(fileName);
	fileName = "Key/W";
	this->piGrHandle_Key[KEY_W] = pDataList_Image->iGetGrhandle(fileName);
	fileName = "Key/A";
	this->piGrHandle_Key[KEY_A] = pDataList_Image->iGetGrhandle(fileName);
	fileName = "Key/S";
	this->piGrHandle_Key[KEY_S] = pDataList_Image->iGetGrhandle(fileName);
	fileName = "Key/D";
	this->piGrHandle_Key[KEY_D] = pDataList_Image->iGetGrhandle(fileName);
}

// 更新
void Scene_Title::Update()
{
	/* W、Sキーの入力で選択中の項目を変更する */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_W] == TRUE)
	{
		// Wキーが押された場合
		this->iSelectIndex--;
		if (this->iSelectIndex < 0)
		{
			this->iSelectIndex = SELECT_MAX - 1;
		}
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_S] == TRUE)
	{
		// Sキーが押された場合
		this->iSelectIndex++;
		if (this->iSelectIndex >= SELECT_MAX)
		{
			this->iSelectIndex = 0;
		}
	}

	/* Eキーが入力されたらその時点で選択されていた項目を実行 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_E] == TRUE)
	{
		// Eキーが押された場合
		switch (this->iSelectIndex)
		{
			// ゲーム開始
			case SELECT_START_GAME_MAIN:
			{
				/* シーン"ゲームメイン"へ遷移 */
				gpSceneServer->AddSceneReservation(std::make_shared<Scene_GameMain>());
				gpSceneServer->AddSceneReservation(std::make_shared<Scene_Load>());

				/* シーンの削除フラグを有効にする */
				this->bDeleteFlg = true;
				break;
			}
			// ステージ作成へ
			case SELECT_START_STAGE_CREATE:
			{
				/* "ステージ作成"へ遷移 */
				gpSceneServer->AddSceneReservation(std::make_shared<Scene_StageCreate>());
				gpSceneServer->AddSceneReservation(std::make_shared<Scene_Load>());

				/* シーンの削除フラグを有効にする */
				this->bDeleteFlg = true;
				break;
			}
			// 2Dパーツアニメーション作成ツール
			case SELECT_START_2D_PARTS_ANIM_CREATE_TOOL:
			{
				/* 2Dパーツアニメーション作成ツールへ遷移 */
				PUBLIC_FUNCTION::Start2DPartsAnimCreateTool();

				/* シーンの削除フラグを有効にする */
				this->bDeleteFlg = true;
				break;
			}
			// ゲーム終了
			case SELECT_END:
			{
				/* シーンの削除フラグを有効にする */
				this->bDeleteFlg = true;
				break;
			}
		}
	}

	/* 入力待ち */
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_Z] == TRUE)
	{
		/* 2Dパーツアニメーション作成ツールへ遷移 */
		PUBLIC_FUNCTION::Start2DPartsAnimCreateTool();

		/* シーンの削除フラグを有効にする */
		this->bDeleteFlg = true;
	}

	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_X] == TRUE)
	{
		/* "ステージ作成"へ遷移 */
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_StageCreate>());
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_Load>());

		/* シーンの削除フラグを有効にする */
		this->bDeleteFlg = true;
	}

	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_C] == TRUE)
	{
		/* シーン"ゲームメイン"へ遷移 */
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_GameMain>());
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_Load>());
		gpSceneServer->SetDeleteCurrentSceneFlg(true);

		/* シーンの削除フラグを有効にする */
		this->bDeleteFlg = true;
	}
}

// 描画
void Scene_Title::Draw()
{
	/* 空の画像を描写 */
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, *(this->piGrHandle_Sky), TRUE);

	/* 木の画像を描写 */
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE / 2, SCREEN_SIZE_HEIGHT, *(this->piGrHandle_Tree), TRUE);

	/* タイトル画像を描写 */
	// 画像サイズを取得
	int iGrSizeX, iGrSizeY;
	GetGraphSize(*(this->piGrHandle_Title), &iGrSizeX, &iGrSizeY);
	// 画像を描写
	DrawGraph(SCREEN_SIZE_WIDE / 2 - (iGrSizeX / 2), SCREEN_SIZE_HEIGHT / 4 - (iGrSizeY / 2), *(this->piGrHandle_Title), TRUE);

	/* 選択肢を描写 */
	std::string SelectText[SELECT_MAX] =
	{
		"ゲーム開始",
		"ステージ作成へ",
		"2Dパーツアニメーション作成ツール起動",		
		"ゲーム終了"
	};

	// 選択肢の描画位置
	int iSelectInterval	= 50;

	// 上方向の矢印とキー
	int iArrowUpY = SELECT_POSITION_Y - iSelectInterval;
	DrawTriangle(
		SELECT_POSITION_X + 50, iArrowUpY - 20,
		SELECT_POSITION_X + 30, iArrowUpY,
		SELECT_POSITION_X + 70, iArrowUpY,
		GetColor(255, 255, 0), TRUE);
	DrawExtendGraph(
		SELECT_POSITION_X + 80, iArrowUpY - BASE_FONT_SIZE,
		SELECT_POSITION_X + 80 + BASE_FONT_SIZE, iArrowUpY,
		*(this->piGrHandle_Key[KEY_W]), TRUE);

	// 下方向の矢印とキー
	int iArrowDownY = SELECT_POSITION_Y + (SELECT_MAX - 1) * iSelectInterval + iSelectInterval;
	DrawTriangle(
		SELECT_POSITION_X + 50, iArrowDownY + 20,
		SELECT_POSITION_X + 30, iArrowDownY,
		SELECT_POSITION_X + 70, iArrowDownY,
		GetColor(255, 255, 0), TRUE);
	DrawExtendGraph(
		SELECT_POSITION_X + 80, iArrowDownY,
		SELECT_POSITION_X + 80 + BASE_FONT_SIZE, iArrowDownY + BASE_FONT_SIZE,
		*(this->piGrHandle_Key[KEY_S]), TRUE);

	/* 選択肢を描写 */
	for (int i = 0; i < SELECT_MAX; i++)
	{
		int iColor = (i == iSelectIndex) ? GetColor(255, 255, 0) : GetColor(0, 0, 0);
		DrawString(SELECT_POSITION_X, SELECT_POSITION_Y + i * iSelectInterval, SelectText[i].c_str(), iColor);
	}

	/* 操作内容とキーを描写 */
	// Eキー : 決定
	DrawExtendGraph(SELECT_POSITION_X, SELECT_POSITION_Y + (SELECT_MAX * iSelectInterval) + 100, SELECT_POSITION_X + BASE_FONT_SIZE, SELECT_POSITION_Y + (SELECT_MAX * iSelectInterval) + 100 + BASE_FONT_SIZE, *(this->piGrHandle_Key[KEY_E]), TRUE);
	DrawFormatString(SELECT_POSITION_X + (BASE_FONT_SIZE * 2) + 20, SELECT_POSITION_Y + (SELECT_MAX * iSelectInterval) + 100, GetColor(255, 255, 255), "決定");
}
