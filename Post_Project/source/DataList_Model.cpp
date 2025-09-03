/* データリスト"3Dモデル管理"クラスの定義 */

#include "DataList_Model.h"

// コンストラクタ
DataList_Model::DataList_Model() : DataList_Base("DataList_Model")
{

}

// デストラクタ
DataList_Model::~DataList_Model()
{
	/* リスト内の3Dモデルを削除 */
	for (const auto& pair : pModelHandleList)
	{
		/* モデルを削除 */
		MV1DeleteModel(pair.second);
	}

	/* mapをクリアする */
	pModelHandleList.clear();
}

// 3Dモデルロード(事前読み込み用)
void DataList_Model::LoadModel(std::string modelName)
{
	// 引数
	// modelName	: 3Dモデル名

	/* 3Dモデルを読み込む */
	// ※複製は行わない

	/* 対象の3Dモデルが存在するか確認 */
	if (bCheckModel(modelName) == false)
	{
		// 存在しない場合
		/* 3Dモデルのファイルパスを取得 */
		std::string FileName = "resource/ModelData/" + modelName + ".mv1";

		/* 3Dモデルを読み込み */
		int iHandle = MV1LoadModel(FileName.c_str());

		/* 3Dモデルをリストに追加 */
		this->pModelHandleList[modelName] = iHandle;
	}
	return;
}

// 3Dモデル取得
int	DataList_Model::iGetModel(std::string modelName)
{
	// 引数
	// modelName	: 3Dモデル名
	// 戻り値
	// int			: 3Dモデルハンドル(複製したものを渡す)

	int iReturn = 0;

	/* 対象の3Dモデルを取得する */
	// ※すでにあるなら複製、ないなら読み込み

	/* 対象の3Dモデルが存在するか確認 */
	if (bCheckModel(modelName) == false)
	{
		// 存在しない場合
		/* 3Dモデルを読み込む */

		/* 3Dモデルのファイルパスを取得 */
		std::string FileName = "resource/ModelData/" + modelName + ".mv1";

		/* 3Dモデルを読み込み */
		iReturn = MV1LoadModel(FileName.c_str());

		/* 3Dモデルをリストに追加 */
		this->pModelHandleList[modelName] = iReturn;

		/* 読み込んだ3Dモデルを複製 */
		iReturn = MV1DuplicateModel(iReturn);
	}
	else
	{
		// 存在している場合
		/* 対処のモデルを複製 */
		iReturn = MV1DuplicateModel(this->pModelHandleList[modelName]);
	}

	return iReturn;
}

// 3Dモデル存在確認
bool DataList_Model::bCheckModel(std::string modelName)
{
	// 引数
	// modelName	: 3Dモデル名
	// 戻り値
	// bool			: 3Dモデルが登録されているか(true:登録されている / false:登録されていない)

	/* 対象の3Dモデルがリストに登録されているか確認 */

	bool bReturn = false;

	/* 対象の3Dモデルが登録されているか */
	if (this->pModelHandleList.count(modelName) != 0)
	{
		// 登録されている場合
		bReturn = true;
	}

	return bReturn;
}
