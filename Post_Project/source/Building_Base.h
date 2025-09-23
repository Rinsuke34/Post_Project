/* 建造物のベースクラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Ground_Model.h"

/* 前方宣言 */
class DataList_GameStatus;

// 建造物(神木(防衛対象))クラス
class Building_Base : public Ground_Model
{
	public:
		Building_Base();				// コンストラクタ
		virtual ~Building_Base() {};	// デストラクタ

		/* 定数 */
		static const int BUILDING_SIZE_X		= 64 * 3;		// X軸の建造物の大きさ
		static const int BUILDING_SIZE_Y		= 64 * 8;		// Y軸の建造物の大きさ
		static const int BUILDING_SIZE_Z		= 64 * 3;		// Z軸の建造物の大きさ
		static const int POSITION_ADJUSTEMENT_Y	= -16;			// 建造物の位置調整量(少し下に下げる)

		/* 関数 */
		virtual void	InitialSetup()		override;	// 初期設定
		virtual void	Draw_Collision()	override;	// 描画(当たり判定)

	protected:
		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_GameStatus>	pDataList_GameStatus;	// ゲーム状態管理
};
