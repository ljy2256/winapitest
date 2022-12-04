#include "Core.h"
#include "pch.h"
#include "Object.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "CollisionMgr.h"
#include "EventMgr.h"
#include "SoundMgr.h"
//Core* Core::g_pInst = nullptr;

//Object g_obj;
Core::Core()
	: m_hDC(0)
//	, m_hWnd(0)
	, m_ptResolution{}
	, m_hBit(0)
	, m_memDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{
}

Core::~Core()
{
	ReleaseDC(m_hWnd, m_hDC);
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}
}

//LRESULT Core::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	HDC hdc;
//	PAINTSTRUCT ps;
//		// exit �޽��� �����ϰ� �ƹ��͵� ó������ ����.
//		switch (message)
//		{
//		case WM_PAINT:
//			hdc = BeginPaint(hWnd, &ps);
//			//Rectangle(hdc, 1180, 0, 1280, 100); // setwindowpos �׽�Ʈ
//			EndPaint(hWnd, &ps);
//			break;
//		case WM_DESTROY:
//			PostQuitMessage(0);
//			return 0;
//		}
//		return DefWindowProc(hWnd, message, wParam, lParam);
//}

//int Core::Run(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow)
//{
//	m_hInstance = hInstance; // ���ƿ� �ν��Ͻ��� ������ ���� �־��ְ�
//	this->MyRegisterClass();
//	this->WindowCreate();
//	this->WindowShow(nCmdShow);
//	this->WindowUpdate();
//	// Core �ʱ�ȭ
//	if (FAILED(Core::GetInst()->Init(m_hWnd, POINT{1280, 768})))
//	{
//		MessageBox(nullptr, L"Core ��ü �ʱ�ȭ ����", L"ERROR", MB_OK);
//		return FALSE;
//	}
//	return this->MessageLoop(); // ���⼭ ���ѷ���. ������ ���α׷� ����(exitcode�� �԰�)
//}
//
//ATOM Core::MyRegisterClass()
//{
//	WNDCLASSEXW wcex;
//
//	wcex.cbSize = sizeof(WNDCLASSEX);
//
//	wcex.style = CS_HREDRAW | CS_VREDRAW;
//	wcex.lpfnWndProc = WndProc;
//	wcex.cbClsExtra = 0;
//	wcex.cbWndExtra = 0;
//	wcex.hInstance = m_hInstance;
//	wcex.hIcon = LoadIcon(m_hInstance, IDI_APPLICATION);
//	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
//	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//	wcex.lpszMenuName = L"�ִ��� ����";
//	wcex.lpszClassName = L"�ִ��� ����";
//	wcex.hIconSm = LoadIcon(m_hInstance, IDI_APPLICATION);
//
//	return RegisterClassExW(&wcex);
//}
//
//void Core::WindowCreate()
//{
//	m_hWnd = CreateWindowW(L"�ִ��� ����", L"�ִ��� ����", WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInstance, nullptr);
//}
//
//void Core::WindowShow(int nCmdShow)
//{
//	ShowWindow(m_hWnd, nCmdShow);
//}
//
//void Core::WindowUpdate()
//{
//	UpdateWindow(m_hWnd);
//}
//
//int Core::MessageLoop()
//{
//	MSG msg;
//	memset(&msg, 0, sizeof(msg));
//	while (true)
//	{
//		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
//		{
//			if (WM_QUIT == msg.message)
//				break;
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//		else
//		{
//			// ���� ���� ����.
//			Core::GetInst()->Progress();
//		}
//	}
//	return 0;
//}

int Core::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	m_hDC = GetDC(m_hWnd);
	
	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	//HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	//DeleteObject(hOldBit);

	SelectObject(m_memDC, m_hBit);

	// ���� ����� �� �� �귯�� ����
	CreateBrushPen();
	SoundMgr::GetInst()->Init();
	PathMgr::GetInst()->Init();
	TimeMgr::GetInst()->Init();
	KeyMgr::GetInst()->Init();
	SceneMgr::GetInst()->Init();

	//return E_FAIL;
