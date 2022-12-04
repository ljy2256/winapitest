#include "pch.h"
#include "Animation.h"
#include "TimeMgr.h"
#include "Animator.h"
#include "Image.h"
#include "Object.h"
Animation::Animation()
	: m_pAnimator(nullptr)
	, m_iCurFrm(0)
	, m_pImage(nullptr)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (m_bFinish)
		return;
	m_fAccTime += fDT;
	if (m_fAccTime > m_vecFrm[m_iCurFrm].fDuration)
	{
		++m_iCurFrm;
		if (m_iCurFrm >= m_vecFrm.size())
		{
//			m_iCurFrm = 0;
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}
		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
	}
}

void Animation::Render(HDC _dc)
{
	if (m_bFinish)
		return;
	Object* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	// 원래 위치로
	//TransparentBlt(_dc
	//	, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
	//	, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
	//	, (int)(m_vecFrm[m_iCurFrm].vSlice.x 			  )
	//	, (int)(m_vecFrm[m_iCurFrm].vSlice.y			 )
	//	,  m_pImage->GetDC()						  
	//	, (int)(m_vecFrm[m_iCurFrm].vLT.x				  )
	//	, (int)(m_vecFrm[m_iCurFrm].vLT.y				  )
	//	, (int)(m_vecFrm[m_iCurFrm].vSlice.x				  )
	//	, (int)(m_vecFrm[m_iCurFrm].vSlice.y				  )
	//	, RGB(255,0,255));
	
	// 오프셋으로
	vPos += m_vecFrm[m_iCurFrm].vOffset; //  object pos에 offset만큼 추가 이동위치
	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
		, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x 			  )
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y			 )
		,  m_pImage->GetDC()						  
		, (int)(m_vecFrm[m_iCurFrm].vLT.x				  )
		, (int)(m_vecFrm[m_iCurFrm].vLT.y				  )
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x				  )
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y				  )
		, RGB(255,0,255));

}

void Animation::Create(Image* _pImage, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _iFrameCount, float _fDuration)
{
	m_pImage = _pImage;
	tAniFrm frm= {};
	for (UINT i = 0; i < _iFrameCount; i++)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * i;
		m_vecFrm.push_back(frm);
	}
}
