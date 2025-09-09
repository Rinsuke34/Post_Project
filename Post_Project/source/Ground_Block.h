/* 地形(ブロック)クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Ground_Base.h"

// 地形(ブロック)クラス
class Ground_Block : public Ground_Base
{
	public:
		Ground_Block();					// コンストラクタ
		virtual ~Ground_Block() {};		// デストラクタ

		/* クラス内で使用する定数 */
		// 面の種類
		static const int FACE_TYPE_TOP		= 0;	// 面の種類:上面
		static const int FACE_TYPE_SIDE		= 1;	// 面の種類:横面
		static const int FACE_TYPE_BOTTOM	= 2;	// 面の種類:下面
		// 面の方向
		static const int DIRECTION_X_PLUS	= 0;	// +X方向
		static const int DIRECTION_X_MINUS	= 1;	// -X方向
		static const int DIRECTION_Y_PLUS	= 2;	// +Y方向
		static const int DIRECTION_Y_MINUS	= 3;	// -Y方向
		static const int DIRECTION_Z_PLUS	= 4;	// +Z方向
		static const int DIRECTION_Z_MINUS	= 5;	// -Z方向
		static const int DIRECTION_MAX		= 6;	// 方向数

		/* 関数 */
		virtual void	Draw();			// 描画

		/* セッター */
		void SetBoxCollision(Struct_Collision::COLLISION_BOX stBox)				{ this->stBox						= stBox; }			// ボックスコリジョンの情報を設定
		void SetTextureHandle(int iFaceType, std::shared_ptr<int> iGrhandle)	{ this->apiGrHandle[iFaceType]		= iGrhandle; };		// 面のテクスチャハンドルを設定(0:上面, 1:横面, 2:下面)
		void SetFaceDrawFlg(int iDirection, bool bFaceDrawFlg)					{ this->bFaceDrawFlg[iDirection]	= bFaceDrawFlg; };	// 面の描画フラグを設定(0:+X, 1:-X, 2:+Y, 3:-Y, 4:+Z, 5:-Z)

		/* ゲッター */
		Struct_Collision::COLLISION_BOX GetBoxCollision()				{ return stBox; }						// ボックスコリジョンの情報を取得
		bool							GetFaceDrawFlg(int iDirection)	{ return bFaceDrawFlg[iDirection]; }	// 面の描写フラグを取得

	private:
		/* 変数 */
		std::shared_ptr<int>			apiGrHandle[3];					// 使用する画像のハンドル(0:上面, 1:横面: 2,下面)
		bool							bFaceDrawFlg[DIRECTION_MAX];	// 面の描画フラグ
};
