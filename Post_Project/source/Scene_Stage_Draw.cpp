/* シーン"ステージ"の定義 */
// ※描写関連の関数のみ

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Scene_Stage.h"
// 関連クラス
#include "DataList_Object.h"
#include "DataList_GameStatus.h"
#include "DataList_StageCreate.h"
// 共通定義
#include "ConstantDefine.h"

// 描画
void Scene_Stage::Draw()
{
	/* ゲーム状態管理データリストが読み込まれているか確認 */
	if (this->pDataList_GameStatus != nullptr)
	{
		// 読み込まれている場合
		/* シャドウマップ描写 */
		DrawSetup_ShadowMap();

		/* ステージ描写 */
		DrawSetup_Stage();

		///* シャドウマップ描写 */
		//TestDrawShadowMap(this->iScreenHandle_ShadowMap[0], 0, 0, 256, 256);
		//TestDrawShadowMap(this->iScreenHandle_ShadowMap[1], 0, 256, 256, 512);
	}
	/* ステージクリエイト情報管理データリストが読み込まれているか確認 */
	else if (this->pDataList_StageCreate != nullptr)
	{
		// 読み込まれている場合
		DrawSetup_Stage_StageCreate();
	}

	/* ステージ画像を描写 */
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDE, SCREEN_SIZE_HEIGHT, this->iScreenHandle_Stage, FALSE);

	/* カメラ設定 */
	DrawSetup_CameraPosition();
}

