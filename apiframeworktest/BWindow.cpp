#include "pch.h"
#include "BWindow.h"
#include "Core.h"
#include "Resource.h"
BWindow::BWindow() : m_hWnd(0), m_hInstance(0)
{
}

BWindow::~BWindow()
{
}

LRESULT BWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// exit 메시지 제외하곤 아무것도 처리하지 않음.
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
// Core 초기화
//if (FAILED(Core::GetInst()->Init(m_hWnd, POINT{ 1280, 768 })))
//{
//	MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);
//	return FALSE;
//}
int BWindow::Run(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	m_hInstance = hInstance; // 돌아온 인스턴스를 참조를 위해 넣어주고
	this->MyRegisterClass();
	this->WindowCreate();
	this->WindowShow(nCmdShow);
	this->WindowUpdate();

		// Core 초기화
	if (FAILED(Core::GetInst()->Init(m_hWnd, POINT{ 1280, 768 })))
	{
		MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);
		return FALSE;
	}
	return this->MessageLoop(); // 여기서 무한루프. 끝나면 프로그램 종료(exitcode와 함게)
}

ATOM BWindow::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = LoadIcon(m_hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = WINDOW_NAME;
	wcex.hIconSm = LoadIcon(m_hInstance, IDI_APPLICATION);

	return RegisterClassExW(&wcex);
}

void BWindow::WindowCreate()
{
	m_hWnd = CreateWindowW(WINDOW_NAME, L"주뇽's Gameframework", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInstance, nullptr);
}

void BWindow::WindowShow(int nCmdShow)
{
	ShowWindow(m_hWnd, nCmdShow);
}

void BWindow::WindowUpdate()
{
	UpdateWindow(m_hWnd);
}

int BWindow::MessageLoop()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			//if (msg.message == WM_QUIT)
			//	break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 게임 루프 시작
			Core::GetInst()->Progress();
		}
	}
	return 0;
}
