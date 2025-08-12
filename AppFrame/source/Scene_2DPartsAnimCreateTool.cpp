/* シーン"汎用2Dパーツアニメーションツール"の定義 */

#include "Scene_2DPartsAnimCreateTool.h"

#include "AppVariableDefine.h"
#include "AppFunctionDefine.h"

// コンストラクタ
Scene_2DPartsAnimCreateTool::Scene_2DPartsAnimCreateTool() : SceneBase("Scene_2DPartsAnimCreateTool", 9999, true)
{
	/* 起動時点でのマウス関連のフラグを保持し、各フラグを無効に設定する */
	this->bOldMouseCursorCenterFixedFlg = gbMouseCursorCenterFixedFlg;
	gbMouseCursorCenterFixedFlg			= false;
	this->bOldMouseCursorNotDepictedFlg = gbMouseCursorNotDepictedFlg;
	gbMouseCursorNotDepictedFlg			= false;

	/* UIの作成 */
	paUI_Table[0] = std::make_shared<Scene_UI_Table>(400, 16, 16 * 5, "パーツリスト");					// 0:パーツリスト
	paUI_Table[1] = std::make_shared<Scene_UI_Table>(400, 16, 16 * 20, "アニメーションリスト");			// 1:アニメーションリスト
	paUI_Table[2] = std::make_shared<Scene_UI_Table>(400, 1500, 16 * 5, "フレームリスト");				// 2:フレームリスト
	paUI_Table[3] = std::make_shared<Scene_UI_Table>(400, 1500, 16 * 20, "選択フレームのパーツリスト");	// 3:選択フレームのパーツリスト

	// UIの登録
	for (int i = 0; i < 4; ++i)
	{
		gpSceneServer->AddSceneReservation(paUI_Table[i]);
	}

}

// デストラクタ
Scene_2DPartsAnimCreateTool::~Scene_2DPartsAnimCreateTool()
{
	/* ツール終了時にマウス関連のフラグを元に戻す */
	gbMouseCursorCenterFixedFlg = this->bOldMouseCursorCenterFixedFlg;
	gbMouseCursorNotDepictedFlg = this->bOldMouseCursorNotDepictedFlg;

	/* 作成したUIの削除フラグを有効化 */
	for (int i = 0; i < 4; ++i)
	{
		paUI_Table[i]->SetDeleteFlg(true);
	}

	///* 選択した画像のグラフィックハンドルを解放 */
	//for (int iGrHandle : this->iSelectGrHandle)
	//{
	//	DeleteGraph(iGrHandle);
	//}
	//this->iSelectGrHandle.clear();
	//this->stSelectGrPath.clear();
}

// 計算
void Scene_2DPartsAnimCreateTool::Process()
{
	/* パーツアニメーション群新規作成 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_Z] == TRUE)
	{
		/* パーツアニメーション群の名称を入力(半角文字) */
		char cAnimName[20];
		int iReturn = KeyInputSingleCharString(0, 0, 20, cAnimName, TRUE);
		if (iReturn == 1)
		{
			// 正常に入力された場合
			/* 入力されたパーツアニメーション群名に設定 */
			this->stPartsAnimData.stAnimName = cAnimName; // パーツアニメーション群名を設定

			/* 現在のアニメーション情報を削除 */
			this->stPartsAnimData.vecPartsImageData.clear();
			this->stPartsAnimData.vecPartsAnimData.clear();
		}
	}

	/* アニメーション用パーツ追加 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_X] == TRUE)
	{
		/* ダイアログを表示 */
		std::string path = PUBLIC_FUNCTION::aOpenFileDialog(".png");

		/* パスが取得されたか確認 */
		if (!path.empty())
		{
			// 取得された場合
			/* 画像のグラフィックハンドルを取得 */
			int iGrHandle = LoadGraph(path.c_str());

			/* パーツ名を入力(半角文字) */
			char cPartsName[20];
			int iReturn = KeyInputSingleCharString(0, 0, 20, cPartsName, TRUE);
			if (iGrHandle != -1 && iReturn == 1)
			{
				// グラフィックハンドルが取得でき、正常に名称が入力された場合
				/* パーツの画像データに入力された情報を追加する */
				Struct_2DPartsAnim::PARTS_ANIM_PARTS_IMAGE_DATA stPartsImageData;
				stPartsImageData.stPartsName	= cPartsName;	// パーツ名を設定
				stPartsImageData.stPartsPath	= path;			// パーツの画像ファイルパスを設定
				stPartsImageData.iPartsGrHandle	= iGrHandle;	// パーツの画像のグラフィックハンドルを設定

				/* パーツの画像データをパーツアニメーション群に追加 */
				this->stPartsAnimData.vecPartsImageData.push_back(stPartsImageData);
			}
		}
	}

	/* アニメーション追加 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_C] == TRUE)
	{
		/* アニメーションの名称を入力(半角文字) */
		char cAnimName[20];
		int iReturn = KeyInputSingleCharString(0, 0, 20, cAnimName, TRUE);
		if (iReturn == 1)
		{
			// 正常に入力された場合
			/* アニメーションを新規作成 */
			Struct_2DPartsAnim::PARTS_ANIM_ANIM_DATA stAnimData;
			stAnimData.stAnimName	= cAnimName;
			this->stPartsAnimData.vecPartsAnimData.push_back(stAnimData);
		}
	}

	/* 選択中のアニメーションにフレーム追加 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_V] == TRUE)
	{

	}

	/* 選択中のアニメーションのフレームにパーツ追加 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_B] == TRUE)
	{

	}

	//if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_Z] == TRUE)
	//{
	//	/* ダイアログを表示 */
	//	std::string path = PUBLIC_FUNCTION::aOpenFileDialog(".png");

	//	/* パスが取得されたか確認 */
	//	if (!path.empty())
	//	{
	//		// 取得された場合
	//		/* 画像のグラフィックハンドルを取得 */
	//		int iGrHandle = LoadGraph(path.c_str());

	//		/* グラフィックハンドルが取得できたか確認 */
	//		if (iGrHandle != -1)
	//		{
	//			// グラフィックハンドルが取得できた場合
	//			///* 選択した画像のグラフィックハンドルとパスを保存 */
	//			//this->iSelectGrHandle.push_back(iGrHandle);
	//			//this->stSelectGrPath.push_back(path);
	//		}
	//	}
	//}

	/* テーブルUIへの要素設定 */
	// パーツリスト
	std::vector<std::string> partsNameList;
	for (const auto& part : this->stPartsAnimData.vecPartsImageData) {
		partsNameList.push_back(part.stPartsName);
	}
	paUI_Table[0]->SetElement(partsNameList);

	/* アニメーションリスト */
	std::vector<std::string> animNameList;
	for (const auto& anim : this->stPartsAnimData.vecPartsAnimData) {
		animNameList.push_back(anim.stAnimName);
	}
	paUI_Table[1]->SetElement(animNameList);
}

