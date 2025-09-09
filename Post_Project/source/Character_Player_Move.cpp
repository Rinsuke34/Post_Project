/* プレイヤークラスの定義 */
// ※ 移動部分のみ

/* 使用する要素のインクルード */
// 標準ライブラリ
#define NOMINMAX
#include <algorithm>
// ヘッダファイル
#include "Character_Player.h"
// 関連クラス
#include "DataList_Object.h"
#include "Ground_Base.h"
// 共通定義
#include "Test_ConstantDefine.h"

// 重力処理
void Character_Player::Update_ApplyGravity()
{
	// テスト
	this->fGravityAcceleration = TEST_GRAVITY_ACCELERATION;	// 重力加速度(仮設定)

	/* ジャンプ処理 */
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_SPACE] == TRUE)
	{
		this->fGravityVelocity = TEST_JUMP_GRAVITY_VELOCITY;
	}

	/* 重力加速度を加算 */
	this->fGravityVelocity -= this->fGravityAcceleration;
	 
	/* 移動前の基準座標を保存 */
	VECTOR vecPrevPosition	= this->vecBasePosition;

	/* 移動後の基準座標を算出 */
	VECTOR vecMovePosition = VAdd(vecPrevPosition, VGet(0.f, this->fGravityVelocity, 0.f));

	/* 移動後の座標と移動前の座標からボックスコリジョンを作成 */
	// ※ 中心点を平均値、大きさは高さを(移動量 + 直径)にすれば2点を通るボックスになるのでそれを基準にコリジョンをつくる
	// ※ 横方向には少し余裕を持たせる(壁に接触した状態でジャンプができるようにするため)
	Struct_Collision::COLLISION_BOX stMoveBox;
	stMoveBox.vecBoxCenter		= VGet(this->vecBasePosition.x, (vecMovePosition.y + this->vecBasePosition.y) / 2.f, this->vecBasePosition.z);
	stMoveBox.vecBoxHalfSize	= VGet(this->stBox.vecBoxHalfSize.x - COLLISION_CHECK_CEILING_PREVENTION, (fabsf(vecMovePosition.y - this->vecBasePosition.y) / 2) + this->stBox.vecBoxHalfSize.y, this->stBox.vecBoxHalfSize.z - COLLISION_CHECK_CEILING_PREVENTION);

	// 上昇中、下降中それぞれの補正
	if (this->fGravityVelocity > 0)
	{
		// 上昇中
		// ボックスコリジョンの下部分を判定しないようにする(ジャンプ直後に着地判定が出てしまう問題対策)
		stMoveBox.vecBoxCenter.y	+= COLLISION_CHECK_CEILING_PREVENTION / 2.f;
		stMoveBox.vecBoxHalfSize.y	-= COLLISION_CHECK_CEILING_PREVENTION;
	}
	else
	{
		// 下降中
		// ボックスコリジョンの上部分を判定しないようにする(天井に対して着地判定が出てしまう問題対策)
		stMoveBox.vecBoxCenter.y	-= COLLISION_CHECK_CEILING_PREVENTION / 2.f;
		stMoveBox.vecBoxHalfSize.y	-= COLLISION_CHECK_CEILING_PREVENTION;
	}

	/* 地形との接地判定 */
	// ※ 軽量化のため現在のエリアの足場のみ確認
	// ※ エリア外の場合は足場との当たり判定を行わない
	bool bGroundHit = false;	// 地面に接地しているか
	int iAreaNo		= iCheckCurrentAreaNo();
	if (iAreaNo != -1)
	{
		for (auto& Ground : this->pDataList_Object->GetGroundList(iAreaNo))
		{
			/* 接触しているか確認 */
			if (Ground->HitCheck(stMoveBox))
			{
				// 接触している場合
				/* 接地しているとみなす */
				bGroundHit = true;

				/* 対象のオブジェクトのコリジョン情報を取得 */
				Struct_Collision::COLLISION_BOX stGroundBoxCollision;

				stGroundBoxCollision = Ground->GetBoxCollision();

				/* プレイヤーが上昇中であるか下降中であるか判定 */
				// ※ 上昇中の場合は下方向に押し出し、下降中の場合は上方向に押し出し
				if (this->fGravityVelocity > 0)
				{
					// 上昇中(下方向へ押し出し)
					vecMovePosition.y = stGroundBoxCollision.vecBoxCenter.y - stGroundBoxCollision.vecBoxHalfSize.y;
				}
				else
				{
					// 下降中(上方向へ押し出し)
					vecMovePosition.y = stGroundBoxCollision.vecBoxCenter.y + stGroundBoxCollision.vecBoxHalfSize.y;
				}
				break;
			}
		}
	}

	/* 接地しているか確認 */
	if (bGroundHit == true)
	{
		// 接地している場合
		/* 基準座標を移動後の座標に設定 */
		this->vecBasePosition = vecMovePosition;

		/* 落下速度をリセット */
 		this->fGravityVelocity = 0.f;
	}
	else
	{
		// 接地していない場合
		/* 基準座標を移動後の座標に設定 */
		this->vecBasePosition = vecMovePosition;
	}
}

