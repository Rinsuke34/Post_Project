/* データリスト"汎用2Dパーツアニメーションツール"クラスの定義 */

/* 使用する要素のインクルード */
// 標準ライブラリ
#include <filesystem>
#include <fstream>
// 外部ライブラリ
#include <nlohmann/json.hpp>
// ヘッダファイル
#include "DataList_2DPartsAnimCreateTool.h"
// 共通定義
#include "AppFunctionDefine.h"

// コンストラクタ
DataList_2DPartsAnimCreateTool::DataList_2DPartsAnimCreateTool() : DataList_Base("DataList_2DPartsAnimCreateTool")
{
	/* 初期化 */
	this->iDrawScreenSize[SCREEN_SIZE_WIDE]		= SCREEN_SIZE_WIDE;
	this->iDrawScreenSize[SCREEN_SIZE_HEIGHT]	= SCREEN_SIZE_HEIGHT;
}

// デストラクタ
DataList_2DPartsAnimCreateTool::~DataList_2DPartsAnimCreateTool()
{
	/* 各パーツのグラフィックハンドルを解放する */
	for (const auto& partAnim : this->PartsAnimDataList)
	{
		for (const auto& partImage : partAnim.PartsImageData)
		{
			DeleteGraph(partImage.iPartsGrHandle);
		}
	}
}

// パーツアニメーションのデータ読み込み
void DataList_2DPartsAnimCreateTool::LoadPartsAnimData(std::string FileName)
{
	// 引数
	// FileName	<- パーツアニメーション群の名称(==ファイル名)

	/* 指定されたパーツアニメーション群名のデータが既に存在するか確認 */
	for (const auto& partAnim : this->PartsAnimDataList)
	{
		if (partAnim.FileName == FileName)
		{
			// 既に存在する場合
			return;
		}
	}

	/* パーツアニメーションの情報 */
	Struct_2DPartsAnim::PARTS_ANIM_DATA PartsAnimData;

	/* ファイル名を設定 */
	PartsAnimData.FileName = FileName;

	/* Jsonファイルを読み込み */
	using json = nlohmann::json;

	/* AppData/AnimDataフォルダの絶対パス取得 */
	std::filesystem::path currentDir	= std::filesystem::current_path();
	std::filesystem::path parentDir		= currentDir.parent_path();
	std::filesystem::path dataDir		= parentDir / "AppResource";
	std::filesystem::path jsonPath		= dataDir / "AnimData_Json" / (FileName + ".json");

	/* ファイルを開く */
	std::ifstream ifs(jsonPath);
	if (!ifs.is_open())
	{
		return;
	}

	json j;
	try
	{
		ifs >> j;
	}
	catch (...)
	{
		return;
	}
	ifs.close();

	/* パーツの画像データの読み込み */
	if (j.contains("ImagePath") && j["ImagePath"].is_array())
	{
		/* パーツの画像データ */
		std::vector<Struct_2DPartsAnim::PARTS_ANIM_PARTS_IMAGE_DATA> PartsImageData;

		for (const auto& part : j["ImagePath"])
		{
			/* 追加するイメージデータ */
			Struct_2DPartsAnim::PARTS_ANIM_PARTS_IMAGE_DATA AddImageData;
			AddImageData.stPartsName		= part.value("Name", "");							// パーツ名
			std::filesystem::path filename	= part.value("Path", "");							// 画像ファイル名
			std::filesystem::path absPath	= dataDir / "AnimData_Resource" / filename;			// 絶対パス + 画像フォルダ名 +  画像ファイル名
			AddImageData.stPartsPath		= absPath.generic_string();							// パーツの画像ファイルパス
			AddImageData.iPartsGrHandle		= LoadGraph(AddImageData.stPartsPath.c_str());		// パーツの画像のグラフィックハンドル
			PartsImageData.push_back(AddImageData);												// パーツの画像データに追加
		}

		/* パーツの画像データを設定 */
		PartsAnimData.PartsImageData = PartsImageData;
	}

	/* アニメーションデータの読み込み */
	if (j.contains("Animation") && j["Animation"].is_array())
	{
		/* パーツアニメーションの情報 */
		std::vector<Struct_2DPartsAnim::PARTS_ANIM_ANIM_DATA> AnimData;

		for (const auto& anim : j["Animation"])
		{
			/* 追加するアニメーションデータ */
			Struct_2DPartsAnim::PARTS_ANIM_ANIM_DATA AddAnimData;
			AddAnimData.AnimName			= anim.value("Name", "");	// アニメーション名
			AddAnimData.PartsAnimFrameData.clear();

			if (anim.contains("Parts") && anim["Parts"].is_array())
			{
				for (const auto& frameArray : anim["Parts"])
				{
					/* 追加するフレームでのパーツ情報のリスト */
					std::vector<Struct_2DPartsAnim::PARTS_ANIM_PARTS_FRAME_DATA> AddAnimFrameData;
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
							AddAnimFrameData.push_back(AddFrameData);
						}
					
					}
					AddAnimData.PartsAnimFrameData.push_back(AddAnimFrameData);
				}
			}
			AnimData.push_back(AddAnimData);
		}

		/* アニメーションデータを設定 */
		PartsAnimData.PartsAnimData = AnimData;
	}

	/* パーツアニメーションの情報を設定 */
	this->PartsAnimDataList.push_back(PartsAnimData);
}

