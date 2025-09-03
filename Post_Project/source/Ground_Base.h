#/* 地形のベースクラスの宣言 */

#include "Object_Base.h"
#include "AppFrame.h"

// 地形ベースクラス
class Ground_Base : public Object_Base
{
	public:
		Ground_Base();					// コンストラクタ
		virtual ~Ground_Base() {};		// デストラクタ

		/* 関数 */
		virtual void	InitialSetup()	{};	// 初期設定
		virtual void	Update()		{};	// 更新
		virtual void	Draw()			{};	// 描画

		// コリジョン接触判定
		virtual bool HitCheck(Struct_Collision::COLLISION_CAPSULE	stCapsule)	{ return false; };	// カプセル
		virtual bool HitCheck(Struct_Collision::COLLISION_SQHERE	stSqhere)	{ return false; };	// 球体
		virtual bool HitCheck(Struct_Collision::COLLISION_LINE		stLine)		{ return false; };	// 線分
};
