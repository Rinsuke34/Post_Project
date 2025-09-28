/* データリスト"サウンド管理"クラスの定義 */

#pragma once

/* 使用する要素のインクルード */
// ヘッダファイル
#include "DataList_Sound.h"
// 共通定義
#include "ConstantDefine.h"

// コンストラクタ
DataList_Sound::DataList_Sound() : DataList_Base("DataList_Sound")
{
	/* 初期化 */
	this->iSoundHandle_BGM	= FALSE;
	this->iVolume_BGM		= 0;
	this->iVolume_SE		= 128;
}

// デストラクタ
DataList_Sound::~DataList_Sound()
{
	/* BGMのサウンドハンドルを削除 */
	DeleteSoundMem(this->iSoundHandle_BGM);

	/* SEのサウンドハンドルを削除 */
	for (const auto& pair : SoundHandleList_SE)
	{
		/* サウンドハンドルを削除 */
		DeleteSoundMem(pair.second);
	}
	SoundHandleList_SE.clear();
	/* 3DサウンドのSEのサウンドハンドルを削除 */
	for (const auto& pair : SoundHandleLISE_SE_3D)
	{
		/* サウンドハンドルを削除 */
		DeleteSoundMem(pair.second);
	}
	SoundHandleLISE_SE_3D.clear();
}

/* BGM系 */
// BGM再生
void DataList_Sound::BGM_Play(std::string BgmName)
{
	// 引数
	// BgmName	: BGM名

	/* 現在流れているBGMを停止 */
	BGM_Stop();

	/* BGMのファイルパスを取得 */
	std::string FileName = "resource/SoundData/BGM/" + BgmName + ".ogg";

	/* BGMを読み込み */
	this->iSoundHandle_BGM = LoadSoundMem(FileName.c_str());

	/* BGMの音量を設定 */
	ChangeVolumeSoundMem(this->iVolume_BGM, this->iSoundHandle_BGM);

	/* BGMを再生 */
	PlaySoundMem(this->iSoundHandle_BGM, DX_PLAYTYPE_LOOP);
}

// BGM停止
void DataList_Sound::BGM_Stop()
{
	/* BGMを停止 */
	if (this->iSoundHandle_BGM != FALSE)
	{
		StopSoundMem(this->iSoundHandle_BGM);
		DeleteSoundMem(this->iSoundHandle_BGM);
		this->iSoundHandle_BGM = FALSE;
	}
}

// BGMの音量設定
void DataList_Sound::BGM_VolumeChange(int iVolume)
{
	// 引数
	// iVolume	: 音量(0～255)

	/* BGMの音量を設定 */
	this->iVolume_BGM = iVolume;
	ChangeVolumeSoundMem(this->iVolume_BGM, this->iSoundHandle_BGM);
}

/* SE系 */
// SE再生(通常)
void DataList_Sound::SE_Play(std::string SeName)
{
	// 引数
	// SeName	: SE名

	/* 使用するサウンドがすでに読み込まれているか確認 */
	int iSoundHandle = 0;
	auto it = SoundHandleList_SE.find(SeName);
	if (it != SoundHandleList_SE.end())
	{
		// 読み込まれている場合
		iSoundHandle = it->second;
	}
	else
	{
		// 読み込まれていない場合
		/* SEのファイルパスを取得 */
		std::string FileName = "resource/SoundData/SE/" + SeName + ".mp3";
		/* SEを読み込み */
		iSoundHandle = LoadSoundMem(FileName.c_str());
		/* リストに追加 */
		this->SoundHandleList_SE[SeName] = iSoundHandle;
	}

	/* SEの音量を設定 */
	ChangeVolumeSoundMem(this->iVolume_SE, iSoundHandle);

	/* SEを再生 */
	PlaySoundMem(iSoundHandle, DX_PLAYTYPE_BACK);
}

// SE再生(3Dサウンド)
void DataList_Sound::SE_Play(std::string SeName, VECTOR vecSePos)
{
	// 引数
	// SeName	: SE名
	// vecSePos	: SEの位置

	/* 使用するサウンドがすでに読み込まれているか確認 */
	int iSoundHandle = 0;
	auto it = SoundHandleLISE_SE_3D.find(SeName);
	if (it != SoundHandleLISE_SE_3D.end())
	{
		// 読み込まれている場合
		iSoundHandle = it->second;
	}
	else
	{
		// 読み込まれていない場合
		/* SEのファイルパスを取得 */
		std::string FileName = "resource/SoundData/SE/" + SeName + ".mp3";
		/* SEを読み込み */
		iSoundHandle = LoadSoundMem(FileName.c_str());
		/* リストに追加 */
		this->SoundHandleLISE_SE_3D[SeName] = iSoundHandle;
	}

	/* SEの音量を設定 */
	ChangeVolumeSoundMem(this->iVolume_SE, iSoundHandle);

	/* 3Dサウンドの位置を設定 */
	SetNextPlay3DPositionSoundMem(vecSePos, iSoundHandle);

	/* 3Dサウンドの聞こえる範囲を設定 */
	SetNextPlay3DRadiusSoundMem(VOLUME_SE_RADIUS, iSoundHandle);

	/* SEを再生 */
	PlaySoundMem(iSoundHandle, DX_PLAYTYPE_BACK);
}

// 全てのSE停止
void DataList_Sound::SE_AllStop()
{
	/* SEを停止 */
	for (const auto& pair : SoundHandleList_SE)
	{
		/* サウンドハンドルを停止 */
		StopSoundMem(pair.second);
	}
	/* 3DサウンドのSEを停止 */
	for (const auto& pair : SoundHandleLISE_SE_3D)
	{
		/* サウンドハンドルを停止 */
		StopSoundMem(pair.second);
	}
}

// SEの音量設定
void DataList_Sound::SE_VolumeChange(int iVolume)
{
	// 引数
	// iVolume	: 音量(0～255)
	/* SEの音量を設定 */
	this->iVolume_SE = iVolume;

	/* 読み込まれているSEの音量を変更 */
	for (const auto& pair : SoundHandleList_SE)
	{
		ChangeVolumeSoundMem(this->iVolume_SE, pair.second);
	}
	for (const auto& pair : SoundHandleLISE_SE_3D)
	{
		ChangeVolumeSoundMem(this->iVolume_SE, pair.second);
	}
}
