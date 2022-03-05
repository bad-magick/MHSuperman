#ifndef _USE_MFC
	#include <Windows.h>
#else
	#include "stdafx.h"
#endif
#include "sdk.h"
#include "MHWalker.h"
#include "NetVarDump.h"
#include "ServerPlugin.h"
#include <fstream>
#include "Constructs.h"
#include <string>
#include <vector>
#include "SigScan.h"
#include "Console.h"
#include "NetVarDumper.h"

#include "StringUtils.h"
#include "FileIO.h"
#include "WinUtils.h"
#include "MHSuperman.h"
#include "resource.h"
#include "CustomCommands.h"
#include <algorithm>
#include <iostream>
#include "EncryptStrings.h"
#include "MHWalker.h"
#include "LuaThreads.h"
#include "NamedPipes.h"

HICON				hIcon1;
HICON				hIcon2;
HWND				hWndConsole;
HWND				hWndVindictus;

using namespace std;

//Define Strings
#define VINUNIVERSAL
#define string_CMDFILE			"\\a8dc570da319.tmp"
#define string_KILL2			"asdfkj23"

#define PUBLIC_NA_VERSION		L"1.9"
#define PUBLIC_EU_VERSION		L"1.2"
#define PRIVATE_VERSION			L"1.2"
#define OFFTHERECORD_VERSION	L"2.0"
#define NUM_READ_CHARS			4096

#define ShowMessageBoxes		0

#define OFF_FILL 0xEC0E9

/**************************
**	Forward Declarations **
**	and global variables **
**************************/
int GetNumInHostedParty(void);
void HackThread(void);
bool IsGameReady(void);
bool IsGamePartiallyReady(void);
void PublicProtectionThread(void);
void ConsoleThread(void);
void SendCommand(char *pCmd);
void ReloadLoadCommands(void);
void printLoadCommands(void);
int RunSpawnCommands(void);
void RunSpawnCommandsCallback(void);
void printSpawnCommands(void);
void SetProgramIconRed(HMODULE hModule);
void SetProgramIconBlue(HMODULE hModule);
void ExternalCommandThread(void);

typedef SpewOutputFunc_t (__cdecl *GetSpewOutputFuncFn)();
typedef void (__cdecl *SpewOutputFuncFn)( SpewOutputFunc_t func );
typedef void (__stdcall *MsgFn)( char *pMsg, ... );
typedef void (__stdcall *DevMsgFn)( int level, char *pMsg, ... );
typedef void (__stdcall *WarningFn)( char *pMsg, ... );

int InitState = 0;

HMODULE				hEngineModule, hClientModule, hTier0Module, hServerModule, hVStdlibModule, hInputModule, hFileSysModule; //module handles
CreateInterfaceFn	pEngineFactory, pClientFactory, pServerFactory, pServerGame, pInputFactory, pFileSysFactory, pVStdLibFactory;   //CreateInterface function pointers

CSigScan					enhance;

IBaseClientDLL				*pBaseClient		= NULL;		//a pointer to the IBaseClientDLL interface, initialized as NULL
IVEngineClient				*pEngineClient		= NULL;		//a pointer to the IVEngineClient interface, initialized as NULL
IClientEntityList			*pClientEntityList	= NULL;		//a pointer to the IClientEntityList interface, initialized as NULL
ICvar						*pCvar				= NULL;		//a pointer to the ICvar interface, initialized as NULL
IInputSystem				*pInput				= NULL;
IVEngineServer				*pEngineServer		= NULL;
IServerPluginHelpers		*pPluginHelpers		= NULL;

DWORD						*pEngineClientVTable= NULL;		

GenDT_BaseEntity			*pBaseEnt			= NULL;
GenDT_BaseCombatCharacter	*pCCharacter		= NULL;

GetSpewOutputFuncFn			_GetSpewOutputFunc	= NULL;
SpewOutputFuncFn			_SpewOutputFunc		= NULL;
SpewOutputFunc_t			ZeOldSpewOutput		= NULL;

MsgFn						_Msg				= NULL;
DevMsgFn					_DevMsg				= NULL;
WarningFn					_Warning			= NULL;

BOOL						bShowLog			= FALSE;

BOOL						bConReady			= FALSE;
BOOL						bTermCon			= FALSE;
HANDLE						hConThread;

HANDLE						hPublicThread;
vector<string>				binds;
vector<string>				unbinds;
BOOL						bAllowCommands		= FALSE;
BOOL						bReady				= FALSE;
string						sLastMap			= "";
string						sCurrentMap			= "";

vector<string>				alwaysAllowedCmds;
vector<string>				disallowedCommands;
vector<string>				disallowedMaps;

vector<string>				loadCommands;
vector<string>				spawnCommands;
string						spawnCommandsFilename;

bool						bUseSpawnCmds		= true;

bool						bCanNuke			= true;

MHWalker					Walker;

char						sA[67];
char						sB[67];
char						s1[67];
char						s2[67];

int							ptrExecute			= NULL;
int							ptrEnhance			= NULL;
int							ptrEngine			= NULL;
int							ptrBind				= NULL;

char						cT[1024];
wchar_t						wT[1024];

char						DungeonName[1024];

//int (__cdecl *myClientCmd5)(char *a1) = (int (__cdecl *)(char *a1))0x4201D010;

//int (__cdecl *myClientCmd4)(char *a1) = (int (__cdecl *)(char *a1))0x4204B520;
//int (__cdecl *myClientCmd3)(char *a1) = (int (__cdecl *)(char *a1))0x4204B340;
//int (__cdecl *myClientCmd2)(char *a1) = (int (__cdecl *)(char *a1))0x4204BDC0;
int (__cdecl *myClientCmd)(char *a1, int a2) = (int (__cdecl *)(char *a1, int a2))0x4204BAD0;
int (__stdcall *getCurrentDungeon)(const char* lpMultiByteStr) = (int (__stdcall*)(const char* lpMultiByteStr))0x42308F00;

const wchar_t* GetResString(int ID)
{
	//wchar_t buf[1024];
	LANGID User = ::GetUserDefaultLangID();
	SetThreadUILanguage(User);
	LoadStringW(hCurrentModule, ID, wT, 1024);
	return wT;
}

const char* GetResStringA(int ID)
{
	//char buf[1024];
	LANGID User = ::GetUserDefaultLangID();
	SetThreadUILanguage(User);
	LoadStringA(hCurrentModule, ID, cT, 1024);
	return cT;
}

inline void ErasePEHeaderFromMemory(HINSTANCE hModule)
{
	DWORD OldProtect = 0;

	// Get base address of module
	char *pBaseAddr = (char*)hModule;

	// Change memory protection
	VirtualProtect(pBaseAddr, 4096, // Assume x86/x64 page size
		PAGE_READWRITE, &OldProtect);

	// Erase the header
	ZeroMemory(pBaseAddr, 4096);
	VirtualFree(pBaseAddr,4096,MEM_DECOMMIT);
}

