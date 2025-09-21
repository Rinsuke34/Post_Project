/* アイテムのベースクラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Actor_Base.h"

/* 前方宣言 */
class DataList_GameStatus;

// アイテムベースクラス
class Item_Base : public Actor_Base
{
	public:
		Item_Base();				// コンストラクタ
		virtual ~Item_Base() {};	// デストラクタ

		/* 定数 */
		static const int DESPAWN_TIME			= 600;	// アイテムが消滅するまでの時間(フレーム数)
		static const int COLLISION_HALF			= 32;	// コリジョンの半径

		/* 関数 */
		virtual void	InitialSetup()		override;	// 初期設定
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描画

	protected:
		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_GameStatus>	pDataList_GameStatus;		// ゲーム状態管理
		// 描画系
		std::shared_ptr<int>					piGrHandle;					// 使用する画像のハンドル
		// 状態系
		int										iDespawnTime;				// アイテムが消滅するまでの時間 

		/* 関数 */
		virtual void	Update_ItemGet() {};	// アイテム取得時の更新処理
};
