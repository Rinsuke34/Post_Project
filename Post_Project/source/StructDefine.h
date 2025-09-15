/* プロジェクトで使用する構造体の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 標準ライブラリ
#include <string>

// ベクトル(INT型)
struct VECTOR_INT
{
	int x;
	int y;
	int z;
};

// テクスチャ情報
struct TEXTURE_DATA
{
	std::string BlockName;		// ブロック名
	int			iBlockIndex;	// ブロックのインデックス番号
	std::string aImageName[3];	// 画像名(0:上面, 1:横面, 2:下面)
};

// モデル情報
struct MODEL_DATA
{
	std::string ModelName;		// モデル名
	VECTOR_INT	vecPosition;	// 座標
	VECTOR		vecRotation;	// 回転
	VECTOR		vecScale;		// 拡縮
};

// マーカー情報
struct MARKER_DATA
{
	std::string MarkerName;		// マーカー名
	VECTOR_INT	vecPosition;	// 座標
	VECTOR		vecRotation;	// 回転
};

// ワールドマップ管理用情報
struct WOLD_MAP_DATA
{
	std::string MapName;		// マップ名
	int			iMapType;		// マップの種類(0:中央、1:外側)
};

// エネミースポーンポイント情報
struct ENEMY_SPAWN_POINT_DATA
{
	VECTOR		vecPosition;	// 座標
	int			iPointType;		// ポイントの種類(0:平地、1:岩場、2:砂漠)
};

// 評価リスト(A*アルゴリズム用)
struct ASTAR_EVALUATION_LIST
{
	bool bStartNodeFlg;			// このノードがスタート位置であるかのフラグ
	bool bGoalNodeFlg;			// このノードがゴール位置であるかのフラグ
	int iCost_G;				// Gコスト(開始地点からの移動コスト)
	int iCost_H;				// Hコスト(目的地点までの推定コスト)
	int iCost_F;				// Fコスト(Gコスト + Hコスト)
	bool bOpenListFlg;			// オープンリストに登録されているかのフラグ
	bool bCloseListFlg;			// クローズリストに登録されているかのフラグ
	VECTOR vecPosition;			// ノードの座標
	VECTOR vecParentPosition;	// 親ノードの座標
};
