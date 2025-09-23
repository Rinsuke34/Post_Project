/* データリスト"オブジェクト管理"クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"
#include "ConstantDefine.h"
#include "StructDefine.h"

/* 前方宣言 */
class Ground_Base;
class Ground_Marker;
class Character_Base;
class Building_Base;
class Item_Base;
class Bullet_Base;

// データリスト"オブジェクト管理"クラス
class DataList_Object : public DataList_Base
{
	public:
		DataList_Object();				// コンストラクタ
		virtual ~DataList_Object() {};	// デストラクタ

		/* 関数 */
		// リスト内オブジェクト初期化
		void	InitialSetup_All();			// すべてのオブジェクト
		void	InitialSetup_Ground();		// 地形
		void	InitialSetup_Character();	// キャラクター
		void	InitialSetup_Building();	// 建造物
		void	InitialSetup_Item();		// アイテム
		void	InitialSetup_Bullet();		// バレット

		// オブジェクト更新
		void	Update_All();			// すべてのオブジェクト
		void	Update_Ground();		// 地形
		void	Update_Character();		// キャラクター
		void	Update_Building();		// 建造物
		void	Update_Item();			// アイテム
		void	Update_Bullet();		// バレット

		// オブジェクト描画
		void	Draw_All();				// すべてのオブジェクト
		void	Draw_Ground();			// 地形
		void	Draw_Character();		// キャラクター
		void	Draw_Building();		// 建造物
		void	Draw_Item();			// アイテム
		void	Draw_Bullet();			// バレット

		// オブジェクト描写(シャドウマップ用)
		void	Draw_All_Shadow();			// すべてのオブジェクト
		void	Draw_Ground_Shadow();		// 地形
		void	Draw_Character_Shadow();	// キャラクター
		void	Draw_Building_Shadow();		// 建造物
		void	Draw_Item_Shadow();			// アイテム
		void	Draw_Bullet_Shadow();		// バレット

		// オブジェクト描写(当たり判定)
		void	Draw_All_Collision();		// すべてのオブジェクト
		void	Draw_Ground_Collision();	// 地形
		void	Draw_Character_Collision();	// キャラクター
		void	Draw_Building_Collision();	// 建造物
		void	Draw_Item_Collision();		// アイテム
		void	Draw_Bullet_Collision();	// バレット

		// 削除フラグが有効なオブジェクト削除
		void	DeleteFlagged_AllObject();		// すべてのオブジェクト
		void	DeleteFlagged_AllGround();		// 地形
		void	DeleteFlagged_AllCharacter();	// キャラクター
		void	DeleteFlagged_AllBuilding();	// 建造物
		void	DeleteFlagged_AllItem();		// アイテム
		void	DeleteFlagged_AllBullet();		// バレット

		/* セッター */
		void	AddObject_Ground(std::shared_ptr<Ground_Base> pGround, int iGridX, int iGridY)	{ this->pGroundList[iGridX][iGridY].push_back(pGround); };	// 指定エリアの地形追加
		void	AddObject_Marker(std::shared_ptr<Ground_Marker> pMarker, int iAreaNo)			{ this->pMarkerList[iAreaNo].push_back(pMarker); };			// 指定エリアのマーカー追加
		void	AddObject_Character(std::shared_ptr<Character_Base> pActor)							{ this->pCharacterList.push_back(pActor); };				// キャラクター追加
		void	AddObject_Building(std::shared_ptr<Building_Base> pBuilding)					{ this->pBuildingList.push_back(pBuilding); };				// 建造物追加
		void	AddObject_Item(std::shared_ptr<Item_Base> pItem)								{ this->pItemList.push_back(pItem); };						// アイテム追加
		void	AddObject_Bullet(std::shared_ptr<Bullet_Base> pBullet)							{ this->pBulletList.push_back(pBullet); };					// バレット追加

		/* ゲッター */
		std::vector<std::shared_ptr<Ground_Base>>&		GetGroundList(int iGridX, int iGridY);													// 指定エリアの地形リスト取得
		std::vector<std::shared_ptr<Ground_Marker>>&	GetMarkerList(int iAreaNo)				{ return this->pMarkerList[iAreaNo]; }			// 指定エリアのマーカーリスト取得
		std::vector<std::shared_ptr<Character_Base>>&	GetCharacterList()						{ return this->pCharacterList; }				// キャラクターリスト取得
		std::vector<std::shared_ptr<Building_Base>>&	GetBuildingList()						{ return this->pBuildingList; }					// 建造物リスト取得
		std::vector<std::shared_ptr<Item_Base>>&		GetItemList()							{ return this->pItemList; }						// アイテムリスト取得
		std::vector<std::shared_ptr<Bullet_Base>>&		GetBulletList()							{ return this->pBulletList; }					// バレットリスト取得

	private:
		/* 変数 */
		// リスト
		std::vector<std::shared_ptr<Ground_Base>>		pGroundList[GRID_NUMBER_X][GRID_NUMBER_X];	// 地形リスト[エリア番号]
		std::vector<std::shared_ptr<Ground_Marker>>		pMarkerList[AREA_NO_MAX];					// マーカーリスト
		std::vector<std::shared_ptr<Character_Base>>	pCharacterList;								// キャラクターリスト
		std::vector<std::shared_ptr<Building_Base>>		pBuildingList;								// 建造物リスト
		std::vector<std::shared_ptr<Item_Base>>			pItemList;									// アイテムリスト
		std::vector<std::shared_ptr<Bullet_Base>>		pBulletList;								// バレットリスト
};
