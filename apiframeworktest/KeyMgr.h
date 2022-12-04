#pragma once
#include "define.h"
#include <map>
// 1. ������ ����ȭ
// ���� ������ ������ ���� Ű�� ����, ������ �̺�Ʈ�� ��������.

// 2. Ű �Է� �̺�Ʈ ó��

// ��ü���� Ű ���¿� ���� ���ǰ� �ȵǾ��ִ�.
struct tKeyInfo
{
//	KEY			eKey;  �ε����� �� Ű ����.
	KEY_STATE	eState; // Ű�� ���°�
	bool		bPrevCheck; // ���� �����ӿ��� ���ȴ��� ����
};
class KeyMgr
{
public:
	SINGLE(KeyMgr);
private:
	KeyMgr();
	~KeyMgr();
private:
	vector<tKeyInfo> m_vecKey;
	map<int, bool> m_mapKey;
public:
	void Init();
	void Update();
	KEY_STATE	GetKey(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }
};