void CreateHackThread(void)
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HackThread, 0, 0, 0); //Create a thread that runs our HackThread function
	RemoveBugReport();
	RemoveAllTraces();
}

void ToggleSpawnCommands(void)
{
	SetConsoleTextColor(0xF);
	if (bUseSpawnCmds) {
		bUseSpawnCmds = false;
		_cwprintf_s(GetResString(101)); //"Spawn commands disabled.\n"
	} else {
		bUseSpawnCmds = true;
		_cwprintf_s(GetResString(102)); //"Spawn commands enabled.\n"
		RunSpawnCommands();
	}
	SetConsoleTextColor(0x7);
}

void SpawnCommandsFile(void) {
	spawnCommandsFilename = pEngineClient->Cmd_Argv(1);
	RunSpawnCommands();
}

void nuke(void)
{
	if (bCanNuke) {
		bCanNuke = false;
		kill1();
	}
}

bool IsOnAllowedList(char* pCmd)
{
	string sTemp = pCmd;
	sTemp = tolowers(sTemp);
	string sTemp2;
	for (vector<string>::iterator i = alwaysAllowedCmds.begin(); i != alwaysAllowedCmds.end(); ++i) {
		sTemp2 = *i;
		sTemp2 = tolowers(sTemp2);
		if (sTemp.find(sTemp2) != string::npos) {
			return true;
		}
	}
	return false;
}

bool IsOnDisallowedList(char* pCmd)
{
	string sTemp = pCmd;
	sTemp = tolowers(sTemp);
	string sTemp2;
	for (vector<string>::iterator i = disallowedCommands.begin(); i != disallowedCommands.end(); ++i) {
		sTemp2 = *i;
		sTemp2 = tolowers(sTemp2);
		if (sTemp.find(sTemp2) != string::npos) {
			return true;
		}
	}
	return false;
}

bool IsPublicMap(void)
{
	string sTemp;
	for (vector<string>::iterator i = disallowedMaps.begin(); i != disallowedMaps.end(); ++i) {		//check for disallowed map
		sTemp = *i;
		if (sCurrentMap.compare(sTemp) == 0) {
			return true;
		}
	}
	return false;
}

void MakeJMP(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen)
{
    DWORD dwOldProtect, dwBkup, dwRelAddr;
    VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    dwRelAddr = (DWORD) (dwJumpTo - (DWORD) pAddress) - 5;
    *pAddress = 0xE9;
    *((DWORD *)(pAddress + 0x1)) = dwRelAddr;
    for(DWORD x = 0x5; x < dwLen; x++) {
		*(pAddress + x) = 0x90;
	}
    VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
    return;
}

void EnhanceFix(void)
{
	CSigScan sEnhanceCheat;
	sEnhanceCheat.sigscan_dllfunc = (void *(__cdecl *)(const char *,int *))pBaseClient;
	sEnhanceCheat.GetDllMemInfo();
	sEnhanceCheat.Init((unsigned char*)"\x0A\x7C\x00\xE8\x00\x00\x00\x00\x8B\x10\x6A\x01\x53\x6A\x01\x68\x00\x00\x00\x00\x8B\xC8\x8B\x42\x00\x68\x00\x00\x00\x00\xFF\xD0", "xx?x????xxxxxxxx????xxxx?x????xx",32);
	unsigned char *ptr = (unsigned char*)(((unsigned long)sEnhanceCheat.sig_addr));
	DWORD dwOld;
	VirtualProtect(ptr, 1, PAGE_EXECUTE_READWRITE, &dwOld);
	*ptr = 0xF;
	VirtualProtect(ptr, 1, dwOld, &dwOld);
	ptrEnhance = (int)ptr;
}

void BindFix(void)
{
	/*
	CSigScan cssBindFix;
	cssBindFix.sigscan_dllfunc = (void *(__cdecl *)(const char *,int *))pEngineClient;
	cssBindFix.GetDllMemInfo();
	cssBindFix.Init((unsigned char*)"\x33\xFF\x5B\x85\xF6\x74\x00\x8B\x00\x00\x00\x51\x56\xE8\x00\x00\x00\x00\x83\xC4\x00\x85\xC0\x75", "xxxxxx?x???xxx????xx?xxx", 24);
	unsigned char *ptr = (unsigned char*)(((unsigned long)cssBindFix.sig_addr) + 24);
	DWORD dwOld;
	VirtualProtect(ptr, 1, PAGE_EXECUTE_READWRITE, &dwOld);
	*ptr = 0x00;
	VirtualProtect(ptr, 1, dwOld, &dwOld);
	ptrBind = (int)ptr;
	*/
	unsigned char *ptr = (unsigned char*)0x420EE9B1;
	DWORD dwOld;
	VirtualProtect(ptr, 1, PAGE_EXECUTE_READWRITE, &dwOld);
	*ptr = 0xEB;
	VirtualProtect(ptr, 1, dwOld, &dwOld);
	ptrBind = (int)ptr;
}

void InitClientCmd(void)
{
#if USE_CLIENTCMD == 1
	CSigScan execCmd_Sig;
	execCmd_Sig.sigscan_dllfunc = (void *(__cdecl *)(const char *,int *))pEngineClient;
	execCmd_Sig.GetDllMemInfo();
	execCmd_Sig.Init((unsigned char*)"\xE8\x00\x00\x00\x00\x83\xC4\x04\x83\x3D\x00\x00\x00\x00\x00\xC6\x05\x00\x00\x00\x00\x00\x75\x03", "x????xxxxx????xxx????xxx", 24);
	myClientCmd = (int (__cdecl*)(char*,int))(((unsigned long)execCmd_Sig.sig_addr)-21);
#endif

#if USE_CLIENTCMD == 2
	CSigScan execCmd2_Sig;
	execCmd2_Sig.sigscan_dllfunc = (void *(__cdecl *)(const char *,int *))pEngineClient;
	execCmd2_Sig.GetDllMemInfo();
	EncryptString("\x8B\x4C\x24\x04\x81\xEC\x00\x08\x00\x00\x57\x8B\xF9\x8D\x57\x00\x8A\x07\x47\x84\xC0\x75\x00\x2B\xFA\x85\xFF\x00\x00\x00\x00\x00\x00\x8D\x47\x00\x3D", sA);
	EncryptString("xxxxxxxxxxxxxxx?xxxxxx?xxxx??????xx?x", sB);
	execCmd2_Sig.Init((unsigned char*)sA, sB, 37);
	myClientCmd = (int (__cdecl*)(char*))(((unsigned long)execCmd2_Sig.sig_addr));
#endif

#if USE_CLIENTCMD == 4
	EncryptString("ISERVERPLUGINHELPERS001", sA);
	pPluginHelpers	= (IServerPluginHelpers*)pEngineFactory(sA, 0);
	if (pPluginHelpers == NULL) {
		MessageBox(0, "Nope", "Nope", 0);
	}
#endif

#if USE_CLIENTCMD == 5
	CSigScan execCmd_Sig5;
	execCmd_Sig5.sigscan_dllfunc = (void *(__cdecl *)(const char *,int *))pEngineClient;
	execCmd_Sig5.GetDllMemInfo();
	execCmd_Sig5.Init((unsigned char*)"\x64\xa1\x00\x00\x00\x00\x6a\xff\x68\x00\x00\x00\x00\x50\x64\x89\x25\x00\x00\x00\x00\x83\xec\x08\x55\x8b\x6c\x24\x1c\x8b\xc5\x56\x8d\x50\x01","xx????xxx????xxxx????xxxxxxxxxxxxxx",35);
	myClientCmd = (int (__cdecl*)(char*,int))(((unsigned long)execCmd_Sig5.sig_addr));
#endif

	ptrExecute = (int)myClientCmd;
	//WIPE_END
}

