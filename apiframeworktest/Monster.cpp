#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"
#include "Collider.h"
Monster::Monster()
	: m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_vCenterPos(Vec2(0.f,0.f))
	, m_iDir(1)
	, m_iHp(5)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

Monster::~Monster()
{
}

void Monster::Update()
{
	Vec2 vCurPos = GetPos();
	// ����������� �ð��� m_fSpeed��ŭ �̵�
//	vCurPos.x += m_fSpeed * fDT * m_iDir;
	vCurPos.x += fDT* m_fSpeed * m_iDir;

	// ��ȸ �Ÿ� ���ط��� �Ѿ���� Ȯ��
	//if (m_fMaxDistance < abs(m_vCenterPos.x - vCurPos.x))
	//{

	//}
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;
	if (fDist > 0.f)
	{
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}
	SetPos(vCurPos);
}

void Monster::EnterCollision(Collider* _pOther)
{
	Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Bullet_Player")
	{
		m_iHp -= 1;
		if(m_iHp <= 0)
			DeleteObject(this);
	}
}

