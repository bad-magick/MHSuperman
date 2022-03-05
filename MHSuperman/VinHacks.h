#pragma once
#ifndef _USE_MFC
	#include <Windows.h>
#else
	#include "stdafx.h"
#endif
#include "sdk.h"
#include "NetVarDump.h"
#include "Constructs.h"
#include <fstream>
#include "SigScan.h"
#include "Console.h"
#include <string>
#include <vector>

using namespace std;

extern HMODULE				hEngineModule, hClientModule, hTier0Module, hServerModule, hVStdlibModule, hInputModule; //module handles
extern CreateInterfaceFn	pEngineFactory, pClientFactory, pServerFactory, pServerGame, pInputFactory;   //CreateInterface function pointers

extern IBaseClientDLL				*pBaseClient;
extern IVEngineClient				*pEngineClient;
extern IClientEntityList			*pClientEntityList;
extern ICvar						*pCvar;
extern IInputSystem					*pInput;
extern IVEngineServer				*pEngineServer;

extern GenDT_BaseEntity				*pBaseEnt;
extern GenDT_BaseCombatCharacter	*pCCharacter;

extern BOOL							bShowLog;

extern BOOL							bConReady;

extern vector<string>				binds;
extern vector<string>				unbinds;
extern BOOL							bAllowCommands;
extern string						sCurrentMap;

extern vector<string>				alwaysAllowedCmds;
extern vector<string>				disallowedCommands;
extern vector<string>				disallowedMaps;

extern vector<string>				loadCommands;
extern vector<string>				spawnCommands;
extern string						spawnCommandsFilename;

void GetAllInterfaces(void);
void HackThread(void);
void CreateHackThread(void);
void SendCommand(char *pCmd);
void ProcessCommand (char *pCmd);
void Ping(void);