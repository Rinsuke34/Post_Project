/* オブジェクトのベースクラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Object_Base.h"

// コンストラクタ
Object_Base::Object_Base()
{
	/* 初期化 */
	this->bDeleteFlg = false;	// 削除フラグ
}

// 描画(シャドウマップ用)
void Object_Base::Draw_Shadow()
{
	// ※基本的に通常の描写と同じで良いが、オブジェクトの形と影の形が異なる場合はこの関数をオーバーライドして調整
	Draw();
}
