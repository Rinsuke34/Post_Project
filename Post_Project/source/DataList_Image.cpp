/* データリスト"画像データ管理"クラスの定義 */

/* 使用する要素のインクルード */
// 標準ライブラリ
#include <fstream>
// ヘッダファイル
#include "DataList_Image.h"
// 共通定義
#include "StructDefine.h"

// コンストラクタ
DataList_Image::DataList_Image() : DataList_Base("DataList_Image")
{
	/* 初期化 */
	this->GrHandleList.clear();	// 画像データリスト

	/* テクスチャ読み込み */
	JsonLoad_Texture();
}

// デストラクタ
DataList_Image::~DataList_Image()
{
	/* リスト内の画像ハンドルを削除 */
	for (auto& list : this->GrHandleList)
	{
		/* 画像を削除 */
		DeleteGraph(list.second);
		list.second = -1;
	}
}

// 画像データ読み込み
void DataList_Image::LoadGrHandle(std::string& cFileName)
{
	// 引数
	// cFileName		<-	読み込む画像データのファイル名

	/* 対象の画像データが読み込まれていないか確認 */
	if (bCheckGrHandle(cFileName) == false)
	{
		// 読み込まれていない場合
		/* 画像のファイルパスを取得 */
		std::string FileName = "resource/ImageData/" + cFileName + ".png";

		/* 画像データ読み込み */
		int GrHandle = LoadGraph(FileName.c_str());

		/* 画像データをリストに追加 */
		this->GrHandleList[cFileName] = GrHandle;
	}

	return;
}

// 画像データ取得
std::shared_ptr<int> DataList_Image::iGetGrhandle(std::string& cFileName)
{
	// 引数
	// cFileName			: 画像ファイル名
	// 戻り値
	// std::shared_ptr<int>	: 画像ハンドルのポインタ

	int iReturn = 0;

	/* 対象の画像を取得する */
	// ※読み込まれていないなら読み込み

	/* 対象の画像データが読み込まれていないか確認 */
	if (bCheckGrHandle(cFileName) == false)
	{
		// 読み込まれていない場合
		/* 画像データを読み込む */
		LoadGrHandle(cFileName);
	}
	
	/* 画像ハンドルのポインタをスマートポインタで返す */
	auto list = GrHandleList.find(cFileName);
	if (list != GrHandleList.end())
	{
		/* 対象の画像ハンドルのポインタを戻り値で返却 */
		return std::make_shared<int>(list->second);
	}

	/* 見つからなかった場合はnullptrを返す */
	// ※通常はここに来ることはない想定
	return nullptr;
}

// 該当画像ハンドルデータ存在確認
bool DataList_Image::bCheckGrHandle(std::string& cFileName)
{
	// 引数
	// cFileName	: 読み込む画像データのファイル名
	// 戻り値
	// bool			: 画像データが登録されているか(true:登録されている / false:登録されていない)

	/* 対象の画像がリストに登録されているか確認 */

	bool bReturn = false;

	/* 対象の3Dモデルが登録されているか */
	if (this->GrHandleList.count(cFileName) != 0)
	{
		// 登録されている場合
		bReturn = true;
	}

	return bReturn;
}

// テクスチャ読み込み
void DataList_Image::JsonLoad_Texture()
{
	/* テクスチャデータを読み込み、テクスチャデータリストに登録する */

	/* Jsonファイル読み込み */
	std::string FilePath = "resource/MapData/Texture_Data.json";

	std::ifstream ifs(FilePath);
	if (!ifs) return;

	using json = nlohmann::json;
	json j;
	ifs >> j;

	/* テクスチャデータリストへの設定 */
	for (const auto& elem : j)
	{
		TEXTURE_DATA data;
		data.BlockName		= elem.value("BlockName", "");
		data.iBlockIndex	= elem.value("BlockIndex", -1);
		data.aImageName[0]	= elem.value("ImageName_Upper", "");
		data.aImageName[1]	= elem.value("ImageName_Side", "");
		data.aImageName[2]	= elem.value("ImageName_Under", "");

		this->AddTexture(data);
	}

	/* データリスト"画像データ管理"へテクスチャ画像の登録 */
	for (auto& texData : this->GetTextureDataList())
	{
		// 上面
		if (!texData.aImageName[0].empty())
		{
			this->LoadGrHandle(texData.aImageName[0]);
		}
		// 横面
		if (!texData.aImageName[1].empty())
		{
			this->LoadGrHandle(texData.aImageName[1]);
		}
		// 下面
		if (!texData.aImageName[2].empty())
		{
			this->LoadGrHandle(texData.aImageName[2]);
		}
	}
}
