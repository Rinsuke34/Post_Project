/* データリスト"ゲーム状態管理"クラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "DataList_GameStatus.h"

// コンストラクタ
DataList_GameStatus::DataList_GameStatus() : DataList_Base("DataList_GameStatus")
{
	/* 初期化 */
	this->vecPlayerPosition_WoldMap	= VGet(0.0f, 0.0f, 0.0f);
	this->iHaveCoin					= 0;
	this->iHp_CoreTree				= 0;
	this->iMaxHp_CoreTree			= 0;
	this->iHp_Player				= 0;
	this->iMaxHp_Player				= 0;
	this->bBuildModeFlg				= false;
	this->iSelectedBuildingIndex	= 0;
	this->bPlayerMeleeFlg			= true;
	this->iScore					= 0;
	this->iWave						= 0;
	this->iBuilldingBuff_Sword		= 0;
	this->iBuilldingBuff_Rod		= 0;
}
