#pragma once
#include "define.h"
#include <map>
// 1. 프레임 동기화
// 동일 프레임 내에서 같은 키에 대해, 동일한 이벤트를 가져간다.

// 2. 키 입력 이벤트 처리

// 구체적인 키 상태에 대해 정의가 안되어있다.
struct tKeyInfo
{
//	KEY			eKey;  인덱스가 곧 키 값임.
	KEY_STATE	eState; // 키의 상태값
	bool		bPrevCheck; // 이전 프레임에서 눌렸는지 여부
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

