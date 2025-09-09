/* プレイヤークラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Character_Base.h"

/* 前方宣言 */
class DataList_GameStatus;

// プレイヤークラス
class Character_Player : public Character_Base
{
	public:
		Character_Player();				// コンストラクタ
		virtual ~Character_Player();	// デストラクタ

		/* 関数 */
		virtual void	Update()	override;	// 更新
		virtual void	Draw()		override;	// 描画

	protected:
		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_GameStatus>			pDataList_GameStatus;				// ゲーム状態管理
		std::shared_ptr<DataList_2DPartsAnimCreateTool>	pDataList_2DPartsAnimCreateTool;	// 2Dパーツアニメーションツール
		// 画像データ
		int iScreenHandle_Animation;	// アニメーション描写用
		// アニメーション関係
		std::string		AnimFileName;	// アニメーションファイル名
		std::string		NowMotionName;	// 現在のモーション名
		int				iMotionCount;	// モーションカウント

		/* 関数 */
		void	Update_ApplyGravity();		// 重力処理
		void	Update_ApplyMovement();		// 移動処理
		void	Update_Animation();			// アニメーション更新
		void	Draw_Animation();			// アニメーション描写
};
