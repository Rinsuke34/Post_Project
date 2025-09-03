/* シーン"UI(ボタン)"の宣言 */

#pragma once
#include <vector>
#include "SceneBase.h"
#include "AppVariableDefine.h"

// シーン"UI(ボタン)"
class Scene_UI_Button : public SceneBase
{
	public:
		Scene_UI_Button(int iButtonWidth, int iDrawPosX, int iDrawPosY, std::string ButtonName, int iInputType);	// コンストラクタ
		virtual ~Scene_UI_Button();		// デストラクタ

		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描画

		bool	bGetSelectFlg()				{ return this->bSelectFlg; }	// 選択状態であるかのフラグを取得

		/* クラス内で使用する定数 */
		static const int INPUT_TYPE_TOGGLE	= 0;	// 入力タイプ:トグル
		static const int INPUT_TYPE_TRIGGER = 1;	// 入力タイプ:トリガー

	private:
		/* 変数 */
		int			iButtonWidth;		// テーブルの幅
		int			iDrwawPosX;			// 描画位置X
		int			iDrwawPosY;			// 描画位置Y
		bool		bSelectFlg;			// 選択状態であるかのフラグ
		int			iInputType;			// 入力タイプ(0:トグル, 1:トリガー)
		std::string	ButtonName;			// ボタン名
};
