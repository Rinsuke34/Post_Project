/* 地形のベースクラスの定義 */

/* 使用する要素のインクルード */
// 標準ライブラリ
#define NOMINMAX
#include <algorithm>
// ヘッダファイル
#include "Ground_Base.h"
// 共通定義
#include "ConstantDefine.h"

// コンストラクタ
Ground_Base::Ground_Base() : Object_Base()
{

}

// コリジョン接触判定
// 球体 - ボックス
bool Ground_Base::HitCheck(Struct_Collision::COLLISION_SQHERE stSqhere)
{
	// 引数
	// stSqhere	: 判定する球体コリジョン
	// 戻り値
	// bool		: 接触している(true) / 接触していない(false)

	bool bHitFlg = false;

	/* 判定を行う距離内であるか */
	if (std::abs(VSquareSize(VSub(stSqhere.vecSqhere, this->stBox.vecBoxCenter))) > COLLISION_CHECK_DISTANCE)
	{
		// 判定を行う距離外である場合は接触していないとみなす
		return bHitFlg;
	}

	/* 接触判定 */
	// ボックスの各軸の最小値と最大値を取得
	float fBoxMinX = this->stBox.vecBoxCenter.x - (this->stBox.vecBoxHalfSize.x / 2.0f);
	float fBoxMaxX = this->stBox.vecBoxCenter.x + (this->stBox.vecBoxHalfSize.x / 2.0f);
	float fBoxMinY = this->stBox.vecBoxCenter.y - (this->stBox.vecBoxHalfSize.y / 2.0f);
	float fBoxMaxY = this->stBox.vecBoxCenter.y + (this->stBox.vecBoxHalfSize.y / 2.0f);
	float fBoxMinZ = this->stBox.vecBoxCenter.z - (this->stBox.vecBoxHalfSize.z / 2.0f);
	float fBoxMaxZ = this->stBox.vecBoxCenter.z + (this->stBox.vecBoxHalfSize.z / 2.0f);

	// 球体の中心座標をボックスの各軸の範囲内に収める
	float fClosestX = PUBLIC_PROCESS::fClamp(stSqhere.vecSqhere.x, fBoxMaxX, fBoxMinX);
	float fClosestY = PUBLIC_PROCESS::fClamp(stSqhere.vecSqhere.y, fBoxMaxY, fBoxMinY);
	float fClosestZ = PUBLIC_PROCESS::fClamp(stSqhere.vecSqhere.z, fBoxMaxZ, fBoxMinZ);

	// 球体の中心と最も近い点との距離を計算
	float fDistanceX = stSqhere.vecSqhere.x - fClosestX;
	float fDistanceY = stSqhere.vecSqhere.y - fClosestY;
	float fDistanceZ = stSqhere.vecSqhere.z - fClosestZ;
	float fDistanceSquared = (fDistanceX * fDistanceX) + (fDistanceY * fDistanceY) + (fDistanceZ * fDistanceZ);

	// 距離の二乗が球体の半径の二乗以下であれば接触している
	if (fDistanceSquared <= (stSqhere.fSqhereRadius * stSqhere.fSqhereRadius))
	{
		bHitFlg = true;
	}

	return bHitFlg;
}

// 線分 - ボックス
bool Ground_Base::HitCheck(Struct_Collision::COLLISION_LINE stLine)
{
	// 引数
	// stLine	: 判定する線コリジョン
	// 戻り値
	// bool		: 接触している(true) / 接触していない(false)

	// ボックスの各軸の最小値と最大値を配列で取得
	float boxCenter[3] = { this->stBox.vecBoxCenter.x, this->stBox.vecBoxCenter.y, this->stBox.vecBoxCenter.z };
	float boxSize[3] = { this->stBox.vecBoxHalfSize.x,   this->stBox.vecBoxHalfSize.y,   this->stBox.vecBoxHalfSize.z };
	float boxMin[3], boxMax[3];
	for (int i = 0; i < 3; ++i)
	{
		boxMin[i] = boxCenter[i] - boxSize[i] / 2.0f;
		boxMax[i] = boxCenter[i] + boxSize[i] / 2.0f;
	}

	// 線分の始点・終点・方向ベクトルを配列で取得
	float start[3] = { stLine.vecLineStart.x, stLine.vecLineStart.y, stLine.vecLineStart.z };
	float end[3] = { stLine.vecLineEnd.x,   stLine.vecLineEnd.y,   stLine.vecLineEnd.z };
	float dir[3] = { end[0] - start[0], end[1] - start[1], end[2] - start[2] };

	float tmin = 0.0f;
	float tmax = 1.0f;

	/* 接触判定 */
	// 各軸ごとにスラブ法で判定
	for (int i = 0; i < 3; ++i)
	{
		if (fabs(dir[i]) < 1e-6f)
		{
			if (start[i] < boxMin[i] || start[i] > boxMax[i])
			{
				return false;
			}
		}
		else
		{
			float ood = 1.0f / dir[i];
			float t1 = (boxMin[i] - start[i]) * ood;
			float t2 = (boxMax[i] - start[i]) * ood;
			if (t1 > t2)
			{
				std::swap(t1, t2);
			}
			tmin = std::max(tmin, t1);
			tmax = std::min(tmax, t2);
			if (tmin > tmax)
			{
				return false;
			}
		}
	}

	// tmin <= tmax なら交差
	return true;
}

