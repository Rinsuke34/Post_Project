/* データリスト"サウンド管理"クラスの宣言 */

#pragma once

/* 使用する要素のインクルード */
// 共通定義
#include "AppFrame.h"

// データリスト"サウンド管理"クラス
class DataList_Sound : public DataList_Base
{
	public:
		DataList_Sound();			// コンストラクタ
		virtual ~DataList_Sound();	// デストラクタ

		/* 関数 */
		// BGM関係
		void BGM_Play(std::string BgmName);	// BGM再生
		void BGM_Stop();					// BGM停止
		void BGM_VolumeChange(int iVolume);	// BGMの音量設定

		// SE関係
		void SE_Play(std::string SeName);					// SE再生(通常)
		void SE_Play(std::string SeName, VECTOR vecSePos);	// SE再生(3Dサウンド)
		void SE_AllStop();									// 全てのSE停止
		void SE_VolumeChange(int iVolume);					// SEの音量設定

	private:
		/* 変数 */
		// BGM関係
		// ※ BGMは再生するタイミングで読み込む
		int iSoundHandle_BGM;	// BGMのサウンドハンドル
		int iVolume_BGM;		// BGMのボリューム

		// SE関係
		std::map<std::string, int> SoundHandleList_SE;		// SEのサウンドハンドルリスト
		std::map<std::string, int> SoundHandleLISE_SE_3D;	// 3DサウンドのSEのサウンドハンドルリスト
		int iVolume_SE;										// SEのボリューム
};
