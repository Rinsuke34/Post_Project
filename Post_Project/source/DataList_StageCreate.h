/* データリスト"ステージクリエイト情報管理"クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"
#include "ConstantDefine.h"
#include "StructDefine.h"

/* 前方宣言 */
class Ground_Base;

// データリスト"ステージクリエイト情報管理"クラス
class DataList_StageCreate : public DataList_Base
{
	public:
		DataList_StageCreate();				// コンストラクタ
		virtual ~DataList_StageCreate() {};	// デストラクタ

		/* 定数 */
		static const int OBJECT_TYPE_BLOCK	= 0;	// ブロック
		static const int OBJECT_TYPE_MODEL	= 1;	// 3Dモデル
		static const int OBJECT_TYPE_MARKER	= 2;	// マーカー
		static const int OBJECT_TYPE_MAX	= 3;	// オブジェクトの種類

		/* 関数 */
		void Load_ObjectData();					// オブジェクトデータ読み込み
		void Load_WoldMapList();				// ワールドマップリスト読み込み
		void Load_MapData(std::string MapName);	// ワールドマップデータ読み込み
		void Save_MapData(std::string MapName);	// ワールドマップデータ保存
		void Draw_GroundObject();				// 地形オブジェクト描画

		/* ゲッター */
		VECTOR_INT	vecGetSelectPos()									{ return this->vecSelectPos; }					// 選択座標を取得
		std::vector<WOLD_MAP_DATA>& GetMapDataList()					{ return this->MapDataList; }					// マップリストを取得
		std::vector<std::string>& GetObjectNameList(int iObjectType)	{ return this->ObjectNameList[iObjectType]; }	// オブジェクト名リストを取得

		/* セッター */
		void	SetSelectPos(VECTOR_INT vecSelectPos)	{ this->vecSelectPos = vecSelectPos; }	// 選択座標を設定
		void	AddGroundObject(VECTOR_INT AddPos, std::shared_ptr<Ground_Base> AddObject);		// オブジェクトを追加
		void	DeleteGroundObject(VECTOR_INT DeletePos);										// オブジェクトを削除

	private:
		/* 変数 */
		// マップの情報
		std::vector<WOLD_MAP_DATA>	MapDataList;															// マップリスト
		// マップの内容
		std::shared_ptr<Ground_Base> pGoundObject[AREA_SIZE_BLOCK_X][AREA_SIZE_BLOCK_Y][AREA_SIZE_BLOCK_Z];	// マップのオブジェクト情報

		// 操作用変数
		VECTOR_INT	vecSelectPos;	// 選択座標

		/* 関数 */
		void						Reset_MapData();					// マップデータの初期化
		std::vector<std::string>	ObjectNameList[OBJECT_TYPE_MAX];	// オブジェクト名リスト(0:ブロック, 1:3Dモデル, 2:マーカー)
};
