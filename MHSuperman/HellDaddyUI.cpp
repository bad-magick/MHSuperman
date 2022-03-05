#include "Constructs.h"
#include <Windows.h>
#include <string>

using namespace std;

HWND myDialog;
HWND editBox;

void conHandler(void)
{
	MSG msg;

	myDialog = CreateWindowEx(0, WC_DIALOG,"MHCyanide", WS_OVERLAPPEDWINDOW | WS_VISIBLE,	400,100,800,380,NULL,NULL,NULL,NULL	);

	CreateWindow( "listbox", "",
		WS_VISIBLE|WS_CHILD|LBS_HASSTRINGS|WS_HSCROLL|WS_VSCROLL,
		0, 0, 780, 300, myDialog, (HMENU)156, 0, NULL);

	editBox = CreateWindow( "edit", "",
		WS_VISIBLE|WS_CHILD,
		0, 305, 780, 20, myDialog, (HMENU)158, 0, NULL);

	//HellSigScan DevMss((unsigned char*)"\x75\x21\x68\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x68\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x08", "xxx????x????x????x????xxx", 25);
	//unsigned long DevMsgH = (unsigned long)DevMss.sigaddy
	//DevMsgH+=8;
	//unsigned long tmpp = (DevMsgH+4) + *(unsigned long*)DevMsgH;
	//MakeJMP((PBYTE)tmpp, (DWORD)&xDevMsg, 5);
	//MakeJMP((PBYTE)(GetProcAddress(GetModuleHandle("tier0.dll"), "?DevMsg@@YAXPBDZZ")), (DWORD)&xDevMsg, 5);
	//MakeJMP((PBYTE)(GetProcAddress(GetModuleHandle("tier0.dll"), "Msg")), (DWORD)&xDevMsg, 5);
	//MakeJMP((PBYTE)(GetProcAddress(GetModuleHandle("tier0.dll"), "Log")), (DWORD)&xDevMsg, 5);

	while(1)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.hwnd == editBox && msg.message == WM_KEYDOWN && msg.wParam == VK_RETURN)
			{
				int len = GetWindowTextLength(editBox);
				char *tmp = new char[len+1];
				GetWindowText(editBox, tmp, len+1);
				string tmps(tmp);
				if(tmps.find(" ") == string::npos)
				{
					//if(cvar->FindVar(tmp) != NULL)
					{
						int selpos = SendDlgItemMessage(myDialog, 156, LB_ADDSTRING, 0, (LPARAM)tmp);
						SendDlgItemMessage(myDialog, 156, LB_SETCURSEL, selpos, 0);
						char tbuff[512] = "";
						//sprintf(tbuff, "\"%s\" = \"%s\" (def. \"%s\")", tmp, cvar->FindVar(tmp)->GetString(), cvar->FindVar(tmp)->m_pszDefaultValue);
						selpos = SendDlgItemMessage(myDialog, 156, LB_ADDSTRING, 0, (LPARAM)tbuff);
						SendDlgItemMessage(myDialog, 156, LB_SETCURSEL, selpos, 0);
					}
					//else
					{
						int selpos = SendDlgItemMessage(myDialog, 156, LB_ADDSTRING, 0, (LPARAM)tmp);
						SendDlgItemMessage(myDialog, 156, LB_SETCURSEL, selpos, 0);
						//SendConsoleCommand(tmp);
					}
				}
				else
				{
					int selpos = SendDlgItemMessage(myDialog, 156, LB_ADDSTRING, 0, (LPARAM)tmp);
					SendDlgItemMessage(myDialog, 156, LB_SETCURSEL, selpos, 0);
					//SendConsoleCommand(tmp);
				}
				SetWindowText(editBox, "");
				delete tmp;
			}
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
		if(GetAsyncKeyState(VK_OEM_3))
		{
			BringWindowToTop(myDialog);
			SetFocus(editBox);
		}
		Sleep(1);
	}
}