//	g_obj.m_ptPos = { m_ptResolution.x /2 , m_ptResolution.y /2};
	// �ڡڡڿ��� üũ�ϱ�ڡڡ�
//	g_obj.SetPos(Vec2((float)m_ptResolution.x / 2 , (float)m_ptResolution.y / 2 ));
//	g_obj.SetPos(Vec2(m_ptResolution.x / 2, m_ptResolution.y / 2));
//	g_obj.SetScale(Vec2(100, 100)); 
//	g_obj.m_ptScale = { 100,100 };
	
	return S_OK;
}

void Core::Progress()
{
	//static int callcount = 0;
	//++callcount;
	//static int iPrevCount = GetTickCount64();
	//int iCurCount = GetTickCount64();
	//if (iCurCount - iPrevCount > 1000)
	//{
	//	iPrevCount = iCurCount;
	//	callcount = 0;
	//}	
	Update();
	Render();
}

void Core::Update()
{

	//SoundMgr::GetInst()->LoadSound(L"BGM", true, L"Sound\\wave.mp3");
	//SoundMgr::GetInst()->Volume(SOUND_CHANNEL::SC_BGM, 10.f);
	//SoundMgr::GetInst()->Play(L"BGM");

	// ==== Manager Update====
	TimeMgr::GetInst()->Update();
	KeyMgr::GetInst()->Update();

	// ==== Scene Update ====
	SceneMgr::GetInst()->Update();
	// ==== �浹 üũ ====
	CollisionMgr::GetInst()->Update();
//	Vec2 vPos = g_obj.GetPos();
////	if(GetAsyncKeyState(VK_LEFT) & 0x8000)
//	if(KeyMgr::GetInst()->GetKey(KEY::LEFT) == KEY_STATE::AWAY)
//	{
//		//g_obj.m_ptPos.x -= 1;
////		vPos.x -= 0.01f;
////		vPos.x -= 100.f * TimeMgr::GetInst()->GetfDT();//* Deltatime;
//		vPos.x -= 100.f; //* fDT; //* fDT;//* Deltatime;
//	}
////	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
//	if (KeyMgr::GetInst()->GetKey(KEY::RIGHT) == KEY_STATE::TAP)
//	{
//		//g_obj.m_ptPos.x += 1;
////		vPos.x += 0.01f;
////		vPos.x += 100.f * TimeMgr::GetInst()->GetfDT();
//		vPos.x += 100.f; //* fDT;//* fDT;
//	}
//	g_obj.SetPos(vPos);
}


void Core::Render()
{
	// ==== Rendering ====
	// ȭ�� clear blt�� ������ �̹���..
	PatBlt(m_memDC, 0, 0, m_ptResolution.x, m_ptResolution.y, WHITENESS); // ���ϸ�,invalidaterect ������ ���� false�ΰž�
	//Rectangle(m_memDC, -1, -1,
	//	m_ptResolution.x + 1, m_ptResolution.y + 1); // fillrect�� ��ġ��!

	SceneMgr::GetInst()->Render(m_memDC);
	// �׸���
	//Vec2 vPos = g_obj.GetPos();
	//Vec2 vScale = g_obj.GetScale(); 
	//Rectangle(m_memDC
	//	, int(vPos.x - vScale.x / 2.f)
	//	, int(vPos.y - vScale.y / 2.f)
	//	, int(vPos.x + vScale.x / 2.f)
	//	, int(vPos.y + vScale.y / 2.f));
	// ������۸����� �׸���
		BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
			,m_memDC, 0, 0, SRCCOPY);
		TimeMgr::GetInst()->Render();
	// === �̺�Ʈ ���� ó�� === //
		EventMgr::GetInst()->Update();



		//Rectangle(m_hDC  
//	, g_obj.m_ptPos.x -g_obj.m_ptScale.x /2
//	, g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2
//	, g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2
//	, g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
}

void Core::CreateBrushPen()
{
	// HOLLOW
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	//RED GREEN BLUE PEN
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