void ClientCmd(CHAR *pCmd)
{

#if USE_CLIENTCMD == 1
	myClientCmd(pCmd, 1);
#endif

#if USE_CLIENTCMD == 2
	myClientCmd(pCmd, 1);
#endif

#if USE_CLIENTCMD == 3
	int object = (int)pEngineClient; //0x42620D54;
	__asm {
		MOV		ECX, object;
		MOV		EAX, DWORD PTR DS:[ECX];
		MOV		EDX, DWORD PTR DS:[EAX+0x188];
		PUSH	pCmd;
		CALL	EDX;
	}
#endif

#if USE_CLIENTCMD == 4
	pPluginHelpers->ClientCommand(pEngineServer->PEntityOfEntIndex(1), pCmd);
#endif

#if USE_CLIENTCMD == 5
	myClientCmd(pCmd, 1);
#endif
}

void SafeClientCommand(CHAR *pCmd)
{
	/*
	CHAR newCmd[NUM_READ_CHARS];
	sprintf(newCmd, "bind \"Q\" \"%s\"", pCmd);
	ClientCmd(newCmd);	//bind to rarely used key

	DWORD myThread = GetCurrentThreadId();
	DWORD newThread = GetWindowThreadProcessId(hWndVindictus, NULL);
	DWORD curThread = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
	AttachThreadInput(myThread, curThread, true);
	AttachThreadInput(curThread, newThread, true);
	AttachThreadInput(myThread, newThread, true);
	PostMessage(hWndVindictus, WM_KEYDOWN, 0x51, 0x00000001 | (LPARAM)(0x51 << 16));
	Sleep(56);
	PostMessage(hWndVindictus, WM_KEYUP, 0x51, 0x00000001 | (LPARAM)(0x51 << 16));
	AttachThreadInput(myThread, newThread, false);
	AttachThreadInput(curThread, newThread, false);
	AttachThreadInput(myThread, curThread, false);

	ClientCmd("unbind \"Q\""); //unbind
	*/
}

void ServerCmd(CHAR *pCmd)
{
	pEngineServer->ClientCommand(pEngineServer->PEntityOfEntIndex(1), pCmd);
}

void SendCommand(char *pCmd)
{
	bool allow = TRUE;
	string sTemp = pCmd;
	string sTemp2;

	if (bAllowCommands || IsOnAllowedList(strtrim(pCmd))) {				//for public hacks
		if (IsOnDisallowedList(strtrim(pCmd))) {
			SetConsoleTextColor(0x4);
			_cwprintf_s(GetResString(103)); //"This command has been disabled.\n"
			SetConsoleTextColor(0x7);
			allow = FALSE;
		}
		if (allow || IsOnAllowedList(strtrim(pCmd))) {
			if (bPluginLoaded) {		//use server command?
				ServerCmd(pCmd);
				//ClientCmd(pCmd);
			} else {					//use client command
				ClientCmd(pCmd);
			}
		}
	} else {
		if (bConReady) {
			SetConsoleTextColor(0x4);
			_cwprintf_s(GetResString(104)); //"Console currently disabled.\n"
			SetConsoleTextColor(0x7);
		}
	}
}

void __stdcall MyMsgPublic(char *pMsg, ... )
{
	/*	let's turn this shit off for now
	va_list va;
	va_start(va, pMsg);
	char buf[NUM_READ_CHARS];
	vsprintf(buf, pMsg, va);
	strtrim(buf);

	va_end(va);
	*/
}

void __stdcall MyMsg(char *pMsg, ... )
{
	va_list va;
	va_start(va, pMsg);
	char buf[NUM_READ_CHARS];
	vsprintf(buf, pMsg, va);
	strtrim(buf);

	SendMsg(buf);
	if (bShowLog) {
		SetConsoleTextColor(0xF);
		if (bConReady) {
			_cprintf_s("%s\n", buf);
		}
		SetConsoleTextColor(0x7);
	} else {
/*		if ((FindInStr(buf, "Unknown command") > 0) && (FindInStr(buf, "con_enable") == 0) && (FindInStr(buf, "stuffcmds") == 0)) {
			SetConsoleTextColor(0xF);
			if (bConReady) {_cprintf_s("%s\n", buf);}
			SetConsoleTextColor(0x7);
		}*/
	}
	
	va_end(va);
}

void __stdcall MyDevMsg(int level, char *pMsg, ... )
{
	va_list va;
	va_start(va, pMsg);
	char buf[NUM_READ_CHARS];
	vsprintf(buf, pMsg, va);
	strtrim(buf);

	//SendDevMsg(buf);
	if (bShowLog) {
		if ((FindInStr(buf, "health") == 0) && (FindInStr(buf, ".break()") == 0) && (FindInStr(buf, "Health") == 0)) {
			SetConsoleTextColor(0x3);
			if (bConReady) {_cprintf_s("%s\n", buf);}
			SetConsoleTextColor(0x7);
		}
	}
	
	va_end(va);
}

void __stdcall MyWarning(char *pMsg, ... )
{
	va_list va;
	va_start(va, pMsg);
	char buf[NUM_READ_CHARS];
	vsprintf(buf, pMsg, va);
	strtrim(buf);
	
	SendWarning(buf);
	if (bShowLog) {
		SetConsoleTextColor(0x4);
		if (bConReady) {_cprintf_s("%s\n", buf);}
		SetConsoleTextColor(0x7);
	}
	
	va_end(va);
}

