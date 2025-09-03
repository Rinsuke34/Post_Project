/* 地形(平面)クラスの宣言 */

#include "Ground_Base.h"

// 地形(平面)クラス
class Ground_Plane : public Ground_Base
{
	public:
		Ground_Plane();					// コンストラクタ
		virtual ~Ground_Plane() {};		// デストラクタ

		/* 関数 */
		virtual void	Update();	// 更新
		virtual void	Draw();		// 描画

		// コリジョン接触判定
		bool HitCheck(Struct_Collision::COLLISION_CAPSULE	stCapsule)	override;	// カプセル
		bool HitCheck(Struct_Collision::COLLISION_SQHERE	stSqhere)	override;	// 球体
		bool HitCheck(Struct_Collision::COLLISION_LINE		stLine)		override;	// 線分

	private:
		/* 変数 */
		VECTOR		vecNormal;			// 法線ベクトル
		VECTOR		avecVertex[4];		// 頂点座標(4頂点)反時計回り[0:左奥,1:右奥,2:右前,3,左前]
};
