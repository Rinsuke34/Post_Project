/* シーン"汎用2Dパーツアニメーションツール"の定義 */

#include "Scene_2DPartsAnimCreateTool.h"

#include "AppVariableDefine.h"
#include "AppFunctionDefine.h"

#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>

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
	paUI_Table[2] = std::make_shared<Scene_UI_Table>(400, 16, 16 * 35, "選択時間でのパーツリスト");		// 2:選択時間でのパーツリスト

	// UIの登録
	for (int i = 0; i < 3; ++i)
	{
		gpSceneServer->AddSceneReservation(paUI_Table[i]);
	}

	/* 初期化 */
	this->iSelectTime	= 0;
}

// デストラクタ
Scene_2DPartsAnimCreateTool::~Scene_2DPartsAnimCreateTool()
{
	/* ツール終了時にマウス関連のフラグを元に戻す */
	gbMouseCursorCenterFixedFlg = this->bOldMouseCursorCenterFixedFlg;
	gbMouseCursorNotDepictedFlg = this->bOldMouseCursorNotDepictedFlg;

	/* 作成したUIの削除フラグを有効化 */
	for (int i = 0; i < 3; ++i)
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
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_N] == TRUE)
	{
		/* ファイル名を入力(半角文字) */
		char cAnimName[20];
		int iReturn = KeyInputSingleCharString(0, 0, 20, cAnimName, TRUE);
		if (iReturn == 1)
		{
			// 正常に入力された場合
			/* 入力されたパーツアニメーション群名に設定 */
			this->FileName = cAnimName; // パーツアニメーション群名を設定

			/* 現在のアニメーションの情報を削除 */
			for (int i = 0; i < this->PartsImageData.size(); i++)
			{
				// 画像ハンドルを解放
				DeleteGraph(this->PartsImageData[i].iPartsGrHandle);
			}
			this->PartsImageData.clear();		// パーツの画像データをクリア
			this->PartsAnimData.clear();		// パーツアニメーションの情報をクリア
		}
	}

	/* アニメーション用パーツ追加 */
	if(paUI_Table[0]->bGetTableSelectedFlg() && gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_A] == TRUE)
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
				this->PartsImageData.push_back(stPartsImageData);
			}
		}
	}

	/* アニメーション追加 */
	if (paUI_Table[1]->bGetTableSelectedFlg() && gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_A] == TRUE)
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
			this->PartsAnimData.push_back(stAnimData); // パーツアニメーションの情報に追加
		}
	}

	/* 選択中のアニメーションの指定時間にパーツ追加 */
	if(paUI_Table[2]->bGetTableSelectedFlg() && gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_A] == TRUE)
	{
		// 選択中のアニメーションのインデックス
		int iSelectAnimIndex = paUI_Table[1]->iGetSelectElementIndex();
		// 選択中のパーツリストのインデックス
		int iSelectPartsIndex = paUI_Table[0]->iGetSelectElementIndex();

		// インデックス範囲チェック
		if (iSelectAnimIndex >= 0 && iSelectAnimIndex < PartsAnimData.size() &&
			iSelectPartsIndex >= 0 && iSelectPartsIndex < PartsImageData.size())
		{
			// 選択中のアニメーション・時間のフレームが存在しない場合は新規作成
			auto& animData = PartsAnimData[iSelectAnimIndex];
			if (iSelectTime >= animData.PartsAnimFrameData.size())
			{
				animData.PartsAnimFrameData.resize(iSelectTime + 1);
			}

			// パーツ情報を取得
			const auto& srcPart = PartsImageData[iSelectPartsIndex];
			Struct_2DPartsAnim::PARTS_ANIM_PARTS_FRAME_DATA stPartsFrameData;
			stPartsFrameData.stPartsName	= srcPart.stPartsName;
			stPartsFrameData.fPartsX		= 0.0f;
			stPartsFrameData.fPartsY		= 0.0f;
			stPartsFrameData.fPartsScaleX	= 1.0f;
			stPartsFrameData.fPartsScaleY	= 1.0f;
			stPartsFrameData.fPartsAngle	= 0.0f;
			stPartsFrameData.bPartsFlipX	= false;

			// 選択中アニメーションの指定時間に追加
			animData.PartsAnimFrameData[iSelectTime].push_back(stPartsFrameData);
		}
	}

	/* 選択時間の変更 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_LEFT] == TRUE)
	{
		// 左キーが押された場合
		if (this->iSelectTime > 0)
		{
			this->iSelectTime--;
		}
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_RIGHT] == TRUE)
	{
		// 右キーが押された場合
		this->iSelectTime++;
	}

	/* テーブルUIへの要素設定 */
	int iSelectAnimIndex = 0; // 選択中のアニメーションのインデックス
	// パーツリスト
	std::vector<std::string> partsNameList;
	for (const auto& part : this->PartsImageData) {
		partsNameList.push_back(part.stPartsName);
	}
	paUI_Table[0]->SetElement(partsNameList);

	// アニメーションリスト
	std::vector<std::string> animNameList;
	for (const auto& anim : this->PartsAnimData) {
		animNameList.push_back(anim.stAnimName);
	}
	paUI_Table[1]->SetElement(animNameList);
	iSelectAnimIndex = paUI_Table[1]->iGetSelectElementIndex();

	// 選択した時間でのパーツリスト
	std::vector<std::string> framePartsNameList;
	if (iSelectAnimIndex >= 0 && iSelectAnimIndex < PartsAnimData.size()) {
		const auto& animData = PartsAnimData[iSelectAnimIndex];
		if (iSelectTime >= 0 && iSelectTime < animData.PartsAnimFrameData.size()) {
			for (const auto& part : animData.PartsAnimFrameData[iSelectTime]) {
				framePartsNameList.push_back(part.stPartsName);
			}
		}
	}
	paUI_Table[2]->SetElement(framePartsNameList);
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

	/* 現在のアニメーションの選択時間に登録されたパーツを描写 */
	int iSelectAnimIndex = paUI_Table[1]->iGetSelectElementIndex(); // 選択中のアニメーションのインデックス
	if (iSelectAnimIndex >= 0 && iSelectAnimIndex < PartsAnimData.size())
	{
		const auto& animData = PartsAnimData[iSelectAnimIndex];
		if (iSelectTime >= 0 && iSelectTime < animData.PartsAnimFrameData.size())
		{
			const auto& frameData = animData.PartsAnimFrameData[iSelectTime];
			for (const auto& part : frameData)
			{
				int iGrHandle = -1;
				for (const auto& image : PartsImageData)
				{
					if (image.stPartsName == part.stPartsName)
					{
						iGrHandle = image.iPartsGrHandle;
						break;
					}
				}
				if (iGrHandle != -1)
				{
					int iGrSizeX, iGrSizeY;
					GetGraphSize(iGrHandle, &iGrSizeX, &iGrSizeY);
					DrawRotaGraph3(part.fPartsX + (SCREEN_SIZE_WIDE / 2), part.fPartsY + (SCREEN_SIZE_HEIGHT / 2), iGrSizeX / 2, iGrSizeY / 2, part.fPartsScaleX, part.fPartsScaleY, part.fPartsAngle, iGrHandle, TRUE, part.bPartsFlipX);
				}
			}
		}
	}

	/* ファイル名描写 */
	DrawBox(16, 16 * 1, 400, 16 * 2, GetColor(0, 0, 0), TRUE);
	DrawBox(16, 16 * 1, 400, 16 * 3, GetColor(0, 0, 0), FALSE);
	DrawString(16, 16 * 1, "ファイル名", GetColor(255, 255, 255));
	DrawString(16, 16 * 2, this->FileName.c_str(), GetColor(0, 0, 0));

	/* 現在のアニメーションの時間描写 */
	DrawBox(16, 1080 - 16 * 4, 1920 - 16, 1080 - 16 * 3, GetColor(0, 0, 0), TRUE);
	DrawString(16, 1080 - 16 * 4, "時間", GetColor(255, 255, 255));
	DrawBox(16, 1080 - 16 * 3, 1920 - 16, 1080 - 16 * 2, GetColor(128, 128, 128), FALSE);
	// 時間部分
	DrawBox(16, 1080 - 16 * 3 + 4, 1920 - 16, 1080 - 16 * 2 - 4, GetColor(128, 128, 128), TRUE);
	DrawBox(16, 1080 - 16 * 3 + 4, 16 + this->iSelectTime * 25, 1080 - 16 * 2 - 4, GetColor(255, 0, 0), TRUE);
}

