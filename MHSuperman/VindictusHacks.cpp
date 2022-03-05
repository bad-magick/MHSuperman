#include <windows.h> //windows header
#include <Psapi.h>
#include <io.h>
#include <WinCon.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <direct.h>
#include <StdAfx.h>
#include "sdk.h" //contains the sdk headers that we'll be using.
#include "sigscan.h"
#include "Console.h"
#include "NetVarDump.h"


using namespace std;

//Define Strings
#define string_CMDFILE			"\\a8dc570da319.tmp"
#define string_KILL2			"asdfkj23"

#define PUBLIC_VERSION			"1.00"
#define PRIVATE_VERSION			"1.00"
#define OFFTHERECORD_VERSION	"1.00"


#define GODOHK			//defines God/OHK support

#define OFFTHERECORD	//defines Off-The-Record Edition

#define PUBLIC			//defines Public Edition
#undef PUBLIC			//defines Private Edition

#ifdef OFFTHERECORD		//ensures Public Edition takes higher prescedience than Off-The-Record Edition
#ifdef PUBLIC
#undef OFFTHERECORD
#endif
#endif

#ifndef PUBLIC			//esnures God/OHK always available in Private Edition
#ifndef GODOHK
#define GODOHK
#endif
#endif

#define OFF_FILL 0xEC0E9

/**************************
**	Forward Declarations **
**	and global variables **
**************************/
void HackThread(void);
bool IsGameReady(void);
void ConsoleThread(void);

typedef SpewOutputFunc_t (__cdecl *GetSpewOutputFuncFn)();
typedef void (__cdecl *SpewOutputFuncFn)( SpewOutputFunc_t func );
typedef void (__stdcall *MsgFn)( char *pMsg, ... );
typedef void (__stdcall *DevMsgFn)( int level, char *pMsg, ... );
typedef void (__stdcall *WarningFn)( char *pMsg, ... );

HANDLE				hCurrentProcess;

HMODULE				hEngineModule, hClientModule, hTier0Module, hServerModule, hVStdlibModule, hInputModule; //module handles
CreateInterfaceFn	pEngineFactory, pClientFactory, pServerFactory, pServerGame, pInputFactory;   //CreateInterface function pointers


IBaseClientDLL		*pBaseClient		= NULL;		//a pointer to the IBaseClientDLL interface, initialized as NULL
IVEngineClient		*pEngineClient		= NULL;		//a pointer to the IVEngineClient interface, initialized as NULL
IClientEntityList	*pClientEntityList	= NULL;		//a pointer to the IClientEntityList interface, initialized as NULL
ICvar				*pCvar				= NULL;		//a pointer to the ICvar interface, initialized as NULL
IInputSystem		*pInput				= NULL;

GetSpewOutputFuncFn	_GetSpewOutputFunc	= NULL;
SpewOutputFuncFn	_SpewOutputFunc		= NULL;
SpewOutputFunc_t	ZeOldSpewOutput		= NULL;

MsgFn				_Msg				= NULL;
DevMsgFn			_DevMsg				= NULL;
WarningFn			_Warning			= NULL;

CSigScan			CEBN;
CSigScan			DS;

BOOL				bShowLog			= FALSE;

int (__cdecl *myClientCmd)(char *a1, int a2) = (int (__cdecl *)(char *a1, int a2))0x4204BAD0;
CBaseEntity *(__cdecl *myCreateEntityByName)( const char *className, int iForceEdictIndex) = NULL;
int (__cdecl *myDispatchSpawn)( CBaseEntity *pEntity ) = NULL;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch(dwReason) //'switch' to dwReason, could use if's instead
	{
	case DLL_PROCESS_ATTACH: //we 'attached' to the process
		DisableThreadLibraryCalls(hModule); //Disable calls to dllmain for DLL_THREAD_ATTACH and DLL_THREAD_DETACH
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HackThread, 0, 0, 0); //Create a thread that runs our HackThread function
		hCurrentProcess = GetCurrentProcess();
		break; //break out of the switch statement
	}
	return TRUE; //success
}

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *strtrim(char *s)
{
    return rtrim(ltrim(s)); 
}

