#pragma once
#include <string>

void CreateConsole (char *welcome, char *cName);
void CreateConsole (wchar_t *welcome, wchar_t *cName);
void CreateConsole (const wchar_t *welcome, wchar_t *cName);
void KillConsole(void);
void SetConsoleTextColor(int color);
void ConWrite(char* text, int color = 0x7);
void ConWrite(wchar_t* text, int color = 0x7);
void c_printf(char *fmt, ...);
void c_printf(wchar_t *fmt, ...);