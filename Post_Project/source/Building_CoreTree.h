/* 建造物(神木(防衛対象))クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Building_Base.h"

/* 前方宣言 */
class DataList_Object;
class DataList_Sound;

// 建造物(神木(防衛対象))クラス
class Building_CoreTree : public Building_Base
{
	public:
		Building_CoreTree();				// コンストラクタ
		virtual ~Building_CoreTree() {};	// デストラクタ

		/* 関数 */
		virtual void	InitialSetup()	override;	// 初期設定
		virtual void	Update()		override;	// 更新

	private:
		/* 定数 */
		static const int MAX_HP				= 100;	// HP最大値
		static const int SE_COOLDOWN_TIME	= 10;	// SEクールタイム(ダメージを受けてから次にSEが鳴るまでの時間)

		/* 変数 */
		// データリストのポインタ
		std::shared_ptr<DataList_Sound>	pDataList_Sound;	// サウンド管理
		// 状態系
		int iHpPrevFrame;		// 前のフレームの体力
		int iSECooldownTimer;	// SEクールタイム（SEが鳴るまでの残り時間）
};
