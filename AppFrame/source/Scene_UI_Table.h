/* シーン"UI(テーブル)"の宣言 */

#pragma once
#include <vector>
#include "SceneBase.h"
#include "AppVariableDefine.h"

// シーン"UI(テーブル)"
class Scene_UI_Table : public SceneBase
{
	public:
		Scene_UI_Table(int iTableWidth, int iDrawPosX, int iDrawPosY, std::string TableName);	// コンストラクタ
		virtual ~Scene_UI_Table();		// デストラクタ

		/* 関数 */
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描画

		/* セッター */
		void SetElement(std::vector<std::string> vecElement) { this->vecElement = vecElement; }	// 要素を設定

		/* ゲッター */
		int		iGetSelectElementIndex()	const { return this->iSelectElementIndex; }	// 選択中の要素の番号を取得
		bool	bGetTableSelectedFlg()		const { return this->bTableSelectedFlg; }	// テーブルが選択状態であるかのフラグを取得

	private:
		/* 変数 */
		int		iTableWidth;				// テーブルの幅
		int		iDrwawPosX;					// 描画位置X
		int		iDrwawPosY;					// 描画位置Y
		int		iSelectElementIndex;		// 選択中の要素の番号
		bool	bTableSelectedFlg;			// このテーブルが選択状態であるかのフラグ

		std::string					TableName;		// テーブル名
		std::vector<std::string>	vecElement;		// テーブルの要素
};
