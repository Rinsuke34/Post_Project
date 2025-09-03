/* オブジェクトのベースクラスの宣言 */

#pragma once
#include <DxLib.h>

// オブジェクトベースクラス
class Object_Base
{
	public:
		Object_Base();					// コンストラクタ
		virtual ~Object_Base() {};		// デストラクタ

		/* 関数 */
		virtual void	InitialSetup()		{};	// 初期設定
		virtual void	Update()			{};	// 更新
		virtual void	Draw()				{};	// 描画
		
		/* セッター */
		void	SetDeleteFlg(bool bDeleteFlg) { this->bDeleteFlg = bDeleteFlg; }	// 削除フラグを設定(有効ならばオブジェクトを削除する)

		/* ゲッター */
		bool	bGetDeleteFlg() { return this->bDeleteFlg; };			// 削除フラグを取得

	protected:
		/* 変数 */
		bool	bDeleteFlg;		// 削除フラグ(有効ならばオブジェクトを削除する)
};

