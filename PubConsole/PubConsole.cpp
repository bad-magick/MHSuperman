// PubConsole.cpp : Defines the exported functions for the DLL application.
//
#include "interface.h"
#include "icvar.h"
#include "cdll_int.h"
#include "eiface.h"
#undef ARRAYSIZE
#include "stdafx.h"
//#include <Windows.h>
#include <direct.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <io.h>
#include "SigScan.h"

#define NOP __asm {nop}

using namespace std;

HMODULE hCurrentModule;
HANDLE	hCurrentProcess;
HMODULE				hEngineModule, hClientModule, hServerModule, hVStdlibModule, hInputModule; //module handles
CreateInterfaceFn	pEngineFactory, pClientFactory, pServerFactory, pServerGame, pInputFactory;   //CreateInterface function pointers
IBaseClientDLL				*pBaseClient		= NULL;		//a pointer to the IBaseClientDLL interface, initialized as NULL
IVEngineClient				*pEngineClient		= NULL;		//a pointer to the IVEngineClient interface, initialized as NULL
//IClientEntityList			*pClientEntityList	= NULL;		//a pointer to the IClientEntityList interface, initialized as NULL
ICvar						*pCvar				= NULL;		//a pointer to the ICvar interface, initialized as NULL
IVEngineServer				*pEngineServer		= NULL;

vector<string>	disallowedCommands;
vector<string>	disallowedMaps;
vector<string>	alwaysAllowedCmds;
vector<string>	binds;
vector<string>	unbinds;

string	sCurrentMap;

bool	bCanNuke = true;
bool	bAllowCommands = false;

int (__cdecl *myClientCmd)(char *a1, int a2) = (int (__cdecl *)(char *a1, int a2))0x4204BAD0;
CBaseEntity *(__cdecl *myCreateEntityByName)( const char *className, int iForceEdictIndex) = NULL;
int (__cdecl *myDispatchSpawn)( CBaseEntity *pEntity ) = NULL;

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
	//VirtualFree(pBaseAddr,4096,MEM_DECOMMIT);
}

void HideModule(HINSTANCE hModule)
{
        DWORD dwPEB_LDR_DATA = 0;
        _asm
        {
        pushad;
        pushfd;
        mov eax, fs:[30h];
        mov eax, [eax+0Ch];
        mov dwPEB_LDR_DATA, eax;
        mov esi, [eax+0Ch];
        mov edx, [eax+10h];
        LoopInLoadOrderModuleList:
                lodsd;
                mov esi, eax;
                mov ecx, [eax+18h];
                cmp ecx, hModule;
                jne SkipA
                mov ebx, [eax]
                mov ecx, [eax+4]
                mov [ecx], ebx
                mov [ebx+4], ecx
                jmp InMemoryOrderModuleList
        SkipA:
                cmp edx, esi
                jne LoopInLoadOrderModuleList
InMemoryOrderModuleList:
        mov eax, dwPEB_LDR_DATA
        mov esi, [eax+14h]
        mov edx, [eax+18h]
        LoopInMemoryOrderModuleList:
                lodsd
                mov esi, eax
                mov ecx, [eax+10h]
                cmp ecx, hModule
                jne SkipB
                mov ebx, [eax]
                mov ecx, [eax+4]
                mov [ecx], ebx
                mov [ebx+4], ecx
                jmp InInitializationOrderModuleList
        SkipB:
                cmp edx, esi
                jne LoopInMemoryOrderModuleList
InInitializationOrderModuleList:
        mov eax, dwPEB_LDR_DATA
        mov esi, [eax+1Ch]
        mov edx, [eax+20h]
        LoopInInitializationOrderModuleList:
                lodsd
                mov esi, eax      
                mov ecx, [eax+08h]
                cmp ecx, hModule      
                jne SkipC
                mov ebx, [eax]
                mov ecx, [eax+4]
                mov [ecx], ebx
                mov [ebx+4], ecx
                jmp Finished
        SkipC:
                cmp edx, esi
                jne LoopInInitializationOrderModuleList
        Finished:
                popfd;
                popad;
        }
}

