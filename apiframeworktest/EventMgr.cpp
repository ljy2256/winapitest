#include "pch.h"
#include "EventMgr.h"
#include "Object.h"
#include "SceneMgr.h"
#include "Scene.h"
EventMgr::EventMgr()
{
}

EventMgr::~EventMgr()
{
}

void EventMgr::Update()
{
	// ���� �����ӿ��� ����ص� dead object ���� �����Ѵ�.
	for (size_t i = 0; i < m_vecDead.size(); i++)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	// ==== event ó�� ====

	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		Excute(m_vecEvent[i]);	
	}
	m_vecEvent.clear();
}

void EventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
		// lParam: Object Address
		// wParam: Group Type
	{
		Object* pNewObj = (Object*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;
		SceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam: Object Address
		// Object�� Dead ���·� �����ϰ� �������� ������Ʈ���� ��Ƶд�.
		Object* pDeadObj = (Object*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		// lParam: Next Scene Type
		SceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);
	}
		break;
	}
}
