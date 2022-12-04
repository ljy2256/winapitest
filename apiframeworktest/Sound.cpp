#include "pch.h"
#include "Sound.h"
#include "PathMgr.h"
Sound::Sound()
{
}

Sound::~Sound()
{
	//map<wstring, PSOUNDINFO>::iterator iter;
	//for (iter = m_mapSod.begin(); iter != m_mapSod.end(); ++iter)
	//{
	//	iter->second->pSound->release();
	//  safe_delete(iter->second);
	//}
	Safe_Delete_Map(m_mapSod);
	m_pSystem->close();
	m_pSystem->release();
}

bool Sound::Init()
{
	// fmod system 생성
	FMOD::System_Create(&m_pSystem);
//	FMOD_System_Create(&m_pSystem, ? );
	m_pSystem->init(10, FMOD_INIT_NORMAL, 0);
	return true;
}

bool Sound::LoadSound(const wstring& _strKey, bool _bLoop, char* _pFileName
					,const wstring& _strPathKey)
{
	if(FindSound(_strKey))
		return false;
	const wchar_t* pPath = PathMgr::GetInst()->GetRsrcPath(_strPathKey);
	string strPath;
	if (pPath)
		strPath = pPath;
	strPath += _pFileName;

	FMOD_MODE eMode = FMOD_LOOP_NORMAL;
	if (!_bLoop)
		eMode = FMOD_DEFAULT;

	PSOUNDINFO pSound = new SOUNDINFO;

	pSound->bLoop = _bLoop;

	m_pSystem->createSound(strPath.c_str(), eMode, NULL, &pSound->pSound);

	m_mapSod.insert({ _strKey,pSound });
	
	return true;
}

bool Sound::Play(const wstring& _strKey)
{
	return false;
}

bool Sound::Stop(SOUND_CHANNEL _eChannel)
{
	return false;
}

bool Sound::Volume(SOUND_CHANNEL _eChannel, float _fVol)
{
	return false;
}

PSOUNDINFO Sound::FindSound(const wstring& _strKey)
{
	return PSOUNDINFO();
}


