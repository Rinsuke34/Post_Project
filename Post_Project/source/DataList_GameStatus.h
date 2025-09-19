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
		void SetPlayerPosition_WoldMap(VECTOR vecPosition)				{ this->vecPlayerPosition_WoldMap	= vecPosition; }		// プレイヤーのワールドマップ座標の設定
		void SetHp_CoreTree(int iHP)									{ this->iHp_CoreTree				= iHP; }				// 神木(防衛対象)の体力の設定
		void SetMaxHp_CoreTree(int iMaxHp)								{ this->iMaxHp_CoreTree				= iMaxHp; }				// 神木(防衛対象)の最大体力の設定
		void SetHp_Player(int iHp)										{ this->iHp_Player					= iHp; }				// プレイヤーの体力の設定
		void SetMaxHp_Player(int iMaxHp)								{ this->iMaxHp_Player				= iMaxHp; }				// プレイヤーの最大体力の設定
		// 中央エリアマーカー関連
		void SetPlayerStartPosition(VECTOR vecPosition)					{ this->vecPlayerStartPosition		= vecPosition; }		// プレイヤーのスタート座標の設定
		void SetBuildAreaPositionList(VECTOR vecPosition)				{ this->vecBuildAreaPositionList.push_back(vecPosition); }	// 建築エリアの座標リストの設定
		void SetCoreTreePosition(VECTOR vecPosition)					{ this->vecCoreTreePosition			= vecPosition; }		// 神木(防衛対象)の座標の設定
		// 外側エリアマーカー関連
		void SetEnemySpawnPoint(ENEMY_SPAWN_POINT_DATA EnemySpawnPoint)	{ this->stEnemySpawnPointList.push_back(EnemySpawnPoint); }	// エネミーのスポーン座標リストの設定

		/* ゲッター */
		// 共通
		VECTOR								GetPlayerPosition_WoldMap()		{ return this->vecPlayerPosition_WoldMap; }		// プレイヤーのワールドマップ座標の取得
		int									GetHp_CoreTree()				{ return this->iHp_CoreTree; }					// 神木(防衛対象)の体力の取得
		int									GetMaxHp_CoreTree()				{ return this->iMaxHp_CoreTree; }				// 神木(防衛対象)の最大体力の取得
		int									GetHp_Player()					{ return this->iHp_Player; }					// プレイヤーの体力の取得
		int									GetMaxHp_Player()				{ return this->iMaxHp_Player; }					// プレイヤーの最大体力の取得
		// 中央エリアマーカー関連
		VECTOR								GetPlayerStartPosition()		{ return this->vecPlayerStartPosition; }		// プレイヤーのスタート座標の取得
		std::vector<VECTOR>					GetBuildAreaPositionList()		{ return this->vecBuildAreaPositionList; }		// 建築エリアの座標リストの取得
		VECTOR								GetCoreTreePosition()			{ return this->vecCoreTreePosition; }			// 神木(防衛対象)の座標の取得
		// 外側エリアマーカー関連
		std::vector<ENEMY_SPAWN_POINT_DATA>	GetEnemySpawnPointList()		{ return this->stEnemySpawnPointList; }			// エネミーのスポーン座標リストの取得

	private:
		/* 変数 */
		// 共通
		VECTOR				vecPlayerPosition_WoldMap;	// プレイヤーのワールドマップ座標
		int					iHp_CoreTree;				// 神木(防衛対象)の体力
		int					iMaxHp_CoreTree;			// 神木(防衛対象)の最大体力
		int					iHp_Player;					// プレイヤーの体力
		int					iMaxHp_Player;				// プレイヤーの最大体力
		// 中央エリアマーカー関連
		VECTOR				vecPlayerStartPosition;		// プレイヤーのスタート座標
		std::vector<VECTOR>	vecBuildAreaPositionList;	// 建築エリアの座標リスト
		VECTOR				vecCoreTreePosition;		// 神木(防衛対象)の座標
		// 外側エリアマーカー関連
		std::vector<ENEMY_SPAWN_POINT_DATA> stEnemySpawnPointList;	// エネミーのスポーン座標リスト
};