static SpewRetval_t ZeNewSpewOutput( SpewType_t spewType, const tchar *msg )  
{
	size_t t;
	char c[4096];
	wcstombs(c, (wchar_t*)msg, 4096);
	SendSpew(c);
	if (bShowLog) {
		SetConsoleTextColor(0xD);
		if (bConReady) {_cprintf_s("%s\n", msg);}
		SetConsoleTextColor(0x7);
	}
	return ZeOldSpewOutput(spewType, msg);
}

void HookSpew()
{
	ZeOldSpewOutput = (_GetSpewOutputFunc)();
	(_SpewOutputFunc)(ZeNewSpewOutput);
}

void HookMessages() {
	//MakeJMP((PBYTE)_Msg, (DWORD)MyMsgPublic, 5);
	MakeJMP((PBYTE)_Msg, (DWORD)MyMsg, 5);
	MakeJMP((PBYTE)_DevMsg, (DWORD)MyDevMsg, 5);
	MakeJMP((PBYTE)_Warning, (DWORD)MyWarning, 5);
	HookSpew();
}

ConCommand *Fcmd( char const *name ){
	ConCommandBase *cmd = pCvar->GetCommands();
	for ( ; cmd; cmd = const_cast<ConCommandBase*>(cmd->m_pNext) ){
		if ( !stricmp( name, cmd->GetName() ) ) {
			return (ConCommand*)cmd;
		}
	}
	return NULL;
}

ConCommand *CreateCmd(const char *name,int flags,const char *help, FnCommandCallback callback){
	ConCommand* mCmd = Fcmd("echo");	
	if ( mCmd == NULL ){
		return NULL;
	}
	ConCommand* mNewCmd = (ConCommand*)malloc( sizeof ConCommand);
	memcpy( mNewCmd, mCmd,sizeof( ConCommand ));
	mNewCmd->m_pNext = 0;
	mNewCmd->Create(name,callback,help,flags);
	pCvar->RegisterConCommandBase(mNewCmd);
	return mNewCmd;
}

void MHWalkerOptionsThread(void)
{
	Walker.ShowOptionsWindow(hCurrentModule);
}

void MHWalkerOptions(void)
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MHWalkerOptionsThread, 0, 0, 0);
}

void CreateCustomConCommands(void)
{
	//MHWalker
	CreateCmd("mhwalker_options", FCVAR_NONE, GetResStringA(105), &MHWalkerOptions); //"Displays the MHWalker options window"

	//public
	CreateCmd("useskill", FCVAR_NONE, GetResStringA(106), &useskill); //"Uses a character skill"
	CreateCmd("help", FCVAR_NONE, GetResStringA(107), &help); //"Displays help on custom commands"
	CreateCmd("superloot", FCVAR_NONE, GetResStringA(108), &superloot); //"Picks up 10 items from far away"
	CreateCmd("bombsaway", FCVAR_NONE, GetResStringA(109), &bombsaway); //"Throws 10 bombs very far, very fast"
	CreateCmd("fullsp", FCVAR_NONE, GetResStringA(110), &fullsp); //"Fills you SP bar"
	CreateCmd("nuke", FCVAR_NONE, GetResStringA(111), &nuke); //"Kills all spawned enemies"
	CreateCmd("lua_run", FCVAR_NONE, "Runs a Lua script", &lua_run);
	CreateCmd("lua_info", FCVAR_NONE, "Prints current Lua interpreter info", &lua_info);

	CreateCmd("ohk", FCVAR_NONE, GetResStringA(112), &ohk); //"Enables One-Hit-Kill"
	CreateCmd("god", FCVAR_NONE, GetResStringA(113), &god); //"Enables godmode"
	CreateCmd("godmode", FCVAR_NONE, GetResStringA(113), &god);	//"Enables godmode" //ty Hell_Demon for making this necessary :P

	CreateCmd("disable", FCVAR_NONE, GetResStringA(114), &disable); //"Disables god/ohk/kill2 for the current map"
	//CreateCmd("disable", FCVAR_NONE, GetResStringA(115), &disable); //"Disables god/ohk for the current map"

	//vip
	CreateCmd("docks", FCVAR_NONE, GetResStringA(116), &docks); //"Sends you to the docks"
	CreateCmd("showlog", FCVAR_NONE, GetResStringA(117), &showlog); //"Show Log"
	CreateCmd("hidelog", FCVAR_NONE, GetResStringA(118), &hidelog); //"Hide Log"
	CreateCmd("reloadcmds", FCVAR_NONE, GetResStringA(119), &ReloadLoadCommands); //"Reloads loadcommands.txt"
	CreateCmd("printload", FCVAR_NONE, GetResStringA(120), &printLoadCommands); //"Displays current load commands"
	CreateCmd("spawncmds", FCVAR_NONE, GetResStringA(121), &ToggleSpawnCommands); //"Toggles spawn commands on/off (Default on)"
	CreateCmd("spawncmdsfile", FCVAR_NONE, GetResStringA(122), &SpawnCommandsFile); //"Specifies the file to use as a list of spawn commands"
	CreateCmd("mode", FCVAR_NONE, GetResStringA(123), &mode); //"Sets special mode variables"
	CreateCmd("superember", FCVAR_NONE, GetResStringA(124), &superember); //"Enables/disables super ember mode"
	CreateCmd("SetCursorPos", FCVAR_NONE, GetResStringA(125), &setcursorposcmd); //"Sets the mouse cursor position"
	CreateCmd("MLeft", FCVAR_NONE, GetResStringA(126), &m_left); //"Clicks the left mouse button"

	//do not give out
//	CreateCmd("speedmod", FCVAR_NONE, "Sets player speed", &speedmod);
	CreateCmd("brk", FCVAR_NONE, GetResStringA(127), &brk); //"Break all items"
	CreateCmd("dumpCmds", FCVAR_NONE, GetResStringA(128), &DumpCmds); //"Dumps all commands to dumpcmds.csv"
	CreateCmd("dumpEnts", FCVAR_NONE, GetResStringA(129), &DumpEntities); //"Dumps all entities to dumpents.csv"
	CreateCmd("dumpNetVars", FCVAR_NONE, GetResStringA(143), &dumpNetVars); //"Dumps netvars"
	CreateCmd("kill1", FCVAR_NONE, GetResStringA(130), &kill1); //"Kill all enemies one time"
	CreateCmd("kill2", FCVAR_NONE, GetResStringA(131), &kill2); //"Kill all enemies on spawn"
	CreateCmd("respawnMobs", FCVAR_NONE, GetResStringA(132), &respawn); //"Respawns mobs"
	CreateCmd("respawnBosses", FCVAR_NONE, GetResStringA(133), &respawn2); //"Respawns bosses"
	CreateCmd("killProcess", FCVAR_NONE, GetResStringA(134), &killtimer);  //"Kills a named process"
	CreateCmd("ohk2", FCVAR_NONE, GetResStringA(135), &ohk2); //"Playes does max damage"
	CreateCmd("origin", FCVAR_NONE, GetResStringA(136), &origin); //"Sets current position and rotation"
	CreateCmd("no_ai", FCVAR_NONE, GetResStringA(137), &no_ai); //"Disable enemy AI"
	CreateCmd("thecrazies", FCVAR_NONE, GetResStringA(138), &thecrazies); //"Enemies attack each other"
	CreateCmd("getServerVarPlayer", FCVAR_NONE, GetResStringA(139), &getServerVarPlayer); //"Gets a netvar value"
	CreateCmd("setServerVarPlayer", FCVAR_NONE, GetResStringA(140), &setServerVarPlayer); //"Sets a netvar value"
	CreateCmd("getServerVarNPC", FCVAR_NONE, GetResStringA(139), &getServerVarNPC); //"Gets a netvar value"
	CreateCmd("setServerVarNPC", FCVAR_NONE, GetResStringA(140), &setServerVarNPC); //"Sets a netvar value"
	CreateCmd("getNetVar", FCVAR_NONE, GetResStringA(139), &getNetVar); //"Gets a netvar value"
	CreateCmd("setNetVar", FCVAR_NONE, GetResStringA(140), &setNetVar); //"Sets a netvar value"
	CreateCmd("stam", FCVAR_NONE, GetResStringA(141), &stam); //"Infinite stamina"
	CreateCmd("god2", FCVAR_NONE, GetResStringA(142), &god2); //"Alternative godmode"
	CreateCmd("god2_noevy", FCVAR_NONE, GetResStringA(142), &god2_noevy); //"Alternative godmode"
	CreateCmd("revive", FCVAR_NONE, GetResStringA(144), &ReviveTorch); //"Revives everyone in a specified area"
	CreateCmd("damageMultiplier", FCVAR_NONE, GetResStringA(144), &DamageMultiplier); //"Revives everyone in a specified area"
}

