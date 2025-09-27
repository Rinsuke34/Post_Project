/* シーン"ゲームメイン"の定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_GameMain.h"
// 関連クラス
#include "Scene_Stage.h"
#include "Scene_GameOver_Fadeout.h"
#include "Scene_GameMain_UI_Status_CoreTree.h"
#include "Scene_GameMain_UI_Status_Player.h"
#include "Scene_GameMain_UI_Resource.h"
#include "DataList_Object.h"
#include "DataList_GameStatus.h"
#include "DataList_Sound.h"
// 共通定義
#include "VariableDefine.h"

// コンストラクタ
Scene_GameMain::Scene_GameMain() : Scene_Base("Scene_GameMain", 0, false, false)
{
	/* データリスト作成 */	
	gpDataListServer->AddDataList(std::make_shared<DataList_GameStatus>());		// ゲーム状態管理
	gpDataListServer->AddDataList(std::make_shared<DataList_Object>());			// オブジェクト管理

	/* シーン作成 */
	gpSceneServer->AddSceneReservation(std::make_shared<Scene_Stage>());						// ステージシーン
	gpSceneServer->AddSceneReservation(std::make_shared<Scene_GameMain_UI_Status_CoreTree>());	// UI:神木(防衛対象)の状態
	gpSceneServer->AddSceneReservation(std::make_shared<Scene_GameMain_UI_Status_Player>());	// UI:プレイヤーの状態
	gpSceneServer->AddSceneReservation(std::make_shared<Scene_GameMain_UI_Resource>());			// UI:ゲーム内リソース

	/* データリスト取得 */
	this->pDataList_Object							= std::dynamic_pointer_cast<DataList_Object>(gpDataListServer->GetDataList("DataList_Object"));			// オブジェクト管理
	this->pDataList_GameStatus						= std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));	// ゲーム状態管理
	std::shared_ptr<DataList_Sound>	pDataList_Sound	= std::dynamic_pointer_cast<DataList_Sound>(gpDataListServer->GetDataList("DataList_Sound"));			// サウンド管理

	/* BGMを設定 */
	pDataList_Sound->BGM_Play("fantasyXV");

	/* 初期化 */
	this->iScoreUpdateTimer	= 0;	// スコア更新までのカウントダウン
	this->iWaveUpdateTimer	= 0;	// ウェーブ更新までのカウントダウン
}

// デストラクタ
Scene_GameMain::~Scene_GameMain()
{
	 /* データリスト削除 */
	gpDataListServer->DeleteDataList("DataList_GameStatus");	// ゲーム状態管理
	gpDataListServer->DeleteDataList("DataList_Object");		// オブジェクト管理
}

// 更新
void Scene_GameMain::Update()
{
	/* オブジェクト更新 */
	this->pDataList_Object->Update_All();

	/* 削除フラグが有効なオブジェクト削除 */
	this->pDataList_Object->DeleteFlagged_AllObject();

	/* スコア更新 */
	if (this->iScoreUpdateTimer <= 0)
	{
		// カウントが0以下であるならば
		/* スコアを加算 */
		// ※ ウェーブ数分のスコアを加算
		int iScore = this->pDataList_GameStatus->GetScore();
		iScore += this->pDataList_GameStatus->GetWave();
		this->pDataList_GameStatus->SetScore(iScore);

		/* カウントダウンをリセット */
		this->iScoreUpdateTimer = SCORE_UPDATE_TIME;
	}
	else
	{
		// カウントが0以下でないならば
		this->iScoreUpdateTimer--;
	}

	/* ウェーブ更新 */
	if (this->iWaveUpdateTimer <= 0)
	{
		// カウントが0以下であるならば
		/* ウェーブ数を加算 */
		int iWave = this->pDataList_GameStatus->GetWave();
		iWave++;
		this->pDataList_GameStatus->SetWave(iWave);

		/* カウントダウンをリセット */
		this->iWaveUpdateTimer = WAVE_UPDATE_TIME;
	}
	else
	{
		// カウントが0以下でないならば
		this->iWaveUpdateTimer--;
	}

	/* "F1"キーが入力されたらデバッグモードの有効・無効の切り替え */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_F1] == TRUE)
	{
		gbDebugMode = !gbDebugMode;
	}

	/* プレイヤー、あるいは神木のHPが0以下であるか */
	if (this->pDataList_GameStatus->GetHp_Player() <= 0 || this->pDataList_GameStatus->GetHp_CoreTree() <= 0)
	{
		/* シーン"ゲームオーバー(フェードアウト)"を作成 */
		gpSceneServer->AddSceneReservation(std::make_shared<Scene_GameOver_Fadeout>());

		return;
	}
}
