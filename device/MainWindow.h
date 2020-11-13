#pragma once

#include "device/Scene.h"

#include <windows.h>
#include <windowsx.h>
#include <memory.h>
#include <malloc.h>
#include <memory>
#include <cstdlib>
#include <tchar.h>
#include <string>


class MainWindow
{
public:

	MainWindow(HINSTANCE instance, int width, int height, const char* szTitle = "Lovely Fancy");
	~MainWindow();

	bool IsValid()const { return m_IsValid; }		
	Scene& GetGameScene() { return *m_pGameScene; }
	void Run();


private:

	static bool        m_IsValid;
	static Scene*      m_pGameScene;
	static HINSTANCE   m_Hinstance;
	static HWND        m_Hwnd;
	static int         m_Width;
	static int         m_Height;
	static const char* m_Title;

	static LRESULT CALLBACK WndProc(HWND hWnd, uint32 uMsg, WPARAM wParam, LPARAM lParam);
	static bool    Register(HINSTANCE instance, LPSTR lpClassName, WNDPROC wndProc);
	static HWND    CreateMain(LPCSTR lpClassName, LPCSTR lpWndName);
};