// パーツアニメーションのデータ読み込み
bool Scene_2DPartsAnimCreateTool::bLoadPartsAnimData()
{
	return false;
}

// パーツアニメーションのデータ保存
bool Scene_2DPartsAnimCreateTool::bSavePartsAnimData()
{

	using json = nlohmann::json;

	// JSONオブジェクト作成
	json j;

	// PartsImageDataの出力
	j["ImagePath"] = json::array();
	for (const auto& part : PartsImageData) {
		j["ImagePath"].push_back({
			{"Name", part.stPartsName},
			{"Path", part.stPartsPath}
			});
	}

	// PartsAnimDataの出力
	j["Animation"] = json::array();
	for (const auto& anim : PartsAnimData) {
		json animObj;
		animObj["Name"] = anim.stAnimName;
		animObj["Parts"] = json::array();

		for (const auto& frameList : anim.PartsAnimFrameData) {
			json frameArray = json::array();
			for (const auto& frame : frameList) {
				frameArray.push_back({
					{"Name", frame.stPartsName},
					{"PosX", frame.fPartsX},
					{"PosY", frame.fPartsY},
					{"ScaleX", frame.fPartsScaleX},
					{"ScaleY", frame.fPartsScaleY},
					{"Angle", frame.fPartsAngle},
					{"FlipX", frame.bPartsFlipX}
					});
			}
			animObj["Parts"].push_back(frameArray);
		}
		j["Animation"].push_back(animObj);
	}

	// 保存先パス作成
	std::filesystem::path currentDir = std::filesystem::current_path();
	std::filesystem::path parentDir = currentDir.parent_path();
	std::filesystem::path saveDir = parentDir / "AppResource" / "AnimData_Json";
	std::filesystem::create_directories(saveDir); // フォルダがなければ作成

	std::filesystem::path savePath = saveDir / (FileName + ".json");

	// ファイル保存
	std::ofstream ofs(savePath);
	if (!ofs.is_open()) {
		return false;
	}
	ofs << j.dump(4); // インデント4で出力
	ofs.close();

	return true;
}

