#include "pch.h"
#include "TimeMgr.h"
#include "Core.h"
TimeMgr::TimeMgr()
	:m_llCurCount{}
	, m_llFrequency{}
	, m_llPrevCount{}
	, m_dDT(0.)
	, m_iCallCount(0)
{
}

TimeMgr::~TimeMgr()
{
}

void TimeMgr::Init() 
{
	// 현재 카운트
	QueryPerformanceCounter(&m_llPrevCount);

	// 초당 카운트 횟수(1000만)
	QueryPerformanceFrequency(&m_llFrequency);
}

void TimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);
	// 이전 프레임의 카운팅과, 현재 프레임 카운팅 값의 차이를 구한다.
	//이전 프레임과 현재 카운트 값을 이용해서 델타타임 구하기
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	// 이전 카운트 값을 현재값으로 갱신(다음번에 계산을 위해서)
	m_llPrevCount = m_llCurCount; //카운트 값 갱신

	//= 1. / m_dDT;
#ifdef _DEBUG
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.);
#endif
}
void TimeMgr::Render()
{
	++m_iCallCount; //호출횟수 누적

	m_dAcc += m_dDT; //DT(델타타임) 누적
	if (m_dAcc >= 1.) //1초가 지났나면 fps 계산
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;
		static wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d,  DT: %lf", m_iFPS, m_dDT);
		//		wsprintf(szBuffer, L"FPS : %d,  DT: %lf", m_iFPS, m_dDT);
		SetWindowText(Core::GetInst()->GetWndHandle(), szBuffer);
	}

}
