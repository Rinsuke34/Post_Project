/* 建造物(NPC拠点)クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Building_Base.h"

/* 前方宣言 */
class Npc_Base;
class DataList_Object;
class DataList_Sound;

// 建造物(NPC拠点(ウィスプ))クラス
class Building_NpcBase : public Building_Base
{
	public:
		Building_NpcBase();				// コンストラクタ
		virtual ~Building_NpcBase() {};	// デストラクタ

		/* 定数 */
		static const int RESPAWN_TIME_DEFAULT = 60 * 20;	// NPC再出現時間(フレーム数)

		static const int NPCBASE_SIZE_Y			= 10;		// Y軸の建造物の大きさ
		static const int POSITION_ADJUSTEMENT_Y	= -16;		// 建造物の位置調整量(少し下に下げる)

		/* 関数 */
		virtual void	InitialSetup();		// 初期設定
		virtual void	Update();			// 更新

		/* セッター */
		void SetNpcName(const std::string& Name)	{ this->NpcName = Name; }	// 生成するNPCの名前を設定

		/* ゲッター */
		std::string GetNpcName()	{ return this->NpcName; }				// 生成するNPCの名前を取得

	private:
		/* 変数 */
		// データリストのポインタ
		std::shared_ptr<DataList_Object>	pDataList_Object;	// オブジェクト管理
		std::shared_ptr<DataList_Sound>		pDataList_Sound;	// サウンド管理
		// 状態系
		std::string	NpcName;		// 生成するNPCの名前
		int			iRespawnTime;	// NPC再出現時間(フレーム数)
};
