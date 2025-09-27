/* データリスト"ゲーム状態管理"クラスの宣言 */

#pragma once
/* 使用する要素のインクルード */
// 標準ライブラリ
#include <vector>
// 共通定義
#include "AppFrame.h"
#include "StructDefine.h"

// データリスト"ゲーム状態管理"クラス
class DataList_GameStatus : public DataList_Base
{
	public:
		DataList_GameStatus();				// コンストラクタ
		virtual ~DataList_GameStatus() {};	// デストラクタ

		/* セッター */
		// 共通
		void SetPlayerPosition_WoldMap(VECTOR vecPosition)					{ this->vecPlayerPosition_WoldMap	= vecPosition; }		// プレイヤーのワールドマップ座標の設定
		void SetHp_CoreTree(int iHP)										{ this->iHp_CoreTree				= iHP; }				// 神木(防衛対象)の体力の設定
		void SetMaxHp_CoreTree(int iMaxHp)									{ this->iMaxHp_CoreTree				= iMaxHp; }				// 神木(防衛対象)の最大体力の設定
		void SetHp_Player(int iHp)											{ this->iHp_Player					= iHp; }				// プレイヤーの体力の設定
		void SetMaxHp_Player(int iMaxHp)									{ this->iMaxHp_Player				= iMaxHp; }				// プレイヤーの最大体力の設定
		void SetHaveCoin(int iHaveCoin)										{ this->iHaveCoin					= iHaveCoin; }			// 所持しているコインの設定
		void SetScore(int iScore)											{ this->iScore						= iScore; }				// スコアの設定
		void SetWave(int iWave)												{ this->iWave						= iWave; }				// 現在のウェーブ数の設定
		void SetMaxFriendNpc(int iMaxFriendNpc)								{ this->iMaxFriendNpc				= iMaxFriendNpc; }		// 最大味方NPC数の設定
		void SetCurrentFriendNpc(int iCurrentFriendNpc)						{ this->iCurrentFriendNpc			= iCurrentFriendNpc; }	// 現在の味方NPC数の設定
		// マーカー関連
		void SetPlayerStartPosition(VECTOR vecPosition)						{ this->vecPlayerStartPosition		= vecPosition; }		// プレイヤーのスタート座標の設定
		void SetBuildAreaPositionList(BUILDING_AREA_DATA AreaData)			{ this->BuildAreaPositionList.push_back(AreaData); }		// 建築エリアリストの設定
		void SetBuildAreaPosition(int iIndex, BUILDING_AREA_DATA AreaData)	{ this->BuildAreaPositionList[iIndex] = AreaData; }			// 建築エリアリストの設定(インデックス指定)
		void SetCoreTreePosition(VECTOR vecPosition)						{ this->vecCoreTreePosition			= vecPosition; }		// 神木(防衛対象)の座標の設定
		void SetEnemySpawnPoint(ENEMY_SPAWN_POINT_DATA EnemySpawnPoint)		{ this->stEnemySpawnPointList.push_back(EnemySpawnPoint); }	// エネミーのスポーン座標リストの設定
		void SetEnemySpawnTable(ENEMY_SPAWN_TABLE EnemySpawnTable)			{ this->stEnemySpawnTableList.push_back(EnemySpawnTable); }	// エネミースポーンテーブルリストの設定
		// ゲーム状態
		void SetBuildModeFlg(bool bFlg)										{ this->bBuildModeFlg				= bFlg; }				// 建築モードフラグの設定
		void SetBuildModeChangePossibleFlg(bool bFlg)						{ this->bChangeBuildModePossibleFlg = bFlg; }				// 建築モード変更可能フラグの設定
		void SetSelectedBuildingIndex(int iIndex)							{ this->iSelectedBuildingIndex		= iIndex; }				// 選択している建造物のインデックス番号の設定
		void SetPlayerMeleeFlg(bool bFlg)									{ this->bPlayerMeleeFlg				= bFlg; }				// プレイヤーが近接攻撃状態であるかのフラグを設定
		void SetBuilldingBuff_Sword(int iBuff)								{ this->iBuilldingBuff_Sword		= iBuff; }				// 建築物バフ(剣)の設定
		void SetBuilldingBuff_Rod(int iBuff)								{ this->iBuilldingBuff_Rod			= iBuff; }				// 建築物バフ(杖)の設定

