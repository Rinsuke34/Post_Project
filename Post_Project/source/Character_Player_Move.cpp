/* プレイヤークラスの定義 */
// ※ 移動部分のみ

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Character_Player.h"
// 関連クラス
#include "DataList_Object.h"
#include "Ground_Base.h"
#include "Ground_Model.h"
// 共通定義
#include "Test_ConstantDefine.h"

// 重力処理
void Character_Player::Update_ApplyGravity()
{
	// テスト
	this->fGravityAcceleration = TEST_GRAVITY_ACCELERATION;	// 重力加速度(仮設定)

	/* ジャンプ処理 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_SPACE] == TRUE)
	{
		this->fGravityVelocity = TEST_JUMP_GRAVITY_VELOCITY;
	}

	/* 押し出し処理 */
	Character_Base::bGround_PushBack_Gravity();
}

// 移動処理
void Character_Player::Update_ApplyMovement()
{
	/* 移動方向を取得 */
	VECTOR vecMoveDirection = VGet(0.f, 0.f, 0.f);
	// 入力から移動方向を取得
	bool bIsMoving = false;
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_W] == TRUE)
	{
		vecMoveDirection = VAdd(vecMoveDirection, VGet(0.f, 0.f, 1.f));
		bIsMoving = true;
	}
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_S] == TRUE)
	{
		vecMoveDirection = VAdd(vecMoveDirection, VGet(0.f, 0.f, -1.f));
		bIsMoving = true;
	}
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_A] == TRUE)
	{
		vecMoveDirection = VAdd(vecMoveDirection, VGet(-1.f, 0.f, 0.f));
		bIsMoving = true;
	}
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_D] == TRUE)
	{
		vecMoveDirection = VAdd(vecMoveDirection, VGet(1.f, 0.f, 0.f));
		bIsMoving = true;
	}

	// 移動していない場合は処理を抜ける
	if (!bIsMoving)
	{
		return;
	}

	/* 押し出し処理 */
	Character_Base::bGround_PushBack_Movement(vecMoveDirection);
}