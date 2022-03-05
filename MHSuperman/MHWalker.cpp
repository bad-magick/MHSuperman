#ifndef _USE_MFC
	#include <Windows.h>
#else
	#include "stdafx.h"
#endif
#include "MHWalker.h"
#include "MHWalkerDlg.h"
#include "AutoIt.h"
#include "MHWalkerDlg.h"
#include <GdiPlus.h>
#include <Gdipluspixelformats.h>
#include <string>
#include <conio.h>
#include <Commctrl.h>

#ifdef _MHWALKER
using namespace std;
using namespace Gdiplus;

HS_SendKeys	SendKeys;
HWND hWalker;
HINSTANCE hInst;
bool bOptionsWindowDisplayed = false;
bool bWinReg = false;

HWND TabStrip;

LRESULT CALLBACK WalkerCallback(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	TCITEMW tabPage = {0};

	switch (message) {
		case WM_COMMAND:
			break;
		case WM_CREATE:
			TabStrip = CreateWindowEx(0, WC_TABCONTROL, NULL, TCS_FIXEDWIDTH | WS_CHILD | WS_VISIBLE, 8, 8, 529, 449, hwnd, reinterpret_cast<HMENU>(static_cast<INT_PTR>(200)), hInst, NULL);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(TabStrip));

			tabPage.mask = TCIF_TEXT;
			tabPage.pszText = L"Info";
			tabPage.cchTextMax = 4;
			SendMessageW(TabStrip, TCM_INSERTITEM, 0, (LPARAM)(&tabPage));
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

void WalkerCreateWindow(void)
{
	bOptionsWindowDisplayed = true;
	if (!bWinReg) {
		INITCOMMONCONTROLSEX iccx;
		iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
		iccx.dwICC = ICC_LISTVIEW_CLASSES | ICC_TAB_CLASSES;
		InitCommonControlsEx(&iccx);

		WNDCLASSEX wcl;
		wcl.cbSize = sizeof(WNDCLASSEX);
		wcl.hInstance = hInst;
		wcl.lpszClassName = "MHWalkerOpts";
		wcl.lpfnWndProc = WalkerCallback;
		wcl.style = 0;
		//wcl.hIcon = ;
		//wcl.hIconSm = ;
		//wcl.hCursor = ;
		wcl.lpszMenuName = NULL;
		wcl.cbClsExtra = 0;
		wcl.cbWndExtra = 0;
		wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		RegisterClassEx(&wcl);
		bWinReg = true;
	}
	MSG msg;
	HWND hWnd = CreateWindowEx(NULL, "MHWalkerOpts", "MHWalker  v1.00", WS_BORDER | WS_CAPTION | WS_DLGFRAME | WS_MINIMIZEBOX | WS_POPUP | WS_SYSMENU | WS_VISIBLE, 0, 0, 544, 499, NULL, NULL, hInst, NULL);
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	hWalker = hWnd;

	BOOL bRet;
	while(GetMessage(&msg, NULL, 0, 0) != 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	bOptionsWindowDisplayed = false;

	hWalker = NULL;
}

void ThrowSpearsThread(void)
{
}

void ErrorCheckThread(void)
{
}

MHWalker::MHWalker(void)
{
	bIsPaused = false;
	bIsStarted = false;
}

MHWalker::~MHWalker(void)
{
}

void MHWalker::ShowOptionsWindow(HINSTANCE hInst)
{
	//SendKeys.Send("c", hwnd);
	//MHWalker
	::hInst = hInst;
	if (!bOptionsWindowDisplayed) {
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)WalkerCreateWindow, NULL, 0, NULL);
	} else {
		ShowWindow(hWalker, SW_SHOW);
		SetForegroundWindow(hWalker);
	}
}

void MHWalker::Start(void)
{
	if (!bIsStarted) {
		bIsStarted = true;
	}
}

void MHWalker::Pause(void)
{
	if (!bIsPaused) {
		bIsPaused = true;
	} else {
		bIsPaused = false;
	}
}

void MHWalker::Stop(void)
{
	if (bIsStarted) {
		bIsStarted = false;
	}
}

#endif

FastPixel::FastPixel(void)
{
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	bGotScreen = false;
}

FastPixel::~FastPixel(void)
{
	if (hBMP != NULL) {ReleaseScreen();}
	GdiplusShutdown(gdiplusToken);
}

DWORD FastPixel::fastPixelGetColor(int x, int y)
{
	if ((x == 0) && (y == 0)) {return 0;}
	if (bGotScreen) {
		DWORD *pixel = (DWORD*)((DWORD)hBitmapData->Scan0 + (y * hBitmapData->Stride) + (x * 4));
		return *pixel & 0x00FFFFFF;
	} else {
		return 0;
	}
}

void FastPixel::GetScreen(HWND hWnd)
{
	if (hBMP != NULL) {ReleaseScreen();}
	RECT rClient;
	GetClientRect(hWnd, &rClient);
	int iH, iW;
	int iTop, iLeft;
	HDC hDDC = GetDC(hWnd);
	HDC hCDC = CreateCompatibleDC(hDDC);
	hBMP = CreateCompatibleBitmap(hDDC, rClient.right, rClient.bottom);
	SelectObject(hCDC, hBMP);
	BitBlt(hCDC, 0, 0, rClient.right, rClient.bottom, hDDC, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hDDC);
	DeleteDC(hCDC);

	Rect gdRect(0, 0, rClient.right, rClient.bottom);
	hBitmap = Bitmap::FromHBITMAP(hBMP, NULL);
	hBitmapData = new BitmapData;
	hBitmap->LockBits(&gdRect, ImageLockModeRead || ImageLockModeWrite, PixelFormat32bppRGB, hBitmapData);
	bGotScreen = true;
}

