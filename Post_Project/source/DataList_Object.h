/* データリスト"オブジェクト管理"クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"
#include "ConstantDefine.h"
#include "StructDefine.h"

/* 前方宣言 */
class Ground_Base;
class Actor_Base;

// データリスト"オブジェクト管理"クラス
class DataList_Object : public DataList_Base
{
	public:
		DataList_Object();				// コンストラクタ
		virtual ~DataList_Object();		// デストラクタ

		/* 関数 */
		// リスト内オブジェクト初期化
		void	InitialSetup_All();		// すべてのオブジェクト
		void	InitialSetup_Ground();	// 地形
		void	InitialSetup_Actor();	// アクター

		// オブジェクト更新
		void	Update_All();			// すべてのオブジェクト
		void	Update_Ground();		// 地形
		void	Update_Actor();			// アクター

		// オブジェクト描画
		void	Draw_All();				// すべてのオブジェクト
		void	Draw_Ground();			// 地形
		void	Draw_Actor();			// アクター

		// オブジェクト描写(シャドウマップ用)
		void	Draw_All_Shadow();		// すべてのオブジェクト
		void	Draw_Ground_Shadow();	// 地形
		void	Draw_Actor_Shadow();	// アクター

		// オブジェクト描写(当たり判定)
		void	Draw_All_Collision();		// すべてのオブジェクト
		void	Draw_Ground_Collision();	// 地形
		void	Draw_Actor_Collision();		// アクター

		// 削除フラグが有効なオブジェクト削除
		void	DeleteFlagged_AllObject();		// すべてのオブジェクト
		void	DeleteFlagged_AllGround();		// 地形
		void	DeleteFlagged_AllActor();		// アクター

		/* セッター */
		void	AddTexture(TEXTURE_DATA stTexture)									{ this->TextureDataList.push_back(stTexture); };	// テクスチャデータ追加
		void	AddObject_Ground(std::shared_ptr<Ground_Base> pGround, int iAreaNo)	{ this->pGroundList[iAreaNo].push_back(pGround); };	// 指定エリアの地形追加
		void	AddObject_Actor(std::shared_ptr<Actor_Base> pActor)					{ this->pActorList.push_back(pActor); };			// アクター追加

		/* ゲッター */
		std::vector<TEXTURE_DATA>&					GetTextureDataList()		{ return this->TextureDataList; }		// テクスチャデータリスト取得
		std::vector<std::shared_ptr<Ground_Base>>&	GetGroundList(int iAreaNo)	{ return this->pGroundList[iAreaNo]; }	// 指定エリアの地形リスト取得
		std::vector<std::shared_ptr<Actor_Base>>& GetActorList()				{ return this->pActorList; }			// アクタリスト取得

	private:
		/* 変数 */
		// リスト
		std::vector<TEXTURE_DATA>					TextureDataList;				// テクスチャリスト
		std::vector<std::shared_ptr<Ground_Base>>	pGroundList[AREA_NO_MAX];		// 地形リスト[エリア番号]
		std::vector<std::shared_ptr<Actor_Base>>	pActorList;						// アクターリスト
};
