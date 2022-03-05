#ifndef _USE_MFC
	#include <Windows.h>
#else
	#include "stdafx.h"
#endif
#include <tlhelp32.h>
#include <shlwapi.h>
#include <string>
#include <Psapi.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "StringUtils.h"
#include "MHSuperman.h"
#include "VinHacks.h"
#include "Console.h"
#include "direct.h"

using namespace std;

int ReadLoadCommands(vector<string> &loadCommands)
{
	NOP
	loadCommands.clear();
	NOP
	char fqp[1024];
	NOP
	GetModuleFileName(hCurrentModule, fqp, 1024);
	NOP
	string spec = fqp;
	NOP
	string path = spec.substr(0, spec.find_last_of("\\"));
	NOP
	char me[1024];
	NOP
	sprintf(me, "%s\\loadcommands.txt", path.c_str());
	NOP

	NOP
	char buffer[1024];
	NOP
	ifstream fLC(me);
	NOP

	NOP
	string buf;
	NOP

	NOP
	int lines = 0;
	NOP
	if (fLC.good()) {
		NOP
		while (!fLC.eof()) {
			NOP
			fLC.getline(buffer, 1024);
			NOP
			if (strcmp(buffer, "") != 0) {
				NOP
				buf = buffer;
				NOP
				loadCommands.push_back(buf);
				NOP
				lines++;
				NOP
			}
			NOP
		}
		NOP
		fLC.close();
		NOP
	}
	NOP
	return lines;
	NOP
}

int ReadSpawnCommands(vector<string> &spawnCommands)
{
	//spawnCommands.clear();
	char fqp[1024];
	GetModuleFileName(hCurrentModule, fqp, 1024);
	string spec = fqp;
	string path = spec.substr(0, spec.find_last_of("\\"));

	char me[1024];
	sprintf(me, "%s\\%s", path.c_str(), spawnCommandsFilename.c_str());

	char buffer[1024];
	ifstream fLC(me);

	string buf;

	int lines = 0;
	if (fLC.good()) {
		while (!fLC.eof()) {
			fLC.getline(buffer, 1024);
			if (strcmp(buffer, "") != 0) {
				//buf = buffer;
				//spawnCommands.push_back(buf);
				//cprintf("Spawn command: %s\n", buffer);
				SendCommand(buffer);
				lines++;
			}
		}
		fLC.close();
	}
	return lines;
}

std::string ExtractDirectory( const std::string& path )
  {
  return path.substr( 0, path.find_last_of( '\\' ) +1 );
  }

std::string ExtractFilename( const std::string& path )
  {
  return path.substr( path.find_last_of( '\\' ) +1 );
  }

std::string ChangeExtension( const std::string& path, const std::string& ext )
  {
  std::string filename = ExtractFilename( path );
  return ExtractDirectory( path ) + filename.substr( 0, filename.find_last_of( '.' ) ) +ext;
  }

string GetTargetPathFromProcname(const char *procName)
{
   PROCESSENTRY32 pe;
   HANDLE thSnapshot;
   BOOL retval, ProcFound = false;

   thSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

   if(thSnapshot == INVALID_HANDLE_VALUE)
   {
      return "";
   }

   pe.dwSize = sizeof(PROCESSENTRY32);

   retval = Process32First(thSnapshot, &pe);

   string processName = procName;
   processName = tolowers(processName);

   string curProcess;
   string filespec;

   while(retval)
   {
	  curProcess = ExtractFilename(pe.szExeFile);
	  curProcess = tolowers(curProcess);
	  if (strcmp(curProcess.c_str(), processName.c_str()) == 0)
      {
		 HANDLE proc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ, false, pe.th32ProcessID); // 
		 if (proc == NULL) {
			return "";
		 }
		 char exe[4096];
		 if (GetModuleFileNameEx(proc, NULL, exe, 4096) == 0) {
			return "";
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
		return "";
	}
}

BOOL FolderExists(string strFolderName)
{   
    return GetFileAttributes(strFolderName.c_str()) != INVALID_FILE_ATTRIBUTES;   
}

int DeleteDirectory(const std::string &refcstrRootDirectory,
                    bool              bDeleteSubdirectories = true)
{
  bool            bSubdirectory = false;       // Flag, indicating whether
                                               // subdirectories have been found
  HANDLE          hFile;                       // Handle to directory
  std::string     strFilePath;                 // Filepath
  std::string     strPattern;                  // Pattern
  WIN32_FIND_DATA FileInformation;             // File information


  strPattern = refcstrRootDirectory + "\\*.*";
  hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
  if(hFile != INVALID_HANDLE_VALUE)
  {
    do
    {
      if(FileInformation.cFileName[0] != '.')
      {
        strFilePath.erase();
        strFilePath = refcstrRootDirectory + "\\" + FileInformation.cFileName;

        if(FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
          if(bDeleteSubdirectories)
          {
            // Delete subdirectory
            int iRC = DeleteDirectory(strFilePath, bDeleteSubdirectories);
            if(iRC)
              return iRC;
          }
          else
            bSubdirectory = true;
        }
        else
        {
          // Set file attributes
          if(::SetFileAttributes(strFilePath.c_str(),
                                 FILE_ATTRIBUTE_NORMAL) == FALSE)
            return ::GetLastError();

          // Delete file
          if(::DeleteFile(strFilePath.c_str()) == FALSE)
            return ::GetLastError();
        }
      }
    } while(::FindNextFile(hFile, &FileInformation) == TRUE);

    // Close handle
    ::FindClose(hFile);

    DWORD dwError = ::GetLastError();
    if(dwError != ERROR_NO_MORE_FILES)
      return dwError;
    else
    {
      if(!bSubdirectory)
      {
        // Set directory attributes
        if(::SetFileAttributes(refcstrRootDirectory.c_str(),
                               FILE_ATTRIBUTE_NORMAL) == FALSE)
          return ::GetLastError();

        // Delete directory
        if(::RemoveDirectory(refcstrRootDirectory.c_str()) == FALSE)
          return ::GetLastError();
      }
    }
  }

  return 0;
}

void RemoveBugReport(void)
{
	char temp[1024];
	_getcwd(temp, 1024);
	string me = temp;
	me = me + "\\bugreport.exe";
	ifstream fLC(me.c_str());
	if (fLC.good()) {
		fLC.close();
		::DeleteFileA(me.c_str());
	}
}

void RemoveAllTraces(void)
{
	//string sPath = GetTargetPathFromProcname("Vindictus.exe");
	char temp[1024];
	_getcwd(temp, 1024);
	string sPath = temp;
	sPath = sPath + "\\Addons";
	string sFiles = sPath + "\\*.*";
	int count = 0;

	string sFile;
	WIN32_FIND_DATA FileInformation;
	HANDLE hFile = ::FindFirstFileA(sFiles.c_str(), &FileInformation);
	if (hFile != INVALID_HANDLE_VALUE) {
		do {
			if (FileInformation.cFileName[0] != '.') {
				count++;
				sFile = FileInformation.cFileName;
				sFile = sFile.substr(0, 5);
				if (sFile.find("mmds-") != sFile.npos) {
					string thisFile;
					thisFile = sPath + "\\" + FileInformation.cFileName;
					::DeleteFile(thisFile.c_str());
					count--;
				}
			}
		} while(::FindNextFile(hFile, &FileInformation) == TRUE);
	}
	::FindClose(hFile);
	if (count == 0) {
		if (FolderExists(sPath)) {
			DeleteDirectory(sPath, true);
		}
	}
}
