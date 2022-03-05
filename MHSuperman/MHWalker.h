#pragma once

#ifndef _USE_MFC
	#include <Windows.h>
#else
	#include "stdafx.h"
#endif
#include <GdiPlus.h>
#include <Gdipluspixelformats.h>
#include <string>

using namespace Gdiplus;
using namespace std;

#ifdef _MHWALKER
class MHWalker
{
public:
	MHWalker(void);
	~MHWalker(void);

	void ShowOptionsWindow(HINSTANCE hInst);
	void Start(void);
	void Pause(void);
	void Stop(void);

	bool bIsPaused;
	bool bIsStarted;
	bool bIsRunning;
	wstring sDungeonName;
	wstring sDifficulty;
	
	int iErrorCount;
	bool bErrorFlag;
	wstring sFixNext;

};
#endif

class FastPixel
{
public:
	FastPixel(void);
	~FastPixel(void);

	DWORD fastPixelGetColor(int x, int y);
	void GetScreen(HWND hWnd);
	void ReleaseScreen(void);
	void FastPixel::SaveBitmap(wchar_t * fileName);

private:
	HBITMAP hBMP;
	Bitmap* hBitmap;
	BitmapData* hBitmapData;
	ULONG_PTR gdiplusToken;
	bool bGotScreen;

	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
};

#ifdef _MHWALKER
class _MHWalkerOptions
{
public:
	class _MHWalkerOptions_Delays
	{
	public:
		int ToTownLag;
		int DungeonComplete;
	};
	class _MHWalkerOptions_Options
	{
	public:
		bool SpendAP;
		int APRuns;
		int LogFile;
		int LogSize;
		bool DeleteLog;
		int MaxRuns;
		int OnUnfocus;
		bool KeyboardMode;
		bool UseTimeHack;
		int HostTimeScale;
		bool NonWindow;
		bool FastBattleCleared;
		bool SlowMouse;
		bool ChangeChannel;
		int ChannelMin;
		int ChannelMax;
		bool CloseBattleCleared;
		bool FastCutscene;
		int LogoutTime;
		int Relog;
		bool PickItems;
		bool BreakItems;
	};
	class _MHWalkerOptions_Merchant
	{
	public:
		bool On;
		bool NoScrolls;
		bool NoEmpowered;
		bool NoEpic;
		bool NoMagicPowder;
		bool NoBlessedPowder;
		bool Chest2;
		bool Chest3;
		bool Chest4;
		bool Chest5;
		bool Chest6;
		bool Chest7;
		bool Chest8;
		bool Chest9;
	};

	_MHWalkerOptions_Delays Delays;
	_MHWalkerOptions_Options Options;
	_MHWalkerOptions_Merchant Merchant;
};

class MHWalkerOptions
{
public:
	MHWalkerOptions(_MHWalkerOptions *Options);
	~MHWalkerOptions(void);

	

	void ReadSettings(char* fileName);

private:
	_MHWalkerOptions* opts;

};
#endif