// ボックス - ボックス
bool Ground_Base::HitCheck(Struct_Collision::COLLISION_BOX stBox)
{
	// 引数
	// stBox	: 判定するボックスコリジョン
	// 戻り値
	// bool		: 接触している(true) / 接触していない(false)

	/* 判定を行う距離内であるか */
	if (std::abs(VSquareSize(VSub(stBox.vecBoxCenter, this->stBox.vecBoxCenter))) > COLLISION_CHECK_DISTANCE)
	{
		// 判定を行う距離外である場合は接触していないとみなす
		return false;
	}

	// 自身のボックスの最小・最大座標を取得
	float afBox_Min_This[3] =
	{
		this->stBox.vecBoxCenter.x - this->stBox.vecBoxHalfSize.x,
		this->stBox.vecBoxCenter.y - this->stBox.vecBoxHalfSize.y,
		this->stBox.vecBoxCenter.z - this->stBox.vecBoxHalfSize.z
	};

	float afBox_Max_This[3] =
	{
		this->stBox.vecBoxCenter.x + this->stBox.vecBoxHalfSize.x,
		this->stBox.vecBoxCenter.y + this->stBox.vecBoxHalfSize.y,
		this->stBox.vecBoxCenter.z + this->stBox.vecBoxHalfSize.z
	};

	// 判定するボックスの最小・最大を取得
	float afBox_Min[3] =
	{
		stBox.vecBoxCenter.x - stBox.vecBoxHalfSize.x,
		stBox.vecBoxCenter.y - stBox.vecBoxHalfSize.y,
		stBox.vecBoxCenter.z - stBox.vecBoxHalfSize.z
	};

	float afBox_Max[3] =
	{
		stBox.vecBoxCenter.x + stBox.vecBoxHalfSize.x,
		stBox.vecBoxCenter.y + stBox.vecBoxHalfSize.y,
		stBox.vecBoxCenter.z + stBox.vecBoxHalfSize.z
	};

	// 各軸で重なっている個所がないならfalseを返す
	for (int i = 0; i < 3; ++i)
	{
		if (afBox_Max_This[i] < afBox_Min[i] || afBox_Min_This[i] > afBox_Max[i])
		{
			return false;
		}
	}

	// すべての軸で重なりがあればtrue
	return true;
}

// 衝突点取得
// 線分 - ボックス
VECTOR Ground_Base::HitPosition(Struct_Collision::COLLISION_LINE stLine)
{
	// 引数
	// stLine	: 判定する線コリジョン
	// 戻り値
	// VECTOR	: 接触した座標(最もStartに近い点) / 接触していない場合はEnd座標(終点)を返す

	// ボックスの各軸の最小値と最大値を配列で取得
	float boxCenter[3]	= { this->stBox.vecBoxCenter.x,		this->stBox.vecBoxCenter.y,		this->stBox.vecBoxCenter.z };
	float boxSize[3]	= { this->stBox.vecBoxHalfSize.x,	this->stBox.vecBoxHalfSize.y,	this->stBox.vecBoxHalfSize.z };
	float boxMin[3], boxMax[3];
	for (int i = 0; i < 3; ++i)
	{
		boxMin[i] = boxCenter[i] - boxSize[i] / 2.0f;
		boxMax[i] = boxCenter[i] + boxSize[i] / 2.0f;
	}

	// 線分の始点・終点・方向ベクトルを配列で取得
	float start[3] = { stLine.vecLineStart.x, stLine.vecLineStart.y, stLine.vecLineStart.z };
	float end[3] = { stLine.vecLineEnd.x, stLine.vecLineEnd.y, stLine.vecLineEnd.z };
	float dir[3] = { end[0] - start[0], end[1] - start[1], end[2] - start[2] };

	float tmin = 0.0f;
	float tmax = 1.0f;

	// スラブ法で交差判定とtmin算出
	for (int i = 0; i < 3; ++i)
	{
		if (fabs(dir[i]) < 1e-6f)
		{
			if (start[i] < boxMin[i] || start[i] > boxMax[i])
			{
				// 交差しない
				return stLine.vecLineStart;
			}
		}
		else
		{
			float ood = 1.0f / dir[i];
			float t1 = (boxMin[i] - start[i]) * ood;
			float t2 = (boxMax[i] - start[i]) * ood;
			if (t1 > t2)
			{
				std::swap(t1, t2);
			}
			tmin = std::max(tmin, t1);
			tmax = std::min(tmax, t2);
			if (tmin > tmax)
			{
				// 交差しない
				return stLine.vecLineStart;
			}
		}
	}

	// tminが0～1の範囲なら交点あり
	if (tmin >= 0.0f && tmin <= 1.0f)
	{
		VECTOR hitPos;
		hitPos.x = start[0] + dir[0] * tmin;
		hitPos.y = start[1] + dir[1] * tmin;
		hitPos.z = start[2] + dir[2] * tmin;
		return hitPos;
	}
	else
	{
		// 交差範囲外
		return stLine.vecLineStart;
	}
}
