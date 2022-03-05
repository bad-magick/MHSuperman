#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <string>
#include <Psapi.h>
#include <wchar.h>

using namespace std;

//#define PROCESS_NAME "Vindictus.exe"
//#define DLL_NAME "C:\\Users\\Den\\Documents\\Visual Studio 2010\\Projects\\MHSuperman\\bin\\Public\\PubConsole.dll"

//I could just use PROCESS_ALL_ACCESS but it's always best to use the absolute bare minimum of priveleges, so that your code works in as 
//many circumstances as possible.
#define CREATE_THREAD_ACCESS (PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ)
  
BOOL WriteProcessBYTES(HANDLE hProcess,LPVOID lpBaseAddress,LPCVOID lpBuffer,SIZE_T nSize);

bool LoadDll(const wchar_t *procName, const wchar_t *dllName);
BOOL InjectDLL(DWORD ProcessID, const wchar_t *dllName);
unsigned long GetTargetProcessIdFromProcname(const wchar_t *procName);

std::wstring ExtractDirectory( const std::wstring& path )
  {
  return path.substr( 0, path.find_last_of( '\\' ) +1 );
  }

std::wstring ExtractFilename( const std::wstring& path )
  {
  return path.substr( path.find_last_of( '\\' ) +1 );
  }

std::wstring ChangeExtension( const std::wstring& path, const std::wstring& ext )
  {
  std::wstring filename = ExtractFilename( path );
  return ExtractDirectory( path ) + filename.substr( 0, filename.find_last_of( '.' ) ) +ext;
  }


std::wstring tolowers(std::wstring str)
{
    for (int i=0;i<wcslen(str.c_str());i++) 
        if (str[i] >= 0x41 && str[i] <= 0x5A) 
            str[i] = str[i] + 0x20;
    return str;
}

bool LoadDll(const wchar_t *procName, const wchar_t *dllName)
{
   DWORD ProcID = 0;

   ProcID = GetTargetProcessIdFromProcname(procName);

   if(!(InjectDLL(ProcID, dllName)))
      MessageBox(NULL, L"Injection failed", L"Loader", NULL);
   
   return true;
}

BOOL InjectDLL(DWORD ProcessID, const wchar_t *dllName)
{
   HANDLE Proc;
   wchar_t buf[50]={0};
   LPVOID RemoteString, LoadLibAddy;

   if(!ProcessID)
      return false;

   Proc = OpenProcess(CREATE_THREAD_ACCESS, FALSE, ProcessID);

   if(!Proc)
   {
      swprintf(buf, L"OpenProcess() failed: %d", GetLastError());
      MessageBox(NULL, buf, L"Loader", NULL);
      return false;
   }

   char dllName2[2048];
   wcstombs(dllName2, dllName, 2048);

   LoadLibAddy = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");

   RemoteString = (LPVOID)VirtualAllocEx(Proc, NULL, strlen(dllName2), MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
   WriteProcessMemory(Proc, (LPVOID)RemoteString, dllName2, strlen(dllName2), NULL);
   CreateRemoteThread(Proc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddy, (LPVOID)RemoteString, NULL, NULL);   
   
   CloseHandle(Proc);

   return true;
}

unsigned long GetTargetProcessIdFromProcname(const wchar_t *procName)
{
   PROCESSENTRY32 pe;
   HANDLE thSnapshot;
   BOOL retval, ProcFound = false;

   thSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

   if(thSnapshot == INVALID_HANDLE_VALUE)
   {
      return 0;
   }

   pe.dwSize = sizeof(PROCESSENTRY32);

   retval = Process32First(thSnapshot, &pe);

   wstring processName = procName;
   processName = tolowers(processName);

   wstring curProcess;

   while(retval)
   {
	  curProcess = ExtractFilename(pe.szExeFile);
	  curProcess = tolowers(curProcess);
	  if (wcscmp(curProcess.c_str(), processName.c_str()) == 0)
      //if(StrStrI(pe.szExeFile, procName) )
      {
         ProcFound = true;
         break;
      }

      retval    = Process32Next(thSnapshot,&pe);
      pe.dwSize = sizeof(PROCESSENTRY32);
   }

	if (ProcFound) {
		return pe.th32ProcessID;
	} else {
		return 0;
	}
}

wstring GetTargetPathFromProcname(const wchar_t *procName)
{
   PROCESSENTRY32 pe;
   HANDLE thSnapshot;
   BOOL retval, ProcFound = false;

   thSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

   if(thSnapshot == INVALID_HANDLE_VALUE)
   {
      return L"NULL";
   }

   pe.dwSize = sizeof(PROCESSENTRY32);

   retval = Process32First(thSnapshot, &pe);

   wstring processName = procName;
   processName = tolowers(processName);

   wstring curProcess;
   wstring filespec;

   while(retval)
   {
	  curProcess = ExtractFilename(pe.szExeFile);
	  curProcess = tolowers(curProcess);
	  if (wcscmp(curProcess.c_str(), processName.c_str()) == 0)
      //if(StrStrI(pe.szExeFile, procName) )
      {
		 HANDLE proc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ, false, pe.th32ProcessID); // 
		 if (proc == NULL) {
			wchar_t buf[200];
			swprintf(buf, L"Open process failed: %d", GetLastError());
			MessageBox(NULL, buf, L"Loader", NULL);
			return L"";
		 }
		 wchar_t exe[4096];
		 if (GetModuleFileNameEx(proc, NULL, exe, 4096) == 0) {
			wchar_t buf[200];
			swprintf(buf, L"Process information failed: %d", GetLastError());
			MessageBox(NULL, buf, L"Loader", NULL);
			return L"";
		 }
		 CloseHandle(proc);
		 filespec = exe;
         ProcFound = true;
         break;
      }

      retval    = Process32Next(thSnapshot,&pe);
      pe.dwSize = sizeof(PROCESSENTRY32);
   }

	if (ProcFound) {
		return ExtractDirectory(filespec);
	} else {
		return L"NULL";
	}
}