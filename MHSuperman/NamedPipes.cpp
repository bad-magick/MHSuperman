#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <vector>
#include "VinHacks.h"

using namespace std;

unsigned long __stdcall NET_RvThr(void * pParam) ;
DWORD WINAPI ThreadProc() ;
DWORD cbWritten;

HANDLE hPipeOutSpew = INVALID_HANDLE_VALUE;
HANDLE hPipeOutMsg = INVALID_HANDLE_VALUE;
HANDLE hPipeOutDevMsg = INVALID_HANDLE_VALUE;
HANDLE hPipeOutWarning = INVALID_HANDLE_VALUE;
HANDLE hPipeOutData1 = INVALID_HANDLE_VALUE;
HANDLE hPipeInCommand = INVALID_HANDLE_VALUE;

BOOL Finished;

void StartPipes(void)
{
	//Pipe Init Data
	char buf[65535];
    
	LPTSTR lpszPipeOutSpew = TEXT("\\\\.\\pipe\\myNamedPipe1");
	LPTSTR lpszPipeOutMsg = TEXT("\\\\.\\pipe\\myNamedPipe2");
	LPTSTR lpszPipeOutDevMsg = TEXT("\\\\.\\pipe\\myNamedPipe3");
	LPTSTR lpszPipeOutWarning = TEXT("\\\\.\\pipe\\myNamedPipe4");
	LPTSTR lpszPipeInCommand = TEXT("\\\\.\\pipe\\myNamedPipe5");
	LPTSTR lpszPipeOutData1 = TEXT("\\\\.\\pipe\\myNamedPipe6");

	DWORD cbWritten;
	DWORD dwBytesToWrite = (DWORD)strlen(buf);

	while (1)
	{
		if (hPipeOutSpew == NULL || hPipeOutSpew == INVALID_HANDLE_VALUE)
		{
			hPipeOutSpew=CreateFile(lpszPipeOutSpew,	GENERIC_WRITE ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);
		}
		if (hPipeOutMsg == NULL || hPipeOutMsg == INVALID_HANDLE_VALUE)
		{
			hPipeOutMsg=CreateFile(lpszPipeOutMsg,	GENERIC_WRITE ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);
		}
		if (hPipeOutDevMsg == NULL || hPipeOutDevMsg == INVALID_HANDLE_VALUE)
		{
			hPipeOutDevMsg=CreateFile(lpszPipeOutDevMsg,	GENERIC_WRITE ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);
		}
		if (hPipeOutWarning == NULL || hPipeOutWarning == INVALID_HANDLE_VALUE)
		{
			hPipeOutWarning=CreateFile(lpszPipeOutWarning,	GENERIC_WRITE ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);
		}
		if (hPipeOutData1 == NULL || hPipeOutData1 == INVALID_HANDLE_VALUE)
		{
			hPipeOutData1=CreateFile(lpszPipeOutData1,	GENERIC_WRITE ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);
		}
		
		if (hPipeInCommand == NULL || hPipeInCommand == INVALID_HANDLE_VALUE)
		{
			hPipeInCommand=CreateFile(lpszPipeInCommand,	GENERIC_READ ,0,NULL, OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);
			if (hPipeInCommand == NULL || hPipeInCommand == INVALID_HANDLE_VALUE)
			{
				DWORD dwMode = PIPE_READMODE_MESSAGE;
				SetNamedPipeHandleState(hPipeInCommand, &dwMode, NULL, NULL);
			}
			//hPipeInCommand=CreateFile(lpszPipeInCommand,	GENERIC_READ , PIPE_WAIT, NULL, OPEN_EXISTING,NULL,NULL);
		}
		
		Sleep(2500);
	}
}

void SendSpew(char* pChr)
{
	if (hPipeOutSpew != INVALID_HANDLE_VALUE)
	{
		bool a = WriteFile(hPipeOutSpew, pChr, 4096, &cbWritten, NULL);
		if (!a && GetLastError() != ERROR_IO_PENDING)
		{
			hPipeOutSpew = INVALID_HANDLE_VALUE;
		}
	}
}

