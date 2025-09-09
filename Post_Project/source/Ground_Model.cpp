/* 地形(3Dモデル)クラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Ground_Model.h"

// コンストラクタ
Ground_Model::Ground_Model() : Ground_Base()
{
	/* 初期化 */
	this->iModelHandle		= -1;	// モデルハンドル

	this->vecPosition		= VGet(0.f, 0.f, 0.f);		// オブジェクトの座標
	this->vecRotation		= VGet(0.f, 0.f, 0.f);		// オブジェクトの回転量
	this->vecScale			= VGet(0.f, 0.f, 0.f);		// オブジェクトの拡大率(x,y,z方向それぞれの拡大倍率)
}

// デストラクタ
Ground_Model::~Ground_Model()
{
	/* モデルハンドル削除 */
	MV1DeleteModel(this->iModelHandle);
}

// 初期設定
// ※モデルハンドル、座標、回転量、拡大率を設定した後に呼び出すこと
void Ground_Model::InitialSetup()
{
	/* 座標設定 */
	MV1TerminateCollInfo(this->iModelHandle);

	/* 回転量設定 */
	MV1SetRotationXYZ(this->iModelHandle, this->vecRotation);

	/* 拡大率設定 */
	MV1SetScale(this->iModelHandle, this->vecScale);

	/* 更新(コリジョン情報) */
	SetUpCollision();
}

// 描画
void Ground_Model::Draw()
{
	/* 現在のモデルの透明度取得 */
	float OpacityRate = MV1GetOpacityRate(this->iModelHandle);

	/* 透明度確認 */
	if (OpacityRate > 0.f)
	{
		// 完全に透明でない場合
		/* モデル描写 */
		MV1DrawModel(this->iModelHandle);
	}
}

// コリジョンの設定
void Ground_Model::SetUpCollision()
{
	this->stBox.vecBoxCenter	= { 0.f, 0.f, 0.f };
	this->stBox.vecBoxHalfSize	= { 0.f, 0.f, 0.f };
}
