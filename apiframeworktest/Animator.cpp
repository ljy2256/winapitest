#include "pch.h"
#include "Animator.h"
#include "Animation.h"
Animator::Animator()
	: m_pOwner(nullptr)
	, m_pCurAni(nullptr)
	, m_bRepeat(false)
{
}

Animator::~Animator()
{
	Safe_Delete_Map(m_mapAni);
}

void Animator::CreateAnimation(const wstring _strName, Image* _pImage, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _iFrameCount, float _fDuration)
{
	Animation* pAnim = FindAnimation(_strName);
	assert(nullptr == pAnim);

	pAnim = new Animation;
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;

	pAnim->Create(_pImage, _vLT, _vSliceSize, _vStep, _iFrameCount, _fDuration);
	m_mapAni.insert({ _strName , pAnim });
}

Animation* Animator::FindAnimation(const wstring _strName)
{
	map<wstring, Animation*>::iterator iter = m_mapAni.find(_strName);
	
	if (iter == m_mapAni.end())
		return nullptr;
	return iter->second;
}

void Animator::Play(const wstring _strName, bool _bRepeat)
{
	m_pCurAni= FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}


void Animator::Update()
{
	if (nullptr != m_pCurAni)
	{
		m_pCurAni->Update();
		if (m_bRepeat && m_pCurAni->IsFinish())
		{
			m_pCurAni->SetFrame(0);
		}
	}
}

void Animator::Render(HDC _dc)
{
	if (nullptr != m_pCurAni)
		m_pCurAni->Render(_dc);
}
