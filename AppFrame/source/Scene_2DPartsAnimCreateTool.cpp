/* シーン"汎用2Dパーツアニメーションツール"の定義 */

/* 使用する要素のインクルード */
// 標準ライブラリ
#include <filesystem>
#include <fstream>
// 外部ライブラリ
#include <nlohmann/json.hpp>
// ヘッダファイル
#include "Scene_2DPartsAnimCreateTool.h"
// 関連クラス
#include "Scene_UI_Table.h"
#include "SceneServer.h"
// 共通定義
#include "AppVariableDefine.h"
#include "AppFunctionDefine.h"

// コンストラクタ
Scene_2DPartsAnimCreateTool::Scene_2DPartsAnimCreateTool() : Scene_Base("Scene_2DPartsAnimCreateTool", 9999, true, false)
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
	this->iSelectTime		= 0;
	this->iAnimMaxTime		= 0;
	this->bNameSelectedFlg	= false;
	this->bTimeSelectedFlg	= false;
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

	/* パーツアニメーションの画像データを解放 */
	for (const auto& partImage : this->PartsImageData)
	{
		DeleteGraph(partImage.iPartsGrHandle);
	}
}

// 更新
void Scene_2DPartsAnimCreateTool::Update()
{
	/* 左クリックでの項目選択 */
	if (gstKeyboardInputData.igInput[INPUT_TRG] & MOUSE_INPUT_LEFT)
	{
		/* マウスカーソルがファイル名部分に重なっている状態であるか確認 */
		if (gstKeyboardInputData.iMouseX >= 16 && gstKeyboardInputData.iMouseX <= 400 &&
			gstKeyboardInputData.iMouseY >= 16 * 1 && gstKeyboardInputData.iMouseY <= 16 * 3)
		{
			// マウスカーソルがファイル名部分に重なっている場合
			this->bNameSelectedFlg = true;
			this->bTimeSelectedFlg = false;
		}
		else if (gstKeyboardInputData.iMouseX >= 16 && gstKeyboardInputData.iMouseX <= 1920 - 16 &&
			gstKeyboardInputData.iMouseY >= 1080 - 16 * 4 && gstKeyboardInputData.iMouseY <= 1080 - 16 * 2)
		{
			// マウスカーソルが時間部分に重なっている場合
			this->bNameSelectedFlg = false;
			this->bTimeSelectedFlg = true;
		}
		else
		{
			// マウスカーソルがどちらにも重なっていない場合
			this->bNameSelectedFlg = false;
			this->bTimeSelectedFlg = false;
		}
	}

	/* パーツアニメーションファイル新規作成 */
	if (this->bNameSelectedFlg && (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_I] == TRUE))
	{
		NewPartsAnimFile();
	}

	/* アニメーション用パーツ追加 */
	if(paUI_Table[0]->bGetTableSelectedFlg() && (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_I] == TRUE))
	{
		AddAnimPaarts();
	}
	/* アニメーション用パーツ削除 */
	if (paUI_Table[0]->bGetTableSelectedFlg() && gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_K] == TRUE)
	{
		DeleteAnimPaarts();
	}

	/* アニメーション追加 */
	if (paUI_Table[1]->bGetTableSelectedFlg() && gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_I] == TRUE)
	{
		AddAnim();
	}
	/* アニメーション削除 */
	if (paUI_Table[1]->bGetTableSelectedFlg() && gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_K] == TRUE)
	{
		DeleteAnim();
	}

	/* 選択中のアニメーションの指定時間にパーツ追加 */
	if(paUI_Table[2]->bGetTableSelectedFlg() && gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_I] == TRUE)
	{
		AddPartsToAnim();
	}
	/* 選択中のアニメーションの指定時間にパーツ削除 */
	if (paUI_Table[2]->bGetTableSelectedFlg() && gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_K] == TRUE)
	{
		DeletePartsToAnim();
	}

	/* 選択中のパーツの状態変更(位置や回転量) */
	if (paUI_Table[2]->bGetTableSelectedFlg())
	{
		ChangeSelectPartsStatus();
	}

	/* 選択時間の変更 */
	if (this->bTimeSelectedFlg)
	{
		ChangeSelectTime();
	}

	/* セーブ */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_O] == TRUE)
	{
		// Sキーが押された場合
		bSavePartsAnimData();
	}

	/* ロード */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_L] == TRUE)
	{
		// Lキーが押された場合
		bLoadPartsAnimData();
	}

	/* 終了(シーン削除) */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_ESCAPE] == TRUE)
	{
		// ESCキーが押された場合
		this->bDeleteFlg = true;
	}

	/* テーブルUIへの要素設定 */
	SetUiTableElement();
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
	static const int iStandardSize = 256;	// 標準の四角形のサイズ
	DrawBox(SCREEN_SIZE_WIDE / 2 - iStandardSize / 2, SCREEN_SIZE_HEIGHT / 2 - iStandardSize / 2, SCREEN_SIZE_WIDE / 2 + iStandardSize / 2, SCREEN_SIZE_HEIGHT / 2 + iStandardSize / 2, GetColor(0, 255, 0), FALSE);

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
					DrawRotaGraph3(
						static_cast<int>(part.fPartsX + (SCREEN_SIZE_WIDE / 2)),		// 画像を回転描写する画面上での中心座標X
						static_cast<int>(part.fPartsY + (SCREEN_SIZE_HEIGHT / 2)),		// 画像を回転描写する画面上での中心座標Y
						static_cast<int>(iGrSizeX / 2),									// 画像を回転描写する画像上での中心座標X
						static_cast<int>(iGrSizeY / 2),									// 画像を回転描写する画像上での中心座標Y
						part.fPartsScaleX,												// 横方向の拡大率
						part.fPartsScaleY,												// 縦方向の拡大率
						part.fPartsAngle,												// 画像の回転角度(ラジアン)
						iGrHandle,														// 描写するグラフィックハンドル
						TRUE,															// 画像の透明度を有効にするかどうか
						part.bPartsFlipX);												// 画像を左右反転して描写するかどうか
				}
			}
		}
	}

	/* ファイル名描写 */
	DrawBox(16, 16 * 1, 400, 16 * 2, GetColor(0, 0, 0), TRUE);
	DrawBox(16, 16 * 1, 400, 16 * 3, GetColor(0, 0, 0), FALSE);
	DrawString(16, 16 * 1, "ファイル名", GetColor(255, 255, 255));
	DrawString(16, 16 * 2, this->FileName.c_str(), GetColor(0, 0, 0));
	if (this->bNameSelectedFlg == true)
	{
		DrawBox(16, 16 * 1, 400, 16 * 3, GetColor(255, 0, 0), FALSE);
	}

	/* 現在のアニメーションの時間描写 */
	DrawBox(16, 1080 - 16 * 4, 1920 - 16, 1080 - 16 * 3, GetColor(0, 0, 0), TRUE);
	DrawString(16, 1080 - 16 * 4, "時間", GetColor(255, 255, 255));
	DrawBox(16, 1080 - 16 * 3, 1920 - 16, 1080 - 16 * 2, GetColor(128, 128, 128), FALSE);
	// 時間部分
	DrawBox(16, 1080 - 16 * 3 + 4, 1920 - 16, 1080 - 16 * 2 - 4, GetColor(128, 128, 128), TRUE);
	// 最大時間が0の場合は赤色バーを非表示
	if (iAnimMaxTime > 0)
	{
		// 割合計算
		float rate = static_cast<float>(iSelectTime) / static_cast<float>(iAnimMaxTime);
		if (rate > 1.0f) rate = 1.0f;
		if (rate < 0.0f) rate = 0.0f;
		int barStartX = 16;
		int barEndX = static_cast<int>(16 + (1920 - 16 - 16) * rate);
		DrawBox(barStartX, 1080 - 16 * 3 + 4, barEndX, 1080 - 16 * 2 - 4, GetColor(255, 0, 0), TRUE);
	}
	if (this->bTimeSelectedFlg == true)
	{
		DrawBox(16, 1080 - 16 * 4, 1920 - 16, 1080 - 16 * 2, GetColor(255, 0, 0), FALSE);
	}
}

