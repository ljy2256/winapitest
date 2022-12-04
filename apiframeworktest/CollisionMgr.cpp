#include "pch.h"
#include "CollisionMgr.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Object.h"
#include "Collider.h"

//struct Test // 8바이트
//{
//	int a;
//	char c;
//};
//
//union Test2 // 4바이트
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
		// 충돌체를 보유하지 않는 경우
		if (nullptr == vecLeft[i]->GetCollider())
			continue;
		for (size_t j = 0; j < vecRight.size(); j++)
		{
			// 충돌체가 없거나, 자기 자신과의 충돌인 경우
			if (nullptr == vecRight[j]->GetCollider()
				|| vecLeft[i] == vecRight[j])
				continue;

			Collider* pLeftCol = vecLeft[i]->GetCollider();
			Collider* pRightCol = vecRight[j]->GetCollider();

			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();
			iter = m_mapColInfo.find(ID.ID);
			

			// 이전 프레임 충돌한 적 없다!!
			// 충돌 정보가 미 등록 상태인 경우 등록(충돌하지 않았다 로)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert({ ID.ID, false});
				iter = m_mapColInfo.find(ID.ID);
			}
			// 충돌 하네?
			if (IsCollision(pLeftCol, pRightCol))
			{
				// 현재 충돌중..
				if (iter->second)
				{
					// 근데 둘중 하나 삭제 예정이면 충돌 해제.
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						pLeftCol->ExitCollision(pRightCol);
						pRightCol->ExitCollision(pLeftCol);
						iter->second = false;
					}
					// 이전에도 충돌 중 => Stay
					else
					{
						pLeftCol->StayCollision(pRightCol);
						pRightCol->StayCollision(pLeftCol);

					}
				}
				else
				{
					// 이전에는 충돌하지 않았다. 현재는 충돌중이다. => Enter
					// 근데 둘 중 하나가 삭제 예정이라면, 충돌하지 않은 것으로 취급
					if (!vecLeft[i]->IsDead() || !vecRight[j]->IsDead())
					{
						pLeftCol->EnterCollision(pRightCol);
						pRightCol->EnterCollision(pLeftCol);
						iter->second = true;
					}
				}
			}
			// 충돌 안하네?
			else
			{
				// 충돌 안하고 있다.
				if (iter->second)
				{
					// 이전에는 충돌하고 있었다.
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
	// 더 작은 값의 그룹 타입을 행으로, 큰 값을 열(비트)로 사용
	UINT Row = (UINT)_eLeft;
	UINT Col = (UINT)_eRight;
	if (Col < Row)
	{
		Row = (UINT)_eRight;
		Col = (UINT)_eLeft;
	}
	// 체크가 되어 있다면
	if (m_arrCheck[Row] &= (1 << Col))
	{
		// 체크 풀기
		m_arrCheck[Row] &= ~(1 << Col);
	}
	// 체크가 안되어 있다면
	else
	{
		m_arrCheck[Row] |= (1 << Col);
	}
}

void CollisionMgr::CheckReset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
}