string replaceChar(string str, char ch1, char ch2) {
  for (DWORD i = 0; i < str.length(); ++i) {
    if (str[i] == ch1)
      str[i] = ch2;
  }

  return str;
}

void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
		"`~!@#$%^&*()[]{}-_=+,.<>/?\\:;'"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

int instr( char *SearchString, char *SearchTerm )
{
    int stringSize = strlen( SearchString );
    int termSize = strlen( SearchTerm );

    if ( termSize > stringSize )
    {
        return 0;
    }

    int numberFound = 0;
//    const char* subString = NULL;

    for ( int i = 0 ; i <= stringSize - termSize; ++i )
    {
        if ( strncmp( &SearchString[ i ], SearchTerm, termSize ) == 0 )
        {
            i += termSize;    // Skip past this term.
            ++numberFound;
        }
    }
    
    return numberFound;
}

unsigned FindInStr(const std::string& src, const std::string& trm)
{
    unsigned numOccurrences = 0;
    size_t loc = 0;
    while (loc < src.size() &&
          (loc = src.find(trm, loc)) != std::string::npos)
    {
        ++numOccurrences;
        ++loc;
    }
    return numOccurrences;
}

#ifdef GODOHK

void InitGodOHK(void) {
	//CSigScan::sigscan_dllfunc = (CreateInterfaceFn)pServerFactory("IVEngineServer021", 0);
	CSigScan::sigscan_dllfunc = pServerFactory;
	CSigScan::GetDllMemInfo();
	CEBN.Init((unsigned char*)"\x56\x8b\x74\x24\x0c\x57\x8b\x7c\x24\x0c\x83\xfe\xff\x74\x27\x8b\x0d\xc8\x29\x99\x40\x8b\x01\x8b\x50\x54\x56\xff\xd2\xa3\x54\x69","xxxxxxxxxxxxxxxxx????xxxxxxxxx??",32);
	DS.Init((unsigned char*)"\x53\x55\x56\x8b\x74\x24\x10\x57\x85\xf6\x0f\x84\x43\x01\x00\x00\x8b\x1d\x04\x2a\x99\x40\x8b\x03\x8b\x50\x60\x8b\xcb\xff\xd2\x8b","xxxxxxxxxxxxxxxxxx????xxxxxxxxxx",32);
	if(CEBN.is_set&&DS.is_set)
	{
		myCreateEntityByName = (CBaseEntity *(__cdecl *)(const char*, int))CEBN.sig_addr;
		myDispatchSpawn = (int(__cdecl *)(CBaseEntity*))DS.sig_addr;
		//char buf[64], buf2[64];
		//sprintf(buf,"CEBN: 0x%x",CEBN.sig_addr);
		//sprintf(buf2,"DS: 0x%x",DS.sig_addr);
		//MessageBoxA(0,buf2,buf,0);
	}
}

bool __stdcall SetKeyValue(CBaseEntity *pEnt, const char *szKeyName, const char *szValue )
{
	__asm
	{
		pushad;
		push szValue;
		push szKeyName;
		mov ESI, DWORD PTR DS:[pEnt]; //EAX now holds the VTable address
        mov EAX, [ESI];
		add EAX, 0x88;				//index 0x22 in the vtable
		mov ECX, pEnt;
		call [EAX];
		popad;
	}
}

void god(void)
{
	CBaseEntity *timer = myCreateEntityByName("logic_timer",-1);
	if(!timer){
		//MessageBoxA(0,"FAIL","D:",0);
	}else{
		SetKeyValue(timer,"startdisabled","0");
		SetKeyValue(timer,"refiretime","0.01");
		SetKeyValue(timer,"targetname", "god");
		SetKeyValue(timer,"OnTimer","player,addoutput,health 100000");
		SetKeyValue(timer,"OnTimer","player,addoutput,max_health 100000");
		myDispatchSpawn(timer);
	}
}

