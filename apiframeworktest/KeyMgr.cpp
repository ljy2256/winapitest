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
	// ������ ��Ŀ�� �˾Ƴ���
//	HWND hMainWnd = Core::GetInst()->GetWndHandle();
	HWND hWnd = GetFocus();
//	m_mapKey.0
	if(nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			// Ű�� �����ִ�.
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				// ���� ������ ���ȳ�?
				if (m_vecKey[i].bPrevCheck)
				{
					// �������� �����־���.
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					//������ �������� �ʾҴ�.
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevCheck = true;
			}
			// Ű�� �ȴ��� �ִ�.
			else
			{
				if (m_vecKey[i].bPrevCheck)
				{
					//������ �����־���.
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					//�������� �ȴ����־���.
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrevCheck = false;
			}
		}
	}
	// ������ ��Ŀ�� ���� ����
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