char *ltrim(char *s)
{
	NOP
    while(isspace(*s)) s++;
	NOP
    return s;
	NOP
}

char *rtrim(char *s)
{
	NOP
    char* back = s + strlen(s);
	NOP
    while(isspace(*--back));
	NOP
    *(back+1) = '\0';
	NOP
    return s;
	NOP
}

char *strtrim(char *s)
{
	NOP
    return rtrim(ltrim(s)); 
}

std::string tolowers(std::string str)
{
	NOP
    for (DWORD i=0;i<strlen(str.c_str());i++) {
		NOP
        if (str[i] >= 0x41 && str[i] <= 0x5A) {
			NOP
            str[i] = str[i] + 0x20;
		}
		NOP
	}
	NOP
    return str;
	NOP
}

bool IsGameReady(void)
{
	NOP
	if(	GetModuleHandle("client.dll") &&	//Can we get a handle to client.dll
		GetModuleHandle("engine.dll")		//and engine.dll?
		)
	{
		NOP
		return true;
	} else {
		NOP
		return false;
	}
	NOP
}

string CreateUnbind(string bind)
{
	NOP
	string unbind;
	NOP
	int end = bind.find_first_of("\"", bind.find_first_of("\"", 0) + 1);
	NOP
	unbind = bind.substr(0, end + 1);
	NOP
	unbind = "un" + unbind;
	NOP
	return unbind;
	NOP
}

bool IsOnAllowedList(char* pCmd)
{
	NOP
	string sTemp = pCmd;
	NOP
	sTemp = tolowers(sTemp);
	NOP
	string sTemp2;
	NOP
	for (vector<string>::iterator i = alwaysAllowedCmds.begin(); i != alwaysAllowedCmds.end(); ++i) {
		NOP
		sTemp2 = *i;
		NOP
		sTemp2 = tolowers(sTemp2);
		NOP
		if (sTemp.find(sTemp2) != string::npos) {
			NOP
			return true;
			NOP
		}
		NOP
	}
	NOP
	return false;
	NOP
}

bool IsOnDisallowedList(char* pCmd)
{
	NOP
	string sTemp = pCmd;
	NOP
	sTemp = tolowers(sTemp);
	NOP
	string sTemp2;
	NOP
	for (vector<string>::iterator i = disallowedCommands.begin(); i != disallowedCommands.end(); ++i) {
		NOP
		sTemp2 = *i;
		NOP
		sTemp2 = tolowers(sTemp2);
		NOP
		if (sTemp.find(sTemp2) != string::npos) {
			NOP
			return true;
			NOP
		}
	NOP
	}
	NOP
	return false;
	NOP
}

int GetNumInHostedParty(void)
{
	NOP
	if (!pEngineClient->IsInGame()) {
		NOP
		return 0;
		NOP
	}
	NOP
	int num = 0;
	NOP
	player_info_t info; 
	NOP
	for(int i = 0; i <= 7; i++) {
		NOP
		pEngineClient->GetPlayerInfo(i, &info);
		NOP
		if (&info != NULL) {
			NOP
			if(strlen(info.name)) num++;
			NOP
		}
		NOP
	}
	NOP
	return num;
	NOP
}

bool IsPublicMap(void)
{
	NOP
	string sTemp;
	NOP
	for (vector<string>::iterator i = disallowedMaps.begin(); i != disallowedMaps.end(); ++i) {		//check for disallowed map
		NOP
		sTemp = *i;
		NOP
		if (sCurrentMap.compare(sTemp) == 0) {
			NOP
			return true;
			NOP
		}
		NOP
	}
	NOP
	return false;
	NOP
}