void ohk(void)
{
	CBaseEntity *timer = myCreateEntityByName("logic_timer",-1);
	if(!timer){
		//MessageBoxA(0,"FAIL","D:",0);
	}else{
		SetKeyValue(timer,"startdisabled","0");
		SetKeyValue(timer,"refiretime","0.1");
		SetKeyValue(timer,"targetname", "ohk");
		SetKeyValue(timer,"OnTimer","*,sethealth,1");
		myDispatchSpawn(timer);
	}
}

#ifndef PUBLIC

void kill1()
{
	CBaseEntity *timer = myCreateEntityByName("logic_timer",-1);
	if(!timer){
		MessageBoxA(0,"FAIL","D:",0);
	}else{
		SetKeyValue(timer,"startdisabled","0");
		SetKeyValue(timer,"refiretime","0.1");
		SetKeyValue(timer,"OnTimer","*,sethealth,0");
		SetKeyValue(timer,"OnTimer","!self,kill,,0.01");
		myDispatchSpawn(timer);
	}
}

void kill2(void)
{
	CBaseEntity *timer = myCreateEntityByName("logic_timer",-1);
	if(!timer){
		//MessageBoxA(0,"FAIL","D:",0);
	}else{
		SetKeyValue(timer,"startdisabled","0");
		SetKeyValue(timer,"refiretime","0.1");
		SetKeyValue(timer,"targetname", "kill2");
		SetKeyValue(timer,"OnTimer","*,sethealth,0");
		myDispatchSpawn(timer);
	}
}

void brk()
{
	CBaseEntity *timer = myCreateEntityByName("logic_timer",-1);
	if(!timer){
		MessageBoxA(0,"FAIL","D:",0);
	}else{
		SetKeyValue(timer,"startdisabled","0");
		SetKeyValue(timer,"refiretime","0.1");
		SetKeyValue(timer,"OnTimer","prop_*,break");
		SetKeyValue(timer,"OnTimer","prop_*,sethealth,0");
		SetKeyValue(timer,"OnTimer","!self,kill,,0.01");
		myDispatchSpawn(timer);
	}
}

#ifdef OFFTHERECORD

void respawn( ){
	int maxnpc = atoi(pEngineClient->Cmd_Argv(2)), maxchild = atoi(pEngineClient->Cmd_Argv(3));
	char maxNpc[128], maxChild[128];
	sprintf(maxNpc,"npc_template_maker,addoutput,MaxNPCCount %i", maxnpc); sprintf(maxChild, "npc_template_maker,addoutput,MaxLiveChildren %i", maxchild); 
	CBaseEntity *pEnt = myCreateEntityByName("logic_timer",-1);
	if(!pEnt){MessageBoxA(0,"FAIL","D:",0);}else{
		SetKeyValue(pEnt,"startdisabled","0");
		SetKeyValue(pEnt,"refiretime", pEngineClient->Cmd_Argv(1));
		SetKeyValue(pEnt,"OnTimer","npc_template_maker,enable");
		SetKeyValue(pEnt, "targetname", "respawn");
		SetKeyValue(pEnt,"OnTimer",maxNpc);
		SetKeyValue(pEnt,"OnTimer",maxChild);
		myDispatchSpawn(pEnt);
	}
}

void respawn2( ){
	int maxnpc = atoi(pEngineClient->Cmd_Argv(2)), maxchild = atoi(pEngineClient->Cmd_Argv(3));
	char maxNpc[128], maxChild[128];
	sprintf(maxNpc,"npc_template_maker,addoutput,MaxNPCCount %i", maxnpc); sprintf(maxChild, "npc_template_maker,addoutput,MaxLiveChildren %i", maxchild); 
	CBaseEntity *pEnt = myCreateEntityByName("logic_timer",-1);
	if(!pEnt){MessageBoxA(0,"FAIL","D:",0);}else{
		SetKeyValue(pEnt,"startdisabled","0");
		SetKeyValue(pEnt,"refiretime", pEngineClient->Cmd_Argv(1));
		SetKeyValue(pEnt,"OnTimer","npc_hunter_maker,enable");
		SetKeyValue(pEnt, "targetname", "respawn2");
		SetKeyValue(pEnt,"OnTimer",maxNpc);
		SetKeyValue(pEnt,"OnTimer",maxChild);
		myDispatchSpawn(pEnt);
	}
}

