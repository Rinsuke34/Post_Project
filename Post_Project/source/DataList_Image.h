/* データリスト"画像データ管理"クラスの宣言 */

#pragma once
/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"
#include "StructDefine.h"

// データリスト"画像データ管理"クラス
class DataList_Image : public DataList_Base
{
	public:
		DataList_Image();			// コンストラクタ
		virtual ~DataList_Image();	// デストラクタ

		/* 関数 */
		void					LoadGrHandle(std::string& cFileName);				// 画像データ読み込み
		std::shared_ptr<int>	iGetGrhandle(std::string& cFileName);				// 画像データ取得

		/* セッター */
		void	AddTexture(TEXTURE_DATA stTexture) { this->TextureDataList.push_back(stTexture); };	// テクスチャデータ追加

		/* ゲッター */
		std::vector<TEXTURE_DATA>& GetTextureDataList() { return this->TextureDataList; }		// テクスチャデータリスト取得

	private:
		/* 変数 */
		// リスト
		std::map<std::string, int>	GrHandleList;		// 画像データリスト
		std::vector<TEXTURE_DATA>	TextureDataList;	// テクスチャリスト

		/* 関数 */
		bool	bCheckGrHandle(std::string& cFileName);	// 該当画像ハンドルデータ存在確認
		void	JsonLoad_Texture();						// テクスチャ読み込み
};