// 移動処理
void Character_Player::Update_ApplyMovement()
{
	/* 移動前の座標を保存 */
	VECTOR vecPrevPosition	= this->vecBasePosition;

	/* 移動方向を取得 */
	VECTOR vecMoveDirection = VGet(0.f, 0.f, 0.f);
	// 入力から移動方向を取得
	bool bIsMoving = false;
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_W] == TRUE)
	{
		vecMoveDirection = VAdd(vecMoveDirection, VGet(0.f, 0.f, 1.f));
		bIsMoving = true;
	}
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_S] == TRUE)
	{
		vecMoveDirection = VAdd(vecMoveDirection, VGet(0.f, 0.f, -1.f));
		bIsMoving = true;
	}
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_A] == TRUE)
	{
		vecMoveDirection = VAdd(vecMoveDirection, VGet(-1.f, 0.f, 0.f));
		bIsMoving = true;
	}
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_D] == TRUE)
	{
		vecMoveDirection = VAdd(vecMoveDirection, VGet(1.f, 0.f, 0.f));
		bIsMoving = true;
	}

	// 移動していない場合は処理を抜ける
	if (!bIsMoving)
	{
		return;
	}

	/* 移動している場合の処理 */
	// 正規化→速度反映
	vecMoveDirection = VScale(VNorm(vecMoveDirection), static_cast<float>(this->iSpeed));

	/* 移動後の基準座標を算出 */
	VECTOR vecMovePosition = VAdd(vecPrevPosition, vecMoveDirection);

	/* 移動後座標のコリジョン作成 */
	// ※ 縦方向には少し余裕を持たせる(地形の凹凸に引っかからないようにするため)
	Struct_Collision::COLLISION_BOX stMoveBox;
	stMoveBox.vecBoxCenter		= VAdd(vecMovePosition, VGet(0.f, this->stBox.vecBoxHalfSize.y, 0.f));
	stMoveBox.vecBoxHalfSize	= this->stBox.vecBoxHalfSize;
	stMoveBox.vecBoxHalfSize.y += COLLISION_CHECK_FLOOR_MARGIN;

	/* 地形との接地判定 */
	// ※ 軽量化のため現在のエリアの足場のみ確認
	// ※ エリア外の場合は足場との当たり判定を行わない
	int iAreaNo = iCheckCurrentAreaNo();
	if (iAreaNo != -1)
	{
		/* 接触した全ての地形を記録 */
		std::vector<Struct_Collision::COLLISION_BOX> hitGroundBoxes;
		for (auto& Ground : this->pDataList_Object->GetGroundList(iAreaNo))
		{
			/* 接触しているか確認 */
			if (Ground->HitCheck(stMoveBox))
			{
				// 接触している場合
				/* 接触した地形のコリジョン情報を保存 */
				hitGroundBoxes.push_back(Ground->GetBoxCollision());
			}
		}

		/* 押し出しが完了するまで判定を繰り返す */
		int		iLoopCount = 0;	// ループ回数
		bool	bPushed;	// 押し出しが発生したか
		do
		{
			bPushed = false;
			for (const auto& stGroundBox : hitGroundBoxes)
			{
				/* 各軸の最小・最大座標を計算 */
				float playerMinX = vecMovePosition.x - stMoveBox.vecBoxHalfSize.x;
				float playerMaxX = vecMovePosition.x + stMoveBox.vecBoxHalfSize.x;
				float playerMinZ = vecMovePosition.z - stMoveBox.vecBoxHalfSize.z;
				float playerMaxZ = vecMovePosition.z + stMoveBox.vecBoxHalfSize.z;

				float groundMinX = stGroundBox.vecBoxCenter.x - stGroundBox.vecBoxHalfSize.x;
				float groundMaxX = stGroundBox.vecBoxCenter.x + stGroundBox.vecBoxHalfSize.x;
				float groundMinZ = stGroundBox.vecBoxCenter.z - stGroundBox.vecBoxHalfSize.z;
				float groundMaxZ = stGroundBox.vecBoxCenter.z + stGroundBox.vecBoxHalfSize.z;

				// X軸の重なり量
				float overlapX = std::min(playerMaxX, groundMaxX) - std::max(playerMinX, groundMinX);
				// Z軸の重なり量
				float overlapZ = std::min(playerMaxZ, groundMaxZ) - std::max(playerMinZ, groundMinZ);

				// 接触していなければスキップ
				if (overlapX <= 0.f || overlapZ <= 0.f) continue;

				// 最小の重なり方向に押し出し
				if (overlapX < overlapZ)
				{
					// X軸方向に押し出し
					if (vecPrevPosition.x < stGroundBox.vecBoxCenter.x)
					{
						vecMovePosition.x = groundMinX - stMoveBox.vecBoxHalfSize.x;
					}
					else
					{
						vecMovePosition.x = groundMaxX + stMoveBox.vecBoxHalfSize.x;
					}
				}
				else
				{
					// Z軸方向に押し出し
					if (vecPrevPosition.z < stGroundBox.vecBoxCenter.z)
					{
						vecMovePosition.z = groundMinZ - stMoveBox.vecBoxHalfSize.z;
					}
					else
					{
						vecMovePosition.z = groundMaxZ + stMoveBox.vecBoxHalfSize.z;
					}
				}
				// 押し出しが発生したので再判定
				stMoveBox.vecBoxCenter = VAdd(vecMovePosition, VGet(0.f, this->stBox.vecBoxHalfSize.y, 0.f));
				bPushed = true;
			}

			/* 無限ループ防止処理 */
			iLoopCount++;
			if (iLoopCount > COLLISION_PUSH_MAX_LOOP)
			{
				// 最大ループ回数を超えた場合は強制終了
				/* 元の座標に戻す */
				vecMovePosition = vecPrevPosition;
				break;
			}
		} while (bPushed);
	}

	// 押し出し後の座標を基準座標に反映
	this->vecBasePosition = vecMovePosition;
}