void no_ai(void)
{
	CBaseEntity *timer = myCreateEntityByName("logic_timer",-1);
	if(!timer){
		//MessageBoxA(0,"FAIL","D:",0);
	}else{
		SetKeyValue(timer,"startdisabled","0");
		SetKeyValue(timer,"refiretime","0.1");
		SetKeyValue(timer,"targetname", "no_ai");
		SetKeyValue(timer,"OnTimer","*,setrelationship,!player D_LI 0");
		myDispatchSpawn(timer);
	}
}

void thecrazies(void)
{
	CBaseEntity *timer = myCreateEntityByName("logic_timer",-1);
	if(!timer){
		//MessageBoxA(0,"FAIL","D:",0);
	}else{
		SetKeyValue(timer,"startdisabled","0");
		SetKeyValue(timer,"refiretime","0.1");
		SetKeyValue(timer,"targetname", "thecrazies");
		SetKeyValue(timer,"OnTimer","*,setrelationship,* D_HT 0");
		myDispatchSpawn(timer);
	}
}

void killtimer(){
	char targetname[128];sprintf(targetname, "%s,kill,,0.01", pEngineClient->Cmd_Argv(1)); 
	CBaseEntity *pEnt = myCreateEntityByName("logic_timer",-1);
	if(!pEnt){MessageBoxA(0,"FAIL","D:",0);}else{
		SetKeyValue(pEnt,"startdisabled","0");
		SetKeyValue(pEnt,"refiretime","0.1");
		SetKeyValue(pEnt,"OnTimer",targetname);
		SetKeyValue(pEnt,"OnTimer","!self,kill,,0.01");
		myDispatchSpawn(pEnt);
	}
}

void origin(){
	char Cpos[128];sprintf(Cpos,"player,addoutput,origin %i %i %i",atoi(pEngineClient->Cmd_Argv(1)), atoi(pEngineClient->Cmd_Argv(2)), atoi(pEngineClient->Cmd_Argv(3)));
	char Cang[128];sprintf(Cang,"player,addoutput,angles %i %i %i",atoi(pEngineClient->Cmd_Argv(4)), atoi(pEngineClient->Cmd_Argv(5)), atoi(pEngineClient->Cmd_Argv(6)));
	CBaseEntity *pEnt = myCreateEntityByName("logic_timer",-1);
	if(!pEnt){MessageBoxA(0,"FAIL",":D",0);}else{
		SetKeyValue(pEnt,"startdisabled","0");
		SetKeyValue(pEnt,"refiretime","0.01");
		SetKeyValue(pEnt,"OnTimer",Cpos);
		SetKeyValue(pEnt,"OnTimer",Cang);
		SetKeyValue(pEnt,"OnTimer","!self,kill,,0.01");
		myDispatchSpawn(pEnt);
	}
}

void DumpCmds()
{
	ConCommandBase *next = pCvar->GetCommands();
	string helps = "";
	string type = "";
	int count = 0;

	fstream File;
	File.open("dumpcmds.csv", ios::out);

	while(next != NULL) {
		char *name = (char*)next->GetName();

		if (*name != (char)"") {
			count++;

			char *help = (char*)next->GetHelpText();
			string helps = help;
		
			if(next->IsCommand()) {type = "Cmd";}

			File << name << "," << "," << type << "," << "\"" << helps << "\"" << endl;
		}

		next = (ConCommandBase*)next->GetNext();
	}

	File.close();
	printf("Wrote %i lines to dumpcmds.csv\n", count);
}

void click(void)
{
	InputEvent_t event;
	event.m_nType = IE_ButtonPressed;
	event.m_nTick = GetTickCount();
	event.m_nData = MOUSE_LEFT;
	pInput->PostUserEvent(event);
	Sleep(50);
	event.m_nType = IE_ButtonReleased;
	event.m_nTick = GetTickCount();
	event.m_nData = MOUSE_LEFT;
	pInput->PostUserEvent(event);
	//ClientToScreen
}

