#include "pch.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Image.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "SoundMgr.h"
Player::Player()
	//: m_pImage(nullptr)
{
	// Image 로딩
	//m_pImage = new Image;
	//wstring strFilePath = PathMgr::GetInst()->GetRsrcPath();
	//strFilePath += L"Image\\planem.bmp";
	//m_pImage->Load(strFilePath);
//	m_pImage = ResMgr::GetInst()->ImgLoad(L"PlayerImg", L"Image\\planem.bmp");
	CreateCollider();
//	GetCollider()->SetOffsetPos(Vec2(100.f, 0.f));
//	GetCollider()->SetScale(Vec2(90.f, 75.f));
	GetCollider()->SetScale(Vec2(20.f, 30.f));

//	m_pImage = ResMgr::GetInst()->ImgLoad(L"PlayerAni", L"Image\\jiwoo.bmp");
	Image* pImg = ResMgr::GetInst()->ImgLoad(L"PlayerAni", L"Image\\jiwoo.bmp");

	CreateAnimator();
//	GetAnimator()->CreateAnimation(L"Jiwoofront", m_pImage, Vec2(0.f, 150.f), Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5,1.f);
	GetAnimator()->CreateAnimation(L"Jiwoofront", pImg, Vec2(0.f, 150.f), Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->Play(L"Jiwoofront", true);

	// offset 위로 올리기. 
	//Animation* pAnim = GetAnimator()->FindAnimation(L"Jiwoofront");
	//for(size_t i=0;i<pAnim->GetMaxFrame();i++)
	//	pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
}
Player::~Player()
{
	//if(nullptr !=m_pImage)
	//	delete m_pImage;
}
void Player::Update()
{
	Vec2 vPos = GetPos();
//	if (KeyMgr::GetInst()->GetKey(KEY::W) == KEY_STATE::HOLD)
//	if (KEY_CHECK(KEY::W,KEY_STATE::HOLD))
	if(KEY_HOLD(KEY::UP))
	{
		vPos.y -= 300.f * fDT;
	}
//	if (KeyMgr::GetInst()->GetKey(KEY::S) == KEY_STATE::HOLD)
	if (KEY_HOLD(KEY::DOWN))
	{
		vPos.y += 300.f * fDT;
	}
//	if (KeyMgr::GetInst()->GetKey(KEY::A) == KEY_STATE::HOLD)
	if (KEY_HOLD(KEY::LEFT))
	{
		vPos.x -= 300.f * fDT;
	}
//	if (KeyMgr::GetInst()->GetKey(KEY::D) == KEY_STATE::HOLD)
	if (KEY_HOLD(KEY::RIGHT))
	{
		vPos.x += 300.f * fDT;
	}
//	if (KeyMgr::GetInst()->GetKey(KEY::SPACE) == KEY_STATE::TAP)
	if (KEY_TAP(KEY::SPACE))
	{
		CreateBullet();
	}
	if (KEY_TAP(KEY::CTRL))
	{
		SoundMgr::GetInst()->Pause(SOUND_CHANNEL::SC_BGM, true);
	}
	if (KEY_TAP(KEY::C))
	{
		SoundMgr::GetInst()->Pause(SOUND_CHANNEL::SC_BGM, false);
	}
	SetPos(vPos);
	GetAnimator()->Update();
}

void Player::CreateBullet()
{
	Vec2 vBulletPos = GetPos();
	vBulletPos.y -= GetScale().y / 2.f;

	// 
	Bullet* pBullet = new Bullet;
	pBullet->SetName(L"Bullet_Player");
	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vec2(25.f, 25.f));
	pBullet->SetDir(Vec2(0.f, -1.f));
//	pBullet->SetDir(Vec2(-1.f, -7.f));
//	pBullet->SetDir(true);
	CreateObject(pBullet, GROUP_TYPE::BULLET_PLAYER);
	//Scene* pCurScene = SceneMgr::GetInst()->GetCurScene();
	//pCurScene->AddObject(pBullet,GROUP_TYPE::BULLET);
}
void Player::Render(HDC _dc)
{
	Component_Render(_dc);
	/*int Width = (int)m_pImage->GetWidth();
	int Height = (int)m_pImage->GetHeight();

	Vec2 vPos = GetPos();*/
	//BitBlt(_dc
	//	,(int)(vPos.x - (float)(Width / 2))
	//	,(int)(vPos.y - (float)(Height / 2))
	//    , Width, Height
	//    , m_pImage->GetDC()
	//    , 0,0, SRCCOPY);

	//마젠타 색상 뺄때 transparent: 투명한
	//TransparentBlt(_dc
	//	, (int)(vPos.x - (float)(Width / 2))
	//	, (int)(vPos.y - (float)(Height / 2))
	//	,Width, Height
	//    , m_pImage->GetDC()
	//    ,0,0, Width, Height
	//    , RGB(255,0,255));

}