void FastPixel::ReleaseScreen(void)
{
	hBitmap->UnlockBits(hBitmapData);
	DeleteObject(hBMP);
}

int FastPixel::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}

void FastPixel::SaveBitmap(wchar_t *fileName)
{
	CLSID bmpClsid;
	GetEncoderClsid(L"image/bmp", &bmpClsid);

	hBitmap->Save(fileName, &bmpClsid, NULL);
}

#ifdef _MHWALKER

MHWalkerOptions::MHWalkerOptions(_MHWalkerOptions *Options)
{
	opts = Options;
}

MHWalkerOptions::~MHWalkerOptions(void)
{
}

string IniRead(char* fileName, char* section, char* key, char* defaultVal)
{
	char ret[4096];
	GetPrivateProfileString(section, key, defaultVal, ret, strlen(ret), fileName);
	string ret2 = ret;
	return ret2;
}

bool IniRead(char* fileName, char* section, char* key, bool defaultVal)
{
	char ret[4096];
	char s[256];
	if (defaultVal) {
		strcpy(s, "1");
	} else {
		strcpy(s, "0");
	}
	GetPrivateProfileString(section, key, s, ret, strlen(ret), fileName);
	if (strcmp(ret, "1") == 0) {
		return true;
	} else {
		return false;
	}
}


int IniRead(char* fileName, char* section, char* key, int defaultVal)
{
	char ret[4096];
	char s[256];
	_itoa_s(defaultVal, s, 10);
	GetPrivateProfileString(section, key, s, ret, strlen(ret), fileName);
	return atoi(s);
}

void MHWalkerOptions::ReadSettings(char* fileName)
{
	WritePrivateProfileString(NULL, NULL, NULL, fileName);
	srand(GetTickCount());

	opts->Delays.ToTownLag =		IniRead(fileName, "Delays", "ToTownLag", 15000);
	opts->Delays.DungeonComplete =	IniRead(fileName, "Delays", "DungeonComplete", 300000);

	opts->Options.SpendAP =			IniRead(fileName, "Options", "SpendAP", true);
	opts->Options.APRuns =			IniRead(fileName, "Options", "APRuns", 10);
	opts->Options.LogFile =			IniRead(fileName, "Options", "LogFile", true);
	IniRead(fileName, "Options", "LogSize", 10);
	IniRead(fileName, "Options", "DeleteLog", false);
	IniRead(fileName, "Options", "MaxRuns", 0);
	IniRead(fileName, "Options", "OnUnfocus", 1);
	IniRead(fileName, "Options", "KeyboardMode", false);
	IniRead(fileName, "Options", "UseTimeHack", false);
	IniRead(fileName, "Options", "HostTimeScale", 5);
	IniRead(fileName, "Options", "NonWindow", false);
	IniRead(fileName, "Options", "FastBattleCleared", true);
	IniRead(fileName, "Options", "SlowMouse", false);
	IniRead(fileName, "Options", "ChangeChannel", true);
	IniRead(fileName, "Options", "ChannelMin", 160);
	IniRead(fileName, "Options", "ChannelMax", 190);
	IniRead(fileName, "Options", "CloseBattleCleared", true);
	IniRead(fileName, "Options", "FastCutscene", true);
	IniRead(fileName, "Options", "LogoutTime", 5);
	IniRead(fileName, "Options", "Relog", 5);
	IniRead(fileName, "Options", "PickItems", 1);
	IniRead(fileName, "Options", "BreakItems", 1);

	IniRead(fileName, "Merchant", "On", false);
	IniRead(fileName, "Merchant", "NoScrolls", true);
	IniRead(fileName, "Merchant", "NoEmpowered", true);
	IniRead(fileName, "Merchant", "NoEpic", true);
	IniRead(fileName, "Merchant", "NoMagicPowder", true);
	IniRead(fileName, "Merchant", "NoBlessedPowder", true);
	IniRead(fileName, "Merchant", "Chest2", true);
	IniRead(fileName, "Merchant", "Chest3", true);
	IniRead(fileName, "Merchant", "Chest4", true);
	IniRead(fileName, "Merchant", "Chest5", true);
	IniRead(fileName, "Merchant", "Chest6", true);
	IniRead(fileName, "Merchant", "Chest7", true);
	IniRead(fileName, "Merchant", "Chest8", true);
	IniRead(fileName, "Merchant", "Chest9", true);

	IniRead(fileName, "Login", "UserID", "");
	IniRead(fileName, "Login", "Pass", "");

	IniRead(fileName, "Window", "X", 192);
	IniRead(fileName, "Window", "Y", 124);

	IniRead(fileName, "WebServer", "Use", false);
	IniRead(fileName, "WebServer", "Port", (int)((double)rand() / (RAND_MAX + 1) * (10000-1000) + 1000));

	IniRead(fileName, "Advanced", "ColorDelta", 8);
	IniRead(fileName, "Advanced", "IdentifyAttempts", 3);
	IniRead(fileName, "Advanced", "MiningTime", 3300000);
	IniRead(fileName, "Advanced", "YUV", true);
	IniRead(fileName, "Advanced", "WebServerMaxConnections", 15);
}

#endif
