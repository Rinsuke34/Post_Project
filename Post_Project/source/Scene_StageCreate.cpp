/* シーン"ステージ作成"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_StageCreate.h"
// 関連クラス
// 関連クラス
#include "Scene_Stage.h"
#include "DataList_Object.h"
#include "DataList_StageCreate.h"

// コンストラクタ
Scene_StageCreate::Scene_StageCreate() : Scene_Base("Scene_StageCreate", 100, true, false)
{
	/* データリスト作成 */
	gpDataListServer->AddDataList(std::make_shared<DataList_Object>());			// オブジェクト管理
	gpDataListServer->AddDataList(std::make_shared<DataList_StageCreate>());	// ステージクリエイト情報管理

	/* シーン作成 */
	gpSceneServer->AddSceneReservation(std::make_shared<Scene_Stage>());		// ステージシーン

	/* データリスト取得 */
	this->pDataList_StageCreate	= std::dynamic_pointer_cast<DataList_StageCreate>(gpDataListServer->GetDataList("DataList_StageCreate"));	// ステージクリエイト情報管理

	this->pDataList_StageCreate->Load_MapData("AreaData_Front");
}

// デストラクタ
Scene_StageCreate::~Scene_StageCreate()
{
	/* データリスト削除 */
	gpDataListServer->DeleteDataList("DataList_StageCreate");	// ステージクリエイト情報管理
}

// 更新
void Scene_StageCreate::Update()
{
	/* 現在の選択座標を取得 */
	VECTOR_INT vecSelectPos = this->pDataList_StageCreate->vecGetSelectPos();

	/* 選択座標を変更 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_W] == TRUE)
	{
		vecSelectPos.z += 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_S] == TRUE)
	{
		vecSelectPos.z -= 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_D] == TRUE)
	{
		vecSelectPos.x += 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_A] == TRUE)
	{
		vecSelectPos.x -= 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_SPACE] == TRUE)
	{
		vecSelectPos.y += 1;
	}
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_LSHIFT] == TRUE)
	{
		vecSelectPos.y -= 1;
	}

	/* 選択座標を更新 */
	this->pDataList_StageCreate->SetSelectPos(vecSelectPos);
}

// 描画
void Scene_StageCreate::Draw()
{
	/* ステージ作成に関連する情報を描写 */
}
