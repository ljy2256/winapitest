#pragma once
class Object;
class Scene
{
private:
//	Object a;
	// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	vector<Object*> m_vecObj[(UINT)GROUP_TYPE::END];
	wstring         m_strName; // Scene�̸�
public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);
//	virtual void Start() = 0;
	virtual void Enter() abstract; // �ش� Scene�� ���Խ� ȣ��
	virtual void Exit() abstract;  // �ش� Scene�� ���ö� ȣ��
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