#endif

void showlog(void)
{
	bShowLog = TRUE;
}

void hidelog(void)
{
	bShowLog = FALSE;
}

#endif

#endif

void MakeJMP(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen)
{
    DWORD dwOldProtect, dwBkup, dwRelAddr;
    VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    dwRelAddr = (DWORD) (dwJumpTo - (DWORD) pAddress) - 5;
    *pAddress = 0xE9;
    *((DWORD *)(pAddress + 0x1)) = dwRelAddr;
    for(DWORD x = 0x5; x < dwLen; x++) *(pAddress + x) = 0x90;
 
    VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
    return;
}

void BindFix(void)
{
	CSigScan cssBindFix;
	cssBindFix.sigscan_dllfunc = (void *(__cdecl *)(const char *,int *))pEngineClient;
	cssBindFix.GetDllMemInfo();
	cssBindFix.Init((unsigned char*)"\x85\xF6\x74\x12\x8B\x4C\xBC\x0C\x51\x56\xE8", "xxxxxxxxxxx", 11);
	unsigned char *ptr = (unsigned char*)(((unsigned long)cssBindFix.sig_addr) + 25);
	DWORD dwOld;
	VirtualProtect(ptr, 1, PAGE_EXECUTE_READWRITE, &dwOld);
	*ptr = 0x00;
	VirtualProtect(ptr, 3, dwOld, &dwOld);

	unsigned long fillAdd = (unsigned long)hEngineModule + OFF_FILL;
	char ccfillallitemsfix[32] = "         "; 
	VirtualProtect((LPVOID*)fillAdd, 1, PAGE_EXECUTE_READWRITE, &dwOld);
	*(unsigned char*)fillAdd = *ccfillallitemsfix;
	VirtualProtect((LPVOID*)fillAdd, 1, dwOld, &dwOld);
}

void InitClientCmd(void)
{
	CSigScan execCmd_Sig;
	execCmd_Sig.sigscan_dllfunc = (void *(__cdecl *)(const char *,int *))pEngineClient;
	execCmd_Sig.GetDllMemInfo();
	execCmd_Sig.Init((unsigned char*)"\xE8\x00\x00\x00\x00\x83\xC4\x04\x83\x3D\x00\x00\x00\x00\x00\xC6\x05\x00\x00\x00\x00\x00\x75\x03", "x????xxxxx????xxx????xxx", 24);
	
	myClientCmd = (int (__cdecl*)(char*,int))(((unsigned long)execCmd_Sig.sig_addr)-21);
}

void ClientCmd(CHAR *pCmd)
{
	if (strcmp(pCmd, "sleep") == 0) {
		Sleep(2000);
	} else {
		myClientCmd(pCmd, 1);
	}
/*	unsigned long ulCall = 0x4204BAD0;
	__asm {
		PUSH	0
		PUSH	pCmd
		CALL	ulCall
	}
*/
}

void SafeClientCommand(CHAR *pCmd)
{
	CHAR newCmd[256];
	sprintf(newCmd, "bind \"`\" \"%s\"", pCmd)
	ClientCommand(newCmd);	//bind to rarely used key
	
	ClientCommand("unbind \"`\""); //unbind
}

#ifdef PUBLIC

void __stdcall MyMsgPublic(char *pMsg, ... )
{
	va_list va;
	va_start(va, pMsg);
	char buf[256];
	vsprintf(buf, pMsg, va);
	strtrim(buf);
	SetConsoleTextColor(0xF);
	if ((FindInStr(buf, "Unknown command") > 0) && (FindInStr(buf, "con_enable") == 0) && (FindInStr(buf, "stuffcmds") == 0)) {printf("%s\n", buf);}
	SetConsoleTextColor(0x7);
	va_end(va);
}

#else

