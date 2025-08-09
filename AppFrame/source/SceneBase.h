/* 2024.12.08 駒沢風助 ファイル作成 */

#pragma once
#include <DxLib.h>
#include <string>
#include <mutex>

/* すべてのシーンのベースとなるクラスの宣言 */

// シーンベースクラス
class SceneBase
{
	public:
		SceneBase(const std::string& cName, const int iLayer, const bool bLowerLayerStopFlg);		// コンストラクタ
		virtual ~SceneBase() {};																	// デストラクタ

		virtual void	Initialization()	{};	// 初期化
		virtual void	Process()			{};	// 計算
		virtual void	Draw()				{};	// 描画

		bool	bGetDeleteFlg()				{ return this->bDeleteFlg; };				// 削除フラグを取得
		int		iGetSceneLayerOrder()		{ return this->iLayerOrder; };				// レイヤー順序を取得
		bool	bGetLowerLayerProcessFlg()	{ return this->bLowerLayerStopFlg; }		// 下層レイヤー計算停止フラグを取得
		std::string	stGetSceneName()		{ return this->stSceneName; }				// シーン名称を取得

	private:
	protected:
		/* 変数 */
		// SceneServerでの管理用データ
		std::string		stSceneName;					// シーン名称
		int				iLayerOrder;					// レイヤー順序(値が大きいほど手前に描写)
		bool			bLowerLayerStopFlg;				// 下層レイヤー計算停止フラグ(有効なら下層レイヤーで計算を行わない)
		bool			bDeleteFlg;						// 削除フラグ(有効ならシーンを削除)
};
