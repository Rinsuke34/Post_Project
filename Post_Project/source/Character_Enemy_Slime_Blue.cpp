/* 青スライム(エネミー)クラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Character_Enemy_Slime_Blue.h"
// 関連クラス
#include "DataList_GameStatus.h"

// コンストラクタ
Character_Enemy_Slime_Blue::Character_Enemy_Slime_Blue() : Npc_Base()
{
	/* 初期化 */
	this->iMotionCount		= 0;
	this->bMotionLoopFlg	= true;

	/* アニメーション初期設定 */
	// アニメーション設定
	this->AnimFileName	= "Slime_Blue";
	this->NowMotionName	= "Move";
	// パーツアニメーションセットアップ
	this->pDataList_2DPartsAnimCreateTool->LoadPartsAnimData(this->AnimFileName);

	/* チームタグ設定 */
	this->SetTeamTag("Enemy");

	/* ステータス関係 */
	// ※仮設定
	this->iSpeed = 2;
}

// デストラクタ
Character_Enemy_Slime_Blue::~Character_Enemy_Slime_Blue()
{

}

// 初期設定
void Character_Enemy_Slime_Blue::InitialSetup()
{
	/* ベースクラスの初期化処理 */
	Character_Base::InitialSetup();

	/* ルート設定 */
	Route_Search();
}

// 更新
void Character_Enemy_Slime_Blue::Update()
{
	/* 移動処理 */
	Update_Move();

	/* ベースクラスの更新処理 */
	Character_Base::Update();

	/* アニメーションの更新 */
	Character_Base::Update_Animation();
}

// 移動処理
void Character_Enemy_Slime_Blue::Update_Move()
{
	/* 縦方向の押し出し処理 */
	Character_Base::Ground_PushBack_Gravity();

	VECTOR vecTargetPosition	= this->pDataList_GameStatus->GetPlayerPosition_WoldMap();
	VECTOR vecMoveDirection		= VSub(vecTargetPosition, this->vecBasePosition);
	vecMoveDirection.y = 0.f;

	/* 横方向の押し出し処理 */
	Character_Base::Ground_PushBack_Movement(vecMoveDirection);
}
