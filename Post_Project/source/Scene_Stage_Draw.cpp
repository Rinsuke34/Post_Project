/* シーン"ステージ"の定義 */
// ※描写関連の関数のみ

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_Stage.h"
// 関連クラス
#include "DataList_Object.h"
#include "DataList_GameStatus.h"
// 共通定義
#include "ConstantDefine.h"

// 描画
void Scene_Stage::Draw()
{
	/* シャドウマップ描写 */
	DrawSetup_ShadowMap();

	/* ステージ描写 */
	DrawSetup_Stage();

	/* ステージ画像を描写 */
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, this->iScreenHandle_Stage, FALSE);

	/* カメラ設定 */
	DrawSetup_CameraPosition();

	/* シャドウマップ描写 */
	TestDrawShadowMap(this->iScreenHandle_ShadowMap[0], 0, 0, 256, 256);
	TestDrawShadowMap(this->iScreenHandle_ShadowMap[1], 0, 256, 256, 512);
}

// カメラ設定
void Scene_Stage::DrawSetup_CameraPosition()
{
	/* 3D基本設定 */
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	/* グローバルアンビエントライトカラーを赤色に設定 */
	// ※デフォルトの黒色だと暗すぎるので赤色に変更
	SetGlobalAmbientLight(GetColorF(0.5f, 0.5f, 0.5f, 1.0f));

	/* プレイヤー座標を取得 */
	VECTOR vecPlayerPos = this->pDataList_GameStatus->GetPlayerPosition_WoldMap();

	///* カメラの手前と奥のクリップ距離を設定 */
	//// ※スカイスフィア半径(25000)から余裕を少し持たせた値に仮設定
	//SetCameraNearFar(INIT_CAMERA_NEAR, INIT_CAMERA_FAR);

	/* カメラ設定 */
	VECTOR vecCameraPosition	= VAdd(vecPlayerPos, VGet(0.f, 1000.f, -500.f));
	VECTOR vecCameraTarget		= VAdd(vecPlayerPos, VGet(0.f, 10.f, 0.f));
	SetCameraPositionAndTarget_UpVecY(vecCameraPosition, vecCameraTarget);

	///* 3Dサウンドのリスナー位置とリスナー前方位置を設定 */
	//Set3DSoundListenerPosAndFrontPos_UpVecY(this->StageStatusList->vecGetCameraPosition(), this->StageStatusList->vecGetCameraTarget());
}

// シャドウマップ作成
void Scene_Stage::DrawSetup_ShadowMap()
{
	/* プレイヤー座標を取得 */
	VECTOR vecPlayerPos = this->pDataList_GameStatus->GetPlayerPosition_WoldMap();

	/* 透明度に関係なく描写するよう設定　*/
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_ALWAYS);

	/* 動的オブジェクトのシャドウマップ */
	{
		/* ライト方向設定 */
		// ※ ライトの方向は真下とする
		SetShadowMapLightDirection(this->iScreenHandle_ShadowMap[SHADOWMAP_ACTOR], VGet(0.f, -1.f, 0.f));

		/* シャドウマップの範囲指定 */
		// ※ プレイヤー座標を中心に設定
		SetShadowMapDrawArea(this->iScreenHandle_ShadowMap[SHADOWMAP_ACTOR],
			VAdd(vecPlayerPos, VGet(-SHADOW_ACTOR_MAP_SIZE_WIDE, -SHADOW_ACTOR_MAP_SIZE_HEIGHT, -SHADOW_ACTOR_MAP_SIZE_WIDE)),
			VAdd(vecPlayerPos, VGet(+SHADOW_ACTOR_MAP_SIZE_WIDE, +SHADOW_ACTOR_MAP_SIZE_HEIGHT, +SHADOW_ACTOR_MAP_SIZE_WIDE)));

		/* シャドウマップ描写開始 */
		ShadowMap_DrawSetup(this->iScreenHandle_ShadowMap[SHADOWMAP_ACTOR]);

		/* 全ての動的オブジェクトの描写 */
		this->pDataList_Object->Draw_Actor_Shadow();

		/* シャドウマップ描写終了 */
		ShadowMap_DrawEnd();
	}

	/* 動的オブジェクトのシャドウマップ */
	{
		/* ライト方向設定 */
		// ※ ライトの方向は少し奥とする
		SetShadowMapLightDirection(this->iScreenHandle_ShadowMap[SHADOWMAP_GROUND], VNorm(VGet(0.f, -1.f, 1.f)));

		/* シャドウマップの範囲指定 */
		// ※ プレイヤー座標を中心に設定
		SetShadowMapDrawArea(this->iScreenHandle_ShadowMap[SHADOWMAP_GROUND],
			VAdd(vecPlayerPos, VGet(-SHADOW_GROUND_MAP_SIZE_WIDE, -SHADOW_GROUND_MAP_SIZE_HEIGHT, -SHADOW_GROUND_MAP_SIZE_WIDE)),
			VAdd(vecPlayerPos, VGet(+SHADOW_GROUND_MAP_SIZE_WIDE, +SHADOW_GROUND_MAP_SIZE_HEIGHT, +SHADOW_GROUND_MAP_SIZE_WIDE)));

		/* シャドウマップ描写開始 */
		ShadowMap_DrawSetup(this->iScreenHandle_ShadowMap[SHADOWMAP_GROUND]);

		/* 全ての静的オブジェクトの描写 */
		this->pDataList_Object->Draw_Ground_Shadow();

		/* シャドウマップ描写終了 */
		ShadowMap_DrawEnd();
	}
}

// ステージの描写
void Scene_Stage::DrawSetup_Stage()
{
	/* ステージ描写開始 */
	SetDrawScreen(this->iScreenHandle_Stage);

	/* 画面クリア */
	ClearDrawScreen();

	/* カメラ設定 */
	DrawSetup_CameraPosition();

	/* 描写に使用するシャドウマップの設定 */
	SetUseShadowMap(0, this->iScreenHandle_ShadowMap[SHADOWMAP_ACTOR]);
	SetUseShadowMap(1, this->iScreenHandle_ShadowMap[SHADOWMAP_GROUND]);

	/* 半透明部分を描写しないよう設定 */
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_NOT_SEMITRANS_ONLY);

	/* オブジェクト描写(半透明部分を除く) */
	this->pDataList_Object->Draw_All();

	/* 描写に使用するシャドウマップの設定を解除 */
	SetUseShadowMap(0, -1);
	SetUseShadowMap(1, -1);

	/* 半透明部分のみ描写するように設定 */
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_SEMITRANS_ONLY);

	/* オブジェクト描写(半透明部分のみ) */
	// ※ 地形を描写してしまうとシャドウマップが適用されなくなるので描写しない
	this->pDataList_Object->Draw_Actor();

	/* メイン画面への描写を終了 */
	SetDrawScreen(DX_SCREEN_BACK);
}
