/* データリスト"画像データ管理"クラスの定義 */

#include "DataList_GrHandle.h"

// コンストラクタ
DataList_GrHandle::DataList_GrHandle() : DataList_Base("DataList_GrHandle")
{
	/* 初期化 */
	this->GrHandleList.clear();	// 画像データリスト
}

// デストラクタ
DataList_GrHandle::~DataList_GrHandle()
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
void DataList_GrHandle::LoadGrHandle(std::string& cFileName)
{
	// 引数
	// cFileName		<-	読み込む画像データのファイル名

	/* 対象の画像データが読み込まれていないか確認 */
	if (bCheckGrHandle(cFileName) == false)
	{
		// 読み込まれていない場合
		/* 画像のファイルパスを取得 */
		std::string FileName = "resource/ImageData/" + cFileName + ".mv1";

		/* 画像データ読み込み */
		int GrHandle = LoadGraph(FileName.c_str());

		/* 画像データをリストに追加 */
		this->GrHandleList[cFileName] = GrHandle;
	}

	return;
}

// 画像データ読み込み(2Dパーツアニメーション用)
void DataList_GrHandle::LoadGrHandle_2DPartsAnim(std::string& cFileName)
{
	// 引数
	// cFileName		<-	読み込む画像データのファイル名

	/* 対象の画像データが読み込まれていないか確認 */
	if (bCheckGrHandle(cFileName) == false)
	{
		// 読み込まれていない場合
		/* 画像のファイルパスを取得 */
		std::filesystem::path currentDir	= std::filesystem::current_path();
		std::filesystem::path parentDir		= currentDir.parent_path();
		std::filesystem::path resourceDir	= parentDir / "AnimData_Resource";
		std::filesystem::path absPath		= resourceDir / (cFileName + ".png");

		/* 画像データ読み込み */
		int GrHandle = LoadGraph(absPath.generic_string().c_str());

		/* 画像データをリストに追加 */
		this->GrHandleList[cFileName] = GrHandle;
	}

	return;
}

// 画像データ取得
std::shared_ptr<int> DataList_GrHandle::iGetGrhandle(std::string& cFileName)
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
bool DataList_GrHandle::bCheckGrHandle(std::string& cFileName)
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