void SendCommand(char *pCmd)
{
	NOP
	bool allow = TRUE;
	NOP
	string sTemp = pCmd;
	NOP
	string sTemp2;
	NOP

	NOP
	if (bAllowCommands || IsOnAllowedList(strtrim(pCmd))) {				//for public hacks
		NOP
		if (IsOnDisallowedList(strtrim(pCmd))) {
			NOP
			allow = FALSE;
			NOP
		}
		NOP
		if (allow || IsOnAllowedList(strtrim(pCmd))) {
			NOP
			myClientCmd(pCmd, 1);
			NOP
		}
		NOP
	}
	NOP
}
ConCommand *Fcmd( char const *name ){
	NOP
	ConCommandBase *cmd = pCvar->GetCommands();
	NOP
	for ( ; cmd; cmd = const_cast<ConCommandBase*>(cmd->m_pNext) ){
		NOP
		if ( !stricmp( name, cmd->GetName() ) )
			NOP
			return (ConCommand*)cmd;	
			NOP
	}
	NOP
	return NULL;
	NOP
}

ConCommand *CreateCmd(const char *name,int flags,const char *help, FnCommandCallback callback){
	NOP
	ConCommand* mCmd = Fcmd("echo");	
	NOP
	if ( mCmd == NULL ){return NULL;}
	NOP
	ConCommand* mNewCmd = (ConCommand*)malloc( sizeof ConCommand);
	NOP
	memcpy( mNewCmd, mCmd,sizeof( ConCommand ));
	NOP
	mNewCmd->m_pNext = 0;
	NOP
	mNewCmd->Create(name,callback,help,flags);
	NOP
	pCvar->RegisterConCommandBase(mNewCmd);
	NOP
	return mNewCmd;
	NOP
}

bool __stdcall SetKeyValue(CBaseEntity *pEnt, const char *szKeyName, const char *szValue )
{
	__asm
	{
		nop
		pushad;
		nop
		push szValue;
		nop
		push szKeyName;
		nop
		pushad;
		nop
		popad;
		nop
		mov ESI, DWORD PTR DS:[pEnt]; //EAX now holds the VTable address
		nop
        mov EAX, [ESI];
		nop
		pushad;
		nop
		popad;
		nop
		add EAX, 0x88;				//index 0x22 in the vtable
		nop
		mov ECX, pEnt;
		nop
		call [EAX];
		nop
		pushad;
		nop
		popad;
		nop
		popad;
		nop
	}
}

void nuke(void)
{
	NOP
	if (bCanNuke) {
		NOP
		bCanNuke = false;
		NOP
		CBaseEntity *timer = myCreateEntityByName("logic_timer",-1);
		NOP
		SetKeyValue(timer,"startdisabled","0");
		NOP
		SetKeyValue(timer,"refiretime","0.1");
		NOP
		SetKeyValue(timer,"OnTimer","*,sethealth,0");
		NOP
		SetKeyValue(timer,"OnTimer","!self,kill,,0.01");
		NOP
		myDispatchSpawn(timer);
		NOP
	}
	NOP
}