void printThanks(void) {
	_cwprintf_s(GetResString(145)); //"Special Thanks:\n"
	_cwprintf_s(GetResString(146)); //" @"
	SetConsoleTextColor(0xB);
	_cwprintf_s(GetResString(147)); //"Nico"
	SetConsoleTextColor(0x7);
	_cwprintf_s(GetResString(148)); //" (God/OHK and all derivatives)\n"
	_cwprintf_s(GetResString(146)); //" @"
	SetConsoleTextColor(0xB);
	_cwprintf_s(GetResString(149)); //"Hell_Demon"
	SetConsoleTextColor(0x7);
	_cwprintf_s(GetResString(150)); //" (Message Hooks, and more)\n"
	_cwprintf_s(GetResString(146)); //" @"
	SetConsoleTextColor(0xB);
	_cwprintf_s(GetResString(151)); //"DanK"
	SetConsoleTextColor(0x7);
	_cwprintf_s(GetResString(152)); //" (General *s in the >> direction)\n"
}

void SetCheats(ICvar *cvar)
{
	NOP
	ConCommandBase *next = cvar->GetCommands();
	NOP
	while(next != NULL)	{
		NOP
		if(next->IsBitSet(FCVAR_CHEAT))next->m_nFlags &= ~FCVAR_CHEAT;
		NOP
		//if(next->IsBitSet(FCVAR_REPLICATED))next->m_nFlags &= ~FCVAR_REPLICATED;
		NOP
		if(next->IsBitSet(FCVAR_PROTECTED))next->m_nFlags &= ~FCVAR_PROTECTED;
		NOP
	    if(next->IsBitSet(FCVAR_SPONLY))next->m_nFlags &= ~FCVAR_SPONLY;
		NOP
		next = (ConCommandBase*)next->GetNext();
		NOP
	}
	NOP
	cvar->FindVar("sv_cheats")->SetValue(2);
	NOP
	//WIPE_END
	NOP
}

void GetEngineInterfaces(void)
{
	while (hEngineModule == 0)
	{
		hEngineModule = GetModuleHandle("engine.dll"); //Get a handle to the engine dll
	}
	pEngineFactory = (CreateInterfaceFn)GetProcAddress(hEngineModule, "CreateInterface"); //Get the address of the CreateInterface function in engine.dll
	if (pEngineFactory != NULL)
	{
		 pEngineClient	= (IVEngineClient*)pEngineFactory(VENGINE_CLIENT_INTERFACE_VERSION, 0);	//VENGINE_CLIENT_INTERFACE_VERSION is defined as "VEngineClient012"
		 pCvar			= (ICvar*)pEngineFactory(VENGINE_CVAR_INTERFACE_VERSION, 0);			//VENGINE_CVAR_INTERFACE_VERSION is defined as "VEngineCvar003"
		pEngineServer	= (IVEngineServer*)pEngineFactory(INTERFACEVERSION_VENGINESERVER, NULL);								 //INTERFACEVERSION_SERVERGAMEDLL is defined as "ServerGameDLL005"
		INetworkStringTableContainer *pNetworkStrings = (INetworkStringTableContainer *)pEngineFactory(INTERFACENAME_NETWORKSTRINGTABLECLIENT, NULL);
		IPlayerInfoManager *pPlayerInfo = (IPlayerInfoManager*)pEngineFactory(INTERFACEVERSION_PLAYERINFOMANAGER, NULL);
	}
	else
	{
		MessageBox(NULL, "Unable to get CreateInterface from engine.dll", "Console", NULL);
		exit(0);
	}

	InitState = InitState | 1;
}

void GetClientInterfaces(void)
{
	while (hClientModule == 0)
	{
		hClientModule = GetModuleHandle("client.dll"); //Get a handle to the client dll
	}
	pClientFactory = (CreateInterfaceFn)GetProcAddress(hClientModule, "CreateInterface"); //Get the address of the CreateInterface function in client.dll
	if (pClientFactory != NULL)
	{
		 pBaseClient			= (IBaseClientDLL*)pClientFactory(CLIENT_DLL_INTERFACE_VERSION, 0);				//CLIENT_DLL_INTERFACE_VERSION is defined as "VClient013"
		pClientEntityList	= (IClientEntityList*)pClientFactory(VCLIENTENTITYLIST_INTERFACE_VERSION, 0);	//VCLIENTENTITYLIST_INTERFACE_VERSION is defined as "VClientEntityList003"
	}
	else
	{
		MessageBox(NULL, "Unable to get CreateInterface from client.dll", "Console", NULL);
		exit(0);
	}
	InitState = InitState | 2;
}

