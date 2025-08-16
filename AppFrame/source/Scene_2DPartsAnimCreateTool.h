/* シーン"汎用2Dパーツアニメーションツール"の宣言 */

#pragma once
#include "SceneBase.h"
#include "AppStructDefine.h"
#include "Scene_UI_Table.h"
#include <memory>

// シーン"汎用2Dパーツアニメーションツール"
class Scene_2DPartsAnimCreateTool : public SceneBase
{
	public:
		Scene_2DPartsAnimCreateTool();				// コンストラクタ
		virtual ~Scene_2DPartsAnimCreateTool();		// デストラクタ

		virtual void	Process()			override;	// 計算
		virtual void	Draw()				override;	// 描画

	private:
		/* 関数 */
		bool	bLoadPartsAnimData();			// パーツアニメーションのデータ読み込み
		bool	bSavePartsAnimData();			// パーツアニメーションのデータ保存

		/* 変数 */
		bool								bOldMouseCursorCenterFixedFlg;	// ツール起動時のマウスの中心固定フラグ
		bool								bOldMouseCursorNotDepictedFlg;	// ツール起動時のマウスカーソル描写無効フラグ

		int									iSelectTime;					// 指定中のアニメーションの時間

		std::string														FileName;		// パーツアニメーション群の名称(新規作成時に入力する名称)
		std::vector<Struct_2DPartsAnim::PARTS_ANIM_PARTS_IMAGE_DATA>	PartsImageData;	// パーツの画像データ(アニメーション用パーツの画像データ)
		std::vector<Struct_2DPartsAnim::PARTS_ANIM_ANIM_DATA>			PartsAnimData;	// パーツアニメーションの情報(アニメーションのフレーム情報など)

		std::shared_ptr<Scene_UI_Table> 	paUI_Table[3];					// テーブルUI(0:パーツリスト, 1:アニメーションリスト, 2:選択時間でのパーツリスト)
};
