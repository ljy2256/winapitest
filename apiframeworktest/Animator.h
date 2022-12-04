#pragma once
class Object;
class Animation;
class Image;
class Animator
{
private:
	Object* m_pOwner;                  // animation ���� ������Ʈ
	map<wstring, Animation*> m_mapAni; // ��� animation
	Animation*				m_pCurAni;  // ���� ������� animation
	bool					m_bRepeat;
public:
	Animator();
	~Animator();
	friend class Object;
public:
	Object* GetObj() {	return m_pOwner; }
public:
	void CreateAnimation(const wstring _strName, Image* _pImage, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _iFrameCount, float _fDuration);
	Animation* FindAnimation(const wstring _strName);
	void Play(const wstring _strName, bool _bRepeat);
	void Update();
	void Render(HDC _dc);
};

