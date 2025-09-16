/* プロジェクトで使用する定数の宣言 */

#pragma once

/* マップ系 */
// ブロックサイズ
static const float MAP_BLOCK_SIZE_X = 64.f;		// X軸のマップタイルの大きさ
static const float MAP_BLOCK_SIZE_Y = 64.f;		// Y軸のマップタイルの大きさ
static const float MAP_BLOCK_SIZE_Z = 64.f;		// Z軸のマップタイルの大きさ
// エリアサイズ
static const int AREA_SIZE_BLOCK_X = 35;	// X軸のエリアの大きさ(ブロック数単位)
static const int AREA_SIZE_BLOCK_Y = 8;		// X軸のエリアの大きさ(ブロック数単位)
static const int AREA_SIZE_BLOCK_Z = 35;	// X軸のエリアの大きさ(ブロック数単位)
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
// ルート検索関連
static const float	ROUTE_SEARCH_MOVE_DISTANCE		= 64.f;	// ルート検索時の1ステップの移動距離
static const int	ROUTE_SEARCH_MOVE_COST_DEFAULT	= 10;	// ルート検索時の標準のコスト
static const int	ROUTE_SEARCH_MOVE_COST_DIAG		= 15;	// ルート検索時の斜め移動のコスト
static const int	ROUTE_SEARCH_MOVE_COST_YCHANGE	= 20;	// ルート検索時の高さ変更のコスト

/* 当たり判定系 */
static float COLLISION_CHECK_DISTANCE			= 50000.f;				// 当たり判定を行う直線距離(※各頂点の二乗の距離がこれより大きいなら非接触と判定する)
static float COLLISION_CHECK_CEILING_PREVENTION = MAP_BLOCK_SIZE_Y / 2;	// 天井すりぬけ防止用の補正値
static float COLLISION_CHECK_FLOOR_MARGIN		= -20.f;				// 横方向への移動時に床に対する誤判定防止用の補正値
static float COLLISION_PUSH_MAX_LOOP			= 10;					// 押し出し判定の最大ループ回数(無限ループ対策)

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

/* オブジェクト系 */
// エネミーのスポーンポイントの種類
static const int ENEMY_SPAWN_POINT_TYPE_PLAIN	= 0;	// 平原
static const int ENEMY_SPAWN_POINT_TYPE_ROCKY	= 1;	// 岩場
static const int ENEMY_SPAWN_POINT_TYPE_DESERT	= 2;	// 砂漠

/* 行動パターン関係 */
// NPCの行動パターン系
static const int NPC_ENEMY_ACTION_PATTERN_INVASION_CORETREE	= 0;	// 神木(防衛対象)への侵攻
static const int NPC_ENEMY_ACTION_PATTARN_PLAYER_ATTACK		= 1;	// プレイヤーへの攻撃
static const int NPC_ENEMY_ACTION_PATTERN_PLAYER_TRACKING	= 2;	// プレイヤーの追跡
static const int NPC_ENEMY_ACTION_PATTERN_PLAYER_ESCAPE		= 3;	// プレイヤーからの逃走
static const int NPC_ENEMY_ACTION_PATTERN_MAX				= 4;	// 行動パターンの最大数

// 遠距離攻撃の方向パターン
static const int LONG_RANGE_ATTACK_DIR_PATTERN_AIM			= 0;	// 目的へ向けて狙い撃ち
static const int LONG_RANGE_ATTACK_DIR_PATTERN_3WAY			= 1;	// 目標とその左右に撃つ
static const int LONG_RANGE_ATTACK_DIR_PATTERN_DIAGONAL_WAY	= 2;	// 十字方向に撃つ
static const int LONG_RANGE_ATTACK_DIR_PATTERN_CARDINAL_WAY	= 3;	// 斜め方向に撃つ
static const int LONG_RANGE_ATTACK_DIR_PATTERN_EIGHT_WAY	= 4;	// 八方向に撃つ
static const int LONG_RANGE_ATTACK_DIR_PATTERN_MAX			= 5;	// 遠距離攻撃の方向パターンの最大数
