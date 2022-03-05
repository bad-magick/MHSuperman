#ifndef _USE_MFC
	#include <Windows.h>
#else
	#include "stdafx.h"
#endif
#include <stdio.h>
#include <iostream>
#include <WinCon.h>
#include <string>

#include <io.h>
#include <conio.h>
//#include <fcntl.h>
//#include <fstream>

using namespace std;

void c_printf(char *fmt, ...);
void c_printf(wchar_t *fmt, ...);

int hConHandle;
HANDLE lStdHandle;
HANDLE lOutHandle;

void SetConsoleTextColor(int color)
{
	SetConsoleTextAttribute(lOutHandle, (WORD)color);
}

void CreateConsole (char *welcome, char *cName)
{
	char pszNewWindowTitle[255];
	sprintf_s(pszNewWindowTitle, cName);
	DWORD conMode;
	//FILE *fp;
	AllocConsole();
	SetConsoleTitleA(pszNewWindowTitle);
	stdout->_file=_open_osfhandle((intptr_t)GetStdHandle(STD_OUTPUT_HANDLE),0);
	lStdHandle = GetStdHandle(STD_INPUT_HANDLE);
	lOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//GetConsoleMode(lStdHandle, &conMode);
	DWORD conNewMode = ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT;
	SetConsoleMode(lStdHandle, conNewMode);
	SetConsoleTextColor(0xF);
	_cprintf_s("Welcome to %s!\n", welcome);
	SetConsoleTextColor(0x7);
}

void CreateConsole (wchar_t *welcome, wchar_t *cName)
{
	wchar_t pszNewWindowTitle[255];
	swprintf_s(pszNewWindowTitle, cName);
	DWORD conMode;
	//FILE *fp;
	AllocConsole();
	SetConsoleTitleW(pszNewWindowTitle);
	//stdout->_file=_open_osfhandle((intptr_t)GetStdHandle(STD_OUTPUT_HANDLE),0);
	lStdHandle = GetStdHandle(STD_INPUT_HANDLE);
	lOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//GetConsoleMode(lStdHandle, &conMode);
	DWORD conNewMode = ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT;
	SetConsoleMode(lStdHandle, conNewMode);
	SetConsoleTextColor(0xF);
	_cwprintf_s(L"Welcome to %s!\n", welcome);
	SetConsoleTextColor(0x7);
}

void CreateConsole (const wchar_t *welcome, wchar_t *cName)
{
	wchar_t pszNewWindowTitle[255];
	swprintf_s(pszNewWindowTitle, cName);
	DWORD conMode;
	//FILE *fp;
	AllocConsole();
	SetConsoleTitleW(pszNewWindowTitle);
	//stdout->_file=_open_osfhandle((intptr_t)GetStdHandle(STD_OUTPUT_HANDLE),0);
	lStdHandle = GetStdHandle(STD_INPUT_HANDLE);
	lOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//GetConsoleMode(lStdHandle, &conMode);
	DWORD conNewMode = ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT;
	SetConsoleMode(lStdHandle, conNewMode);
	SetConsoleTextColor(0xF);
	_cwprintf_s(L"Welcome to %s!\n", welcome);
	SetConsoleTextColor(0x7);
}

void KillConsole(void) {FreeConsole();}

void ConWrite(char* text, int color = 0x7) {
	SetConsoleTextColor(color);
	c_printf("%s", text);
}

void ConWrite(wchar_t* text, int color = 0x7) {
	SetConsoleTextColor(color);
	c_printf(L"%s", text);
}

void c_printf(char *fmt, ...)
{
	va_list args;
	char str[1024];
	DWORD cw;

	va_start(args, fmt);
	vsprintf(str, fmt, args);
	WriteConsoleA(lOutHandle, str, strlen(str), &cw, NULL);

	va_end(args);
}

void c_printf(wchar_t *fmt, ...)
{
	va_list args;
	wchar_t str[1024];
	DWORD cw;

	va_start(args, fmt);
	vswprintf(str, fmt, args);
	WriteConsoleW(lOutHandle, str, wcslen(str), &cw, NULL);

	va_end(args);
}



