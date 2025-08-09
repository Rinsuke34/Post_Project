/* 2024.12.08 駒沢風助 ファイル作成 */

#include <cstring>
#include "SceneBase.h"
#include "AppVariableDefine.h"

/* シーンのベースとなるクラスの定義 */

// コンストラクタ
SceneBase::SceneBase(const std::string& cName, const int iLayer, const bool bLowerLayerStopFlg)
{
	// 引数
	// iLayer					<- シーンのレイヤー
	// cName					<- シーンの名前
	// bLowerLayerProcessFlg	<- 下層レイヤーの計算停止フラグ(有効でも描写はされます)

	/* 初期化処理 */
	// SceneServerでの管理用データ
	this->stSceneName			= cName;					// シーン名を設定
	this->iLayerOrder			= iLayer;					// レイヤー順序を設定
	this->bDeleteFlg			= false;					// 削除フラグを無効化
	this->bLowerLayerStopFlg	= bLowerLayerStopFlg;		// 下位レイヤーの計算停止フラグを設定
}
