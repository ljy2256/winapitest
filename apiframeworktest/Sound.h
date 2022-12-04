#pragma once
#include "Res.h"
#include "fmod.hpp"
//using namespace FMOD;
enum class SOUND_CHANNEL
{
	SC_BGM, SC_EFFECT, SC_MAX
};

typedef struct tSoundInfo
{
	FMOD::Sound* pSound;
	bool bLoop;
}SOUNDINFO, *PSOUNDINFO;

class Sound : public Res
{
	// 싱글톤?
public:
	SINGLE(Sound);
private:
	Sound();
	~Sound();
private:
	FMOD::System* m_pSystem; // 이 시스템으로 사운드 로드함
	FMOD::Channel* m_pChannel;
	map<wstring, PSOUNDINFO> m_mapSod;

public:
	bool Init();
	bool LoadSound(const wstring& _strKey, bool _bLoop, char* _pFileName, const wstring& _strPathKey);
	bool Play(const wstring& _strKey);
	bool Stop(SOUND_CHANNEL _eChannel);
	bool Volume(SOUND_CHANNEL _eChannel, float _fVol);
private:
	PSOUNDINFO FindSound(const wstring& _strKey);

};
//#pragma once
//#include "Res.h"
//#include "SoundMgr.h"
//class Sound :
//    public Res
//{
//private:
//	LPDIRECTSOUNDBUFFER		m_pSoundBuffer;
//	DSBUFFERDESC			m_tBuffInfo;
//	int						m_iVolume;
//
//public:
//	int Load(const wstring& _strPath);
//
//	// 일반 재생
//	void Play(bool _bLoop = false);
//
//	// BGM 으로 재생
//	void PlayToBGM(bool _bLoop = false);
//
//	void Stop(bool _bReset = false);
//
//	// 볼륨 범위 (0 ~ 100)
//	void SetVolume(float _fVolume);
//
//	// 음악파일 위치 조정
//	void SetPosition(float _fPosition); // 0 ~ 100 사이
//
//private:
//	bool LoadWaveSound(const wstring& _strPath);
//	int GetDecibel(float _fVolume);
//
//
//
//public:
//	Sound();
//	virtual ~Sound();
//};
//