void __stdcall MyMsg(char *pMsg, ... )
{
	va_list va;
	va_start(va, pMsg);
	char buf[256];
	vsprintf(buf, pMsg, va);
	strtrim(buf);
	
	if (bShowLog) {
		SetConsoleTextColor(0xF);
		printf("%s\n", buf);
		SetConsoleTextColor(0x7);
	} else {
		if ((FindInStr(buf, "Unknown command") > 0) && (FindInStr(buf, "con_enable") == 0) && (FindInStr(buf, "stuffcmds") == 0)) {
			SetConsoleTextColor(0xF);
			printf("%s\n", buf);
			SetConsoleTextColor(0x7);
		}
	}
	
	va_end(va);
}

void __stdcall MyDevMsg(int level, char *pMsg, ... )
{
	va_list va;
	va_start(va, pMsg);
	char buf[256];
	vsprintf(buf, pMsg, va);
	strtrim(buf);

	if (bShowLog) {
		if ((FindInStr(buf, "health") == 0) && (FindInStr(buf, ".break()") == 0)) {
			SetConsoleTextColor(0x3);
			printf("%s\n", buf);
			SetConsoleTextColor(0x7);
		}
	}
	
	va_end(va);
}

void __stdcall MyWarning(char *pMsg, ... )
{
	va_list va;
	va_start(va, pMsg);
	char buf[256];
	vsprintf(buf, pMsg, va);
	strtrim(buf);
	
	if (bShowLog) {
		SetConsoleTextColor(0x4);
		printf("%s\n", buf);
		SetConsoleTextColor(0x7);
	}
	
	va_end(va);
}

#endif

