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
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_llPrevCount);

	// �ʴ� ī��Ʈ Ƚ��(1000��)
	QueryPerformanceFrequency(&m_llFrequency);
}

void TimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);
	// ���� �������� ī���ð�, ���� ������ ī���� ���� ���̸� ���Ѵ�.
	//���� �����Ӱ� ���� ī��Ʈ ���� �̿��ؼ� ��ŸŸ�� ���ϱ�
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	// ���� ī��Ʈ ���� ���簪���� ����(�������� ����� ���ؼ�)
	m_llPrevCount = m_llCurCount; //ī��Ʈ �� ����

	//= 1. / m_dDT;
#ifdef _DEBUG
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.);
#endif
}
void TimeMgr::Render()
{
	++m_iCallCount; //ȣ��Ƚ�� ����

	m_dAcc += m_dDT; //DT(��ŸŸ��) ����
	if (m_dAcc >= 1.) //1�ʰ� �������� fps ���
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
