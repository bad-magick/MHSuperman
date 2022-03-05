#ifndef _USE_MFC
	#include <Windows.h>
#else
	#include "stdafx.h"
#endif
#include <Commctrl.h>
#include <string>
#include "SigScan.h"
using namespace std;

HWND hFoundWnd;
CHAR *cSearchTitle;
CHAR *cSearchClass;

HWND m_hWndTip;
int iTipX = 0;
int iTipY = 0;

BOOL CALLBACK WindowSearchProc(HWND hWnd, LPARAM lParam)
{
	char szBuffer[1024];
	
	GetWindowText(hWnd, szBuffer, 1024);
	string sBuffer = szBuffer;
	if (sBuffer.find(cSearchTitle) == sBuffer.npos) {return true;}
	//if (strcmp(szBuffer, cSearchTitle) == NULL) {return TRUE;}

	GetClassName(hWnd, szBuffer, 1024);
	if (strcmp(szBuffer, cSearchClass) != 0) {return TRUE;}

	hFoundWnd = hWnd;
	return FALSE;
}

HWND GetWindow(CHAR *pTitle, CHAR *pClass)
{
	hFoundWnd = 0;
	cSearchTitle = pTitle;
	cSearchClass = pClass;
	EnumWindows((WNDENUMPROC)WindowSearchProc, 0);

	return hFoundWnd;
}

void ToolTipPos(int iX, int iY)
{
	RECT r;
	GetClientRect(m_hWndTip, &r);
	iTipX = iX - (r.right / 2);
	iTipY = iY - (r.bottom / 2);
	SetWindowPos(m_hWndTip, NULL, iTipX, iTipY, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void ToolTip(char *title, char *text, int iX, int iY, HWND hWnd = NULL)
{
	TOOLINFO ti;
	POINT  pt;
	ti.cbSize = sizeof(ti);
	ti.uFlags = TTF_TRACK | TTF_ABSOLUTE | TTF_TRANSPARENT;
	ti.hwnd  = hWnd;
	ti.hinst = NULL;
	ti.uId  = 0;
	ti.lpszText = text;
	ti.rect.left = ti.rect.top = ti.rect.right = ti.rect.bottom = 0;

	pt.x = iTipX;
	pt.y = iTipY;

	if (!m_hWndTip)
	{
		m_hWndTip = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL, TTS_NOPREFIX | TTS_ALWAYSTIP,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);

		RECT dtw;
		GetWindowRect(GetDesktopWindow(), &dtw);

		SendMessage (m_hWndTip , TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO)&ti);
		SendMessage(m_hWndTip, TTM_SETMAXTIPWIDTH, 0, (LPARAM)dtw.right);
		SendMessage(m_hWndTip, TTM_SETTITLE, TTI_NONE, (LPARAM)title);

		dtw.top =  3;
		dtw.left =  3;
		dtw.bottom =  3;
		dtw.right =  3;
		SendMessage(m_hWndTip, TTM_SETMARGIN, 0, (LPARAM)&dtw);
	} else {
		SendMessage(m_hWndTip, TTM_UPDATETIPTEXT, 0, (LPARAM)&ti);
	}

	ToolTipPos(iX, iY);
}

void Patch(DWORD address, size_t length, ...)
{
    va_list list;
    va_start(list, length);
    DWORD oldProtection = 0;
    VirtualProtect((LPVOID)address, length, PAGE_EXECUTE_READWRITE, &oldProtection);
    for(size_t i = 0; i < length; i++, address++)
        *(BYTE *)address = va_arg(list, BYTE);
    VirtualProtect((LPVOID)address, length, oldProtection, &oldProtection);
}

void* FindClearTag(DWORD vFunc, int bytesToSearch = 4096)
{
	DWORD iFound = 0;
	DWORD *iPtr;
	char *cBasePtr = (char*)vFunc;
	char *cEndPtr = (char*)(vFunc + bytesToSearch);
	char *sig = "\x60\x90\x90\x61";
	int i;

	while (cEndPtr > cBasePtr) {
		for (i = 0; i < 4; i++) {
			if (cBasePtr[i] != sig[i]) {
				break;
			}
		}
		if (i == 4) {
			return (void*)cBasePtr;
		}
		cBasePtr++;
	}
	return 0;
}

void WipeFunction(DWORD vFunc)
{
	DWORD pEnd = (DWORD)FindClearTag(vFunc);
	if (pEnd != 0) {
	    DWORD oldProtection;
		int size = pEnd - vFunc + 4;
		VirtualProtect((LPVOID)vFunc, size, PAGE_EXECUTE_READWRITE, &oldProtection);
		for (int i = vFunc; i < vFunc + size; i++) {
			*(BYTE *)i = 0x90;
		}
		VirtualProtect((LPVOID)vFunc, size, oldProtection, &oldProtection);
	}
}