// カメラ設定
void Scene_Stage::DrawSetup_CameraPosition()
{
	/* カメラ座標 */
	VECTOR vecCameraPosition	= VGet(0.f, 0.f, 0.f);
	VECTOR vecCameraTarget		= VGet(0.f, 0.f, 0.f);

	/* 3D基本設定 */
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	/* グローバルアンビエントライトカラーを赤色に設定 */
	// ※デフォルトの黒色だと暗すぎるので赤色に変更
	SetGlobalAmbientLight(GetColorF(0.5f, 0.5f, 0.5f, 1.0f));

	/* ゲーム状態管理データリストが読み込まれているか確認 */
	if (this->pDataList_GameStatus != nullptr)
	{
		// 読み込まれている場合
		/* プレイヤー座標からカメラ設定を実施 */
		VECTOR vecPlayerPos = this->pDataList_GameStatus->GetPlayerPosition_WoldMap();

		/* カメラ設定 */
		vecCameraTarget		= VAdd(vecPlayerPos,	VGet(0.f, 10.f, 0.f));
		vecCameraPosition	= VAdd(vecCameraTarget, VGet(0.f, 1000.f, -500.f));
	}
	/* ステージクリエイト情報管理データリストが読み込まれているか確認 */
	else if (this->pDataList_StageCreate != nullptr)
	{
		// 読み込まれている場合
		/* 選択中の座標からカメラの座標を算出 */
		vecCameraTarget.x = this->pDataList_StageCreate->vecGetSelectPos().x * MAP_BLOCK_SIZE_X + (MAP_BLOCK_SIZE_X / 2);
		vecCameraTarget.y = this->pDataList_StageCreate->vecGetSelectPos().y * MAP_BLOCK_SIZE_Y + (MAP_BLOCK_SIZE_Y / 2);
		vecCameraTarget.z = this->pDataList_StageCreate->vecGetSelectPos().z * MAP_BLOCK_SIZE_Z + (MAP_BLOCK_SIZE_Z / 2);
		vecCameraPosition = VAdd(vecCameraTarget, VGet(0.f, 1000.f, -500.f));
	}
	
	/* カメラ設定 */
	SetCameraPositionAndTarget_UpVecY(vecCameraPosition, vecCameraTarget);
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

// ステージの描写(ステージクリエイト用)
void Scene_Stage::DrawSetup_Stage_StageCreate()
{
	/* ステージ描写開始 */
	SetDrawScreen(this->iScreenHandle_Stage);

	/* 画面クリア */
	ClearDrawScreen();

	/* カメラ設定 */
	DrawSetup_CameraPosition();

	/* 全ての地形オブジェクトの描写 */
	this->pDataList_StageCreate->Draw_GroundObject();

	VECTOR_INT	vecSelectPos		= this->pDataList_StageCreate->vecGetSelectPos();
	/* ポジションをワールド座標に変換 */
	VECTOR vecPosition;
	vecPosition.x = vecSelectPos.x * MAP_BLOCK_SIZE_X + (MAP_BLOCK_SIZE_X / 2);
	vecPosition.y = vecSelectPos.y * MAP_BLOCK_SIZE_Y + (MAP_BLOCK_SIZE_Y / 2);
	vecPosition.z = vecSelectPos.z * MAP_BLOCK_SIZE_Z + (MAP_BLOCK_SIZE_Z / 2);

	VECTOR		vecMapTileHarfSize	= VGet(MAP_BLOCK_SIZE_X / 2, MAP_BLOCK_SIZE_Y / 2, MAP_BLOCK_SIZE_Z / 2);

	/* 選択中の座標を描写 */
	// 頂点を設定
	VECTOR aVertex[8];
	aVertex[0] = VGet(vecPosition.x + vecMapTileHarfSize.x, vecPosition.y + vecMapTileHarfSize.y, vecPosition.z + vecMapTileHarfSize.z);
	aVertex[1] = VGet(vecPosition.x + vecMapTileHarfSize.x, vecPosition.y + vecMapTileHarfSize.y, vecPosition.z - vecMapTileHarfSize.z);
	aVertex[2] = VGet(vecPosition.x + vecMapTileHarfSize.x, vecPosition.y - vecMapTileHarfSize.y, vecPosition.z + vecMapTileHarfSize.z);
	aVertex[3] = VGet(vecPosition.x + vecMapTileHarfSize.x, vecPosition.y - vecMapTileHarfSize.y, vecPosition.z - vecMapTileHarfSize.z);
	aVertex[4] = VGet(vecPosition.x - vecMapTileHarfSize.x, vecPosition.y + vecMapTileHarfSize.y, vecPosition.z + vecMapTileHarfSize.z);
	aVertex[5] = VGet(vecPosition.x - vecMapTileHarfSize.x, vecPosition.y + vecMapTileHarfSize.y, vecPosition.z - vecMapTileHarfSize.z);
	aVertex[6] = VGet(vecPosition.x - vecMapTileHarfSize.x, vecPosition.y - vecMapTileHarfSize.y, vecPosition.z + vecMapTileHarfSize.z);
	aVertex[7] = VGet(vecPosition.x - vecMapTileHarfSize.x, vecPosition.y - vecMapTileHarfSize.y, vecPosition.z - vecMapTileHarfSize.z);

	// 線分を描画
	DrawLine3D(aVertex[0], aVertex[1], GetColor(255, 255, 255));
	DrawLine3D(aVertex[1], aVertex[5], GetColor(255, 255, 255));
	DrawLine3D(aVertex[5], aVertex[4], GetColor(255, 255, 255));
	DrawLine3D(aVertex[4], aVertex[0], GetColor(255, 255, 255));
	DrawLine3D(aVertex[2], aVertex[3], GetColor(255, 255, 255));
	DrawLine3D(aVertex[3], aVertex[7], GetColor(255, 255, 255));
	DrawLine3D(aVertex[7], aVertex[6], GetColor(255, 255, 255));
	DrawLine3D(aVertex[6], aVertex[2], GetColor(255, 255, 255));
	DrawLine3D(aVertex[0], aVertex[2], GetColor(255, 255, 255));
	DrawLine3D(aVertex[1], aVertex[3], GetColor(255, 255, 255));
	DrawLine3D(aVertex[4], aVertex[6], GetColor(255, 255, 255));
	DrawLine3D(aVertex[5], aVertex[7], GetColor(255, 255, 255));
	

	/* メイン画面への描写を終了 */
	SetDrawScreen(DX_SCREEN_BACK);
}
