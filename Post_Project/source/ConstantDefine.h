/* プロジェクトで使用する定数の宣言 */

#pragma once

/* マップ系 */
// ブロックサイズ
static const float MAP_BLOCK_SIZE_X = 64.f;		// X軸のマップタイルの大きさ
static const float MAP_BLOCK_SIZE_Y = 32.f;		// Y軸のマップタイルの大きさ
static const float MAP_BLOCK_SIZE_Z = 64.f;		// Z軸のマップタイルの大きさ
// エリアサイズ
static const int AREA_SIZE_BLOCK_X = 64;	// X軸のエリアの大きさ(ブロック数単位)
static const int AREA_SIZE_BLOCK_Y = 8;		// X軸のエリアの大きさ(ブロック数単位)
static const int AREA_SIZE_BLOCK_Z = 64;	// X軸のエリアの大きさ(ブロック数単位)
// エリア情報
// ※エリアは9つで構成される(中心エリア+周囲8エリア)
// エリア0 | エリア1 | エリア2
// エリア3 | エリア4 | エリア5
// エリア6 | エリア7 | エリア8
static const int AREA_NO_MAX	= 9;	// エリア数
static const int AREA_NO_CENTER	= 4;	// 中心エリアのインデックス
// 各エリアの原点
static const VECTOR AREA_ORIGIN_POS[AREA_NO_MAX] =
{
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 0.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 0.f},
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 1.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 0.f},
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 2.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 0.f},
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 0.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 1.f},
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 1.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 1.f},
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 2.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 1.f},
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 0.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 2.f},
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 1.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 2.f},
	{ AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X * 2.f,	0.f,	AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z * 2.f}
};
// ワールドマップの種類
static const int WOLD_MAP_TYPE_CENTER	= 0;	// 中心エリア
static const int WOLD_MAP_TYPE_SIDE		= 1;	// サイドエリア

/* 当たり判定系 */
static float COLLISION_CHECK_DISTANCE			= 40000.f;	// 当たり判定を行う直線距離(※各頂点の二乗の距離がこれより大きいなら非接触と判定する)
static float COLLISION_CHECK_CEILING_PREVENTION = 20.f;		// 天井すりぬけ防止用の補正値
static float COLLISION_CHECK_FLOOR_MARGIN		= -20.f;	// 横方向への移動時に床に対する誤判定防止用の補正値
static float COLLISION_PUSH_MAX_LOOP			= 10;		// 押し出し判定の最大ループ回数(無限ループ対策)

/* 描写系 */
// シャドウマップ関連
static const int SHADOW_GROUND_MAP_SIZE_WIDE	= 4096;		// 静的オブジェクトのシャドウマップの横幅
static const int SHADOW_GROUND_MAP_SIZE_HEIGHT	= 4096;		// 静的オブジェクトのシャドウマップの縦幅
static const int SHADOW_ACTOR_MAP_SIZE_WIDE		= 2048;		// 動的オブジェクトのシャドウマップの横幅
static const int SHADOW_ACTOR_MAP_SIZE_HEIGHT	= 2048;		// 動的オブジェクトのシャドウマップの縦幅
// 2Dアニメーション用画像関連
static const int CHARACTER_PARTS_ANIM_DRAW_SIZE_WIDE	= 256;	// キャラクターのパーツアニメーション用画像の横幅
static const int CHARACTER_PARTS_ANIM_DRAW_SIZE_HEIGHT	= 256;	// キャラクターのパーツアニメーション用画像の縦幅
// 見下ろし視点でののけぞり量
static const float TOPVIEW_LEAN_AMOUNT			= 150.f;	// 見下ろし視点でののけぞり量
