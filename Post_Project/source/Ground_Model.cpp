/* 地形(3Dモデル)クラスの定義 */

#include "Ground_Model.h"

// コンストラクタ
Ground_Model::Ground_Model() : Ground_Base()
{
	/* 初期化 */
	this->iModelHandle		= -1;	// モデルハンドル
	this->iCollisionFrameNo	= -1;	// コリジョン用のフレーム番号

	this->vecPosition		= VGet(0.f, 0.f, 0.f);		// オブジェクトの座標
	this->vecRotation		= VGet(0.f, 0.f, 0.f);		// オブジェクトの回転量
	this->vecScale			= VGet(0.f, 0.f, 0.f);		// オブジェクトの拡大率(x,y,z方向それぞれの拡大倍率)
}

// デストラクタ
Ground_Model::~Ground_Model()
{

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
	Update_Collision();
}

// 更新
void Ground_Model::Update()
{

}

// 描画
void Ground_Model::Draw()
{

}

// 更新(コリジョン情報)
void Ground_Model::Update_Collision()
{
	/* コリジョンフレーム番号取得 */
	this->iCollisionFrameNo	=	MV1SearchFrame(this->iModelHandle, "Collision");

	/* コリジョンフレーム番号の取得を成功したかの確認 */
	if (this->iCollisionFrameNo >= 0)
	{
		// コリジョンフレーム番号の取得に成功した場合
		/* コリジョンの設定されたフレームのコリジョン情報構築 */
		MV1SetupCollInfo(this->iModelHandle, this->iCollisionFrameNo, 1, 1, 1);

		/* コリジョンの設定されたフレームを描写しないように設定 */
		MV1SetFrameVisible(this->iModelHandle, this->iCollisionFrameNo, FALSE);
	}
}

// コリジョン接触判定
// モデル - カプセル
bool Ground_Model::HitCheck(Struct_Collision::COLLISION_CAPSULE	stCapsule)
{
	// 引数
	// stCapsule	: 判定するカプセルコリジョン
	// 戻り値
	// bool : 接触している(true) / 接触していない(false)

	/* コリジョンフレームが存在しないか確認 */
	if (this->iCollisionFrameNo < 0)
	{
		// 存在しない場合
		/* 非接触として判定する */
		return false;
	}

	/* ポリゴンとの接触情報 */
	MV1_COLL_RESULT_POLY_DIM stHitPolyDim;

	/* プラットフォームのモデルと対象のカプセルコリジョンが接触しているかの情報取得 */
	stHitPolyDim = MV1CollCheck_Capsule(
		/* このオブジェクトのコリジョン */
		this->iModelHandle, this->iCollisionFrameNo,
		/* 判定するオブジェクトのコリジョン */
		stCapsule.vecCapsuleTop, stCapsule.vecCapsuleBottom, stCapsule.fCapsuleRadius);

	/* 接触数を取得 */
	if (stHitPolyDim.HitNum > 0)
	{
		// 接触している場合
		return true;
	}
	//接触していない場合
	return false;
}

// モデル - 球体
bool Ground_Model::HitCheck(Struct_Collision::COLLISION_SQHERE	stSqhere)
{
	// 引数
	// stCapsule	: 判定する球体コリジョン
	// 戻り値
	// bool			: 接触している(true) / 接触していない(false)

	/* コリジョンフレームが存在しないか確認 */
	if (this->iCollisionFrameNo < 0)
	{
		// 存在しない場合
		/* 非接触として判定する */
		return false;
	}

	/* ポリゴンとの接触情報 */
	MV1_COLL_RESULT_POLY_DIM stHitPolyDim;

	/* プラットフォームのモデルと対象の球体コリジョンが接触しているかの情報取得 */
	stHitPolyDim = MV1CollCheck_Capsule(
		/* このオブジェクトのコリジョン */
		this->iModelHandle, this->iCollisionFrameNo,
		/* 判定するオブジェクトのコリジョン */
		stSqhere.vecSqhere, stSqhere.vecSqhere, stSqhere.fSqhereRadius);

	/* 接触数を取得 */
	if (stHitPolyDim.HitNum > 0)
	{
		// 接触している場合
		return true;
	}
	// 接触していない場合
	return false;
}

// モデル - 線分
bool Ground_Model::HitCheck(Struct_Collision::COLLISION_LINE	stLine)
{
	// 引数
	// stLine	: 判定する線分コリジョン
	// 戻り値
	// bool		: 接触している(true) / 接触していない(false)

	/* コリジョンフレームが存在しないか確認 */
	if (this->iCollisionFrameNo < 0)
	{
		// 存在しない場合
		/* 非接触として判定する */
		return false;
	}

	/* ポリゴンとの接触情報 */
	MV1_COLL_RESULT_POLY stHitPolyDim;

	/* プラットフォームのモデルと対象の線分コリジョンが接触しているかの情報取得 */
	stHitPolyDim = MV1CollCheck_Line(
		/* このオブジェクトのコリジョン */
		this->iModelHandle, this->iCollisionFrameNo,
		/* 判定するオブジェクトのコリジョン */
		stLine.vecLineStart, stLine.vecLineEnd);

	/* 接触したか確認 */
	if (stHitPolyDim.HitFlag == 1)
	{
		// 接触している場合
		return true;
	}

	// 接触していない場合
	return false;
}
