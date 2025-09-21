/* バレット(NPC)クラスの提議 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Bullet_Npc.h"
// 関数クラス
#include "DataList_Image.h"

// コンストラクタ
Bullet_Npc::Bullet_Npc() : Bullet_Base()
{
	
}

// 初期設定
void Bullet_Npc::InitialSetup()
{
	/* データリスト取得 */
	// 画像データ管理
	std::shared_ptr<DataList_Image>	pDataList_Image = std::dynamic_pointer_cast<DataList_Image>(gpDataListServer->GetDataList("DataList_Image"));

	/* 使用する画像を設定 */
	std::string fileName;
	if (bCheckTeamTag("Enemy"))
	{
		// エネミーである場合
		fileName = "BulletImage/Bullet_Enemy";
	}
	else
	{
		// 味方NPCである場合
		fileName = "BulletImage/Bullet_Friend";
	}
	this->piGrHandle = pDataList_Image->iGetGrhandle(fileName);
}
