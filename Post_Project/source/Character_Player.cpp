/* プレイヤークラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Character_Player.h"
// 関連クラス
#include "DataList_GameStatus.h"
// 共通定義
#include "Test_ConstantDefine.h"
#include "ConstantDefine.h"

// コンストラクタ
Character_Player::Character_Player() : Character_Base()
{
	// データリスト取得
	this->pDataList_GameStatus				= std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));							// ゲーム状態管理
	this->pDataList_2DPartsAnimCreateTool	= std::dynamic_pointer_cast<DataList_2DPartsAnimCreateTool>(gpDataListServer->GetDataList("DataList_2DPartsAnimCreateTool"));	// 2Dパーツアニメーションツール

	// 画像データ作成
	this->iScreenHandle_Animation	= MakeScreen(CHARACTER_PARTS_ANIM_DRAW_SIZE_WIDE, CHARACTER_PARTS_ANIM_DRAW_SIZE_HEIGHT, TRUE);

	/* 初期化 */
	this->AnimFileName	= "Test_Player";	// アニメーションファイル名
	this->NowMotionName	= "Delay";			// 現在のモーション名
	this->iMotionCount	= 0;

	// パーツアニメーションセットアップ
	this->pDataList_2DPartsAnimCreateTool->LoadPartsAnimData(this->AnimFileName);
	
	/* コリジョン設定 */
	// ※仮設定
	this->stBox.vecBoxHalfSize	= VGet(64 / 2, 32 / 2, 64 / 2);

	/* ステータス関係 */
	// ※仮設定
	this->iSpeed = TEST_PLAYER_MOVE_SPEED;
}

// デストラクタ
Character_Player::~Character_Player()
{
	/* 画像データ削除 */
	// アニメーション用
	DeleteGraph(this->iScreenHandle_Animation);
}

// 更新
void Character_Player::Update()
{
	/* 移動・重力処理 */
	Update_ApplyGravity();
	Update_ApplyMovement();	

	/* ワールドマップ上の座標を設定 */
	this->pDataList_GameStatus->SetPlayerPosition_WoldMap(this->vecBasePosition);

	/* ベースクラスの更新処理 */
	Character_Base::Update();

	/* アニメーションの更新 */
	Update_Animation();
}