void GetTier0Interfaces(void)
{
	while (hTier0Module == 0)
	{
		hTier0Module = GetModuleHandle("tier0.dll"); //Get a handle to the tier0 dll
	}
	InitState = InitState | 4;
}

void GetServerInterfaces(void)
{
	while (hServerModule == 0)
	{
		hServerModule = GetModuleHandle("server.dll"); //Get a handle to the server dll
	}
	pServerFactory = (CreateInterfaceFn)GetProcAddress(hServerModule, "CreateInterface"); //Get the address of the CreateInterface function in server.dll
	if (pServerFactory != NULL)
	{
		IServerGameDLL *pServerBase = (IServerGameDLL*)pServerFactory(INTERFACEVERSION_SERVERGAMEDLL, NULL);
	}
	else
	{
		MessageBox(NULL, "Unable to get CreateInterface from server.dll", "Console", NULL);
		exit(0);
	}
	InitState = InitState | 8;
}

void GetVStdInterfaces(void)
{
	while (hVStdlibModule == 0)
	{
		hVStdlibModule = GetModuleHandle("vstdlib.dll"); //Get the handle to the vstdlib dll
	}
	pVStdLibFactory = (CreateInterfaceFn)GetProcAddress(hVStdlibModule, "CreateInterface");
	InitState = InitState | 16;
}

void GetInputInterfaces(void)
{
	while (hInputModule == 0)
	{
		hInputModule = GetModuleHandle("inputsystem.dll");
	}
	pInputFactory = (CreateInterfaceFn)GetProcAddress(hInputModule, "CreateInterface");
	pInput			= (IInputSystem*)pInputFactory(INPUTSYSTEM_INTERFACE_VERSION, 0);
	InitState = InitState | 32;
}

void GetFileSysInterfaces(void)
{
	while (hFileSysModule == 0)
	{
		hFileSysModule = GetModuleHandle("FileSystem_Stdio.dll");
	}
	pFileSysFactory = (CreateInterfaceFn)GetProcAddress(hFileSysModule, "CreateInterface");
	IFileSystem *pFileSystem = (IFileSystem*)pFileSysFactory(FILESYSTEM_INTERFACE_VERSION, NULL);
	InitState = InitState | 64;
}

void GetAllInterfaces(void)
{
	GetEngineInterfaces();
	GetClientInterfaces();
	GetTier0Interfaces();
	GetServerInterfaces();
	GetVStdInterfaces();
	GetInputInterfaces();
	GetFileSysInterfaces();
}

void HackThread(void)
{
	
	//GetAllInterfaces();

	if (ShowMessageBoxes != 0) MessageBox(0, "Getting Spew functions...", "Console", 0);
	Sleep(100);
	// Get the function pointers to Spew functions
	_GetSpewOutputFunc = (GetSpewOutputFuncFn)GetProcAddress(hTier0Module, "GetSpewOutputFunc");
	_SpewOutputFunc = (SpewOutputFuncFn)GetProcAddress(hTier0Module, "SpewOutputFunc");
	_Msg = (MsgFn)GetProcAddress(hTier0Module, "Msg");
	_DevMsg = (DevMsgFn)GetProcAddress(hTier0Module, "DevMsg");
	_Warning = (WarningFn)GetProcAddress(hTier0Module, "Warning");

	//Nullpointer checks
	if(pEngineFactory == NULL || pClientFactory == NULL) //if any of the two function pointers is NULL
	{
		wchar_t b[1000];
		if (pEngineFactory == NULL)
			wcscat(b, L"pEngineFactory\n");
		if (pClientFactory == NULL)
			wcscat(b, L"pClientFactory\n");
		
		//Warn us about it
		MessageBoxW(0, GetResString(153), GetResString(154), MB_OK); //"A CreateInterface pointer was NULL, shutting down!" / "Failure!"
		MessageBoxW(0, b, GetResString(154), MB_OK);
		exit(0); //and exit the game
	}

	pEngineClientVTable = (DWORD*)pEngineClient;

	if(pBaseClient == NULL || pClientEntityList == NULL || pEngineClient == NULL || pCvar == NULL) //if any of the pointers is NULL
	{
		wchar_t b[1000];
		string a = "";
		if (pBaseClient == NULL)
			wcscat(b, L"pBaseClient\n");
		if (pClientEntityList == NULL)
			wcscat(b, L"pBaseEntityList\n");
		if (pEngineClient == NULL)
			wcscat(b, L"pEngineClient\n");
		if (pCvar == NULL)
			wcscat(b, L"pCvar\n");
		//Warn us about it
		MessageBoxW(0, GetResString(155), GetResString(154), MB_OK); //"One of the interface pointers is NULL, shutting down!" / "Failure"
		MessageBoxW(0, b, GetResString(154), MB_OK);
		exit(0); //and exit the game
	}

	hWndVindictus = GetWindow("", "Valve001");
	pRunSpawnCommands = &RunSpawnCommandsCallback;


	if (ShowMessageBoxes != 0) MessageBox(0, "Setting up execution method...", "Console", 0);
	InitClientCmd();
	if (ShowMessageBoxes != 0) MessageBox(0, "Setting up bind fix...", "Console", 0);
	//BindFix();
	if (ShowMessageBoxes != 0) MessageBox(0, "Setting up god/ohk...", "Console", 0);
	InitGodOHK();

	if (ShowMessageBoxes != 0) MessageBox(0, "Setting up SV_CHEATS...", "Console", 0);
	SetCheats(pCvar);
	if (ShowMessageBoxes != 0) MessageBox(0, "Hooking Spew...", "Console", 0);
	HookMessages();

	//Stuff for public console...
/*
	disallowedCommands.push_back("host_writeconfig");	//disable ability to bypass binds
	//make sure can't do any public hacking
	disallowedMaps.push_back("maps/t01.bsp");	//colhen
	disallowedMaps.push_back("maps/t02.bsp");	//rocheste
	disallowedMaps.push_back("maps/f01.bsp");	//temple area
*/
	//commands that are safe for public use
	alwaysAllowedCmds.push_back("cc_shiplist_ui");
	alwaysAllowedCmds.push_back("cc_mailbox_ui");
	alwaysAllowedCmds.push_back("show_mini_shop");
	alwaysAllowedCmds.push_back("close_last_dialog");
	alwaysAllowedCmds.push_back("cc_enter_colhen_from_rochest");
	alwaysAllowedCmds.push_back("cc_enter_rochest_from_colhen");
	alwaysAllowedCmds.push_back("force_state_transition_to_purgetowharf");

	if (ShowMessageBoxes != 0) MessageBox(0, "Creating custom console commands...", "Console", 0);
	CreateCustomConCommands();

	if (ShowMessageBoxes != 0) MessageBox(0, "Starting protection thread...", "Console", 0);
	hPublicThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)PublicProtectionThread, 0, 0, 0);
	Sleep(250);
	if (ShowMessageBoxes != 0) MessageBox(0, "Starting console...", "Console", 0);

	hConThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ConsoleThread, 0, 0, 0);

}

