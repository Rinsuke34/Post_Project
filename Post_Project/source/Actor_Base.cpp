/* アクタのベースクラスの定義 */

/* 使用する要素のインクルード */
// ヘッダファイル
#include "Actor_Base.h"
// 関連クラス
#include "DataList_Object.h"
#include "Ground_Base.h"

// コンストラクタ
Actor_Base::Actor_Base() : Object_Base()
{
	/* データリスト取得 */
	this->pDataList_Object = std::dynamic_pointer_cast<DataList_Object>(gpDataListServer->GetDataList("DataList_Object"));			// オブジェクト管理

	/* 初期化 */
	this->vecBasePosition		= VGet(0.0f, 0.0f, 0.0f);
	this->bEnableGravityFlg		= false;	// 重力有効フラグ
	this->fGravityVelocity		= 0.f;		// 重力による落下速度
	this->fGravityAcceleration	= 0.f;		// 重力加速度
}

// 更新
void Actor_Base::Update()
{
	/* 重力処理 */
	if (this->bEnableGravityFlg)
	{
		Update_ApplyGravity_Simple();
	}
}

// チームタグの確認
bool Actor_Base::bCheckTeamTag(std::string TeamTag)
{
	// 引数
	// TeamTag	: チームタグ名
	// 戻り値
	// bool		: そのチームタグを所持している(true) / 所持していない(false)

	return (std::find(this->TeamTag.begin(), this->TeamTag.end(), TeamTag) != this->TeamTag.end());
}

// 現在のエリア番号を取得
int Actor_Base::iCheckCurrentAreaNo()
{
	// 戻り値
	// int	: 現在のエリア番号(存在しない場合は-1)

	int col = static_cast<int>(this->vecBasePosition.x / (AREA_SIZE_BLOCK_X * MAP_BLOCK_SIZE_X));
	int row = static_cast<int>(this->vecBasePosition.z / (AREA_SIZE_BLOCK_Z * MAP_BLOCK_SIZE_Z));

	if (col < 0 || col > 2 || row < 0 || row > 2)
	{
		// エリア外
		return -1;
	}
	else
	{
		return col + row * 3;
	}
}


// 重力処理(簡易)
// ※ 基準座標と重力による落下速度のみを考慮した簡易的な処理
void Actor_Base::Update_ApplyGravity_Simple()
{
	/* 移動前の座標を保存 */
	VECTOR vecBasePosition = this->vecBasePosition;

	/* 重力による落下速度と移動後の座標を算出 */
	this->fGravityVelocity	+=	this->fGravityAcceleration;
	VECTOR vecNextPosition	=	VAdd(this->vecBasePosition, VGet(0.f, this->fGravityVelocity, 0.f));

	/* 移動前と移動後の座標からコリジョンを作成 */
	Struct_Collision::COLLISION_LINE stMovementLine;
	stMovementLine.vecLineStart	= vecBasePosition;
	stMovementLine.vecLineEnd	= vecNextPosition;

	/* 足場との当たり判定処理 */
	// ※ 軽量化のため現在のエリアの足場のみ確認
	// ※ エリア外の場合は足場との当たり判定を行わない
	int iAreaNo = iCheckCurrentAreaNo();
	if (iAreaNo != -1)
	{
		for (auto& Ground : this->pDataList_Object->GetGroundList(iAreaNo))
		{
			// 足場のコリジョンと接触しているか確認
			if (Ground->HitCheck(stMovementLine))
			{
				// 接触している場合
				/* 衝突点を取得 */
				VECTOR vecHitPosition = Ground->HitPosition(stMovementLine);

				// 衝突点が移動前座標により近い場合のみ移動後の座標を更新
				float fDistCurrent = VSize(VSub(vecNextPosition, vecBasePosition));
				float fDistHit = VSize(VSub(vecHitPosition, vecBasePosition));
				if (fDistHit < fDistCurrent)
				{
					vecNextPosition = vecHitPosition;
				}

				/* 落下速度を更新 */
				this->fGravityVelocity = 0.f;
			}
		}
	}

	/* 基準座標を更新 */
	this->vecBasePosition = vecNextPosition;
}