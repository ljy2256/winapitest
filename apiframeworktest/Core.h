#pragma once
#include "framework.h"
#include "define.h"
// 싱글톤 패턴
// 객체의 생성을 1개로 제한
// 어디서든 쉽게 접근 가능

// 1. 동적할당을 활용한 싱글톤
//class Core
//{ 
//private:
//	static Core* g_pInst;
//public:
//	// 정적 멤버함수 
//	static Core* GetInstance()
//	{
//		/*static Core* pCore = nullptr;*/
//
//		// 최초 호출 된 경우
//		if (nullptr == g_pInst)
//		{
//			g_pInst = new Core;
//		}
//		return g_pInst;
//	}
//	static void Release()
//	{
//		/*Core* p = GetInstance();
//		delete p;*/
//		if (nullptr != g_pInst)
//		{
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//	}
//private:
//	Core();
//	~Core();
//public:
//	static LRESULT CALLBACK     WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//	int							Run(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);
//private:
//	ATOM					    MyRegisterClass();
//	//	BOOL						InitInstance(HINSTANCE hInstance, int nCmdShow);
//	void						WindowCreate();
//	void						WindowShow(int nCmdShow);
//	void						WindowUpdate();
//	int							MessageLoop();
//protected:
//	HWND						m_hWnd;
//	HINSTANCE					m_hInstance;
//public:
//	const HWND& GetWndHandle() { return m_hWnd; }
//	const HINSTANCE& GetInstanceHandle() { return m_hInstance; }
//};
//

// 2. 데이터 영역을 이용한 싱글톤
#include "BWindow.h"
class Core
	: public BWindow
{
public:
//	SINGLE(Core);
public:
	static Core* GetInst()
	{
		static Core core;
		return &core;
	}
private:
	Core();
	~Core();
//public:
//	static LRESULT CALLBACK     WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//	int							Run(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);
//private:
//	ATOM					    MyRegisterClass();
//	//	BOOL						InitInstance(HINSTANCE hInstance, int nCmdShow);
//	void						WindowCreate();
//	void						WindowShow(int nCmdShow);
//	void						WindowUpdate();
//	int							MessageLoop();
private:
//	HWND						m_hWnd;// 메인  윈도우 핸들
//	HINSTANCE					m_hInstance;
	POINT						m_ptResolution; // 메인 윈도우 해상도
	HDC							m_hDC;   // 메인 윈도우에 Draw할 DC
	HBITMAP						m_hBit;	 //사본용 비트맵
	HDC							m_memDC; // 사본용 DC

	// 자주 사용하는 GDI(Graphic Device Interface) Object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

public:
	const HWND& GetWndHandle() { return m_hWnd; }
	const POINT& GetResolution() { return m_ptResolution; }
	const HDC& GetMainDC() { return m_hDC; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }

//	const HINSTANCE& GetInstanceHandle() { return m_hInstance; }
public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Progress();
private:
	void Update();
	void Render();
	void CreateBrushPen();
};