// 描画
void Scene_2DPartsAnimCreateTool::Draw()
{
	/* 文字サイズを16に設定 */
	SetFontSize(16);

	/* 背景描写 */
	DrawBox(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, GetColor(255, 255, 255), TRUE);
	DrawLine(SCREEN_SIZE_WIDE / 2, 0, SCREEN_SIZE_WIDE / 2, SCREEN_SIZE_HEIGHT, GetColor(255, 0, 0));
	DrawLine(0, SCREEN_SIZE_HEIGHT / 2, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT / 2, GetColor(0, 0, 255));

	///* 選択した画像のグラフィックハンドルを描写 */
	//for (int iIndex = 0; iIndex < this->iSelectGrHandle.size(); ++iIndex)
	//{
	//	DrawString(iIndex * 100, 0, this->stSelectGrPath[iIndex].c_str(), GetColor(255, 255, 255));
	//	DrawGraph(iIndex * 100, 20, this->iSelectGrHandle[iIndex], FALSE);
	//}

	/* 現在のアニメーションの名称描写 */
	DrawBox(16, 16 * 1, 400, 16 * 2, GetColor(0, 0, 0), TRUE);
	DrawBox(16, 16 * 1, 400, 16 * 3, GetColor(0, 0, 0), FALSE);
	DrawString(16, 16 * 1, "現在のアニメーション群名称", GetColor(255, 255, 255));
	DrawString(16, 16 * 2, this->stPartsAnimData.stAnimName.c_str(), GetColor(0, 0, 0));

	///* 現在のアニメーションのパーツリスト */
	//DrawBox(16, 16 * 5, 400, 16 * 6, GetColor(0, 0, 0), TRUE);
	//DrawString(16, 16 * 5, "現在のパーツリスト", GetColor(255, 255, 255));
	//for (iIndex = 0; iIndex < this->stPartsAnimData.vecPartsImageData.size(); ++iIndex)
	//{
	//	const auto& imageData = this->stPartsAnimData.vecPartsImageData[iIndex];
	//	DrawString(16, 16 * (iIndex + 6), imageData.stPartsName.c_str(), GetColor(0, 0, 0));
	//}
	//DrawBox(16, 16 * 5, 400, 16 * 16, GetColor(0, 0, 0), FALSE);

	///* 現在のアニメーションリスト */
	//DrawBox(16, 16 * 15, 400, 16 * 16, GetColor(0, 0, 0), TRUE);
	//DrawString(16, 16 * 15, "現在のアニメーションリスト", GetColor(255, 255, 255));
	//for (iIndex = 0; iIndex < this->stPartsAnimData.vecPartsAnimData.size(); ++iIndex)
	//{
	//	const auto& animData = this->stPartsAnimData.vecPartsAnimData[iIndex];
	//	DrawString(16, 16 * (iIndex + 25), animData.stAnimName.c_str(), GetColor(0, 0, 0));
	//}
	//DrawBox(16, 16 * 15, 400, 16 * (iIndex + 25), GetColor(0, 0, 0), FALSE);

	/* フレームのパーツリストの現在選択中のパーツ詳細 */




}

// パーツアニメーションのデータ読み込み
bool Scene_2DPartsAnimCreateTool::bLoadPartsAnimData()
{
	return false;
}

// パーツアニメーションのデータ保存
bool Scene_2DPartsAnimCreateTool::bSavePartsAnimData()
{
	return false;
}