// パーツアニメーションのデータ読み込み
bool Scene_2DPartsAnimCreateTool::bLoadPartsAnimData()
{
	/* Jsonファイルを読み込み */
	using json = nlohmann::json;

	/* ファイル選択ダイアログでJSONファイルパスを取得 */
	std::string jsonPathStr = PUBLIC_FUNCTION::aOpenFileDialog(".json");
	if (jsonPathStr.empty())
	{
		return false;
	}
	std::filesystem::path jsonPath = jsonPathStr;

	/* ファイル名（拡張子なし）をShift-JISに変換してFileNameに設定 */
	this->FileName = PUBLIC_PROCESS::aUtf8ToShiftJIS(jsonPath.stem().string());

	/* AppResource/AnimData_Resourceの絶対パス取得 */
	std::filesystem::path currentDir	= std::filesystem::current_path();
	std::filesystem::path parentDir		= currentDir.parent_path();
	std::filesystem::path resourceDir	= parentDir / "AnimData_Resource";

	/* ファイルを開く */
	std::ifstream ifs(jsonPath);
	if (!ifs.is_open())
	{
		return false;
	}

	json j;
	try
	{
		ifs >> j;
	}
	catch (...)
	{
		return false;
	}
	ifs.close();

	/* 読み込み成功した場合、既存のデータをクリア */
	PartsImageData.clear();
	PartsAnimData.clear();

	/* パーツの画像データの読み込み */
	if (j.contains("ImagePath") && j["ImagePath"].is_array())
	{
		for (const auto& part : j["ImagePath"])
		{
			/* 追加するイメージデータ */
			Struct_2DPartsAnim::PARTS_ANIM_PARTS_IMAGE_DATA AddImageData;
			AddImageData.stPartsName		= part.value("Name", "");							// パーツ名
			std::filesystem::path filename	= part.value("Path", "");							// 画像ファイル名
			std::filesystem::path absPath	= resourceDir / filename;							// 絶対パス + 画像ファイル名
			AddImageData.stPartsPath		= absPath.generic_string();							// パーツの画像ファイルパス
			AddImageData.iPartsGrHandle		= LoadGraph(AddImageData.stPartsPath.c_str());		// パーツの画像のグラフィックハンドル
			PartsImageData.push_back(AddImageData);												// パーツの画像データに追加
		}
	}

	/* アニメーションデータの読み込み */
	if (j.contains("Animation") && j["Animation"].is_array())
	{
		for (const auto& anim : j["Animation"])
		{
			/* 追加するアニメーションデータ */
			Struct_2DPartsAnim::PARTS_ANIM_ANIM_DATA AddAnimData;
			AddAnimData.AnimName	= anim.value("Name", "");	// アニメーション名
			AddAnimData.PartsAnimFrameData.clear();

			if (anim.contains("Parts") && anim["Parts"].is_array())
			{
				for (const auto& frameArray : anim["Parts"])
				{
					/* 追加するフレームでのパーツ情報のリスト */
					std::vector<Struct_2DPartsAnim::PARTS_ANIM_PARTS_FRAME_DATA> AddFrameList;
					if (frameArray.is_array())
					{
						for (const auto& frame : frameArray)
						{
							/* 追加するフレームでのパーツ情報 */
							Struct_2DPartsAnim::PARTS_ANIM_PARTS_FRAME_DATA AddFrameData;
							AddFrameData.stPartsName	= frame.value("Name", "");		// パーツ名
							AddFrameData.fPartsX		= frame.value("PosX", 0.0f);	// パーツのX座標
							AddFrameData.fPartsY		= frame.value("PosY", 0.0f);	// パーツのY座標
							AddFrameData.fPartsScaleX	= frame.value("ScaleX", 1.0f);	// パーツのXスケール
							AddFrameData.fPartsScaleY	= frame.value("ScaleY", 1.0f);	// パーツのYスケール
							AddFrameData.fPartsAngle	= frame.value("Angle", 0.0f);	// パーツの角度(ラジアン)
							AddFrameData.bPartsFlipX	= frame.value("FlipX", false);	// パーツの左右反転フラグ
							AddFrameList.push_back(AddFrameData);
						}
					}
					AddAnimData.PartsAnimFrameData.push_back(AddFrameList);
				}
			}
			PartsAnimData.push_back(AddAnimData);
		}
	}

	return true;
}

