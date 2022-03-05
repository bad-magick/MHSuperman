#ifndef _USE_MFC
	#include <Windows.h>
#else
	#include "stdafx.h"
#endif
#include "MHCyanide.h"
#include "AutoIt.h"
#include <GdiPlus.h>
#include <Gdipluspixelformats.h>
#include <string>
#include <conio.h>
#include <Commctrl.h>

using namespace std;
using namespace Gdiplus;

HS_SendKeys	CSendKeys;
HWND chCyanide;
HINSTANCE chInst;
bool cbOptionsWindowDisplayed = false;
bool cbWinReg = false;
HWND CTabStrip;

LRESULT CALLBACK CyanideCallback(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	TCITEMW tabPage = {0};

	switch (message) {
		case WM_COMMAND:
			break;
		case WM_CREATE:
			CTabStrip = CreateWindowEx(0, WC_TABCONTROL, NULL, TCS_FIXEDWIDTH | WS_CHILD | WS_VISIBLE, 8, 8, 529, 449, hwnd, reinterpret_cast<HMENU>(static_cast<INT_PTR>(200)), chInst, NULL);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(CTabStrip));

			tabPage.mask = TCIF_TEXT;
			tabPage.pszText = L"Info";
			tabPage.cchTextMax = 4;
			SendMessageW(CTabStrip, TCM_INSERTITEM, 0, (LPARAM)(&tabPage));
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_NOTIFY:
			break;
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

void CyanideSetupCreateWindow(void)
{
	cbOptionsWindowDisplayed = true;
	if (!cbWinReg) {
		INITCOMMONCONTROLSEX iccx;
		iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
		iccx.dwICC = ICC_LISTVIEW_CLASSES | ICC_TAB_CLASSES;
		InitCommonControlsEx(&iccx);

		WNDCLASSEX wcl;
		wcl.cbSize = sizeof(WNDCLASSEX);
		wcl.hInstance = chInst;
		wcl.lpszClassName = "MHCyanideSetup";
		wcl.lpfnWndProc = CyanideCallback;
		wcl.style = 0;
		//wcl.hIcon = ;
		//wcl.hIconSm = ;
		//wcl.hCursor = ;
		wcl.lpszMenuName = NULL;
		wcl.cbClsExtra = 0;
		wcl.cbWndExtra = 0;
		wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		RegisterClassEx(&wcl);
		cbWinReg = true;
	}
	MSG msg;
	HWND hWnd = CreateWindowEx(NULL, "MHCyanideSetup", "MHCyanide  v1.00", WS_BORDER | WS_CAPTION | WS_DLGFRAME | WS_MINIMIZEBOX | WS_POPUP | WS_SYSMENU | WS_VISIBLE, 0, 0, 544, 499, NULL, NULL, chInst, NULL);
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	chCyanide = hWnd;

	BOOL bRet;
	while(GetMessage(&msg, NULL, 0, 0) != 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	cbOptionsWindowDisplayed = false;

	chCyanide = NULL;
}

MHCyanide::MHCyanide(void)
{
	bIsPaused = false;
	bIsStarted = false;
}

MHCyanide::~MHCyanide(void)
{
}

void MHCyanide::ShowOptionsWindow(HINSTANCE hInst)
{
	//SendKeys.Send("c", hwnd);
	//MHWalker
	::chInst = hInst;
	if (!cbOptionsWindowDisplayed) {
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)CyanideSetupCreateWindow, NULL, 0, NULL);
	} else {
		ShowWindow(chCyanide, SW_SHOW);
		SetForegroundWindow(chCyanide);
	}
}

void MHCyanide::Start(void)
{
	if (!bIsStarted) {
		bIsStarted = true;
	}
}

void MHCyanide::Pause(void)
{
	if (!bIsPaused) {
		bIsPaused = true;
	} else {
		bIsPaused = false;
	}
}

void MHCyanide::Stop(void)
{
	if (bIsStarted) {
		bIsPaused = false;
		bIsStarted = false;
	}
}