// パーツアニメーションの描画
// ※ 描写用スクリーンのサイズを設定してから実行すること
void DataList_2DPartsAnimCreateTool::DrawPartsAnim(std::string FileName, std::string AnimDame, int iFrame)
{
	// 引数
	// FileName	<- パーツアニメーション群の名称(==ファイル名)
	// AnimDame	<- アニメーション名
	// iFrame	<- フレーム数(時間)

	/* 指定された秒数のアニメーションを描写 */
	// ※ X:0,Y:0を基準位置として描写
	// ※ 描写するスクリーンは事前に設定しておくこと

	for (const auto& partAnim : this->PartsAnimDataList)
	{
		/* 指定されたパーツアニメーション群であるか確認 */
		if (partAnim.FileName == FileName)
		{
			/* 指定されたアニメーション名のアニメーションを探す */
			for (const auto& animData : partAnim.PartsAnimData)
			{
				if (animData.AnimName == AnimDame)
				{
					/* 指定されたフレーム数のパーツ情報が存在するか確認 */
					if (iFrame >= 0 && iFrame < animData.PartsAnimFrameData.size())
					{
						/* 指定されたフレーム数のパーツ情報を描写 */
						for (const auto& partFrameData : animData.PartsAnimFrameData[iFrame])
						{
							/* パーツ名からパーツの画像データを探す */
							for (const auto& partImageData : partAnim.PartsImageData)
							{
								if (partImageData.stPartsName == partFrameData.stPartsName)
								{
									// パーツ名が一致した場合
									/* 画像のサイズを取得 */
									int iGrSizeX, iGrSizeY;
									GetGraphSize(partImageData.iPartsGrHandle, &iGrSizeX, &iGrSizeY);
									/* パーツの画像を描写 */
									DrawRotaGraph3(
										static_cast<int>(partFrameData.fPartsX) + (this->iDrawScreenSize[SCREEN_SIZE_WIDE] / 2),	// 画像を回転描写する画面上での中心座標X
										static_cast<int>(partFrameData.fPartsY) + (this->iDrawScreenSize[SCREEN_SIZE_HEIGHT] / 2),	// 画像を回転描写する画面上での中心座標Y
										static_cast<int>(iGrSizeX / 2),																// 画像を回転描写する画像上での中心座標X
										static_cast<int>(iGrSizeY / 2),																// 画像を回転描写する画像上での中心座標Y
										partFrameData.fPartsScaleX,																	// 横方向の拡大率
										partFrameData.fPartsScaleY,																	// 縦方向の拡大率
										partFrameData.fPartsAngle,																	// 画像の回転角度(ラジアン)
										partImageData.iPartsGrHandle,																// 描写するグラフィックハンドル
										TRUE,																						// 画像の透明度を有効にするかどうか
										partFrameData.bPartsFlipX																	// 画像を左右反転して描写するかどうか
									);
									break;
								}
							}
						}
					}
					break;
				}
			}
			break;
		}
	}
}

// パーツアニメーションの最大フレーム数取得
int DataList_2DPartsAnimCreateTool::iGetPartsAnimMaxTime(std::string FileName, std::string AnimDame)
{
	// 引数
	// FileName	<- パーツアニメーション群の名称(==ファイル名)
	// AnimDame	<- アニメーション名
	// 戻り値
	// iMaxFrame <- 指定されたアニメーションの最大フレーム数(時間)

	int iMaxFrame = 0; // 最大フレーム数(時間)
	for (const auto& partAnim : this->PartsAnimDataList)
	{
		/* 指定されたパーツアニメーション群であるか確認 */
		if (partAnim.FileName == FileName)
		{
			/* 指定されたアニメーション名のアニメーションを探す */
			for (const auto& animData : partAnim.PartsAnimData)
			{
				if (animData.AnimName == AnimDame)
				{
					/* 最大フレーム数(時間)を取得 */
					iMaxFrame = static_cast<int>(animData.PartsAnimFrameData.size());
					break;
				}
			}
			break;
		}
	}
	return iMaxFrame;
}

// 描画用スクリーンのサイズ設定
// ※ 画面中央を基準にパーツを描写するので事前に設定すること
void DataList_2DPartsAnimCreateTool::SetDrawScreenSize(int iWide, int iHeight)
{
	// 引数
	// iWide	<- 描画用スクリーンの横幅
	// iHeight	<- 描画用スクリーンの縦幅

	iDrawScreenSize[SCREEN_SIZE_WIDE]	= iWide;
	iDrawScreenSize[SCREEN_SIZE_HEIGHT]	= iHeight;
}