void PublicProtectionThread(void)
{
	NOP
	bool allow = FALSE;
	NOP
	vector<string>::iterator i, j, k;
	NOP
	string sTemp;
	NOP

	NOP
	while(1) {
		NOP
		if (pEngineClient->IsInGame()) {							//check player entity initialized
			NOP
			allow = TRUE;
			NOP
		}
		NOP
		if (GetNumInHostedParty() > 1) {							//check for public boat
			NOP
			allow = FALSE;
			NOP
		}
		NOP
		string map = pEngineClient->GetLevelName();
		NOP
		if ((map.compare(sCurrentMap) != 0) && (map.compare("") != 0)) {
			NOP
			if (pEngineClient->IsConnected()) {
				NOP
				sCurrentMap = map;
				NOP
				bCanNuke = true;
				NOP
			}
			NOP
		}
		NOP
		if (IsPublicMap()) {
			NOP
			allow = FALSE;
			NOP
		}
		NOP
		if ((bAllowCommands) && (!allow)) {
			NOP
			string cmd;
			NOP
			char pCmd[1024];
			NOP
			//first time through unbind everything
			NOP
			for (vector<string>::iterator i = unbinds.begin(); i != unbinds.end(); ++i) {
				NOP
				cmd = *i;
				NOP
				strcpy(pCmd, cmd.c_str());
				NOP
				SendCommand(pCmd);
				NOP
			}
			NOP
			//SendCommand("host_timescale 1");
			NOP
			bAllowCommands = FALSE;
			NOP
		} 
		NOP
		if ((!bAllowCommands) && (allow)) {
			NOP
			bAllowCommands = TRUE;
			NOP
			string cmd;
			NOP
			char pCmd[1024];
			NOP
			//first time through, rebind everything
			NOP
			for (vector<string>::iterator i = binds.begin(); i != binds.end(); ++i) {
				NOP
				cmd = *i;
				NOP
				strcpy(pCmd, cmd.c_str());
				NOP
				SendCommand(pCmd);
				NOP
			}
			NOP
		}
		NOP

		NOP
		Sleep(100);
		NOP
	}
	NOP
}

void ProcessCommand (char *pCmd)
{
	NOP
	string cmd = pCmd;
	NOP
	tolowers(cmd);
	NOP
	if (cmd.find("bind ") == 0) {
		NOP
		//we have a bind
		NOP
		binds.push_back(cmd);						//always push the bind
		NOP
		if (!IsOnAllowedList(pCmd)) {
			NOP
			unbinds.push_back(CreateUnbind(cmd));	//if not on allowed list, then push the unbind
			NOP
		}
		NOP
	}
	NOP
	if (cmd.find("unbind ") == 0) {
		NOP
		//we have an ubind
		NOP
		binds.push_back(cmd);						//always push the manual unbind
		NOP
	}
	NOP
}

void ConsoleThread(void)
{
	NOP
	stdout->_file=_open_osfhandle((intptr_t)GetStdHandle(STD_OUTPUT_HANDLE),0);

	NOP
	HANDLE hstdi = GetStdHandle(STD_INPUT_HANDLE);
	NOP
	char command[1024];
	NOP
	DWORD charsRead;
	NOP
	while(ReadConsole(hstdi, &command, 1024, &charsRead, 0))
	{
		NOP
		ProcessCommand(command);
		NOP
		SendCommand(command);
		NOP
		memset(command, 0, 1024);
		NOP
	}
	NOP
}

