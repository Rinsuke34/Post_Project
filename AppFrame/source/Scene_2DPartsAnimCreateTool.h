/* シーン"汎用2Dパーツアニメーションツール"の宣言 */

#pragma once

/* 使用する要素のインクルード */
// 標準ライブラリ
#include <memory>
// 基底クラス
#include "Scene_Base.h"
// 共通定義
#include "AppStructDefine.h"

/* 前方宣言 */
class Scene_UI_Table;

// シーン"汎用2Dパーツアニメーションツール"
class Scene_2DPartsAnimCreateTool : public Scene_Base
{
	public:
		Scene_2DPartsAnimCreateTool();				// コンストラクタ
		virtual ~Scene_2DPartsAnimCreateTool();		// デストラクタ

		/* 定数 */
		static const int FONT_SIZE			= 16;		// フォントサイズ
		static const int TABLE_SIZE_W		= 400;		// テーブルの横幅
		static const int STANDARD_SIZE		= 256;		// 標準用の四角形のサイズ
		static const int MAX_INPUT_NUMBER	= 20;		// 入力可能な最大文字数(名称入力用)

		/* 関数 */
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描画

	private:
		/* 関数 */
		bool	bLoadPartsAnimData();				// パーツアニメーションのデータ読み込み
		bool	bSavePartsAnimData();				// パーツアニメーションのデータ保存

		void	NewPartsAnimFile();					// 新規パーツアニメーションファイル作成
		void	AddAnimPaarts();					// アニメーション用パーツ追加
		void	AddAnim();							// アニメーション追加
		void	AddPartsToAnim();					// 選択中のアニメーションにパーツを追加
		void	DeleteAnimPaarts();					// アニメーション用パーツ削除
		void	DeleteAnim();						// アニメーション削除
		void	DeletePartsToAnim();				// 選択中のアニメーションにパーツを削除
		void	ChangeSelectTime();					// 選択時間の変更
		void	SetUiTableElement();				// テーブルUIへの要素設定
		void	ChangeSelectPartsStatus();			// 選択中のパーツの状態変更

		void	Draw_BackGround();					// 背景描写		
		void	Draw_CurrentPartsAtSelectTime();	// 現在のアニメーションの選択時間に登録されたパーツを描写
		void	Draw_SelectFileName();				// ファイル名描写
		void	Draw_SelectTime();					// 選択中の時間描写
		void	Draw_PartsStatus();					// 選択中のパーツの状態描写

		/* 変数 */
		bool								bOldMouseCursorCenterFixedFlg;	// ツール起動時のマウスの中心固定フラグ
		bool								bOldMouseCursorNotDepictedFlg;	// ツール起動時のマウスカーソル描写無効フラグ

		bool								bNameSelectedFlg;				// ファイル名選択中フラグ
		bool								bTimeSelectedFlg;				// 時間選択中フラグ
		int									iSelectTime;					// 指定中のアニメーションの時間
		int									iAnimMaxTime;					// アニメーションの最大時間

		std::string														FileName;		// パーツアニメーション群の名称(==ファイル名)
		std::vector<Struct_2DPartsAnim::PARTS_ANIM_PARTS_IMAGE_DATA>	PartsImageData;	// パーツの画像データ(アニメーション用パーツの画像データ)
		std::vector<Struct_2DPartsAnim::PARTS_ANIM_ANIM_DATA>			PartsAnimData;	// パーツアニメーションの情報(アニメーションのフレーム情報など)

		std::shared_ptr<Scene_UI_Table> 	paUI_Table[3];					// テーブルUI(0:パーツリスト, 1:アニメーションリスト, 2:選択時間でのパーツリスト)
};
