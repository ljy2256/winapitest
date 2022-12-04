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
	// �� ���� �� �Ŀ��� �ݵ�� close, release�ؾ���.
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
	// ã���� ����x
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

	// ���� ���� ���� ����
	FMOD_MODE eMode = FMOD_LOOP_NORMAL; // �ݺ� ���
	if (!_bLoop)
		eMode = FMOD_DEFAULT; // ���� 1���� ���

	PSOUNDINFO ptSound = new SOUNDINFO;

	ptSound->bLoop = _bLoop;

						// ���,				���,   �Ⱦ�,	����
//	m_pSystem->createSound(strPath.c_str(), eMode, NULL, &pSound->pSound);
	// ���� ��ü�� ����°� systemdla. wav, mp3 ���Ϸκ��� sound ������.
	// FMOD_LOOP_OFF: ������� ��, FMOD_LOOP_NORMAL: ���� ��� ��
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

	// ����
	// &channel: � ä���� ���ؼ� ����Ǵ��� ������ �Ķ���ͷ� �ش� ä�� ������ �ѱ��
	// �� ä�ο��� ���� �� ���� ��� ����
	// �� �� �� �Լ��� �� �ѹ��� ����Ǳ� ������ �� �Լ��� �� ������ ������ �����Ű����
	// ���� ������ �־ �ý����� ����ؼ� ������Ʈ ���Ѿ���. ex. while(true) �ȿ���..\

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
//		MessageBox(NULL, L"Sound device ���� ����", L"ERROR", MB_OK);
//		return false;
//	}
//	HWND hWnd = Core::GetInst()->GetWndHandle();
//	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) //Flag�� ����
//	{
//		MessageBox(NULL, L"Sound device �������� ����", L"ERROR", MB_OK);
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
