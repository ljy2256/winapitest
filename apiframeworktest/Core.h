#pragma once
#include "framework.h"
#include "define.h"
// �̱��� ����
// ��ü�� ������ 1���� ����
// ��𼭵� ���� ���� ����

// 1. �����Ҵ��� Ȱ���� �̱���
//class Core
//{ 
//private:
//	static Core* g_pInst;
//public:
//	// ���� ����Լ� 
//	static Core* GetInstance()
//	{
//		/*static Core* pCore = nullptr;*/
//
//		// ���� ȣ�� �� ���
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

// 2. ������ ������ �̿��� �̱���
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
//	HWND						m_hWnd;// ����  ������ �ڵ�
//	HINSTANCE					m_hInstance;
	POINT						m_ptResolution; // ���� ������ �ػ�
	HDC							m_hDC;   // ���� �����쿡 Draw�� DC
	HBITMAP						m_hBit;	 //�纻�� ��Ʈ��
	HDC							m_memDC; // �纻�� DC

	// ���� ����ϴ� GDI(Graphic Device Interface) Object
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

