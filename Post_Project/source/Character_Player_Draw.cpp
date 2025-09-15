/* プレイヤークラスの定義 */
// ※ 描写部分のみ

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Character_Player.h"
// 関連クラス
#include "DataList_Object.h"
#include "Ground_Base.h"
// 共通定義
#include "Test_ConstantDefine.h"
#include "ConstantDefine.h"

// 描画
void Character_Player::Draw()
{
	/* アニメーション描写 */
	Character_Base::Draw_Animation();

	DrawLine3D(VAdd(this->vecBasePosition, VGet(100.f, 0.f, 0.f)), VAdd(this->vecBasePosition, VGet(-100.f, 0.f, 0.f)), GetColor(255, 0, 0));
	DrawLine3D(VAdd(this->vecBasePosition, VGet(0.f, 100.f, 0.f)), VAdd(this->vecBasePosition, VGet(0.f, -100.f, 0.f)), GetColor(0, 255, 0));
	DrawLine3D(VAdd(this->vecBasePosition, VGet(0.f, 0.f, 100.f)), VAdd(this->vecBasePosition, VGet(0.f, 0.f, -100.f)), GetColor(0, 0, 255));
}
