#pragma once
class Scene;
class SceneMgr 
{
public:
	SINGLE(SceneMgr);
private:
	SceneMgr();
	~SceneMgr();
private:
	Scene* m_arrScene[(UINT)SCENE_TYPE::END]; // ��� �� ���
	Scene* m_pCurScene;						  // ���� ��
public:
	Scene* GetCurScene() { return m_pCurScene; }
private:
	void ChangeScene(SCENE_TYPE _eNext);
	friend class EventMgr;
public:
	void	 Init();
	void	 Update();
	void	 Render(HDC _dc);
};

