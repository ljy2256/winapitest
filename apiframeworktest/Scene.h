#pragma once
class Object;
class Scene
{
private:
//	Object a;
	// 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	vector<Object*> m_vecObj[(UINT)GROUP_TYPE::END];
	wstring         m_strName; // Scene이름
public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);
//	virtual void Start() = 0;
	virtual void Enter() abstract; // 해당 Scene에 진입시 호출
	virtual void Exit() abstract;  // 해당 Scene을 나올때 호출
public:
	void AddObject(Object* _pObj, GROUP_TYPE _eType)
	{
		m_vecObj[(UINT)_eType].push_back(_pObj);
	}
	const vector<Object*>& GetGroupObject(GROUP_TYPE _eType)
	{
		return m_vecObj[(UINT)_eType];
	}
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
public:
	Scene();
	virtual ~Scene();
};