static SpewRetval_t ZeNewSpewOutput( SpewType_t spewType, const tchar *msg )  
{
	if (bShowLog) {
		SetConsoleTextColor(0xD);
		printf("%s\n", msg);
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
#ifdef PUBLIC
	MakeJMP((PBYTE)_Msg, (DWORD)MyMsgPublic, 5);
#else
	MakeJMP((PBYTE)_Msg, (DWORD)MyMsg, 5);
	MakeJMP((PBYTE)_DevMsg, (DWORD)MyDevMsg, 5);
	MakeJMP((PBYTE)_Warning, (DWORD)MyWarning, 5);
#endif
	HookSpew();
}

#ifdef GODOHK
ConCommand *Fcmd( char const *name ){
	ConCommandBase *cmd = pCvar->GetCommands();
	for ( ; cmd; cmd = const_cast<ConCommandBase*>(cmd->m_pNext) ){
		if ( !stricmp( name, cmd->GetName() ) )
			return (ConCommand*)cmd;	
	}
	return NULL;
}

ConCommand *CreateCmd(const char *name,int flags,const char *help, FnCommandCallback callback){
	ConCommand* mCmd = Fcmd("echo");	
	if ( mCmd == NULL ){return NULL;}
	ConCommand* mNewCmd = (ConCommand*)malloc( sizeof ConCommand);
	memcpy( mNewCmd, mCmd,sizeof( ConCommand ));
	mNewCmd->m_pNext = 0;
	mNewCmd->Create(name,callback,help,flags);
	pCvar->RegisterConCommandBase(mNewCmd);
	return mNewCmd;
}

#endif

void CreateCustomConCommands(void)
{
#ifdef GODOHK
	CreateCmd("ohk", FCVAR_NONE, "Enables One-Hit-Kill", &ohk);
	CreateCmd("god", FCVAR_NONE, "Enables godmode", &god);
	CreateCmd("godmode", FCVAR_NONE, "Enables godmode", &god);	//ty Hell_Demon for making this necessary :P
	CreateCmd(string_KILL2, FCVAR_NONE, "", &kill2);
#endif

#ifndef PUBLIC
#ifdef GODOHK
	CreateCmd("kill1", FCVAR_NONE, "Kill all enemies one time", &kill1);
	CreateCmd("kill2", FCVAR_NONE, "Kill all enemies", &kill2);
	CreateCmd("brk", FCVAR_NONE, "Break all items", &brk);
#endif

#ifdef OFFTHERECORD
	CreateCmd("dumpcmds", FCVAR_NONE, "Dumps all commands to dumpcmds.csv", &DumpCmds);
	CreateCmd("respawn", FCVAR_NONE, "Respawns mobs", &respawn);
	CreateCmd("respawn2", FCVAR_NONE, "Respawns mobs2", &respawn2);
	CreateCmd("killtimer", FCVAR_NONE, "Kills a named timer", &killtimer);
	CreateCmd("origin", FCVAR_NONE, "Sets current position", &origin);
	CreateCmd("no_ai", FCVAR_NONE, "Kills a named timer", &no_ai);
	CreateCmd("thecrazies", FCVAR_NONE, "Sets current position", &thecrazies);
	CreateCmd("click", FCVAR_NONE, "Clicks the mouse", &click);
#endif

	CreateCmd("showlog", FCVAR_NONE, "Show Log", &showlog);
	CreateCmd("hidelog", FCVAR_NONE, "Hide Log", &hidelog);
#endif
}


void printThanks(void) {
	printf("Special Thanks:\n");
	printf("  @Nico (God/OHK and all derivatives)\n");
	printf("  @Hell_Demon (Message Hooks)\n");
	printf("  @DanK (General *s in the >> direction)\n");
}

#ifndef PUBLIC

void SetCheats(ICvar *cvar)
{
	ConCommandBase *next = cvar->GetCommands();
	while(next != NULL)
	{
		if(next->IsBitSet(FCVAR_CHEAT))next->m_nFlags &= ~FCVAR_CHEAT;
		if(next->IsBitSet(FCVAR_REPLICATED))next->m_nFlags &= ~FCVAR_REPLICATED;
		if(next->IsBitSet(FCVAR_PROTECTED))next->m_nFlags &= ~FCVAR_PROTECTED;
	    if(next->IsBitSet(FCVAR_SPONLY))next->m_nFlags &= ~FCVAR_SPONLY;
		next = (ConCommandBase*)next->GetNext();
	}
	cvar->FindVar("sv_cheats")->SetValue(2);
}
#endif

void HackThread(void)
{
	while(!IsGameReady())	//while the game isn't ready
		Sleep(1000);		//wait for a second before checking again

	//Here the game is ready, so we get handles to the dlls
	hEngineModule = GetModuleHandle("engine.dll"); //Get a handle to the engine dll
	hClientModule = GetModuleHandle("client.dll"); //Get a handle to the client dll
	hTier0Module = GetModuleHandle("tier0.dll"); //Get a handle to the tier0 dll
	hServerModule = GetModuleHandle("server.dll"); //Get a handle to the server dll
	hVStdlibModule = GetModuleHandle("vstdlib.dll"); //Get the handle to the vstdlib dll
	hInputModule = GetModuleHandle("inputsystem.dll");

	//Get the function pointers to the CreateInterface functions
	pEngineFactory = (CreateInterfaceFn)GetProcAddress(hEngineModule, "CreateInterface"); //Get the address of the CreateInterface function in engine.dll
	pClientFactory = (CreateInterfaceFn)GetProcAddress(hClientModule, "CreateInterface"); //Get the address of the CreateInterface function in client.dll
	pServerFactory = (CreateInterfaceFn)GetProcAddress(hServerModule, "CreateInterface"); //Get the address of the CreateInterface function in server.dll
	pInputFactory = (CreateInterfaceFn)GetProcAddress(hInputModule, "CreateInterface");

	// Get the function pointers to Spew functions
#ifndef PUBLIC
	_GetSpewOutputFunc = (GetSpewOutputFuncFn)GetProcAddress(hTier0Module, "GetSpewOutputFunc");
	_SpewOutputFunc = (SpewOutputFuncFn)GetProcAddress(hTier0Module, "SpewOutputFunc");
	_Msg = (MsgFn)GetProcAddress(hTier0Module, "Msg");
	_DevMsg = (DevMsgFn)GetProcAddress(hTier0Module, "DevMsg");
	_Warning = (WarningFn)GetProcAddress(hTier0Module, "Warning");
#endif

	//Nullpointer checks
	if(pEngineFactory == NULL || pClientFactory == NULL) //if any of the two function pointers is NULL
	{
		MessageBox(0, "A CreateInterface pointer was NULL, shutting down!", "Failure", MB_OK); //Warn us about it
		exit(0); //and exit the game
	}

	//Get pointers to the existing interfaces in client.dll
	pBaseClient			= (IBaseClientDLL*)pClientFactory(CLIENT_DLL_INTERFACE_VERSION, 0);				//CLIENT_DLL_INTERFACE_VERSION is defined as "VClient013"
	pClientEntityList	= (IClientEntityList*)pClientFactory(VCLIENTENTITYLIST_INTERFACE_VERSION, 0);	//VCLIENTENTITYLIST_INTERFACE_VERSION is defined as "VClientEntityList003"

	//Get pointers to the existing interfaces in engine.dll
	pEngineClient	= (IVEngineClient*)pEngineFactory(VENGINE_CLIENT_INTERFACE_VERSION, 0);	//VENGINE_CLIENT_INTERFACE_VERSION is defined as "VEngineClient012"
	pCvar			= (ICvar*)pEngineFactory(VENGINE_CVAR_INTERFACE_VERSION, 0);			//VENGINE_CVAR_INTERFACE_VERSION is defined as "VEngineCvar003"

	//Get pointers to the existing interfaces in server.dll
	pServerGame		= (CreateInterfaceFn)pEngineFactory("ServerGameDLL005", 0);								 //INTERFACEVERSION_SERVERGAMEDLL is defined as "ServerGameDLL005"
	pInput			= (IInputSystem*)pInputFactory(INPUTSYSTEM_INTERFACE_VERSION, 0);

	if(pBaseClient == NULL || pClientEntityList == NULL || pEngineClient == NULL || pCvar == NULL) //if any of the pointers is NULL
	{
		MessageBox(0, "One of the interface pointers is NULL, shutting down!", "Failure", MB_OK); //Warn us about it
		exit(0); //and exit the game
	}

	InitClientCmd();
	BindFix();
#ifdef GODOHK
	InitGodOHK();
#endif

#ifndef PUBLIC 
	SetCheats(pCvar);
#endif

#ifdef GODOHK
	CreateCustomConCommands();
#endif

	HookMessages();

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ConsoleThread, 0, 0, 0);

	while(1) 
	{
		Sleep(100); //Sleep(pause) the thread for 25 miliseconds
	}
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
		GetModuleHandle("engine.dll") &&	//and engine.dll?
		GetModuleHandle("tier0.dll") &&		//and tier0.dll?
		GetModuleHandle("server.dll") &&	//and server.dll?
		GetModuleHandle("vstdlib.dll")		//and vstdlib.dll?
		)
	{
		return true; //we can get handles, so the game is ready
	}
	return false; //we missed 1 or more handles, so the game isn't ready yet!
}