// パーツアニメーションのデータ保存
bool Scene_2DPartsAnimCreateTool::bSavePartsAnimData()
{
	using json = nlohmann::json;

	// AppResource/AnimData_Resourceの絶対パス取得
	std::filesystem::path currentDir = std::filesystem::current_path();
	std::filesystem::path parentDir = currentDir.parent_path();
	std::filesystem::path resourceDir = parentDir / "AnimData_Resource";

	// JSONオブジェクト作成
	json j;

	// PartsImageDataの出力（画像パスはファイル名のみで保存）
	j["ImagePath"] = json::array();
	for (const auto& part : PartsImageData) {
		std::filesystem::path imagePath = std::filesystem::absolute(part.stPartsPath);
		std::filesystem::path filename = imagePath.filename(); // ファイル名のみ取得
		j["ImagePath"].push_back({
			{"Name", part.stPartsName},
			{"Path", filename.string()}
			});
	}

	// PartsAnimDataの出力（従来通り）
	j["Animation"] = json::array();
	for (const auto& anim : PartsAnimData) {
		json animObj;
		animObj["Name"] = anim.AnimName;
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

	// 保存先パス作成（AppResource/AnimData_Json直下に修正）
	std::filesystem::path saveDir = parentDir / "AnimData_Json";
	std::filesystem::create_directories(saveDir);
	std::filesystem::path savePath = saveDir / (this->FileName + ".json");

	// ファイル保存
	std::ofstream ofs(savePath);
	if (!ofs.is_open()) {
		return false;
	}
	ofs << j.dump(4);
	ofs.close();

	return true;
}

// 新規パーツアニメーションファイル作成
void Scene_2DPartsAnimCreateTool::NewPartsAnimFile()
{
	/* ファイル名を入力(半角文字) */
	char cAnimName[20];
	DrawBox(0, 0, 400, 16, GetColor(0, 0, 0), TRUE);
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

// アニメーション用パーツ追加
void Scene_2DPartsAnimCreateTool::AddAnimPaarts()
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
		DrawBox(0, 0, 400, 16, GetColor(0, 0, 0), TRUE);
		int iReturn = KeyInputSingleCharString(0, 0, 20, cPartsName, TRUE);
		if (iGrHandle != -1 && iReturn == 1)
		{
			// グラフィックハンドルが取得でき、正常に名称が入力された場合
			/* パーツの画像データに入力された情報を追加する */
			Struct_2DPartsAnim::PARTS_ANIM_PARTS_IMAGE_DATA stPartsImageData;
			stPartsImageData.stPartsName = cPartsName;	// パーツ名を設定
			stPartsImageData.stPartsPath = path;			// パーツの画像ファイルパスを設定
			stPartsImageData.iPartsGrHandle = iGrHandle;	// パーツの画像のグラフィックハンドルを設定

			/* パーツの画像データをパーツアニメーション群に追加 */
			this->PartsImageData.push_back(stPartsImageData);
		}
	}
}

