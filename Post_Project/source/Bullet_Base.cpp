/* バレットのベースクラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Bullet_Base.h"
// 関連クラス
#include "DataList_GameStatus.h"
#include "DataList_Object.h"
#include "Ground_Base.h"
// 共通定義
#include "FunctionDefine.h"

// コンストラクタ
Bullet_Base::Bullet_Base() : Actor_Base()
{
	// データリスト取得
	this->pDataList_GameStatus = std::dynamic_pointer_cast<DataList_GameStatus>(gpDataListServer->GetDataList("DataList_GameStatus"));							// ゲーム状態管理

	/* 初期化 */
	this->iAttack		= 0;					// 攻撃力
	this->piGrHandle	= nullptr;				// 使用する画像のハンドル
	this->vecMove		= VGet(0.f, 0.f, 0.f);	// 移動量
	this->iDespawnTime	= DESPAWN_TIME;			// 弾が消滅するまでの時間

	// コリジョン初期設定
	this->stBox.vecBoxCenter	= this->vecBasePosition;
	this->stBox.vecBoxHalfSize = VGet(COLLISION_HALF_SIZE, COLLISION_HALF_SIZE, COLLISION_HALF_SIZE);
}

// 更新
void Bullet_Base::Update()
{
	/* 消滅までの時間を進める */
	--this->iDespawnTime;
	if (this->iDespawnTime <= 0)
	{
		// 消滅する時間になった場合
		/* 削除フラグを有効化 */
		this->bDeleteFlg = true;
		return;
	}

	/* 移動処理 */
	this->vecBasePosition = VAdd(this->vecBasePosition, this->vecMove);

	/* 移動後座標にコリジョンを再設定 */
	this->stBox.vecBoxCenter	= this->vecBasePosition;

	/* 地形との接地判定 */
	// ※ エリア外の場合は足場との当たり判定を行わない
	int iAreaNo = iCheckCurrentAreaNo();
	if (iAreaNo != -1)
	{
		/* 判定対象リストを作成 */
		std::vector<std::shared_ptr<Ground_Base>> CollisionList;
		// 現在のグリッドとその四方のグリッドの地形
		int iGridX = iGetGridIndexX(this->stBox.vecBoxCenter.x);
		int iGridZ = iGetGridIndexZ(this->stBox.vecBoxCenter.z);
		for (int iX = iGridX - 1; iX <= iGridX + 1; iX++)
		{
			for (int iZ = iGridZ - 1; iZ <= iGridZ + 1; iZ++)
			{
				for (auto& Ground : this->pDataList_Object->GetGroundList(iX, iZ))
				{
					CollisionList.push_back(Ground);
				}
			}
		}

		/* 対象の地形に接触しているか確認 */
		for (auto& Collision : CollisionList)
		{
			/* 接触しているか確認 */
			if (Collision->HitCheck(this->stBox))
			{
				// 接触している場合
				/* 削除フラグを有効化 */
				this->bDeleteFlg = true;
				return;
			}
		}
	}
}

// 描画
void Bullet_Base::Draw()
{
	/* 画像のサイズを取得 */
	int iGrWidth, iGrHeight;
	GetGraphSize(*this->piGrHandle, &iGrWidth, &iGrHeight);

	/* 画像サイズの半分を取得 */
	float fHalfGrWidth	= static_cast<float>(iGrWidth) / 2.f;
	float fHalfGrHeight	= static_cast<float>(iGrHeight) / 2.f;

	/* 画像をビルボードで描写する */
	DrawModiBillboard3D(this->vecBasePosition,
		-fHalfGrWidth, -fHalfGrHeight,		// 左上
		+fHalfGrWidth, -fHalfGrHeight,		// 右上
		+fHalfGrWidth, +fHalfGrHeight,		// 右下
		-fHalfGrWidth, +fHalfGrHeight,		// 左下
		*this->piGrHandle, TRUE);

	/* コリジョン描画(デバッグ用) */
	Draw_Collision();
}
