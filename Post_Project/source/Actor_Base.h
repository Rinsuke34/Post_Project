/* アクタのベースクラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 基底クラス
#include "Object_Base.h"
// 共通定義
#include "AppFrame.h"

/* 前方宣言 */
class DataList_Object;

// アクタベースクラス
class Actor_Base : public Object_Base
{
	public:
		Actor_Base();					// コンストラクタ
		virtual ~Actor_Base() {};		// デストラクタ

		/* 関数 */
		virtual void	Update()			override;	// 更新
		virtual void	Draw_Collision()	override;	// 描画(当たり判定)

		bool	bCheckTeamTag(std::string TeamTag);	// チームタグの確認
		int		iCheckCurrentAreaNo();				// 現在のエリア番号を取得

		/* セッター */
		void SetPosition(VECTOR vecPosition)				{ this->vecBasePosition			= vecPosition; }	// 基準座標の設定
		void SetTeamTag(std::string TeamTag)				{ this->TeamTag.push_back(TeamTag); }				// チームタグの設定
		void SetEnableGravityFlg(bool bEnable)				{ this->bEnableGravityFlg		= bEnable; }		// 重力有効フラグの設定
		void SetGravityVelocity(float fVelocity)			{ this->fGravityVelocity		= fVelocity; }		// 重力による落下速度の設定

		/* ゲッター */
		VECTOR							GetPosition()				{ return this->vecBasePosition; }		// 基準座標の取得
		std::vector<std::string>&		GetTeamTag()				{ return this->TeamTag; }				// チームタグの取得
		bool							GetEnableGravityFlg()		{ return this->bEnableGravityFlg; }		// 重力有効フラグの取得
		float							GetGravityVelocity()		{ return this->fGravityVelocity; }		// 重力による落下速度の取得
		Struct_Collision::COLLISION_BOX	GetBoxCollision()			{ return this->stBox; }					// コリジョン情報の取得

	protected:
		/* 変数 */
		// データリストへのポインタ
		std::shared_ptr<DataList_Object>		pDataList_Object;		// オブジェクト管理
		// 状態系
		VECTOR						vecBasePosition;		// 基準座標(足元の位置)
		std::vector<std::string>	TeamTag;				// チームタグ
		bool						bEnableGravityFlg;		// 重力有効フラグ
		float						fGravityVelocity;		// 重力による落下速度
		// コリジョン
		Struct_Collision::COLLISION_BOX	stBox;

		/* 関数 */
		void	Update_ApplyGravity_Simple();					// 重力処理(簡易)
		float	fDistanceToTargetSquare(VECTOR vecTargetPos);	// 指定座標との距離の2乗を取得
};
