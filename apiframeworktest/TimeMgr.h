#pragma once
class TimeMgr
{
public:
	SINGLE(TimeMgr);
private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;
	
	double		  m_dDT; // ������ ������ �ð� ��
	double		  m_dAcc; // 1�� üũ�� ���� ���� �ð�
	UINT	      m_iCallCount; // �Լ� ȣ�� Ƚ�� üũ
	UINT		  m_iFPS;		// �ʴ� ȣ�� Ƚ��
	// FPS 
	// 1 �����Ӵ� �ð�(delta time)
private:
	TimeMgr();
	~TimeMgr();
public:
	void Init();
	void Update();
	void Render();
public:
	double GetDT() { return m_dDT; }
	float  GetfDT() { return (float)m_dDT; }
};

