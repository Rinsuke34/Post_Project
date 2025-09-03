/* オブジェクトのベースクラスの定義 */

#include "Object_Base.h"


// コンストラクタ
Object_Base::Object_Base()
{
	/* 初期化 */
	this->bDeleteFlg = false;	// 削除フラグ
}
