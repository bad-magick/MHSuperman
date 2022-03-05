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

class MHCyanide
{
public:
	MHCyanide(void);
	~MHCyanide(void);

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

