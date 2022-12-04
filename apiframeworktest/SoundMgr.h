#pragma once
#include "fmod.hpp"
#pragma comment(lib, "fmod_vc")
//#pragma comment(lib, "fmod64_vc")
enum class SOUND_CHANNEL
{
	SC_BGM, SC_EFFECT, SC_END
};
typedef struct tSoundInfo
{
	FMOD::Sound* pSound;
	bool bLoop;
}SOUNDINFO, * PSOUNDINFO;

class SoundMgr
{
public:
	SINGLE(SoundMgr);
private:
	SoundMgr();
	~SoundMgr();
private:
	FMOD::System* m_pSystem;
	map<wstring, PSOUNDINFO> m_mapSod;
	FMOD::Channel* m_pChannel[(UINT)SOUND_CHANNEL::SC_END];

public:
	void Init();
//	bool LoadSound(const wstring& _strKey, bool _bLoop, const char* _pFileName, const wstring& _strRelativePath);
	void LoadSound(const wstring& _strKey, bool _bLoop, const wstring& _strRelativePath);
	void Play(const wstring& _strKey);
	void Stop(SOUND_CHANNEL _eChannel);
	void Volume(SOUND_CHANNEL _eChannel, float _fVol);
	void Pause(SOUND_CHANNEL _eChannel, bool _p);
private:
	PSOUNDINFO FindSound(const wstring& _strKey);
};


//// sound 용도 - 헤더 순서 중요
//#include <mmsystem.h>
//#include <dsound.h>
//#include <dinput.h>
//
//// 코드
//#pragma comment(lib, "winmm.lib")
//#pragma comment(lib, "dsound.lib")
//class Sound;
//class SoundMgr
//{
//public:
//	SINGLE(SoundMgr);
//private:
//	SoundMgr();
//	~SoundMgr();
//private:
//	LPDIRECTSOUND8	m_pSound;	// 사운드카드 대표 객체
//	Sound* m_pBGM;		// 현재 지정된 BGM Sound
//
//public:
//	int Init(void);
//	LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
//	void RegisterToBGM(Sound* _pSound);
//};
//
