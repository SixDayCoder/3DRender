#include "MainWindow.h"
#include <iostream>

bool        MainWindow::m_IsValid = false;
Scene*      MainWindow::m_pGameScene = nullptr;
HINSTANCE   MainWindow::m_Hinstance = 0;
HWND        MainWindow::m_Hwnd = 0;
int         MainWindow::m_Height = 0;
int		    MainWindow::m_Width = 0;
const char* MainWindow::m_Title = "";

MainWindow::MainWindow(HINSTANCE instance, int width, int height, const char * szTitle)
{
	m_Width = width;
	m_Height = height;
	m_Hinstance = instance;
	m_Hwnd = 0;
	m_pGameScene = nullptr;

	bool bRet = Register(instance, "Main", WndProc);
	if (bRet)
	{
		m_pGameScene = new Scene();
		m_Title = szTitle;
		m_IsValid = true;
	}
	else
	{
		std::cerr << "Register Window Error" << std::endl;
		exit(-1);
	}
}

MainWindow::~MainWindow()
{
	if (m_pGameScene)
	{
		delete m_pGameScene;
		m_pGameScene = nullptr;
	}
}

LRESULT MainWindow::WndProc(HWND hWnd, uint32 uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	static BITMAPINFO s_bitmapInfo;
	static HDC s_hdcBackbuffer;
	static HBITMAP s_hBitmap;
	static HBITMAP s_hOldBitmap;
	static void* s_pData;

	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
	{
		m_pGameScene->Init(m_Hinstance, hWnd);
		BITMAPINFOHEADER bmphdr = { 0 };
		bmphdr.biSize = sizeof(BITMAPINFOHEADER);
		bmphdr.biWidth = m_Width;
		bmphdr.biHeight = m_Height;
		bmphdr.biPlanes = 1;
		bmphdr.biBitCount = 32;
		bmphdr.biSizeImage = m_Height * m_Width * 4;
		s_hdcBackbuffer = CreateCompatibleDC(nullptr);
		HDC hdc = GetDC(hWnd);
		void** pFrameBuffer = reinterpret_cast<void**>(&m_pGameScene->GetCanvasBuffer());
		if (!(s_hBitmap = CreateDIBSection(nullptr, (PBITMAPINFO)&bmphdr, DIB_RGB_COLORS, pFrameBuffer, nullptr, 0)))
		{
			MessageBox(nullptr, "Dib Failed", "Error", MB_OK);
			return 0;
		}
		s_hOldBitmap = (HBITMAP)SelectObject(s_hdcBackbuffer, s_hBitmap);
		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		BitBlt(ps.hdc, 0, 0, m_Width, m_Height, s_hdcBackbuffer, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
	{
		SelectObject(s_hdcBackbuffer, s_hOldBitmap);
		DeleteDC(s_hdcBackbuffer);
		DeleteObject(s_hOldBitmap);
		PostQuitMessage(0);
		break;
	}
	case WM_ERASEBKGND:
		return true;
		break;
	case WM_LBUTTONDOWN:
		m_pGameScene->OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_LBUTTONUP:
		m_pGameScene->OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_MOUSEMOVE:
		m_pGameScene->OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_KEYDOWN:
		m_pGameScene->OnKeyDown(wParam);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

bool MainWindow::Register(HINSTANCE instance, LPSTR lpClassName, WNDPROC wndProc)
{
	WNDCLASSEX wce = { 0 };
	wce.cbSize = sizeof(wce);
	wce.cbClsExtra = 0;
	wce.cbWndExtra = 0;
	wce.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wce.hCursor = NULL;
	wce.hIcon = NULL;
	wce.hIconSm = NULL;
	wce.hInstance = instance;
	wce.lpfnWndProc = wndProc;
	wce.lpszClassName = lpClassName;
	wce.lpszMenuName = NULL;
	wce.style = CS_HREDRAW | CS_VREDRAW;
	ATOM nAtom = RegisterClassEx(&wce);
	if (nAtom == 0) return false;
	return true;
}

HWND MainWindow::CreateMain(LPCSTR lpClassName, LPCSTR lpWndName)
{

	RECT rc = { 0, 0, m_Width, m_Height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	HWND hWnd = CreateWindowEx(
		0, lpClassName, lpWndName,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, m_Hinstance, NULL
	);

	return hWnd;
}

void MainWindow::Run()
{
	if (IsValid())
	{
		m_Hwnd = CreateMain("Main", m_Title);

		ShowWindow(m_Hwnd, SW_SHOW);
		UpdateWindow(m_Hwnd);

		MSG msg = { 0 };
		while (msg.message != WM_QUIT) 
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				if (m_pGameScene->IsValid())
				{
					m_pGameScene->Update();
					m_pGameScene->Render();
				}
				InvalidateRect(m_Hwnd, nullptr, true);
				UpdateWindow(m_Hwnd);
			}
		}
	}
}
