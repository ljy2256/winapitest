#pragma once
class Object;
class Collider
{
private:
	Object* m_pOwner; // collider�� �����ϰ� �ִ� ������Ʈ
	Vec2	m_vOffsetPos; // ������Ʈ�κ��� ������� ��ġ
	Vec2	m_vFinalPos; // finalupdate���� �� �����Ӹ��� ���
	Vec2	m_vScale;  // �浹ü ũ��
	UINT	m_iID;     // �浹ü ������ ID ��
	static UINT g_iNextID;
	UINT    m_iCheck;
public:
	Collider();
	Collider(const Collider& _origin);
	~Collider();
public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	UINT GetID() {	return m_iID; }
	Vec2 GetFinalPos() { return m_vFinalPos; }
	Object* GetObj() { return m_pOwner; }
public:
	void FinalUpdate();
	void Render(HDC _dc);
	Collider& operator = (Collider& _origin) = delete;
	void StayCollision(Collider* _pOther); // �浹 ���� ��� ȣ�� �Ǵ� �Լ�
	void EnterCollision(Collider* _pOther); // �浹 ���� ȣ�� �Լ�
	void ExitCollision(Collider* _pOther);
	friend class Object;
};