void ConsoleThread(void)
{
	char sWindowName[50];
	gen_random(sWindowName, 50);
#ifdef PUBLIC 
	char name[80];
	strcpy(name, "Pub Console v");
	strcat(name, PUBLIC_VERSION);
	strcat(name, " by [MPGH]'s l2noob2");
	CreateConsole("Pub Console by l2noob2", name);
#else
	char name[80];
	strcpy(name, "MHConsole v");
#ifdef OFFTHERECORD
	strcat(name, OFFTHERECORD_VERSION);
#else
	strcat(name, PRIVATE_VERSION);
#endif
	strcat(name, " by [MPGH]'s l2noob2");
	CreateConsole("MHConsole by l2noob2", name);
#ifdef OFFTHERECORD
	SetConsoleTextColor(0x4);
	printf("THIS VERSION IS NOT TO BE SHARED!\n");
	SetConsoleTextColor(0x7);
#endif
	SetCheats(pCvar);
#endif

	printThanks();

	HANDLE hstdi = GetStdHandle(STD_INPUT_HANDLE);
	char command[256];
	DWORD charsRead;
	while(ReadConsole(hstdi, &command, 256, &charsRead, 0))
	{
		if (strcmp(strtrim(command), "killconsole") == 0) {break;}
		ClientCmd(command);
		memset(command, 0, 256);
	}
}
