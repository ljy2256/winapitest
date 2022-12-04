#pragma once
class Collider;

union COLLIDER_ID
{
	struct
	{
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};

class CollisionMgr
{
private:
	UINT m_arrCheck[(UINT)GROUP_TYPE::END]; // 그룹 간의 충돌체크 배열
	// 충돌체 간의 이전 프레임 충돌 정보
	map<ULONGLONG, bool> m_mapColInfo; 
public:
	SINGLE(CollisionMgr);
private:
	CollisionMgr();
	~CollisionMgr();
public:
	void Update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void CheckReset();
private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(Collider* _pLeft, Collider* _pRight);
};

