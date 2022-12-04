#pragma once
class Collider;
class Animator;
class Object
{
private:
	//POINT m_ptPos;
	//POINT m_ptScale;
	Vec2 m_vPos;
	Vec2 m_vScale;
	Collider* m_pCollider;
	Animator* m_pAnimator;
	wstring m_strName;
	bool    m_bAlive;
public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	const Vec2& GetPos() { return m_vPos; }
	const Vec2& GetScale() { return m_vScale; }
	Collider* GetCollider() { return m_pCollider; }
	Animator* GetAnimator() { return m_pAnimator; }
	void	CreateCollider();
	void	CreateAnimator();
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }
	bool IsDead() { return !m_bAlive; }
private:
	void SetDead() { m_bAlive = false; }
	friend class EventMgr;
public:
	virtual void	Update() abstract;
	virtual void	FinalUpdate() final;
	virtual void	Render(HDC _dc);
	virtual void	StayCollision(Collider* _pOther) {}
	virtual void	EnterCollision(Collider* _pOther) {}
	virtual void	ExitCollision(Collider* _pOther) {}


	void	Component_Render(HDC _dc);

	virtual Object* Clone() abstract;
public:
	Object();
	Object(const Object& _origin);
	virtual ~Object();
};

