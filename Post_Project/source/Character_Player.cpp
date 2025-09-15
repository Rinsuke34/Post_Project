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
	/* 初期化 */
	this->iMotionCount		= 0;
	this->bMotionLoopFlg	= true;

	/* アニメーション初期設定 */
	// アニメーション設定
	this->AnimFileName		= "Test_Player";
	this->NowMotionName		= "Delay";
	// パーツアニメーションセットアップ
	this->pDataList_2DPartsAnimCreateTool->LoadPartsAnimData(this->AnimFileName);

	/* チームタグ設定 */
	this->SetTeamTag("Player");

	/* ステータス関係 */
	// ※仮設定
	this->iSpeed = TEST_PLAYER_MOVE_SPEED;
}

// デストラクタ
Character_Player::~Character_Player()
{
	
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
	Character_Base::Update_Animation();
}
