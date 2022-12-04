#pragma once
#include "framework.h"
class BWindow
{
//public:
//	static BWindow* GetInst()
//	{
//		static BWindow bwindow;
//		return &bwindow;
//	}
//private:
public:
	BWindow();
	~BWindow();
public:
	static LRESULT CALLBACK     WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	int							Run(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);
private:
	ATOM					    MyRegisterClass();
//	BOOL						InitInstance(HINSTANCE hInstance, int nCmdShow);
	void						WindowCreate();
	void						WindowShow(int nCmdShow);
	void						WindowUpdate();
	int							MessageLoop();
protected:
	HWND						m_hWnd;
	HINSTANCE					m_hInstance;
public:
	const HWND&					GetWndHandle() { return m_hWnd; }
	const HINSTANCE&			GetInstanceHandle() { return m_hInstance; }

};

