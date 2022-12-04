#include "pch.h"
#include "CollisionMgr.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Object.h"
#include "Collider.h"

//struct Test // 8����Ʈ
//{
//	int a;
//	char c;
//};
//
//union Test2 // 4����Ʈ
//{
//	int a;
//	float f;
//};



CollisionMgr::CollisionMgr()
	: m_arrCheck{}
{
}

CollisionMgr::~CollisionMgr()
{
}

void CollisionMgr::Update()
{
	for (UINT Row = 0; Row < (UINT)GROUP_TYPE::END; ++Row)
	{
		for (UINT Col = Row; Col < (UINT)GROUP_TYPE::END; ++Col)
		{
			if (m_arrCheck[Row] & (1 << Col))
			{
				CollisionGroupUpdate((GROUP_TYPE)Row,(GROUP_TYPE)Col);
			}
		}
	}
}

void CollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	Scene* pCurScene = SceneMgr::GetInst()->GetCurScene();

	const vector<Object*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<Object*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;
	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		// �浹ü�� �������� �ʴ� ���
		if (nullptr == vecLeft[i]->GetCollider())
			continue;
		for (size_t j = 0; j < vecRight.size(); j++)
		{
			// �浹ü�� ���ų�, �ڱ� �ڽŰ��� �浹�� ���
			if (nullptr == vecRight[j]->GetCollider()
				|| vecLeft[i] == vecRight[j])
				continue;

			Collider* pLeftCol = vecLeft[i]->GetCollider();
			Collider* pRightCol = vecRight[j]->GetCollider();

			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();
			iter = m_mapColInfo.find(ID.ID);
			

			// ���� ������ �浹�� �� ����!!
			// �浹 ������ �� ��� ������ ��� ���(�浹���� �ʾҴ� ��)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert({ ID.ID, false});
				iter = m_mapColInfo.find(ID.ID);
			}
			// �浹 �ϳ�?
			if (IsCollision(pLeftCol, pRightCol))
			{
				// ���� �浹��..
				if (iter->second)
				{
					// �ٵ� ���� �ϳ� ���� �����̸� �浹 ����.
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						pLeftCol->ExitCollision(pRightCol);
						pRightCol->ExitCollision(pLeftCol);
						iter->second = false;
					}
					// �������� �浹 �� => Stay
					else
					{
						pLeftCol->StayCollision(pRightCol);
						pRightCol->StayCollision(pLeftCol);

					}
				}
				else
				{
					// �������� �浹���� �ʾҴ�. ����� �浹���̴�. => Enter
					// �ٵ� �� �� �ϳ��� ���� �����̶��, �浹���� ���� ������ ���
					if (!vecLeft[i]->IsDead() || !vecRight[j]->IsDead())
					{
						pLeftCol->EnterCollision(pRightCol);
						pRightCol->EnterCollision(pLeftCol);
						iter->second = true;
					}
				}
			}
			// �浹 ���ϳ�?
			else
			{
				// �浹 ���ϰ� �ִ�.
				if (iter->second)
				{
					// �������� �浹�ϰ� �־���.
					pLeftCol->ExitCollision(pRightCol);
					pRightCol->ExitCollision(pLeftCol);
					iter->second = false;
				}
			}

		}
	}
}

bool CollisionMgr::IsCollision(Collider* _pLeft, Collider* _pRight)
{
	Vec2 vLeftPos = _pLeft->GetFinalPos();
	Vec2 vRightPos = _pRight->GetFinalPos();
	Vec2 vLeftScale = _pLeft->GetScale();
	Vec2 vRightScale = _pRight->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}

void CollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// �� ���� ���� �׷� Ÿ���� ������, ū ���� ��(��Ʈ)�� ���
	UINT Row = (UINT)_eLeft;
	UINT Col = (UINT)_eRight;
	if (Col < Row)
	{
		Row = (UINT)_eRight;
		Col = (UINT)_eLeft;
	}
	// üũ�� �Ǿ� �ִٸ�
	if (m_arrCheck[Row] &= (1 << Col))
	{
		// üũ Ǯ��
		m_arrCheck[Row] &= ~(1 << Col);
	}
	// üũ�� �ȵǾ� �ִٸ�
	else
	{
		m_arrCheck[Row] |= (1 << Col);
	}
}

void CollisionMgr::CheckReset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
}


