#pragma once
class Res
{
private:
	wstring	m_strKey; // ���ҽ� Ű 
	wstring m_strRelativeRath; // ���ҽ� �����
public:
	Res();
	virtual ~Res();
public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void SetRelativePath(const wstring _strPath) { m_strRelativeRath = _strPath; }
	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativeRath; }
};

