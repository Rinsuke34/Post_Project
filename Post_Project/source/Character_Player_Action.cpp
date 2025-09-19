/* プレイヤークラスの定義 */
// ※ 行動や攻撃処理を行う

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Character_Player.h"
// 関連クラス
#include "DataList_Object.h"
#include "Ground_Base.h"
#include "Ground_Model.h"

// 行動処理
void Character_Player::Update_Action()
{
	/* 移動・重力処理 */
	Update_ApplyGravity();
	Update_ApplyMovement();


}
