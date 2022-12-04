#include "pch.h"
#include "Object.h"
//#include "KeyMgr.h"
//#include "TimeMgr.h"
#include "Collider.h"
#include "Animator.h"
//void Object::Update()
//{
//
//}

Object::Object()
	: m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bAlive(true)
{
}

Object::Object(const Object& _origin)
	: m_strName(_origin.m_strName)
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bAlive(true)
{
	if (_origin.m_pCollider)
	{
		m_pCollider = new Collider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this;
	}
	if (_origin.m_pAnimator)
	{
		m_pAnimator = new Animator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
}

Object::~Object()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
	if (nullptr != m_pAnimator)
		delete m_pAnimator;
}

void Object::CreateCollider()
{
	m_pCollider = new Collider;
	m_pCollider->m_pOwner = this;
}

void Object::CreateAnimator()
{
	m_pAnimator = new Animator;
	m_pAnimator->m_pOwner = this;
}

void Object::FinalUpdate()
{
	if (m_pCollider)
		m_pCollider->FinalUpdate();
}

void Object::Render(HDC _dc)
{
	Rectangle(_dc,
		 (int)(m_vPos.x - m_vScale.x / 2.f)
		,(int)(m_vPos.y - m_vScale.y / 2.f)
		,(int)(m_vPos.x + m_vScale.y / 2.f)
		,(int)(m_vPos.y + m_vScale.y / 2.f));
	Component_Render(_dc);
}

void Object::Component_Render(HDC _dc)
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->Render(_dc);
	}
	if (nullptr != m_pAnimator)
		m_pAnimator->Render(_dc);
}

