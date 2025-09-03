/* シーン"UI(テーブル)"の定義 */

#include "Scene_UI_Table.h"

// コンストラクタ
Scene_UI_Table::Scene_UI_Table(int iTableWidth, int iDrawPosX, int iDrawPosY, std::string TableName) : SceneBase("Scene_UI_Table", 10000, false)
{
	// 引数
	// iTableWidth					<- テーブルUIの横幅
	// iDrawPosX					<- 描写位置X
	// iDrawPosY					<- 描写位置Y
	// TableName					<- テーブル名


	/* 初期化 */
	this->TableName				= TableName;	// テーブル名
	this->iTableWidth			= iTableWidth;	// テーブルの幅
	this->iDrwawPosX			= iDrawPosX;	// 描画位置X
	this->iDrwawPosY			= iDrawPosY;	// 描画位置Y
	this->iSelectElementIndex	= 0;			// 選択中の要素の番号
	this->bTableSelectedFlg		= false;		// このテーブルが選択状態であるかのフラグ
	this->vecElement.clear();
}

// デストラクタ
Scene_UI_Table::~Scene_UI_Table()
{

}

// 更新
void Scene_UI_Table::Update()
{
	/* 左クリック */
	if (gstKeyboardInputData.igInput[INPUT_TRG] & MOUSE_INPUT_LEFT)
	{
		/* マウスカーソルがこのUIに重なっている状態であるか確認 */
		if (gstKeyboardInputData.iMouseX >= this->iDrwawPosX && gstKeyboardInputData.iMouseX <= this->iDrwawPosX + this->iTableWidth &&
			gstKeyboardInputData.iMouseY >= this->iDrwawPosY && gstKeyboardInputData.iMouseY <= this->iDrwawPosY + 16 * 10)
		{
			// マウスカーソルがこのUIに重なっている場合
			this->bTableSelectedFlg = true;
		}
		else
		{
			// マウスカーソルがこのUIに重なっていない場合
			this->bTableSelectedFlg = false;
		}
	}

	/* 選択要素変更 */
	if (this->bTableSelectedFlg == true)
	{
		/* 上下キーで選択中の要素を変更 */
		if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_UP] == TRUE)
		{
			// 上キーが押された場合
			if (this->iSelectElementIndex > 0)
			{
				this->iSelectElementIndex--;
			}
		}
		else if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_DOWN] == TRUE)
		{
			// 下キーが押された場合
			if (this->iSelectElementIndex + 1 < this->vecElement.size())
			{
				this->iSelectElementIndex++;
			}
		}
	}
}

// 描画
void Scene_UI_Table::Draw()
{
	const int STRING_SIZE = 16; // 文字サイズ

	/* フレーム描写 */
	DrawBox(this->iDrwawPosX, this->iDrwawPosY, this->iDrwawPosX + this->iTableWidth, this->iDrwawPosY + STRING_SIZE, GetColor(0, 0, 0), TRUE);
	DrawBox(this->iDrwawPosX, this->iDrwawPosY, this->iDrwawPosX + this->iTableWidth, this->iDrwawPosY + STRING_SIZE * 10, GetColor(0, 0, 0), FALSE);
	if (this->bTableSelectedFlg == true)
	{
		DrawBox(this->iDrwawPosX, this->iDrwawPosY, this->iDrwawPosX + this->iTableWidth, this->iDrwawPosY + STRING_SIZE * 10, GetColor(255, 0, 0), FALSE);
	}

	/* テーブル名描写 */
	DrawString(this->iDrwawPosX, this->iDrwawPosY, this->TableName.c_str(), GetColor(255, 255, 255));

	/* 各要素描写 */
	for (int iIndex = 0; iIndex < this->vecElement.size(); ++iIndex)
	{
		/* 選択中の要素は赤色の枠を描写 */
		if (iIndex == this->iSelectElementIndex)
		{
			// 選択中の要素の描写
			DrawBox(this->iDrwawPosX, this->iDrwawPosY + STRING_SIZE * (iIndex + 1), this->iDrwawPosX + this->iTableWidth, this->iDrwawPosY + STRING_SIZE * (iIndex + 2), GetColor(255, 0, 0), FALSE);
			DrawString(this->iDrwawPosX + 2, this->iDrwawPosY + STRING_SIZE * (iIndex + 1) + 2, this->vecElement[iIndex].c_str(), GetColor(0, 0, 0));
		}
		else
		{
			DrawString(this->iDrwawPosX + 2, this->iDrwawPosY + STRING_SIZE * (iIndex + 1) + 2, this->vecElement[iIndex].c_str(), GetColor(0, 0, 0));
		}
	}
}