void HackThread(void)
{
	NOP
	//ErasePEHeaderFromMemory(hCurrentModule);
	NOP
	while(!IsGameReady()) {
		NOP
		Sleep(100);
		NOP
	}
	NOP
	hEngineModule = GetModuleHandle("engine.DLL"); //Get a handle to the engine dll
	NOP
	hClientModule = GetModuleHandle("client.DLL"); //Get a handle to the client dll
	NOP
	hServerModule = GetModuleHandle("server.DLL"); //Get a handle to the server dll
	NOP

	NOP
	pEngineFactory = (CreateInterfaceFn)GetProcAddress(hEngineModule, "CreateInterface"); //Get the address of the CreateInterface function in engine.dll
	NOP
	pClientFactory = (CreateInterfaceFn)GetProcAddress(hClientModule, "CreateInterface"); //Get the address of the CreateInterface function in client.dll
	NOP
	pServerFactory = (CreateInterfaceFn)GetProcAddress(hServerModule, "CreateInterface"); //Get the address of the CreateInterface function in server.dll
	NOP

	NOP
	pBaseClient			= (IBaseClientDLL*)pClientFactory(CLIENT_DLL_INTERFACE_VERSION, 0);				//CLIENT_DLL_INTERFACE_VERSION is defined as "VClient013"
	NOP

	NOP
	pEngineClient	= (IVEngineClient*)pEngineFactory(VENGINE_CLIENT_INTERFACE_VERSION, 0);	//VENGINE_CLIENT_INTERFACE_VERSION is defined as "VEngineClient012"
	NOP
	pCvar			= (ICvar*)pEngineFactory(VENGINE_CVAR_INTERFACE_VERSION, 0);			//VENGINE_CVAR_INTERFACE_VERSION is defined as "VEngineCvar003"
	NOP

	NOP
	pEngineServer	= (IVEngineServer*)pEngineFactory(INTERFACEVERSION_VENGINESERVER, 0);								 //INTERFACEVERSION_SERVERGAMEDLL is defined as "ServerGameDLL005"
	NOP

	NOP
	disallowedCommands.push_back("host_writeconfig");	//disable ability to bypass binds
	NOP
	//make sure can't do any public hacking
	NOP
	disallowedMaps.push_back("maps/t01.bsp");	//colhen
	NOP
	disallowedMaps.push_back("maps/t02.bsp");	//rocheste
	NOP
	disallowedMaps.push_back("maps/f01.bsp");	//temple area
	NOP

	NOP
	//commands that are safe for public use
	NOP
	alwaysAllowedCmds.push_back("cc_shiplist_ui");
	NOP
	alwaysAllowedCmds.push_back("cc_mailbox_ui");
	NOP
	alwaysAllowedCmds.push_back("show_mini_shop");
	NOP
	alwaysAllowedCmds.push_back("close_last_dialog");
	NOP
	alwaysAllowedCmds.push_back("cc_enter_colhen_from_rochest");
	NOP
	alwaysAllowedCmds.push_back("cc_enter_rochest_from_colhen");
	NOP
	alwaysAllowedCmds.push_back("force_state_transition_to_purgetowharf");
	NOP

	NOP
	CSigScan execCmd_Sig;
	NOP
	execCmd_Sig.sigscan_dllfunc = (void *(__cdecl *)(const char *,int *))pEngineClient;
	NOP
	execCmd_Sig.GetDllMemInfo();
	NOP
	execCmd_Sig.Init((unsigned char*)"\xE8\x00\x00\x00\x00\x83\xC4\x04\x83\x3D\x00\x00\x00\x00\x00\xC6\x05\x00\x00\x00\x00\x00\x75\x03", "x????xxxxx????xxx????xxx", 24);
	NOP
	myClientCmd = (int (__cdecl*)(char*,int))(((unsigned long)execCmd_Sig.sig_addr)-21);
	NOP

	NOP
	CSigScan cssBindFix;
	NOP
	cssBindFix.sigscan_dllfunc = (void *(__cdecl *)(const char *,int *))pEngineClient;
	NOP
	cssBindFix.GetDllMemInfo();
	NOP
	cssBindFix.Init((unsigned char*)"\x33\xFF\x5B\x85\xF6\x74\x00\x8B\x00\x00\x00\x51\x56\xE8\x00\x00\x00\x00\x83\xC4\x00\x85\xC0\x75", "xxxxxx?x???xxx????xx?xxx", 24);
	NOP
	unsigned char *ptr = (unsigned char*)(((unsigned long)cssBindFix.sig_addr) + 24);
	NOP
	DWORD dwOld;
	NOP
	VirtualProtect(ptr, 1, PAGE_EXECUTE_READWRITE, &dwOld);
	NOP
	*ptr = 0x00;
	NOP
	VirtualProtect(ptr, 1, dwOld, &dwOld);
	NOP

	NOP
	CSigScan CEBN;
	NOP
	CSigScan DS;
	NOP
	CSigScan::sigscan_dllfunc = pServerFactory;
	NOP
	CSigScan::GetDllMemInfo();
	NOP
	CEBN.Init((unsigned char*)"\x56\x8b\x74\x24\x0c\x57\x8b\x7c\x24\x0c\x83\xfe\xff\x74\x27\x8b\x0d\xc8\x29\x99\x40\x8b\x01\x8b\x50\x54\x56\xff\xd2\xa3\x54\x69","xxxxxxxxxxxxxxxxx????xxxxxxxxx??",32);
	NOP
	DS.Init((unsigned char*)"\x53\x55\x56\x8b\x74\x24\x10\x57\x85\xf6\x0f\x84\x43\x01\x00\x00\x8b\x1d\x04\x2a\x99\x40\x8b\x03\x8b\x50\x60\x8b\xcb\xff\xd2\x8b","xxxxxxxxxxxxxxxxxx????xxxxxxxxxx",32);
	NOP
	if(CEBN.is_set&&DS.is_set)
	NOP
	{
		NOP
		myCreateEntityByName = (CBaseEntity *(__cdecl *)(const char*, int))CEBN.sig_addr;
		NOP
		myDispatchSpawn = (int(__cdecl *)(CBaseEntity*))DS.sig_addr;
		NOP
	}
	NOP

	NOP
	CreateCmd("nuke", FCVAR_NONE, "", &nuke);
	NOP

	NOP

	NOP
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)PublicProtectionThread, 0, 0, 0);
	NOP

	AllocConsole();
	NOP

	DWORD conMode;
	NOP
	SetConsoleTitleA("PubConsole v1.06 by [MPGH]'s l2noob2");
	NOP
	HANDLE lStdHandle = GetStdHandle(STD_INPUT_HANDLE);
	NOP
	HANDLE lOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	NOP
	GetConsoleMode(lStdHandle, &conMode);
	NOP
	DWORD conNewMode = ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT;
	NOP
	SetConsoleMode(lStdHandle, conNewMode);
	NOP
	SetConsoleTextAttribute(lOutHandle, 0xF);
	NOP
	_cprintf_s("Welcome to PubConsole!\n");
	NOP
	SetConsoleTextAttribute(lOutHandle, 0x7);
	NOP
	_cprintf_s("Copyright (c) 2011-2012 L2Noob2 LLC., ALL RIGHTS RESERVED\n");
	NOP
	SetConsoleTextAttribute(lOutHandle, 0xC);
	NOP
	_cprintf_s("This console should never be seen on elitepvpers (leecher central).\n");
	NOP
	_cprintf_s("This console can only be found on MPGH.net.\n");
	NOP
	SetConsoleTextAttribute(lOutHandle, 0x7);
	NOP

	NOP
	_cprintf_s("Waiting for engine to become ready...");
	NOP
	while(!IsGameReady()) {
	NOP
		Sleep(100);
	NOP
	}
	NOP
	SetConsoleTextAttribute(lOutHandle, 0xA);
	NOP
	_cprintf_s(" Ready\n");
	NOP
	SetConsoleTextAttribute(lOutHandle, 0x7);
	NOP

	NOP
	_cprintf_s("%s", "Waiting for client to become ready...");
	NOP

	NOP
	while (!bAllowCommands) {Sleep(100);}
	NOP
	SetConsoleTextAttribute(lOutHandle, 0xA);
	NOP
	_cprintf_s(" Ready\n");
	NOP
	SetConsoleTextAttribute(lOutHandle, 0x7);
	NOP
	_cprintf_s("\n");
	NOP
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ConsoleThread, 0, 0, 0);
	NOP
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	NOP
	switch(dwReason) //'switch' to dwReason, could use if's instead
	{
	case DLL_PROCESS_ATTACH: //we 'attached' to the process
		NOP
		DisableThreadLibraryCalls(hModule); //Disable calls to dllmain for DLL_THREAD_ATTACH and DLL_THREAD_DETACH
		NOP
		hCurrentModule = hModule;
		NOP
		HideModule(hCurrentModule);
		NOP
		ErasePEHeaderFromMemory(hCurrentModule);
		NOP
		MessageBox(0, "Loaded", "Loaded", 0);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HackThread, 0, 0, 0);
		NOP
		break; //break out of the switch statement
	NOP
	}
	NOP
	return TRUE; //success
	NOP
}
