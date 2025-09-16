/* キャラクター(NPC)のベースクラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Character_Base.h"
// 共通定義
#include "ConstantDefine.h"

// キャラクター(NPC)のベースクラスの宣言
class Npc_Base : public Character_Base
{
	public:
		Npc_Base();				// コンストラクタ
		virtual ~Npc_Base();	// デストラクタ

		/* 定数 */
		static const int MOVE_NOT		= -1;	// 移動不可
		static const int MOVE_OK		= 0;	// そのまま移動可能
		static const int MOVE_UP		= 1;	// 上方向へ移動すれば移動可能
		static const int MOVE_GOALHIT	= 2;	// 目標へ到達

	protected:
		/* 変数 */
		// 移動系
		std::vector<VECTOR>	avecMovePath;			// ゴールまでの移動ルート
		// パラメーター系(NPC独自)
		float	fSearchRange;		// 探索範囲
		float	fAttackRange;		// 攻撃範囲
		bool	bContactDamageFlg;	// 接触によりダメージ発生するかのフラグ
		bool	bAttackMeleeFlg;	// 近接攻撃を行うかのフラグ
		// 行動パターンフラグ
		bool	abEnemyActionPatternFlg[NPC_ENEMY_ACTION_PATTERN_MAX];			// エネミー行動パターンフラグ
		bool	abLongRangeAttackPatternFlg[LONG_RANGE_ATTACK_DIR_PATTERN_MAX];	// エネミー遠距離攻撃パターンフラグ

		/* 関数 */
		void	Route_Search();										// 移動経路検索
		int		iCheck_Moveble(VECTOR vecMovePos);					// 移動可能か確認
};
