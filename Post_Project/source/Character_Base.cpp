/* キャラクターのベースクラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Character_Base.h"
// 共通定義
#include "ConstantDefine.h"

// コンストラクタ
Character_Base::Character_Base() : Actor_Base()
{
	/* 初期化 */
	// ステータス系
	this->iHealth			= 0;		// 体力
	this->iMaxHealth		= 0;		// 最大体力
	this->iSpeed			= 0;		// 速度
	// 状態系
	this->bDeadFlg			= false;	// 死亡フラグ
	this->iInvincibleTime	= 0;		// 残り無敵時間(フレーム数)
	// コリジョン
	this->stBox.vecBoxCenter	= VGet(0.0f, 0.0f, 0.0f);
	this->stBox.vecBoxHalfSize	= VGet(1.0f, 1.0f, 1.0f);
}

// 更新
// ※ 基準座標の更新が完了してから実行すること
void Character_Base::Update()
{
	/* HPが残っているか確認 */
	if (this->iHealth <= 0)
	{
		// HPが0以下なら死亡フラグを立てる
		this->bDeadFlg = true;
	}

	/* 無敵時間の更新 */
	if (this->iInvincibleTime > 0)
	{
		--this->iInvincibleTime;
	}

	/* コリジョンの更新 */
	Update_Collision();
}

// 描画(シャドウマップ用)
void Character_Base::Draw_Shadow()
{
	/* コリジョンの中心座標と半径から球体を作成し、影とする */
	DrawSphere3D(this->stBox.vecBoxCenter, this->stBox.vecBoxHalfSize.x, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
}

// コリジョン描画(デバッグ用)
void Character_Base::Draw_Collision()
{
	/* 頂点を設定 */
	VECTOR aVertex[8];
	aVertex[0] = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[1] = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);
	aVertex[2] = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[3] = VGet(this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);
	aVertex[4] = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[5] = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);
	aVertex[6] = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z);
	aVertex[7] = VGet(this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x, this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z);

	/* 線分を描画 */
	DrawLine3D(aVertex[0], aVertex[1], GetColor(255, 255, 255));
	DrawLine3D(aVertex[1], aVertex[5], GetColor(255, 255, 255));
	DrawLine3D(aVertex[5], aVertex[4], GetColor(255, 255, 255));
	DrawLine3D(aVertex[4], aVertex[0], GetColor(255, 255, 255));
	DrawLine3D(aVertex[2], aVertex[3], GetColor(255, 255, 255));
	DrawLine3D(aVertex[3], aVertex[7], GetColor(255, 255, 255));
	DrawLine3D(aVertex[7], aVertex[6], GetColor(255, 255, 255));
	DrawLine3D(aVertex[6], aVertex[2], GetColor(255, 255, 255));
	DrawLine3D(aVertex[0], aVertex[2], GetColor(255, 255, 255));
	DrawLine3D(aVertex[1], aVertex[3], GetColor(255, 255, 255));
	DrawLine3D(aVertex[4], aVertex[6], GetColor(255, 255, 255));
	DrawLine3D(aVertex[5], aVertex[7], GetColor(255, 255, 255));
}

// コリジョン更新
void Character_Base::Update_Collision()
{
	/* コリジョンの中心座標を更新 */
	// ※ 現在の基準座標からコリジョンの中心座標を設定
	this->stBox.vecBoxCenter = VAdd(this->vecBasePosition, VGet(0.f, this->stBox.vecBoxHalfSize.y, 0.f));
}