void SendMsg(char* pChr)
{
	if (hPipeOutMsg != INVALID_HANDLE_VALUE)
	{
		bool a = WriteFile(hPipeOutMsg, pChr, 4096, &cbWritten, NULL);
		if (!a && GetLastError() != ERROR_IO_PENDING)
		{
			hPipeOutMsg = INVALID_HANDLE_VALUE;
		}
	}
}

void SendDevMsg(char* pChr)
{
	if (hPipeOutDevMsg != INVALID_HANDLE_VALUE)
	{
		bool a = WriteFile(hPipeOutDevMsg, pChr, 4096, &cbWritten, NULL);
		if (!a && GetLastError() != ERROR_IO_PENDING)
		{
			hPipeOutDevMsg = INVALID_HANDLE_VALUE;
		}
	}
}

void SendWarning(char* pChr)
{
	if (hPipeOutWarning != INVALID_HANDLE_VALUE)
	{
		bool a = WriteFile(hPipeOutWarning, pChr, 4096, &cbWritten, NULL);
		if (!a && GetLastError() != ERROR_IO_PENDING)
		{
			hPipeOutWarning = INVALID_HANDLE_VALUE;
		}
	}
}

void SendData1(char* pChr)
{
	if (hPipeOutData1 != INVALID_HANDLE_VALUE)
	{
		bool a = WriteFile(hPipeOutData1, pChr, 4096, &cbWritten, NULL);
		if (!a && GetLastError() != ERROR_IO_PENDING)
		{
			hPipeOutData1 = INVALID_HANDLE_VALUE;
		}
	}
}

void SendData1(string s)
{
	char pCmd[255];
	strcpy(pCmd, s.c_str());
	SendData1(pCmd);
}

void SendCmd(char* pChr)
{
	if (hPipeInCommand != INVALID_HANDLE_VALUE)
	{
		bool a = WriteFile(hPipeInCommand, pChr, 4096, &cbWritten, NULL);
		if (!a && GetLastError() != ERROR_IO_PENDING)
		{
			hPipeInCommand = INVALID_HANDLE_VALUE;
		}
	}
}


void KeepAlive(void)
{
	while(1)
	{
		Sleep(2500);
		SendSpew("Keep-Alive");
		SendMsg("Keep-Alive");
		SendDevMsg("Keep-Alive");
		SendWarning("Keep-Alive");
		//SendCmd("Keep-Alive");
	}
}

void InitPipes(void)
{
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StartPipes, NULL, 0, NULL);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)KeepAlive, NULL, 0, NULL);
	CreateThread(NULL, 0, &NET_RvThr, NULL, 0, NULL);
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

unsigned long __stdcall NET_RvThr(void * pParam) {
	BOOL fSuccess; 
	char chBuf[4096];
	DWORD dwBytesToWrite = (DWORD)strlen(chBuf);
	DWORD cbRead;
	OVERLAPPED o = {0};
	int i;

	while(1)
	{
		if (hPipeInCommand != INVALID_HANDLE_VALUE || hPipeInCommand != NULL || hPipeInCommand != (HANDLE)ERROR_INVALID_HANDLE)
		{
			memset(chBuf, NULL, 4096);
			fSuccess =ReadFile(hPipeInCommand, chBuf, 4096, &dwBytesToWrite, NULL); 
			if(fSuccess)
			{
				if ((strcmp(chBuf, "Keep-Alive") == 0) || (strcmp(chBuf, "") == 0))
				{
				} else if ((strcmp(chBuf, "ping") == 0))
				{
					Ping();
				}
				else
				{
					std:vector<std::string> x = split(std::string(chBuf), '\n');
					char pCmd[255];
					string cmd;
					cmd = x.front();
					//for (vector<string>::iterator i = x.begin(); i != x.end(); ++i) {
					//	cmd = *i;
						strcpy(pCmd, cmd.c_str());
						ProcessCommand(pCmd);
						SendCommand(pCmd);
					//}
				}
			}
			else
			{
				DWORD error = GetLastError();
				if (error != ERROR_IO_PENDING)
				{
					CancelIoEx(hPipeInCommand, NULL);
					CloseHandle(hPipeInCommand);
					//if (hPipeInCommand != INVALID_HANDLE_VALUE)
					//	_cprintf("Pipe lost: %i\n", error);
					hPipeInCommand = INVALID_HANDLE_VALUE;
					Sleep(2500);
				}
			}
		}
	}
}