/*
	Function: bool IsGameReady(void)
	Purpose: Checks if the game has loaded the required dll's
	Arguments:
		-
	Returns:
		true if the required dlls are loaded
		false if they aren't
*/

bool IsGameReady(void)
{
	if(	GetModuleHandle("client.dll") &&	//Can we get a handle to client.dll
		GetModuleHandle("engine.dll")		//and engine.dll?
		)
	{
		return true; //we can get handles, so the game is ready
	}
	return false; //we missed 1 or more handles, so the game isn't ready yet!
}

bool IsGamePartiallyReady(void)
{
	if(	GetModuleHandle("client.dll") &&	//Can we get a handle to client.dll
		GetModuleHandle("engine.dll")		//and engine.dll?
		)
	{
		return true; //we can get handles, so the game is ready
	}
	return false; //we missed 1 or more handles, so the game isn't ready yet!
}

int GetNumInHostedParty(void)
{
	if (!pEngineClient->IsInGame()) {
		return 0;
	}
	int num = 0;
	player_info_t info; 
	for(int i = 0; i <= 7; i++) {
		pEngineClient->GetPlayerInfo(i, &info);
		if (&info != NULL) {
			if(strlen(info.name))
			{
				num++;
			}
		}
	}
	return num;
}

string CreateUnbind(string bind)
{
	string unbind;
	int end = bind.find_first_of("\"", bind.find_first_of("\"", 0) + 1);
	unbind = bind.substr(0, end + 1);
	unbind = "un" + unbind;
	return unbind;
}

int RunSpawnCommands(void)
{
	if (bUseSpawnCmds) {
		return ReadSpawnCommands(spawnCommands);
	}
	return 0;
}

void RunSpawnCommandsCallback(void)
{
	RunSpawnCommands();
}

void ReloadLoadCommands(void)
{
	int iLC = ReadLoadCommands(loadCommands);
	string cmd;
	char pCmd[NUM_READ_CHARS];
	for (vector<string>::iterator i = loadCommands.begin(); i != loadCommands.end(); ++i) {
		cmd = *i;
		strcpy(pCmd, cmd.c_str());
		SendCommand(pCmd);
	}
}

void printLoadCommands(void)
{
	_cwprintf_s(GetResString(156), loadCommands.size()); //"Current load command list (%i commands):\n"
	string cmd;
	for (vector<string>::iterator i = loadCommands.begin(); i != loadCommands.end(); ++i) {
		cmd = *i;
		_cprintf_s("  %s\n", cmd.c_str());
	}
}

void attemptDataSend(void)
{
	while (!pEngineClient->IsInGame())
	{
		Sleep(1000);
	}
	//getCurrentDungeon(&DungeonName[0]);
	string s = string(DungeonName);
	SendData1("dun:"+s);
}

void PublicProtectionThread(void)
{
	bool allow = FALSE;
	vector<string>::iterator i, j, k;
	string sTemp;

	while(1) {
		if (pEngineClient->IsInGame()) {							//check player entity initialized
			allow = TRUE;
		}
		//disallows public hacking here
		/*
		if (allow) {
			if (GetNumInHostedParty() > 1) {							//check for public boat
				NOP
				allow = FALSE;
				NOP
			}
		}
		*/
		string map = pEngineClient->GetLevelName();
		if ((map.compare(sCurrentMap) != 0) && (map.compare("") != 0)) {
			if (pEngineClient->IsConnected()) {
				sCurrentMap = map;
				SendData1("map:"+sCurrentMap);
				CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)attemptDataSend, NULL, NULL, NULL);
				bCanNuke = true;

				if (!bPluginLoaded) {
					RunSpawnCommands();
				}
			}
		}
		if (IsPublicMap()) {
			allow = FALSE;
		}
		if ((bAllowCommands) && (!allow)) {
			string cmd;
			char pCmd[NUM_READ_CHARS];
			//first time through unbind everything
			for (vector<string>::iterator i = unbinds.begin(); i != unbinds.end(); ++i) {
				cmd = *i;
				strcpy(pCmd, cmd.c_str());
				SendCommand(pCmd);
			}
			if (bConReady) {
				_cwprintf_s(GetResString(157)); //"Console "
				SetConsoleTextColor(0x4);
				_cwprintf_s(GetResString(158)); //"Disabled"
				SetConsoleTextColor(0x7);
				_cwprintf_s(GetResString(159)); //".\n"
				_cwprintf_s(GetResString(160), sCurrentMap); //"Current map: %s\n"
			}
			//SendCommand("host_timescale 1");
			bAllowCommands = FALSE;
			SetProgramIconRed(hCurrentModule);
		} 
		if ((!bAllowCommands) && (allow)) {
			bAllowCommands = TRUE;
			string cmd;
			char pCmd[NUM_READ_CHARS];
			//first time through, rebind everything
			for (vector<string>::iterator i = binds.begin(); i != binds.end(); ++i) {
				cmd = *i;
				strcpy(pCmd, cmd.c_str());
				SendCommand(pCmd);
			}
			if (bReady) {
				if (bConReady) {
					_cwprintf_s(GetResString(157)); //"Console "
					SetConsoleTextColor(0xA);
					_cwprintf_s(GetResString(161)); //"Enabled"
					SetConsoleTextColor(0x7);
					_cwprintf_s(GetResString(159)); //".\n"
					_cwprintf_s(GetResString(160), sCurrentMap); //"Current map: %s\n"
				}
			} else {
				bReady = TRUE;
			}
			SetProgramIconBlue(hCurrentModule);
		}

		Sleep(100);
	}
}

void SetupIcons(HMODULE hModule)
{
	hIcon1 = (HICON)LoadImage(hModule, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, LR_DEFAULTSIZE);
	hIcon2 = (HICON)LoadImage(hModule, MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 16, 16, LR_DEFAULTSIZE);
	hWndConsole = GetWindow("l2noob2", "ConsoleWindowClass");
}

void SetProgramIconBlue(HMODULE hModule)
{
	SendMessage(hWndConsole, WM_SETICON, ICON_SMALL, (LPARAM)hIcon1);
}

void SetProgramIconRed(HMODULE hModule)
{
	SendMessage(hWndConsole, WM_SETICON, ICON_SMALL, (LPARAM)hIcon2);
}

