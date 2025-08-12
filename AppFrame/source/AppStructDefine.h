/* AppFrameで使用する構造体の宣言 */

#pragma once
#include <DxLib.h>
#include <vector>
#include <string>
#include "AppConstantDefine.h"

// 入力関連
namespace Struct_Input
{
	struct PLAYER_INPUT_JOYPAD	// プレイヤー入力(ジョイパッド)
	{
		/* ジョイパッド */
		char	cgInput[INPUT_MAX][16];						// ジョイパッド入力[0:ホールド、1:トリガ、2:リリース][入力内容]
		bool	bgTrigger[INPUT_MAX][INPUT_DIRECTION];		// ジョイパッドのトリガーの入力[0:ホールド、1:トリガ、2:リリース][0:左、1:右]
		short	sAnalogStickX[INPUT_DIRECTION];				// X軸アナログ入力[0:左、1:右]
		short	sAnalogStickY[INPUT_DIRECTION];				// Y軸アナログ入力[0:左、1:右]
	};
	
	struct PLAYER_INPUT_KEYBOARD_MOUSE	// プレイヤー入力(キーボード、マウス)
	{
		/* キーボード */
		char	cgInput[INPUT_MAX][256];	// キー入力[0:ホールド、1:トリガ、2:リリース][入力内容]

		/* マウス */
		int	    igInput[INPUT_MAX];		// 入力[0:ホールド、1:トリガ、2:リリース]

		int		iMouseX;		// マウスX座標
		int		iMouseY;		// マウスY座標
		int		iMouseMoveX;	// X移動量
		int		iMouseMoveY;	// Y移動量
	};
}

// コリジョン関連
namespace Struct_Collision
{
	struct COLLISION_CAPSULE	// カプセルコリジョン
	{
		VECTOR	vecCapsuleTop;		// カプセルの上部
		VECTOR	vecCapsuleBottom;	// カプセルの下部
		float	fCapsuleRadius;		// カプセルの半径
	};

	struct COLLISION_SQHERE		// 球体コリジョン
	{
		VECTOR	vecSqhere;			// 球体の中心
		float	fSqhereRadius;		// 球体の半径
	};

	struct COLLISION_LINE		// 線分コリジョン
	{
		VECTOR	vecLineStart;		// 線分の始点
		VECTOR	vecLineEnd;			// 線分の終点
	};
};

// 2Dパーツアニメーション関連
namespace Struct_2DPartsAnim
{
	struct PARTS_ANIM_PARTS_IMAGE_DATA	// 各パーツの基本情報
	{
		std::string stPartsName;		// パーツ名
		std::string stPartsPath;		// パーツの画像ファイルパス
		int			iPartsGrHandle;		// パーツの画像のグラフィックハンドル(LoadGraphで取得した値)
	};

	struct PARTS_ANIM_PARTS_FRAME_DATA // フレームでのパーツの情報
	{
		std::string stPartsName;		// パーツ名
		float		fPartsX;			// パーツのX座標
		float		fPartsY;			// パーツのY座標
		float		fPartsScaleX;		// パーツのXスケール
		float		fPartsScaleY;		// パーツのYスケール
		float		fPartsAngle;		// パーツの角度(ラジアン)
		bool		bPartsFlipX;		// パーツの左右反転フラグ(有効であるならばパーツを反転する)
		bool		bPartsFlipY;		// パーツの上下反転フラグ(有効であるならばパーツを反転する)
	};

	struct PARTS_ANIM_ANIM_TIME_DATA									// フレームの情報
	{
		int											iDrawTime;			// そのアニメーションが描写される時間(フレーム単位)
		std::vector<PARTS_ANIM_PARTS_FRAME_DATA>	vecPartsFrameData;	// パーツのフレーム単位の情報
	};

	struct PARTS_ANIM_ANIM_DATA												// パーツアニメーションの情報
	{
		std::string									stAnimName;				// アニメーション名
		std::vector<PARTS_ANIM_ANIM_TIME_DATA>		vecPartsAnimTimeData;	// パーツアニメーションの時間単位での情報
	};

	struct PARTS_ANIM_DATA													// パーツアニメーション群の情報
	{
		std::string									stAnimName;				// パーツアニメーション群の名称
		std::vector<PARTS_ANIM_PARTS_IMAGE_DATA>	vecPartsImageData;		// 各パーツの基本情報
		std::vector<PARTS_ANIM_ANIM_DATA>			vecPartsAnimData;		// パーツアニメーションの情報
	};
}
