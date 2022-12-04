#pragma once
class PathMgr
{
public:
	SINGLE(PathMgr);
private:
	wchar_t		m_szRsrcPath[255];
private:
	PathMgr();
	~PathMgr();
public:
	void Init();
	const wchar_t* GetRsrcPath() { return m_szRsrcPath; }
};

