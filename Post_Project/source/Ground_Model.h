/* 地形(3Dモデル)クラスの宣言 */

#include "Ground_Base.h"

// 地形(3Dモデル)クラス
class Ground_Model : public Ground_Base
{
	public:
		Ground_Model();				// コンストラクタ
		virtual ~Ground_Model();	// デストラクタ

		/* 関数 */
		virtual void	InitialSetup();		// 初期設定
		virtual void	Update();			// 更新
		virtual void	Draw();				// 描画
		void			Update_Collision();	// 更新(コリジョン情報)

		// コリジョン接触判定
		bool HitCheck(Struct_Collision::COLLISION_CAPSULE	stCapsule)	override;	// カプセル
		bool HitCheck(Struct_Collision::COLLISION_SQHERE	stSqhere)	override;	// 球体
		bool HitCheck(Struct_Collision::COLLISION_LINE		stLine)		override;	// 線分

		/* セッター */
		void SetModelHandle(int iModelHandle)	{ this->iModelHandle	= iModelHandle; }	// モデルハンドルを設定
		void SetPosition(VECTOR vecPosition)	{ this->vecPosition		= vecPosition; }	// オブジェクトの座標を設定
		void SetRotation(VECTOR vecRotation)	{ this->vecRotation		= vecRotation; }	// オブジェクトの回転量を設定
		void SetScale(VECTOR vecScale)			{ this->vecScale		= vecScale; }		// オブジェクトの拡大率を設定

		/* ゲッター */
		int	GetModelHandle()					{ return this->iModelHandle; }			// モデルハンドルを取得
		VECTOR	GetPosition()					{ return this->vecPosition; }			// オブジェクトの座標を取得
		VECTOR	GetRotation()					{ return this->vecRotation; }			// オブジェクトの回転量を取得
		VECTOR	GetScale()						{ return this->vecScale; }				// オブジェクトの拡大率を取得

	private:
		/* 変数 */
		int iModelHandle;				// モデルハンドル
		int iCollisionFrameNo;			// コリジョン用のフレーム番号
		VECTOR	vecPosition;			// オブジェクトの座標
		VECTOR	vecRotation;			// オブジェクトの回転量
		VECTOR	vecScale;				// オブジェクトの拡大率(x,y,z方向それぞれの拡大倍率)
};
