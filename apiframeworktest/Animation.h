#pragma once
class Animator;
class Image;

struct tAniFrm
{
	Vec2 vLT;
	Vec2 vSlice; 
	Vec2 vOffset;
	float fDuration;
};

class Animation
{
private:
	wstring m_strName;
	Animator* m_pAnimator;
	Image*    m_pImage; // animation�� ����ϴ� �ؽ�ó
	vector<tAniFrm> m_vecFrm; // ��� ������ ����
	int				m_iCurFrm; // ���� ������
	float			m_fAccTime; //�ð� ����
	bool			m_bFinish;
private:
	void SetName(const wstring& _strName) { m_strName = _strName; }
public:
	const wstring& GetName() { return m_strName; }
	bool  IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrame)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrame;
		m_fAccTime = 0.f;
	}
	tAniFrm& GetFrame(int _idx)
	{
		return m_vecFrm[_idx];
	}
	size_t GetMaxFrame() { return m_vecFrm.size(); }
public:
	Animation();
	~Animation();
	friend class Animator;
public:
	void Update();
	void Render(HDC _dc);
	void Create(Image* _pImage, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _iFrameCount, float _fDuration);
};

