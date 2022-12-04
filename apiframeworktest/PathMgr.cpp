#include "pch.h"
#include "PathMgr.h"
#include "Core.h"
PathMgr::PathMgr()
	:m_szRsrcPath{}
{
}

PathMgr::~PathMgr() 
{
}

void PathMgr::Init()
{
	GetCurrentDirectory(255, m_szRsrcPath);
	
	int Length = wcslen(m_szRsrcPath);

	// 상위 폴더로
	for (int i = Length - 1; i >= 0; i--)
	{
		if (m_szRsrcPath[i] == '\\')
		{
			m_szRsrcPath[i] = '\0';
			break;
		}
	}

	// 문자열 이어붙여줘.
	wcscat_s(m_szRsrcPath, 255, L"\\bin\\Rsrc\\");
	// + bin\\Rsrc\\

	// aaaa\\bbbb\0cccc

	SetWindowText(Core::GetInst()->GetWndHandle(), m_szRsrcPath);
}
