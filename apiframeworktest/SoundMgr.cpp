#include "pch.h"
#include "SoundMgr.h"
#include "PathMgr.h"
//#include<locale>
//#include<codecvt>
#include "KeyMgr.h"
SoundMgr::SoundMgr()
	:m_pSystem(nullptr)
{
}

SoundMgr::~SoundMgr()
{
	Safe_Delete_Map(m_mapSod);
	// 다 쓰고 난 후에는 반드시 close, release해야함.
	m_pSystem->close();
	m_pSystem->release();
}

void SoundMgr::Init()
{
	FMOD::System_Create(&m_pSystem);

	if(m_pSystem!=nullptr)
		m_pSystem->init(10, FMOD_INIT_NORMAL, NULL);
}

//bool SoundMgr::LoadSound(const wstring& _strKey, bool _bLoop, char* _pFileName, const wstring& _strPathKey)
//bool SoundMgr::LoadSound(const wstring& _strKey, bool _bLoop, const char* _pFileName, const wstring& _strRelativePath)
void SoundMgr::LoadSound(const wstring& _strKey, bool _bLoop, const wstring& _strRelativePath)
{
	// 찾으면 생성x
	if (FindSound(_strKey))
		return;

	//wstring string_to_convert;
	//using convert_type = std::codecvt_utf8<wchar_t>;
	//wstring_convert<convert_type, wchar_t> converter;

	//
	wstring strFilePath = PathMgr::GetInst()->GetRsrcPath();
	strFilePath += _strRelativePath;
	//string str = converter.to_bytes(string_to_convert);

	string str;
	size_t size;
	str.resize(strFilePath.length());
	wcstombs_s(&size, &str[0], str.size() + 1, strFilePath.c_str(), strFilePath.size());
	//string str = "";
	//str.assign(strFilePath.begin(),strFilePath.end());
	//str += _pFileName;
	//const wchar_t* pPath = PathMgr::GetInst()->GetRsrcPath(_strPathKey);
	//string strPath;
	//if (pPath)
	//	strPath = pPath;
	//strPath += _pFileName;

	// 루프 할지 말지 결정
	FMOD_MODE eMode = FMOD_LOOP_NORMAL; // 반복 출력
	if (!_bLoop)
		eMode = FMOD_DEFAULT; // 사운드 1번만 출력

	PSOUNDINFO ptSound = new SOUNDINFO;

	ptSound->bLoop = _bLoop;

						// 경로,				모드,   안씀,	사운드
//	m_pSystem->createSound(strPath.c_str(), eMode, NULL, &pSound->pSound);
	// 사운드 객체를 만드는건 systemdla. wav, mp3 파일로부터 sound 생성함.
	// FMOD_LOOP_OFF: 무한재생 끔, FMOD_LOOP_NORMAL: 무한 재생 켬
	m_pSystem->createSound(str.c_str(), eMode, NULL, &ptSound->pSound);

	m_mapSod.insert({ _strKey,ptSound });
}

void SoundMgr::Play(const wstring& _strKey)
{
	PSOUNDINFO ptSound = FindSound(_strKey);

	if (!ptSound)
		return;
	
	m_pSystem->update();

	SOUND_CHANNEL eChannel = SOUND_CHANNEL::SC_BGM;

	if (!ptSound->bLoop)
		eChannel = SOUND_CHANNEL::SC_EFFECT;

	// 정리
	// &channel: 어떤 채널을 통해서 재생되는지 마지막 파라미터로 해당 채널 포인터 넘기기
	// 한 채널에서 여러 개 사운드 재생 가능
	// ★ 단 이 함수는 딱 한번만 실행되기 때문에 이 함수가 한 파일을 끝까지 재생시키려면
	// 무한 루프를 넣어서 시스템을 계속해서 업데이트 시켜야함. ex. while(true) 안에서..\

	m_pSystem->playSound(ptSound->pSound, NULL, false, &m_pChannel[(UINT)eChannel]);
}

void SoundMgr::Pause(SOUND_CHANNEL _eChannel, bool _p)
{
	m_pChannel[(UINT)_eChannel]->setPaused(_p);
}
void SoundMgr::Stop(SOUND_CHANNEL _eChannel)
{
	m_pChannel[(UINT)_eChannel]->stop();
}

void SoundMgr::Volume(SOUND_CHANNEL _eChannel, float _fVol)
{
	m_pChannel[(UINT)_eChannel]->setVolume(_fVol);
}

PSOUNDINFO SoundMgr::FindSound(const wstring& _strKey)
{
	map<wstring, PSOUNDINFO>::iterator iter = m_mapSod.find(_strKey);

	if (iter == m_mapSod.end())
		return nullptr;
	return iter->second;
}


//#include "Core.h"
//SoundMgr::SoundMgr()
//	: m_pSound(nullptr)
//	, m_pBGM(nullptr)
//{
//}
//
//SoundMgr::~SoundMgr()
//{
//	
//}
//
//int SoundMgr::Init(void)
//{
//	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
//	{
//		MessageBox(NULL, L"Sound device 생성 실패", L"ERROR", MB_OK);
//		return false;
//	}
//	HWND hWnd = Core::GetInst()->GetWndHandle();
//	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) //Flag값 정리
//	{
//		MessageBox(NULL, L"Sound device 협조레벨 설정", L"ERROR", MB_OK);
//		return false;
//	}
//}
//
//void SoundMgr::RegisterToBGM(Sound* _pSound)
//{
//	if (m_pBGM != nullptr)
//		m_pBGM->Stop(true);
//	m_pBGM = _pSound;
//}
