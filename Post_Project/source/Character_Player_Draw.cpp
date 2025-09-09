/* プレイヤークラスの定義 */
// ※ 描写部分のみ

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Character_Player.h"
// 関連クラス
#include "DataList_Object.h"
#include "Ground_Base.h"
// 共通定義
#include "Test_ConstantDefine.h"
#include "ConstantDefine.h"

// 描画
void Character_Player::Draw()
{
	/* アニメーション描写 */
	Draw_Animation();

	/* 以下、テスト描写 */
	Draw_Collision();

	DrawLine3D(VAdd(this->vecBasePosition, VGet(100.f, 0.f, 0.f)), VAdd(this->vecBasePosition, VGet(-100.f, 0.f, 0.f)), GetColor(255, 0, 0));
	DrawLine3D(VAdd(this->vecBasePosition, VGet(0.f, 100.f, 0.f)), VAdd(this->vecBasePosition, VGet(0.f, -100.f, 0.f)), GetColor(0, 255, 0));
	DrawLine3D(VAdd(this->vecBasePosition, VGet(0.f, 0.f, 100.f)), VAdd(this->vecBasePosition, VGet(0.f, 0.f, -100.f)), GetColor(0, 0, 255));

	DrawTriangle3D(VAdd(this->vecBasePosition, VGet(0.f, 0.f, 0.f)), VAdd(this->vecBasePosition, VGet(50.f, 0.f, 0.f)), VAdd(this->vecBasePosition, VGet(0.f, 50.f, 0.f)), GetColor(255, 255, 0), TRUE);
}

// アニメーション描写
void Character_Player::Draw_Animation()
{
	/* 中心座標を基準としたアニメーションを描写するパネルの頂点座標を計算 */
	float fHalfWide		= CHARACTER_PARTS_ANIM_DRAW_SIZE_WIDE / 2;
	float fHeight		= CHARACTER_PARTS_ANIM_DRAW_SIZE_HEIGHT;
	// 正方形を維持するためのY+側のY座標補正
	float fYLean		= sqrtf(fHeight * fHeight - TOPVIEW_LEAN_AMOUNT * TOPVIEW_LEAN_AMOUNT);

	VERTEX3D aVertex[4];
	aVertex[0].pos = VGet(this->vecBasePosition.x + fHalfWide, this->vecBasePosition.y + fYLean,	this->vecBasePosition.z + TOPVIEW_LEAN_AMOUNT);
	aVertex[1].pos = VGet(this->vecBasePosition.x + fHalfWide, this->vecBasePosition.y,				this->vecBasePosition.z);
	aVertex[2].pos = VGet(this->vecBasePosition.x - fHalfWide, this->vecBasePosition.y + fYLean,	this->vecBasePosition.z + TOPVIEW_LEAN_AMOUNT);
	aVertex[3].pos = VGet(this->vecBasePosition.x - fHalfWide, this->vecBasePosition.y,				this->vecBasePosition.z);

	// 頂点の初期化
	for (int i = 0; i < 4; ++i)
	{
		aVertex[i].dif = GetColorU8(255, 255, 255, 255);
		aVertex[i].spc = GetColorU8(0, 0, 0, 0);
		aVertex[i].su = 0.f;
		aVertex[i].sv = 0.f;
	}

	/* 各面の描画 */
	// インデックスデータ（奥面の2ポリゴン）
	unsigned short IndexBack[6] = { 3, 2, 1, 1, 2, 0 };

	// 法線ベクトルを設定
	for (int i = 0; i < 4; ++i)
	{
		aVertex[i].norm = VGet(0.0f, 0.0f, -1.0f);
	}

	// uv座標を設定
	// 右上
	aVertex[0].u = 1.f;
	aVertex[0].v = 0.f;
	// 右下
	aVertex[1].u = 1.f;
	aVertex[1].v = 1.f;
	// 左上
	aVertex[2].u = 0.f;
	aVertex[2].v = 0.f;
	// 左下
	aVertex[3].u = 0.f;
	aVertex[3].v = 1.f;

	// 四角形（板ポリゴン）の描画
	DrawPolygonIndexed3D(aVertex, 8, IndexBack, 2, this->iScreenHandle_Animation, TRUE);
//	DrawPolygonIndexed3D(aVertex, 8, IndexBack, 2, this->iTestCg, TRUE);
}

// アニメーション更新
void Character_Player::Update_Animation()
{
	/* アニメーション描写開始 */
	SetDrawScreen(this->iScreenHandle_Animation);

	/* 画面クリア */
	ClearDrawScreen();

	/* 画面サイズを設定 */
	this->pDataList_2DPartsAnimCreateTool->SetDrawScreenSize(CHARACTER_PARTS_ANIM_DRAW_SIZE_WIDE, CHARACTER_PARTS_ANIM_DRAW_SIZE_HEIGHT);

	/* 現在モーションのパーツアニメーションの描写 */
	this->pDataList_2DPartsAnimCreateTool->DrawPartsAnim(this->AnimFileName, this->NowMotionName, this->iMotionCount);

	/* アニメーション描写終了 */
	SetDrawScreen(DX_SCREEN_BACK);

	/* モーションカウントを進める */
	++this->iMotionCount;

	/* 現在のモーションの最大カウントを超えているか確認 */
	if (this->iMotionCount >= this->pDataList_2DPartsAnimCreateTool->iGetPartsAnimMaxTime(this->AnimFileName, this->NowMotionName))
	{
		// 超えている場合
		/* モーションカウントをリセット */
		this->iMotionCount = 0;
	}
}