//
//
//Sound::Sound()
//	: m_pSoundBuffer(nullptr)
//	, m_tBuffInfo{}
//	, m_iVolume(0)
//{
//}
//
//Sound::~Sound()
//{
//	if (nullptr != m_pSoundBuffer)
//		m_pSoundBuffer->Release();
//}
//
//int Sound::Load(const wstring& _strPath)
//{
//	if (nullptr == SoundMgr::GetInst()->GetSoundDevice())
//		assert(nullptr); // 사운드 객체 생성되지 않음
//
//	// 확장자 이름 구별하기
//	wchar_t szName[10] = { 0 };
//	_wsplitpath_s(_strPath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szName, 10);
//	
//	if (!wcscmp(szName, L".wav")) // wav 파일 로드
//	{
//		if (LoadWaveSound(_strPath) == false)
//		{
//			assert(nullptr);
//		}
//	}
//	else
//	{
//		assert(nullptr);
//	}
//	return S_OK;
//}
//
//void Sound::Play(bool _bLoop)
//{
//	// Play 함수의 1번째 2번째 인자는 0 으로 이미 예약되어있다.
//	// 3번째 변수는 사운드를 반복재생 할 것인지 아닌지를 결정한다.
//	m_pSoundBuffer->SetCurrentPosition(0);
//
//	if (_bLoop)
//		m_pSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
//	else
//		m_pSoundBuffer->Play(0, 0, 0);
//}
//
//void Sound::PlayToBGM(bool _bLoop)
//{
//	SoundMgr::GetInst()->RegisterToBGM(this);
//
//	// Play 함수의 1번째 2번째 인자는 0 으로 이미 예약되어있다.
//	// 3번째 변수는 사운드를 반복재생 할 것인지 아닌지를 결정한다.
//	if (_bLoop)
//		m_pSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
//	else
//		m_pSoundBuffer->Play(0, 0, 0);
//}
//
//void Sound::Stop(bool _bReset)
//{
//	m_pSoundBuffer->Stop();
//
//	if (_bReset)
//		m_pSoundBuffer->SetCurrentPosition(0);
//}
//
//void Sound::SetVolume(float _fVolume)
//{
//	m_iVolume = GetDecibel(_fVolume);
//	m_pSoundBuffer->SetVolume(m_iVolume);
//}
//
//void Sound::SetPosition(float _fPosition)
//{
//	Stop(true);
//
//	DWORD dwBytes = (DWORD)((_fPosition / 100.f) * (float)m_tBuffInfo.dwBufferBytes);
//	m_pSoundBuffer->SetCurrentPosition(dwBytes);
//
//	Play();
//}
//
//bool Sound::LoadWaveSound(const wstring& _strPath)
//{
//	HMMIO	hFile; // File Handle
//
//	wstring strFilePath = _strPath;
//
//	//CreateFile
//	hFile = mmioOpen((wchar_t*)strFilePath.c_str(), NULL, MMIO_READ);//wave파일을 연다.
//
//	if (nullptr == hFile)
//	{
//		MessageBox(NULL, L"사운드 리소스 경로에 파일 없음", L"사운드 로딩 실패", MB_OK);
//		return false;
//	}
//
//	//Chunk 청크 구조체, 문자열로 색인을 인식해서 WaveFormat 및 버퍼선언정보를 읽어온다.
//	MMCKINFO	pParent;
//	memset(&pParent, 0, sizeof(pParent));
//	pParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
//	mmioDescend(hFile, &pParent, NULL, MMIO_FINDRIFF);
//
//	MMCKINFO	pChild;
//	memset(&pChild, 0, sizeof(pChild));
//	pChild.ckid = mmioFOURCC('f', 'm', 't', ' ');
//	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);
//
//	WAVEFORMATEX	wft;
//	memset(&wft, 0, sizeof(wft));
//	mmioRead(hFile, (char*)&wft, sizeof(wft));
//
//	mmioAscend(hFile, &pChild, 0);
//	pChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
//	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);
//
//
//
//	memset(&m_tBuffInfo, 0, sizeof(DSBUFFERDESC));
//	m_tBuffInfo.dwBufferBytes = pChild.cksize;
//	m_tBuffInfo.dwSize = sizeof(DSBUFFERDESC);
//	m_tBuffInfo.dwFlags = DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLVOLUME;
//	m_tBuffInfo.lpwfxFormat = &wft;
//
//	if (FAILED(SoundMgr::GetInst()->GetSoundDevice()->CreateSoundBuffer(&m_tBuffInfo, &m_pSoundBuffer, NULL)))
//	{
//		MessageBox(NULL, L"사운드버퍼생성실패", L"", MB_OK);
//		return false;
//	}
//
//	void* pWrite1 = NULL;
//	void* pWrite2 = NULL;
//	DWORD dwlength1, dwlength2;
//
//	m_pSoundBuffer->Lock(0, pChild.cksize, &pWrite1, &dwlength1
//		, &pWrite2, &dwlength2, 0L);
//
//	if (pWrite1 != nullptr)
//		mmioRead(hFile, (char*)pWrite1, dwlength1);
//	if (pWrite2 != nullptr)
//		mmioRead(hFile, (char*)pWrite2, dwlength2);
//
//	m_pSoundBuffer->Unlock(pWrite1, dwlength1, pWrite2, dwlength2);
//
//	mmioClose(hFile, 0);
//
//	// 초기 음량 절반으로 설정
//	SetVolume(50.f);
//
//	return true;
//}
//
//int Sound::GetDecibel(float _fVolume)
//{
//	if (_fVolume > 100.f)
//		_fVolume = 100.f;
//	else if (_fVolume <= 0.f)
//		_fVolume = 0.00001f;
//
//	// 1 ~ 100 사이값을 데시벨 단위로 변경
//	int iVolume = (LONG)(-2000.0 * log10(100.f / _fVolume));
//
//	if (iVolume < -10000)
//		iVolume = -10000;
//	return  iVolume;
//}
//
