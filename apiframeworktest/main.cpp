// apiframeworktest.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "apiframeworktest.h"
#include <vector>
#include "BWindow.h"
#include "Core.h"
#include <iostream>
//#include <crtdbg.h>
using namespace std;
//#define MAX_LOADSTRING 100

// 전역 변수:
//HINSTANCE hInst;                                // 현재 인스턴스입니다.
//HWND g_hWnd;
//WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
//WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
//    Core::GetInst()->Run(hInstance, lpCmdLine, nCmdShow);
//    BWindow::GetInst()->Run(hInstance, lpCmdLine, nCmdShow);
    // 메모리 릭(누수)체크.
    // /    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
////    _CrtSetBreakAlloc();
//    int* a = new int[100000000];
//    new int;

    BWindow game;
    game.Run(hInstance, lpCmdLine, nCmdShow);
    return 0;
    _CrtDumpMemoryLeaks();
}

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//void a()
//{
//    static int b;
//    b = 1;
//}
//
//class A
//{
//private:
//    int m_a;
//public:
//    static int m_sa; // 정적 멤버
//public:
//    void func()
//    {
//        this->m_a;
//        m_sa;
//        this->m_sa = 0;
//    }
//    // 정적 멤버함수, 객체없이 호출 가능, this가 없다(멤버 접근 불가)
//    //		/*	
////		*  지역
////		* 전역
////		* 정적(데이터 영역)
////		* 1. 함수 안에(선언되면 데이터 영역에 선언이 됨)
////		* 2. 파일 (cpp파일 안에 선언되면 메모리 데이터영역, 각파일에서만)
////		* 3. 클래스 안에
////		* 외부
//    static void sfunc()
//    {
////        m_a;
//        m_sa;
//    }
//};
//int A::m_sa=0;

//A* a = new A;
//std::cout << a << endl;
//int b = 0;
//delete a;
//cout << a << endl;

//int c = 0;
//BWindow* pGame = nullptr;


