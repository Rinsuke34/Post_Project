/* アイテムのベースクラスの提議 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Item_Base.h"
// 関連クラス
#include "DataList_GameStatus.h"
// 共通提議
#include "ConstantDefine.h"

// コンストラクタ
Item_Base::Item_Base() : Actor_Base()
{
	// データリスト取得
	this->pDataList_GameStatus = std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));							// ゲーム状態管理

	/* 初期化 */
	this->iDespawnTime = DESPAWN_TIME;
}

// 初期設定
void Item_Base::InitialSetup()
{
	/* コリジョンを設定 */
	this->stBox.vecBoxCenter = this->vecBasePosition;
	this->stBox.vecBoxHalfSize = VGet(COLLISION_HALF, COLLISION_HALF, COLLISION_HALF);
}

// 更新
void Item_Base::Update()
{
	/* 消滅までの時間を進める */
	--this->iDespawnTime;
	if (this->iDespawnTime <= 0)
	{
		// 消滅する時間になった場合
		/* 削除フラグを有効化 */
		this->bDeleteFlg = false;
		return;
	}

	/* プレイヤーと接触したか */
	// プレイヤーのコリジョンボックスを作成
	Struct_Collision::COLLISION_BOX stPlayerBox;
	stPlayerBox.vecBoxCenter	= this->pDataList_GameStatus->GetPlayerPosition_WoldMap();
	stPlayerBox.vecBoxHalfSize	= VGet(MAP_BLOCK_SIZE_X / 2.f, MAP_BLOCK_SIZE_Y / 2.f, MAP_BLOCK_SIZE_Z / 2.f);

	/* 接触しているか確認 */
	if(PUBLIC_PROCESS::bBoxHitCheck(this->stBox, stPlayerBox))
	{
		// 接触している場合
		/* アイテム取得処理を行う */
		Update_ItemGet();

		/* 削除フラグを有効化 */
		this->bDeleteFlg = true;
		return;
	}
}

// 描画
void Item_Base::Draw()
{
	/* 画像のサイズを取得 */
	int iGrWidth, iGrHeight;
	GetGraphSize(*this->piGrHandle, &iGrWidth, &iGrHeight);

	/* 画像サイズの半分を取得 */
	float fHalfGrWidth	= static_cast<float>(iGrWidth) / 2.f;
	float fHalfGrHeight	= static_cast<float>(iGrHeight) / 2.f;

	/* 画像をビルボードで描写する */
	DrawModiBillboard3D(this->vecBasePosition,
		-fHalfGrWidth,	-fHalfGrHeight,		// 左上
		+fHalfGrWidth,	-fHalfGrHeight,		// 右上
		+fHalfGrWidth,	+fHalfGrHeight,		// 右下
		-fHalfGrWidth,	+fHalfGrHeight,		// 左下
		*this->piGrHandle, TRUE);
}
