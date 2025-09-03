/* 地形(平面)クラスの定義 */

#include "Ground_Plane.h"


// コンストラクタ
Ground_Plane::Ground_Plane() : Ground_Base()
{
	/* 初期化 */
	this->vecNormal = VGet(0.0f, 1.0f, 0.0f);
	for(int iIndex = 0; iIndex < 4; ++iIndex)
	{
		this->avecVertex[iIndex] = VGet(0.0f, 0.0f, 0.0f);
	}
	this->piGrHandle = nullptr;
}

// 描画
void Ground_Plane::Draw()
{
	/* 頂点座標を設定 */
	VERTEX3D aVertex[4];
	for (int iIndex = 0; iIndex < 4; ++iIndex)
	{
		aVertex[iIndex].pos		= this->avecVertex[iIndex];			// 頂点座標
		aVertex[iIndex].norm	= this->vecNormal;					// 法線ベクトル
		aVertex[iIndex].dif		= GetColorU8(255, 255, 255, 255);	// 拡散光の
		aVertex[iIndex].spc		= GetColorU8(0, 0, 0, 0);			// 鏡面光の色
		// 頂点のテクスチャ座標
		switch (iIndex)
		{
			case 0: aVertex[iIndex].u = 0.0f; aVertex[iIndex].v = 0.0f; break;
			case 1: aVertex[iIndex].u = 1.0f; aVertex[iIndex].v = 0.0f; break;
			case 2: aVertex[iIndex].u = 1.0f; aVertex[iIndex].v = 1.0f; break;
			case 3: aVertex[iIndex].u = 0.0f; aVertex[iIndex].v = 1.0f; break;
		}
	}

	/* 頂点インデックスを設定 */
	// ※四角形を二つの三角形に分割する
	unsigned short IndexTop[6] = { 0, 1, 2, 0, 2, 3 };

	/* 四角形（板ポリゴン）の描画 */
	DrawPolygonIndexed3D(aVertex, 4, IndexTop, 2, *this->piGrHandle, TRUE);
}

// コリジョン接触判定
// 平面 - カプセル
bool Ground_Plane::HitCheck(Struct_Collision::COLLISION_CAPSULE	stCapsule)
{
	// 引数
	// stCapsule		<-	カプセルの情報
	// 戻り値
	// bool				<-	接触している(true) / 接触していない(false)

	bool bHitFlg = false;

	/* 接触判定 */
	// ※面を二つの三角形に分割して、各三角形とカプセルの当たり判定を行う
	// 三角形1: [0,1,2]
	if (HitCheck_Capsule_Triangle(
		stCapsule.vecCapsuleTop,
		stCapsule.vecCapsuleBottom,
		stCapsule.fCapsuleRadius,
		this->avecVertex[0],
		this->avecVertex[1],
		this->avecVertex[2]) == TRUE)
	{
		bHitFlg = true;
	}

	// 三角形2: [0,2,3]
	if (HitCheck_Capsule_Triangle(
		stCapsule.vecCapsuleTop,
		stCapsule.vecCapsuleBottom,
		stCapsule.fCapsuleRadius,
		this->avecVertex[0],
		this->avecVertex[2],
		this->avecVertex[3]) == TRUE)
	{
		bHitFlg = true;
	}

	return bHitFlg;
}

// 平面 - 球体
bool Ground_Plane::HitCheck(Struct_Collision::COLLISION_SQHERE	stSqhere)
{
	// 引数
	// stSqhere		<-	球体の情報
	// 戻り値
	// bool			<-	接触している(true) / 接触していない(false)

	bool bHitFlg = false;

	/* 接触判定 */
	// ※面を二つの三角形に分割して、各三角形と球体の当たり判定を行う
	// 三角形1: [0,1,2]
	if (HitCheck_Sphere_Triangle(
		stSqhere.vecSqhere,
		stSqhere.fSqhereRadius,
		this->avecVertex[0],
		this->avecVertex[1],
		this->avecVertex[2]) == TRUE)
	{
		bHitFlg = true;
	}

	// 三角形2: [0,2,3]
	if (HitCheck_Sphere_Triangle(
		stSqhere.vecSqhere,
		stSqhere.fSqhereRadius,
		this->avecVertex[0],
		this->avecVertex[2],
		this->avecVertex[3]) == TRUE)
	{
		bHitFlg = true;
	}

	return bHitFlg;
}

// 平面 - 線分
bool Ground_Plane::HitCheck(Struct_Collision::COLLISION_LINE	stLine)
{
	// 引数
	// stLine		<-	線分の情報
	// 戻り値
	// bool			<-	接触している(true) / 接触していない(false)

	bool bHitFlg = false;

	/* 接触判定 */
	// ※面を二つの三角形に分割して、各三角形と線分の当たり判定を行う
	// 三角形1: [0,1,2]
	if (HitCheck_Line_Triangle(
		stLine.vecLineStart,
		stLine.vecLineEnd,
		this->avecVertex[0],
		this->avecVertex[1],
		this->avecVertex[2]).HitFlag == TRUE)
	{
		bHitFlg = true;
	}

	// 三角形2: [0,2,3]
	if (HitCheck_Line_Triangle(
		stLine.vecLineStart,
		stLine.vecLineEnd,
		this->avecVertex[0],
		this->avecVertex[1],
		this->avecVertex[2]).HitFlag == TRUE)
	{
		bHitFlg = true;
	}

	return bHitFlg;
}
