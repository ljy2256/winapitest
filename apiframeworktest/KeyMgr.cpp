#include "pch.h"
#include "KeyMgr.h"
#include "Core.h"
int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',
	VK_MENU, VK_LSHIFT, VK_CONTROL, VK_SPACE, VK_RETURN, VK_ESCAPE,
};
KeyMgr::KeyMgr()
{
}

KeyMgr::~KeyMgr()
{
}

void KeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE,false });
	}
}

void KeyMgr::Update()
{
	// 윈도우 포커싱 알아내기
//	HWND hMainWnd = Core::GetInst()->GetWndHandle();
	HWND hWnd = GetFocus();
//	m_mapKey.0
	if(nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			// 키가 눌려있다.
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				// 이전 프레임 눌렸냐?
				if (m_vecKey[i].bPrevCheck)
				{
					// 이전에도 눌려있었다.
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					//이전에 눌려있지 않았다.
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevCheck = true;
			}
			// 키가 안눌려 있다.
			else
			{
				if (m_vecKey[i].bPrevCheck)
				{
					//이전에 눌려있었다.
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					//이전에도 안눌려있었다.
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrevCheck = false;
			}
		}
	}
	// 윈도우 포커싱 해제 상태
	else
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			m_vecKey[i].bPrevCheck = false;
			if (m_vecKey[i].eState == KEY_STATE::TAP || m_vecKey[i].eState == KEY_STATE::HOLD)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (m_vecKey[i].eState == KEY_STATE::AWAY)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}