void Scene_2DPartsAnimCreateTool::AddAnim()
{
	/* アニメーションの名称を入力(半角文字) */
	char cAnimName[20];
	DrawBox(0, 0, 400, 16, GetColor(0, 0, 0), TRUE);
	int iReturn = KeyInputSingleCharString(0, 0, 20, cAnimName, TRUE);
	if (iReturn == 1)
	{
		// 正常に入力された場合
		/* アニメーションを新規作成 */
		Struct_2DPartsAnim::PARTS_ANIM_ANIM_DATA stAnimData;
		stAnimData.AnimName = cAnimName;
		this->PartsAnimData.push_back(stAnimData); // パーツアニメーションの情報に追加
	}
}

// 選択中のアニメーションにパーツを追加
void Scene_2DPartsAnimCreateTool::AddPartsToAnim()
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

// アニメーション用パーツ削除
void Scene_2DPartsAnimCreateTool::DeleteAnimPaarts()
{
	// 選択中のパーツリストのインデックス
	int iSelectPartsIndex = paUI_Table[2]->iGetSelectElementIndex();

	// 選択中のパーツをPartsImageDataから削除
	if (iSelectPartsIndex >= 0 && iSelectPartsIndex < PartsImageData.size())
	{
		PartsImageData.erase(PartsImageData.begin() + iSelectPartsIndex);
	}
}

// アニメーション削除
void Scene_2DPartsAnimCreateTool::DeleteAnim()
{
	// 選択中のアニメーションのインデックス
	int iSelectAnimIndex = paUI_Table[1]->iGetSelectElementIndex();

	// 選択中のアニメーションをPartsAnimDataから削除
	if (iSelectAnimIndex >= 0 && iSelectAnimIndex < PartsAnimData.size())
	{
		PartsAnimData.erase(PartsAnimData.begin() + iSelectAnimIndex);
	}
}

// 選択中のアニメーションにパーツを追加
void Scene_2DPartsAnimCreateTool::DeletePartsToAnim()
{
	// 選択中のアニメーションのインデックス
	int iSelectAnimIndex = paUI_Table[1]->iGetSelectElementIndex();
	// 選択中のパーツリストのインデックス
	int iSelectPartsIndex = paUI_Table[2]->iGetSelectElementIndex();

	// 選択中アニメーションのパーツリストから選択中パーツを削除
	if (iSelectAnimIndex >= 0 && iSelectAnimIndex < PartsAnimData.size())
	{
		auto& anim = PartsAnimData[iSelectAnimIndex];
		if (iSelectPartsIndex >= 0 && iSelectPartsIndex < anim.PartsAnimFrameData.size())
		{
			anim.PartsAnimFrameData.erase(anim.PartsAnimFrameData.begin() + iSelectPartsIndex);
		}
	}
}

