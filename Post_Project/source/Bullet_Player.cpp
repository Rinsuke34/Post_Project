/* バレット(プレイヤー)クラスの提議 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Bullet_Player.h"
// 関数クラス
#include "DataList_Image.h"

// コンストラクタ
Bullet_Player::Bullet_Player() : Bullet_Base()
{
	/* データリスト取得 */
	// 画像データ管理
	std::shared_ptr<DataList_Image>	pDataList_Image = std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));

	/* 使用する画像を設定 */
	std::string fileName = "BulletImage/Bullet_Player";
	this->piGrHandle = pDataList_Image->iGetGrhandle(fileName);

	// チームタグを設定
	this->SetTeamTag("Player");
}