//    core.Run();
//    //pGame = new BWindow;
//    //pGame->Run(hInstance, lpCmdLine, nCmdShow);
//    //Core core;
//    //A a;
//    //a.func();
//    //A::m_sa = 2;
//    //Core* pCore = Core::GetInstance();
//    //Core::GetInstance();
//    //Core::GetInstance();
//    //Core::GetInstance();
//
////    m_sa = 3;
//   //// A::func(); 
//   // a.sfunc();
//   // A::sfunc();
//   // //b = 1;
//   // c = 2;
////    UNREFERENCED_PARAMETER(hPrevInstance);
////    UNREFERENCED_PARAMETER(lpCmdLine);
////
////    // TODO: 여기에 코드를 입력합니다.
////
////    // 전역 문자열을 초기화합니다.
////    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
////    LoadStringW(hInstance, IDC_APIFRAMEWORKTEST, szWindowClass, MAX_LOADSTRING);
////    MyRegisterClass(hInstance);
////
////    // 애플리케이션 초기화를 수행합니다:
////    if (!InitInstance (hInstance, nCmdShow))
////    {
////        return FALSE;
////    }
////
////    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_APIFRAMEWORKTEST));
////
////    MSG msg;
////
////    // GetMessage: 메시지 큐에서 메시지 확인 될 때까지 대기
////    // msg.message == WM_QUIT 인 경우 false를 반환 -> 프로그램 종료
////    
////    // PeekMessage: 메시지 유무와 관계없이 반환
////    // 메시지큐에서 메시지를 확인한경우 true,  메시지큐에 메시지가 없는 경우 false를 반환한다.
////    // 기본 메시지 루프입니다:
////    vector<int> v;
////    v.push_back(1);
////    vector<int>::iterator iter;
////    iter = v.begin();
////    int a = v[0];
////
////    DWORD dwPrevCount = GetTickCount();
////    DWORD dwAccConut = 0;
////    //while (GetMessage(&msg, nullptr, 0, 0))
////    //{
////    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
////    //    {
////    //        TranslateMessage(&msg);
////    //        DispatchMessage(&msg);
////    //    }
////    //}
////    //while (true)
////    //{
////    //    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
////    //    {
////    //        if (WM_QUIT == msg.message)
////    //            break;
////    //        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
////    //        {
////    //            TranslateMessage(&msg);
////    //            DispatchMessage(&msg);
////    //        }
////
////    //    }
////    //    else
////    //    {
////
////    //    }
////    //}
//////}
////    while (true)
////    {
////        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
////        {
////            int iTime = GetTickCount();
////            if (WM_QUIT == msg.message)
////                break;
////            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
////            {
////                TranslateMessage(&msg);
////                DispatchMessage(&msg);
////            } 
////            dwAccConut += (GetTickCount() - iTime);
////        }
////        else
////        {
////            // 메시지가 없는동안 호출
////            DWORD dwCurCount = GetTickCount();
////            if (dwCurCount - dwPrevCount > 1000)
////            {
////                float fRatio = (float)dwAccConut / 1000.f;
////                wchar_t szBuff[50] = {};
////               // wsprintf(szBuff, L"비율: %f",fRatio);
////                swprintf_s(szBuff, L"비율: %f", fRatio);
////                SetWindowText(g_hWnd, szBuff);
////                dwPrevCount = dwCurCount;
////                dwAccConut = 0;
////            }
////        }
////    }
////
////    return (int) msg.wParam;
//}
//
//
//
////
////  함수: MyRegisterClass()
////
////  용도: 창 클래스를 등록합니다.
////
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//    WNDCLASSEXW wcex;
//
//    wcex.cbSize = sizeof(WNDCLASSEX);
//
//    wcex.style          = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc    = WndProc;
//    wcex.cbClsExtra     = 0;
//    wcex.cbWndExtra     = 0;
//    wcex.hInstance      = hInstance;
//    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APIFRAMEWORKTEST));
//    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
//    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
//    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_APIFRAMEWORKTEST);
//    wcex.lpszClassName  = szWindowClass;
//    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//    return RegisterClassExW(&wcex);
//}
//
////
////   함수: InitInstance(HINSTANCE, int)
////
////   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
////
////   주석:
////
////        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
////        주 프로그램 창을 만든 다음 표시합니다.
////
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
//
//   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//
//   if (!g_hWnd)
//   {
//      return FALSE;
//   }
//
//   ShowWindow(g_hWnd, nCmdShow);
//   UpdateWindow(g_hWnd);
//
//   return TRUE;
//}
////
////  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
////
////  용도: 주 창의 메시지를 처리합니다.
////
////  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
////  WM_PAINT    - 주 창을 그립니다.
////  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
////
////
//struct tObjInfo
//{
//    POINT g_ptObjPos;
//    POINT g_ptObjScale;
//};
//vector<tObjInfo> g_vecInfo;
//POINT g_ptLT; // 좌 상단
//POINT g_ptRB; // 우 하단
////#define RECT_MAKE(x,y,s) {x-s/2, y-s/2, x+s/2, y+s/2}
////#define RECT_DRAW(rt) Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom)
//#define RECT_DRAW(x,y,sx,sy) Rectangle(hdc, x-sx/2, y-sy/2, x+sx/2, y+sy/2)
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    PAINTSTRUCT ps;
//    HDC hdc;
//    static bool isClick;
//    switch (message)
//    {
//    case WM_CREATE:
//        isClick = false;
//        break;
//    case WM_LBUTTONDOWN:
//        g_ptLT.x=LOWORD(lParam);
//        g_ptLT.y=HIWORD(lParam);
//        isClick = true;
//        break;
//    case WM_MOUSEMOVE:
//        g_ptRB.x = LOWORD(lParam);
//        g_ptRB.y = HIWORD(lParam);
//        InvalidateRect(hWnd, nullptr, true);
//        break;
//    case WM_LBUTTONUP:
//    {
//        tObjInfo info = {};
//        info.g_ptObjPos.x = (g_ptLT.x + g_ptRB.x) / 2;
//        info.g_ptObjPos.y = (g_ptLT.y + g_ptRB.y) / 2;
//
//        info.g_ptObjScale.x = abs(g_ptLT.x - g_ptRB.x);
//        info.g_ptObjScale.y = abs(g_ptLT.y - g_ptRB.y);
//        g_vecInfo.push_back(info);
//        isClick = false;
//        InvalidateRect(hWnd, nullptr, true);
//    }
//        break;
//    case WM_PAINT:
//    {
//        hdc = BeginPaint(hWnd, &ps);
//        if(isClick)
//        Rectangle(hdc
//            , g_ptLT.x, g_ptLT.y
//            , g_ptRB.x, g_ptRB.y);
//        for (size_t i = 0; i < g_vecInfo.size(); i++)
//        {
//
//            RECT_DRAW(g_vecInfo[i].g_ptObjPos.x, g_vecInfo[i].g_ptObjPos.y, g_vecInfo[i].g_ptObjScale.x, g_vecInfo[i].g_ptObjScale.y);
//            Rectangle(hdc
//                , g_vecInfo[i].g_ptObjPos.x - g_vecInfo[i].g_ptObjScale.x /2
//                , g_vecInfo[i].g_ptObjPos.y - g_vecInfo[i].g_ptObjScale.y / 2
//                , g_vecInfo[i].g_ptObjPos.x + g_vecInfo[i].g_ptObjScale.x / 2
//                , g_vecInfo[i].g_ptObjPos.y + g_vecInfo[i].g_ptObjScale.y / 2);
//        }
//        EndPaint(hWnd, &ps);
//    }
//    break;
//    case WM_COMMAND:
//        {
//            int wmId = LOWORD(wParam);
//            // 메뉴 선택을 구문 분석합니다:
//            switch (wmId)
//            {
//            case IDM_ABOUT:
//                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//                break;
//            case IDM_EXIT:
//                DestroyWindow(hWnd);
//                break;
//            default:
//                return DefWindowProc(hWnd, message, wParam, lParam);
//            }
//        }
//        break;
//
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
//
//// 정보 대화 상자의 메시지 처리기입니다.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}
