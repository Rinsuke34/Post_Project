/* シーン"ステージ"の定義 */
// ※セットアップ用の処理部分のみ

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_Stage.h"
// 関連クラス
#include "DataList_Object.h"
#include "Character_Player.h"

// オブジェクト配置
void Scene_Stage::Setup_PlaceObject()
{
	/* プレイヤー追加(仮) */
	std::shared_ptr<Character_Player> pPlayer = std::make_shared<Character_Player>();
	pPlayer->SetPosition(VGet(6144.f / 2, 300.f, 6144.f / 2));
	this->pDataList_Object->AddObject_Actor(pPlayer);
}