		/* ゲッター */
		// 共通
		VECTOR								GetPlayerPosition_WoldMap()		{ return this->vecPlayerPosition_WoldMap; }		// プレイヤーのワールドマップ座標の取得
		int									GetHp_CoreTree()				{ return this->iHp_CoreTree; }					// 神木(防衛対象)の体力の取得
		int									GetMaxHp_CoreTree()				{ return this->iMaxHp_CoreTree; }				// 神木(防衛対象)の最大体力の取得
		int									GetHp_Player()					{ return this->iHp_Player; }					// プレイヤーの体力の取得
		int									GetMaxHp_Player()				{ return this->iMaxHp_Player; }					// プレイヤーの最大体力の取得
		int									GetHaveCoin()					{ return this->iHaveCoin; }						// 所持しているコインの取得
		int 								GetScore()						{ return this->iScore; }						// スコアの取得
		int									GetWave()						{ return this->iWave; }							// 現在のウェーブ数の取得
		int									GetMaxFriendNpc()				{ return this->iMaxFriendNpc; }					// 最大味方NPC数の取得
		int									GetCurrentFriendNpc()			{ return this->iCurrentFriendNpc; }				// 現在の味方NPC数の取得
		// マーカー関連
		VECTOR								GetPlayerStartPosition()			{ return this->vecPlayerStartPosition; }		// プレイヤーのスタート座標の取得
		std::vector<BUILDING_AREA_DATA>		GetBuildAreaPositionList()			{ return this->BuildAreaPositionList; }			// 建築エリアリストの取得
		BUILDING_AREA_DATA					GetBuildAreaPosition(int iIndex)	{ return this->BuildAreaPositionList[iIndex]; }	// 建築エリアの取得
		VECTOR								GetCoreTreePosition()				{ return this->vecCoreTreePosition; }			// 神木(防衛対象)の座標の取得
		std::vector<ENEMY_SPAWN_POINT_DATA>	GetEnemySpawnPointList()			{ return this->stEnemySpawnPointList; }			// エネミーのスポーン座標リストの取得
		std::vector<ENEMY_SPAWN_TABLE>		GetEnemySpawnTableList()			{ return this->stEnemySpawnTableList; }			// エネミースポーンテーブルリストの取得
		// ゲーム状態
		bool								GetBuildModeFlg()				{ return this->bBuildModeFlg; }					// 建築モードフラグの取得
		bool								GetBuildModeChangePossibleFlg() { return this->bChangeBuildModePossibleFlg; }	// 建築モードに変更可能であるかのフラグを取得
		int									GetSelectedBuildingIndex()		{ return this->iSelectedBuildingIndex; }		// 選択している建造物のインデックス番号の取得
		bool								GetPlayerMeleeFlg()				{ return this->bPlayerMeleeFlg; }				// プレイヤーが近接攻撃状態であるかのフラグを取得
		int									GetBuilldingBuff_Sword()		{ return this->iBuilldingBuff_Sword; }			// 建築物バフ(剣)の取得
		int									GetBuilldingBuff_Rod()			{ return this->iBuilldingBuff_Rod; }			// 建築物バフ(杖)の取得

	private:
		/* 変数 */
		// 共通
		VECTOR	vecPlayerPosition_WoldMap;	// プレイヤーのワールドマップ座標
		int		iHp_CoreTree;				// 神木(防衛対象)の体力
		int		iMaxHp_CoreTree;			// 神木(防衛対象)の最大体力
		int		iHp_Player;					// プレイヤーの体力
		int		iMaxHp_Player;				// プレイヤーの最大体力
		int		iHaveCoin;					// 所持しているコイン
		int		iScore;						// スコア
		int		iWave;						// ウェーブ数
		int		iMaxFriendNpc;				// 最大味方NPC数
		int		iCurrentFriendNpc;			// 現在の味方NPC数
		// マーカー関連
		VECTOR								vecPlayerStartPosition;		// プレイヤーのスタート座標
		std::vector<BUILDING_AREA_DATA>		BuildAreaPositionList;		// 建築エリアリスト
		VECTOR								vecCoreTreePosition;		// 神木(防衛対象)の座標
		std::vector<ENEMY_SPAWN_POINT_DATA>	stEnemySpawnPointList;		// エネミーのスポーン座標リスト
		std::vector<ENEMY_SPAWN_TABLE>		stEnemySpawnTableList;		// エネミースポーンテーブルリスト
		// ゲーム状態
		bool								bBuildModeFlg;					// 建築モードフラグ
		bool								bChangeBuildModePossibleFlg;	// 建築モードに変更可能であるかのフラグ
		int									iSelectedBuildingIndex;			// 選択している建造物のインデックス番号
		bool								bPlayerMeleeFlg;				// プレイヤーが近接攻撃状態であるかのフラグ
		int									iBuilldingBuff_Sword;			// 建築物バフ:攻撃力(剣)
		int									iBuilldingBuff_Rod;				// 建築物バフ:攻撃力(杖)
};