void ExternalCommandThread(void)
{
	_cwprintf_s(GetResString(162)); //"MHWalker process link intializing..."

	char cTempDir[1024];
	string sTempDir = getenv("TEMP");
	ExpandEnvironmentStrings(sTempDir.c_str(), cTempDir, 1024);
	strcat(cTempDir, string_CMDFILE);
	sTempDir = cTempDir;

	char me[1024];
	char buffer[1024];

	SetConsoleTextColor(0xA);
	_cwprintf_s(GetResString(163)); //" Done!\n"
	SetConsoleTextColor(0x7);

	while(1) {
		int lines = 0;

		ifstream fLC(sTempDir.c_str());

		if (fLC.good()) {
			lines = 0;
			while (!fLC.eof()) {
				fLC.getline(buffer, 1024);
				if (strcmp(buffer, "") != 0) {
					SendCommand(buffer);
					lines++;
				}
			}
			fLC.close();
			remove(sTempDir.c_str());
		}
		Sleep(250);
	}
}

void ProcessCommand (char *pCmd)
{
	string cmd = pCmd;
	tolowers(cmd);
	if (cmd.find("bind ") == 0) {
		//we have a bind
		binds.push_back(cmd);						//always push the bind
		if (!IsOnAllowedList(pCmd)) {
			unbinds.push_back(CreateUnbind(cmd));	//if not on allowed list, then push the unbind
		}
	}
	if (cmd.find("unbind ") == 0) {
		//we have an ubind
		binds.push_back(cmd);						//always push the manual unbind
	}
}

void ConsoleThread(void)
{
	HWND iHwnd;
	do {
		iHwnd = GetWindow("Vindictus", "Valve001");
		Sleep(100);
	} while (iHwnd == 0);

	char title[256];
	GetWindowText(iHwnd, title, 256);
	string sTitle = title;

	string cmd;
	char first4[4];
	char sWindowName[50];
	gen_random(sWindowName, 50);
	wchar_t name[80];
	wcscpy(name, GetResString(169)); //"MHSuperman [Private Edition] v"
	wcscat(name, OFFTHERECORD_VERSION);
	wcscat(name, GetResString(167)); //" by [MPGH]'s l2noob2"
	CreateConsole(GetResString(170), name); //"MHSuperman [Private Edition] by l2noob2"
	SetProgramIconBlue(hCurrentModule);

	SetConsoleTextColor(0x4);
	_cprintf_s("THIS VERSION IS NOT TO BE SHARED!\n");
	_cprintf_s("THIS CONSOLE DOES NOT EXIST, AND I WAS NEVER HERE!\n");
	SetConsoleTextColor(0x7);
	_cprintf_s("Copyright (c) 2011-2013 L2Noob2 LLC., ALL RIGHTS RESERVED\n");

	//printThanks();
	SetConsoleTextColor(0xC);
	//_cprintf_s("This console should never be seen on elitepvpers (leecher central).\n");
	//_cprintf_s("This console can only be found on MPGH.net.\n");
	SetConsoleTextColor(0x7);

	_cprintf_s("Waiting for engine to become ready...");
	while(!IsGameReady()) {
		Sleep(100);
	}
	SetConsoleTextColor(0xA);
	_cprintf_s(" Ready\n");
	SetConsoleTextColor(0x7);

	_cprintf_s("%s", "Waiting for client to become ready...");
	while(!bAllowCommands) {
		Sleep(100);
	}
	SetConsoleTextColor(0xA);
	_cprintf_s(" Ready\n");
	SetConsoleTextColor(0x7);

	_cprintf_s("%s", "Waiting for Lua script manager to initialize...");
	//lVM = lua_open(0);

	/*if (lVM == NULL) {
		SetConsoleTextColor(0x4);
		_cprintf_s("%s", "Error!\n");
		SetConsoleTextColor(0x7);
	} else {*/
		//lua_baselibopen(lVM);
		//luaopen_table(lVM);
		//luaopen_io(lVM);
		//luaopen_string(lVM);
		//luaopen_math(lVM);
		SetConsoleTextColor(0xA);
		_cprintf_s("%s", "Done!\n");
		SetConsoleTextColor(0x7);
	//}
	//before applying load commands, we need to manually run a host_writeconfig, sorry Pie :(

	//Pipes...
	_cprintf_s("%s", "Waiting for process-interlink to initialize...");
	InitPipes();
	SetConsoleTextColor(0xA);
	_cprintf_s("%s", "Done!\n");
	SetConsoleTextColor(0x7);

		
	ClientCmd("host_writeconfig\n");
	//PieBinds has now been cleared out, proceed as normal
	_cprintf_s("Applying load command list...");
	int iLC = ReadLoadCommands(loadCommands);

	char pCmd[255];
	for (vector<string>::iterator i = loadCommands.begin(); i != loadCommands.end(); ++i) {
		cmd = *i;
		strcpy(pCmd, cmd.c_str());
		ProcessCommand(pCmd);
		SendCommand(pCmd);
	}
	SetConsoleTextColor(0xA);
	_cprintf_s(" Done!");
	SetConsoleTextColor(0x7);
	_cprintf_s(" (Processed %i commands)\n", iLC);

	spawnCommandsFilename = "spawncommands.txt";
	_cprintf_s("Applying spawn command list...");
	iLC = RunSpawnCommands();
	SetConsoleTextColor(0xA);
	_cprintf_s(" Done!");
	SetConsoleTextColor(0x7);
	_cprintf_s(" (Processed %i commands)\n", iLC);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ExternalCommandThread, 0, 0, 0);
	Sleep(1000);
	//EnhanceFix();
	_cprintf_s("Initilization complete. Console ready!\n\n");
/*
	_cprintf_s("Enter the command ");
	SetConsoleTextColor(0xF);
	_cprintf_s("help");
	SetConsoleTextColor(0x7);
	_cprintf_s(" for a list of custom commands."); 
*/
	bConReady = TRUE;

	//MHWalker	Walker;
	//Walker.ShowOptionsWindow(iHwnd);
	//FastPixel	Pixel;
	//Pixel.GetScreen(iHwnd);
	//Pixel.SaveBitmap(L"C:\\test.bmp");
	//_cprintf_s("0x%x\n", Pixel.fastPixelGetColor(100, 100));
	//CreateLuaMachine("auto2.lua", 0, 1);

	HANDLE hstdi = GetStdHandle(STD_INPUT_HANDLE);
	char command[NUM_READ_CHARS];
	DWORD charsRead;
	while(ReadConsole(hstdi, &command, NUM_READ_CHARS, &charsRead, 0)) {
		if (strcmp(strtrim(command), "killconsole") == 0) {
			bTermCon = TRUE;
			FreeConsole();
			break;
		}
		ProcessCommand(command);
		SendCommand(command);
		memset(command, 0, NUM_READ_CHARS);
	}
}

void Ping(void)
{
	SendData1("map:"+sCurrentMap);
}
