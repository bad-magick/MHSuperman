#ifndef _USE_MFC
	#include <Windows.h>
#else
	#include "stdafx.h"
#endif

#define WIPE_END __asm _emit 0x60 __asm _emit 0x90 __asm _emit 0x90 __asm _emit 0x61

HWND GetWindow(CHAR *pTitle, CHAR *pClass);
void ToolTip(char *title, char *text, int iX, int iY);
void ToolTipPos(int iX, int iY);
void* FindClearTag(DWORD vFunc, int bytesToSearch = 4096);
void WipeFunction(DWORD vFunc);