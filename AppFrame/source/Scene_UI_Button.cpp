/* シーン"UI(ボタン)"の定義 */

#include "Scene_UI_Button.h"

// コンストラクタ
Scene_UI_Button::Scene_UI_Button(int iButtonWidth, int iDrawPosX, int iDrawPosY, std::string ButtonName, int iInputType) : SceneBase("Scene_UI_Table", 10000, false)
{
	// 引数
	// iButtonWidth					<- ボタンUIの横幅
	// iDrawPosX					<- 描写位置X
	// iDrawPosY					<- 描写位置Y
	// ButtonName					<- テーブル名
	// iInputType					<- 入力タイプ(0:トグル, 1:トリガー)

	/* 初期化 */
	this->iButtonWidth	= iButtonWidth;
	this->iDrwawPosX	= iDrawPosX;
	this->iDrwawPosY	= iDrawPosY;
	this->iInputType	= iInputType;
	this->ButtonName	= ButtonName;

	this->bSelectFlg	= false;
}

// デストラクタ
Scene_UI_Button::~Scene_UI_Button()
{

}

// 更新
void Scene_UI_Button::Update()
{
	/* トリガ入力であるなら入力をOFFに設定する */
	if (this->iInputType == INPUT_TYPE_TRIGGER)
	{
		this->bSelectFlg = false;
	}

	/* 左クリック */
	if (gstKeyboardInputData.igInput[INPUT_TRG] & MOUSE_INPUT_LEFT)
	{
		/* マウスカーソルがこのUIに重なっている状態であるか確認 */
		if (gstKeyboardInputData.iMouseX >= this->iDrwawPosX && gstKeyboardInputData.iMouseX <= this->iDrwawPosX + this->iButtonWidth &&
			gstKeyboardInputData.iMouseY >= this->iDrwawPosY && gstKeyboardInputData.iMouseY <= this->iDrwawPosY + 16)
		{
			// マウスカーソルがこのUIに重なっている場合
			/* 入力タイプに応じた処理を実施 */
			switch (this->iInputType)
			{
				// トグル入力
				case INPUT_TYPE_TOGGLE:
					this->bSelectFlg = !this->bSelectFlg;
					break;

				// トリガ入力
				case INPUT_TYPE_TRIGGER:
					this->bSelectFlg = true;
					break;

				default:
					break;
			}
		}
	}
}

// 描画
void Scene_UI_Button::Draw()
{
	const int STRING_SIZE = 16; // 文字サイズ

	/* ボタン描写 */
	DrawBox(this->iDrwawPosX, this->iDrwawPosY, this->iDrwawPosX + this->iButtonWidth, this->iDrwawPosY + STRING_SIZE, GetColor(0, 0, 0), TRUE);

	/* 枠描写 */
	if (this->bSelectFlg)
	{
		// 選択中
		DrawBox(this->iDrwawPosX, this->iDrwawPosY, this->iDrwawPosX + this->iButtonWidth, this->iDrwawPosY + STRING_SIZE, GetColor(255, 0, 0), FALSE);
	}
	else
	{
		// 非選択中
		DrawBox(this->iDrwawPosX, this->iDrwawPosY, this->iDrwawPosX + this->iButtonWidth, this->iDrwawPosY + STRING_SIZE, GetColor(255, 255, 255), FALSE);
	}

	/* ボタン名描写 */
	DrawString(this->iDrwawPosX, this->iDrwawPosY, this->ButtonName.c_str(), GetColor(255, 255, 255));
}
