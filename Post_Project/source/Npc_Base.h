/* キャラクター(NPC)のベースクラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 標準ライブラリ
#include <thread>
#include <future>
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
		static const int MOVE_DOWN		= 3;	// 移動可能だが、足場がないので落下する

		/* 関数 */
		virtual void	InitialSetup()		override;	// 初期設定
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描写

		/* セッター */
		// 基本情報
		void SetName(std::string Name)	{ this->Name = Name; }	// 名前

		/* ゲッター */
		std::string GetName()			{ return this->Name; }	// 名前

	protected:
		/* 定数 */
		// HPバーの描写系
		static const int HPBAR_POS_X		= -25;	// HPバーのX座標(基準座標からの相対位置)
		static const int HPBAR_POS_Y		= 50;	// HPバーのY座標(基準座標からの相対位置)
		static const int HPBAR_WIDE			= 50;	// HPバーの幅
		static const int HPBAR_HEIGHT		= 5;	// HPバーの高さ
		static const int HPBAR_BACK_WIDE	= 1;	// 背景の幅


		/* 変数 */
		// 基本情報
		std::string			Name;	// 名前
		// 非同期処理系
		std::future<void>	thred_RouteSearch;	// 移動経路検索処理の結果確認用
		// 移動系
		std::vector<VECTOR>	avecMovePath;		// 対象エリアまでの移動ルート
		// 処理用
		VECTOR				vecTargetPos;		// ターゲット座標(移動ルート再検索で使用)

		/* 関数 */
		// 基本機能用関数
		void	JsonLoad_CharacterStatus();								// キャラクター情報の読み込み
		void	Route_Search(VECTOR vecGoalPos);						// 移動経路検索
		int		iCheck_Moveble(VECTOR vecMovePos, VECTOR vecGoalPos);	// 移動可能か確認
		void	Update_RouteMove();										// 移動ルートに沿った移動
		void	Draw_Route();											// 移動ルートの描写
		void	Draw_HpBar();											// HPバーの描写
		int		iCost_H_CalcHeuristicCost(const VECTOR& vecCurrentPosition, const VECTOR& vecGoalPosition);	// 現在ノードからゴールノードまでの推定コスト（ヒューリスティック値）を算出
		// 行動パターンなど
		void	Update_Action();											// 行動パターン管理
		void	Update_Action_Enemy();										// 行動パターン管理(エネミー用)
		void	Update_Action_Friend();										// 行動パターン管理(味方NPC用)
		void	Update_MakeBullet(VECTOR vecTarget, std::string TeamTag);	// 弾の生成
};