// 選択時間の変更
void Scene_2DPartsAnimCreateTool::ChangeSelectTime()
{
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
		/* 時間を新規作成する場合、最も最後の時間のパーツ情報を引き継ぐ */
		int iSelectAnimIndex = paUI_Table[1]->iGetSelectElementIndex();
		if (iSelectAnimIndex >= 0 && iSelectAnimIndex < PartsAnimData.size())
		{
			auto& animData = PartsAnimData[iSelectAnimIndex];
			this->iSelectTime++;

			// 新規時間（フレーム）を追加する場合
			if (this->iSelectTime >= animData.PartsAnimFrameData.size())
			{
				// 直前のフレームが存在する場合は複製
				if (!animData.PartsAnimFrameData.empty())
				{
					animData.PartsAnimFrameData.push_back(animData.PartsAnimFrameData.back());
				}
				else
				{
					// 最初のフレームの場合は空で追加
					animData.PartsAnimFrameData.push_back({});
				}
			}
		}
		else
		{
			this->iSelectTime++;
		}
	}
}

// テーブルUIへの要素設定
void Scene_2DPartsAnimCreateTool::SetUiTableElement()
{
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
		animNameList.push_back(anim.AnimName);
	}
	paUI_Table[1]->SetElement(animNameList);
	iSelectAnimIndex = paUI_Table[1]->iGetSelectElementIndex();

	// 最大時間（フレーム数）を毎フレーム更新
	if (iSelectAnimIndex >= 0 && iSelectAnimIndex < PartsAnimData.size())
	{
		this->iAnimMaxTime = static_cast<int>(PartsAnimData[iSelectAnimIndex].PartsAnimFrameData.size());
	}
	else
	{
		this->iAnimMaxTime = 0;
	}

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

// 選択中のパーツの状態変更
void Scene_2DPartsAnimCreateTool::ChangeSelectPartsStatus()
{
	// 選択中のアニメーションのインデックス
	int iSelectAnimIndex = paUI_Table[1]->iGetSelectElementIndex();
	// 選択中のパーツリストのインデックス
	int iSelectPartsIndex = paUI_Table[2]->iGetSelectElementIndex();
	// インデックス範囲チェック
	if (iSelectAnimIndex >= 0 && iSelectAnimIndex < PartsAnimData.size() &&
		iSelectPartsIndex >= 0)
	{
		auto& animData = PartsAnimData[iSelectAnimIndex];
		if (iSelectTime >= 0 && iSelectTime < animData.PartsAnimFrameData.size() &&
			iSelectPartsIndex < animData.PartsAnimFrameData[iSelectTime].size())
		{
			auto& partData = animData.PartsAnimFrameData[iSelectTime][iSelectPartsIndex];
			// 位置変更
			if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_W] == TRUE)
			{
				partData.fPartsY -= 1.0f;
			}
			if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_S] == TRUE)
			{
				partData.fPartsY += 1.0f;
			}
			if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_A] == TRUE)
			{
				partData.fPartsX -= 1.0f;
			}
			if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_D] == TRUE)
			{
				partData.fPartsX += 1.0f;
			}
			// 回転変更
			if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_Q] == TRUE)
			{
				partData.fPartsAngle -= 0.1f;
				if (partData.fPartsAngle < 0.0f) partData.fPartsAngle += 360.0f;
			}
			if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_E] == TRUE)
			{
				partData.fPartsAngle += 0.1f;
				if (partData.fPartsAngle >= 360.0f) partData.fPartsAngle -= 360.0f;
			}
			// 拡大縮小変更
			if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_R] == TRUE)
			{
				partData.fPartsScaleX += 0.01f;
				partData.fPartsScaleY += 0.01f;
				if (partData.fPartsScaleX > 10.0f) partData.fPartsScaleX = 10.0f;
				if (partData.fPartsScaleY > 10.0f) partData.fPartsScaleY = 10.0f;
			}
			if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_F] == TRUE)
			{
				partData.fPartsScaleX -= 0.01f;
				partData.fPartsScaleY -= 0.01f;
				if (partData.fPartsScaleX < 0.1f) partData.fPartsScaleX = 0.1f;
				if (partData.fPartsScaleY < 0.1f) partData.fPartsScaleY = 0.1f;
			}
		}
	}
}