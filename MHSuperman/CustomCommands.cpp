#ifndef _USE_MFC
	#include <Windows.h>
#else
	#include "stdafx.h"
#endif
#include "sdk.h"
#include <HtmlHelp.h>
#include "Constructs.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "StringUtils.h"
#include "VinHacks.h"
#include "Console.h"
#include "SigScan.h"
#include "NetVarDump.h"
#include "NetVarDumper.h"
#include "WinUtils.h"
#include "LuaThreads.h"

using namespace std;

CBaseEntity *(__cdecl *myCreateEntityByName)( const char *className, int iForceEdictIndex) = NULL;
int (__cdecl *myDispatchSpawn)( CBaseEntity *pEntity ) = NULL;

CSigScan					CEBN;
CSigScan					DS;

bool						skillThreadInUse	= false;
int							ptrStam				=0x5D0;

void useSkillThread(int seq)
{
	if (!skillThreadInUse) {
		skillThreadInUse = true;
		switch (seq) {
			case 0x01:
				SendCommand("plr_play_overlay_sequence magic_blind_arrow");
				Sleep(750);
				break;
			case 0x02:
				SendCommand("plr_play_overlay_sequence reverse_gravity");
				Sleep(1000);
				break;
			case 0x03:
				SendCommand("plr_play_overlay_sequence magic_sparrow");
				Sleep(100);
				break;
			case 0x04:
				SendCommand("plr_play_overlay_sequence scythe_blink_dash_attack");
				Sleep(500);
				break;
			case 0x05:
				SendCommand("plr_play_overlay_sequence scythe_blink_N");
				Sleep(1000);
				break;
			case 0x06:
				SendCommand("plr_play_overlay_sequence SP_attack_windmill_end");
				Sleep(750);
				SendCommand("plr_play_overlay_sequence SP_attack_windmill_during_loop_B");
				Sleep(750);
				break;
			case 0x07:
				SendCommand("plr_play_overlay_sequence battle_attack_run_sprint");
				Sleep(750);
				break;
			case 0x08:
				SendCommand("plr_play_overlay_sequence battle_attack_strong_02");
				Sleep(750);
				break;
			case 0x09:
				SendCommand("plr_play_overlay_sequence battle_attack_strong_03_a");
				Sleep(750);
				break;
			case 0x0A:
				SendCommand("plr_play_overlay_sequence battle_attack_strong_03_b");
				Sleep(750);
				break;
			case 0x0B:
				SendCommand("plr_play_overlay_sequence shield_repair");
				Sleep(50);
				SendCommand("plr_play_overlay_sequence counter_attack");
				Sleep(100);
				break;
			case 0x0C:
				SendCommand("plr_play_overlay_sequence shield_repair");
				Sleep(200);
				break;
			case 0x0D:
				SendCommand("plr_play_overlay_sequence battle_hammer_attack_strong_04_finish_d");
				Sleep(300);
				break;
			case 0x0E:
				SendCommand("plr_play_overlay_sequence battle_attack_strong_00_charge_finish_d");
				Sleep(250);
				break;
			case 0x0F:
				SendCommand("plr_play_overlay_sequence heavystander_begin");
				Sleep(300);
				SendCommand("plr_play_overlay_sequence heavystander_during");
				Sleep(100);
				break;
			case 0x10:
				SendCommand("plr_play_overlay_sequence battle_attack_strong_03");
				Sleep(400);
				break;
			case 0x11:
				SendCommand("plr_play_overlay_sequence battle_dualspear_attack_strong_03");
				Sleep(500);
				break;
			case 0x12:
				SendCommand("plr_play_overlay_sequence battle_attack_strong_00_charge_finish_final");
				Sleep(100);
				break;
			case 0x13:
				SendCommand("plr_play_overlay_sequence battle_dualspear_attack_strong_04_loop");
				Sleep(500);
				SendCommand("plr_play_overlay_sequence battle_dualspear_attack_strong_04_loop2");
				Sleep(300);
				break;
			case 0x14:
				SendCommand("plr_play_overlay_sequence gliding_fury_a");
				Sleep(1000);
				break;
			default:
				_cprintf_s("useskill: Unknown useskill command: \"%i\"\n", seq);
				break;
		}
		skillThreadInUse = false;
	}
}

void startUseSkillThread (int code)
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)useSkillThread, (LPVOID)code, 0, 0);
}

void useskill(void)
{
	char arg[256];
	strcpy(arg, pEngineClient->Cmd_Argv(1));
	string sArg = tolowers(arg);
	char skill[256];

	//evie
	if (strcmp(sArg.c_str(), "blind") == 0) {				startUseSkillThread(0x01);
	} else if (strcmp(sArg.c_str(), "gravity") == 0) {		startUseSkillThread(0x02);
	} else if (strcmp(sArg.c_str(), "sparrow") == 0) {		startUseSkillThread(0x03);
	} else if (strcmp(sArg.c_str(), "evywhirl") == 0) {		startUseSkillThread(0x04);
	} else if (strcmp(sArg.c_str(), "blink") == 0) {		startUseSkillThread(0x05);

	//karok
	} else if (strcmp(sArg.c_str(), "karokwhirl") == 0) {	startUseSkillThread(0x06);
	} else if (strcmp(sArg.c_str(), "pillarkick") == 0) {	startUseSkillThread(0x07);
	} else if (strcmp(sArg.c_str(), "karokcharge") == 0) {	startUseSkillThread(0x08);
	} else if (strcmp(sArg.c_str(), "karokspin") == 0) {	startUseSkillThread(0x09);
	} else if (strcmp(sArg.c_str(), "karoksmash") == 0) {	startUseSkillThread(0x0A);

	//fiona
	} else if (strcmp(sArg.c_str(), "shieldrpr") == 0) {	startUseSkillThread(0x0B);
	} else if (strcmp(sArg.c_str(), "fionacharge") == 0) {	startUseSkillThread(0x0C);
	} else if (strcmp(sArg.c_str(), "fionasmash") == 0) {	startUseSkillThread(0x0D);
	} else if (strcmp(sArg.c_str(), "fionawhirl") == 0) {	startUseSkillThread(0x0E);
	} else if (strcmp(sArg.c_str(), "heavystander") == 0) {	startUseSkillThread(0x0F);
															
	//lann
	} else if (strcmp(sArg.c_str(), "lannwhirl") == 0) {	startUseSkillThread(0x10);
	} else if (strcmp(sArg.c_str(), "lanntwirl") == 0) {	startUseSkillThread(0x11);
	} else if (strcmp(sArg.c_str(), "lannslash") == 0) {	startUseSkillThread(0x12);
	} else if (strcmp(sArg.c_str(), "lannspin") == 0) {		startUseSkillThread(0x13);
	} else if (strcmp(sArg.c_str(), "lann7") == 0) {		startUseSkillThread(0x14);

	} else {
		_cprintf_s("useskill: Unknown skill specified: \"%s\"\n", sArg);
	}
}

void fullsp_thread(void)
{
	for(int i=0; i<60; i++) {
		SendCommand("plr_play_overlay_sequence dead_resist");
		Sleep(50);
	}
}

void fullsp(void)
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)fullsp_thread, 0, 0, 0);
}

void bombsaway_thread(void)
{
	SendCommand("host_timescale 3");
	Sleep(100);
	SendCommand("sk_frag_throw_speed 999999");
	Sleep(100);
	SendCommand("plr_play_overlay_sequence frag_thrower_aim_begin");
	Sleep(100);
	SendCommand("plr_play_overlay_sequence frag_thrower_aim_begin");
	Sleep(100);
	for (int i=0; i<10; i++) {
		SendCommand("plr_play_overlay_sequence frag_throw_immediately");
		Sleep(150);
	}
	SendCommand("plr_play_overlay_sequence frag_thrower_aim_begin_with_holding");
	Sleep(100);
	SendCommand("plr_play_overlay_sequence frag_thrower_cancel");
	Sleep(100);
	SendCommand("sk_frag_throw_speed 1000");
	Sleep(100);
	SendCommand("host_timescale 1");
}

void bombsaway(void)
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)bombsaway_thread, 0, 0, 0);
}

void superloot_thread(void)
{
	SendCommand("plr_search_evil_core_distance 3000");
	Sleep(100);
	SendCommand("host_timescale 3");
	Sleep(100);
	SendCommand("cc_change_figure_height 0.0001");
	for (int i=0; i<10; i++) {
		SendCommand("+use");
		Sleep(100);
		SendCommand("-use");
		Sleep(100);
	}
	SendCommand("plr_search_evil_core_distance 100");
	Sleep(100);
	SendCommand("host_timescale 1");
	Sleep(100);
	SendCommand("cc_change_figure_height 0.95");
}

void superloot(void)
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)superloot_thread, 0, 0, 0);
}

void InitGodOHK(void) {
	//CSigScan::sigscan_dllfunc = (CreateInterfaceFn)pServerFactory("IVEngineServer021", 0);
	CSigScan::sigscan_dllfunc = pServerFactory;
	CSigScan::GetDllMemInfo();

	//Deprecated 2013-03-26
	//CEBN.Init((unsigned char*)"\x56\x8b\x74\x24\x0c\x57\x8b\x7c\x24\x0c\x83\xfe\xff\x74\x27\x8b\x0d\xc8\x29\x99\x40\x8b\x01\x8b\x50\x54\x56\xff\xd2\xa3\x54\x69","xxxxxxxxxxxxxxxxx????xxxxxxxxx??",32);
	//DS.Init((unsigned char*)"\x53\x55\x56\x8b\x74\x24\x10\x57\x85\xf6\x0f\x84\x43\x01\x00\x00\x8b\x1d\x04\x2a\x99\x40\x8b\x03\x8b\x50\x60\x8b\xcb\xff\xd2\x8b","xxxxxxxxxxxxxxxxxx????xxxxxxxxxx",32);

	//2013-03-26
	CEBN.Init((unsigned char*)"\x51\x56\x8b\x74\x24\x10\x57\x8b\x7c\x24\x10\x83\xfe\xff\x74\x00\x8b\x0d\x00\x00\x00\x00\x8b\x01\x8b\x50\x58\x56\xff\xd2","xxxxxxxxxxxxxxx?xx????xxxxxxxx",30);
	DS.Init((unsigned char*)"\x53\x55\x56\x8b\x74\x24\x10\x57\x85\xf6\x0f\x84\x43\x01\x00\x00","xxxxxxxxxxxxxxxx",16);

if(CEBN.is_set&&DS.is_set)
	{
		myCreateEntityByName = (CBaseEntity *(__cdecl *)(const char*, int))CEBN.sig_addr;
		myDispatchSpawn = (int(__cdecl *)(CBaseEntity*))DS.sig_addr;
		//char buf[64], buf2[64];
		//sprintf(buf,"CEBN: 0x%x",CEBN.sig_addr);
		//sprintf(buf2,"DS: 0x%x",DS.sig_addr);
		//MessageBoxA(0,buf2,buf,0);
	} else {
		_cprintf_s("Unable to initialize command structure.\n");
	}
	//WIPE_END
}

bool __stdcall SetKeyValue(CBaseEntity *pEnt, const char *szKeyName, const char *szValue )
{
	__asm
	{
		pushad;
		push szValue;
		push szKeyName;
		pushad;
		popad;
		mov ESI, DWORD PTR DS:[pEnt]; //EAX now holds the VTable address
        mov EAX, [ESI];
		pushad;
		popad;
		add EAX, 0x88;				//index 0x22 in the vtable
		mov ECX, pEnt;
		call [EAX];
		pushad;
		popad;
		popad;
	}
}

void god(void)
{
	CBaseEntity *timer = myCreateEntityByName("logic_timer",-1);
	if(!timer){
		_cprintf_s("Unable to execute godmode.\n");
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
		_cprintf_s("Unable to execute ohk.\n");
	}else{
		SetKeyValue(timer,"startdisabled","0");
		SetKeyValue(timer,"refiretime","0.1");
		SetKeyValue(timer,"targetname", "ohk");
		SetKeyValue(timer,"OnTimer","*,sethealth,1");
		myDispatchSpawn(timer);
	}
}

/*void ohk2(void)
{
	GenDT_HeroesPlayer *pPlayer = (GenDT_HeroesPlayer*)pClientEntityList->GetClientEntity(pEngineClient->GetLocalPlayer());
	*pPlayer->totalDamageRatioModifier() = 1000;
}*/

void disable(void)
{
	char targetname[128];
	
	sprintf(targetname, "god,kill,,0.01"); 
	CBaseEntity *pEnt;
	pEnt = myCreateEntityByName("logic_timer",-1);
	if(!pEnt){
		_cprintf_s("Unable to execute disable(1).\n");
	} else {
		SetKeyValue(pEnt,"startdisabled","0");
		SetKeyValue(pEnt,"refiretime","0.1");
		SetKeyValue(pEnt,"OnTimer",targetname);
		SetKeyValue(pEnt,"OnTimer","!self,kill,,0.01");
		myDispatchSpawn(pEnt);
	}
	sprintf(targetname, "ohk,kill,,0.01"); 
	pEnt = myCreateEntityByName("logic_timer",-1);
	if (!pEnt) {
		_cprintf_s("Unable to execute disable(2).\n");
	} else {
		SetKeyValue(pEnt,"startdisabled","0");
		SetKeyValue(pEnt,"refiretime","0.1");
		SetKeyValue(pEnt,"OnTimer",targetname);
		SetKeyValue(pEnt,"OnTimer","!self,kill,,0.01");
		myDispatchSpawn(pEnt);
	}
	sprintf(targetname, "kill2,kill,,0.01"); 
	pEnt = myCreateEntityByName("logic_timer",-1);
	if (!pEnt) {
		_cprintf_s("Unable to execute disable(3).\n");
	} else {
		SetKeyValue(pEnt,"startdisabled","0");
		SetKeyValue(pEnt,"refiretime","0.1");
		SetKeyValue(pEnt,"OnTimer",targetname);
		SetKeyValue(pEnt,"OnTimer","!self,kill,,0.01");
		myDispatchSpawn(pEnt);
	}
}

void kill1(void)
{
	CBaseEntity *timer = myCreateEntityByName("logic_timer",-1);
	if(!timer){
		_cprintf_s("Unable to execute nuke.\n");
	}else{
		SetKeyValue(timer,"startdisabled","0");
		SetKeyValue(timer,"refiretime","0.1");
		SetKeyValue(timer,"OnTimer","*,sethealth,0");
		SetKeyValue(timer,"OnTimer","!self,kill,,0.01");
		myDispatchSpawn(timer);
	}
}

void displayCmd(char* pCmd, char* text, char* usage)
{
	SetConsoleTextColor(0xF);
	_cprintf_s("%s ", pCmd);
	SetConsoleTextColor(0x7);
	_cprintf_s("- %s\n", text);
	_cprintf_s("              Usage: ");
	SetConsoleTextColor(0xF);
	_cprintf_s("%s\n", usage);
	SetConsoleTextColor(0x7);
}

void help(void)
{
	ConCommandBase *ccb = pCvar->GetCommands();
	//ccb->FindCommand
	printf("\nAdditional console commands:\n");
#ifdef OFFTHERECORD
	displayCmd("brk         ", "Destroy all items on map", "brk");
#endif
	displayCmd("bombsaway   ", "Throws 10 bombs very far, very fast", "bombsaway");
#ifdef OFFTHERECORD
	displayCmd("disable     ", "Disables god/ohk/kill2 for the current map.", "disable");
#else
#ifndef PUBLIC
	displayCmd("disable     ", "Disables god/ohk for the current map", "disable");
#endif
#endif
#ifndef PUBLIC
	displayCmd("docks       ", "Moves player to the docks", "docks");
#endif
#ifdef OFFTHERECORD
	displayCmd("dumpcmds    ", "Save complete command list to dumpcmds.csv", "dumpcmds");
#endif
	displayCmd("fullsp      ", "Fills your SP bar", "fullsp");
#ifdef GODOHK
	displayCmd("god/godmode ", "Invulnerable (Process: \"god\")", "god");
#endif
#ifdef OFFTHERECORD
	displayCmd("god2        ", "Alternative godmode", "god2");
#endif
	displayCmd("help        ", "Displays this help list", "help");
#ifndef PUBLIC
	displayCmd("hidelog     ", "Stop display of debug output", "hidelog");
#endif
#ifdef OFFTHERECORD
	displayCmd("kill1        ", "Kill all spawned enemies", "kill1");
	displayCmd("kill2        ", "Continuiously kill all enemies (Process: \"kill2\")", "kill2");
#endif
	displayCmd("killconsole  ", "Closes the console window (not bindable)", "killconsole");
#ifndef PUBLIC
	displayCmd("killprocess  ", "Terminates a running named process", "killprocess [processName]");
#endif
	displayCmd("lua_info     ", "Prints information about the currently running scripts", "lua_info");
	displayCmd("lua_run      ", "Runs a Lua scipt", "lua_run filename [repeat] [delay]");
#ifndef PUBLIC
	displayCmd("MLeft        ", "Clicks the left mouse button", "MLeft");
#endif
#ifndef PUBLIC
	displayCmd("mode         ", "Activates/deactivates special modes", "mode [minecraft/ice/bw] [0/1]");
#endif
#ifdef OFFTHERECORD
	displayCmd("no_ai        ", "Turns off enemy AI (Process: \"no_ai\")", "no_ai");
#endif
	displayCmd("nuke         ", "Kills all currently spawned enemies", "nuke");
#ifdef GODOHK
	displayCmd("ohk          ", "All enemies one-hit-kill (Process: \"ohk\")", "ohk");
#endif
#ifdef OFFTHERECORD
	displayCmd("ohk2         ", "Player does max damage", "ohk2");
#endif
#ifdef OFFTHERECORD
	displayCmd("origin       ", "Teleports player", "origin [posX] [posY] [posZ] [rotX] [rotY] [rotZ]");
#endif
	displayCmd("printload    ", "Displays the current load commands", "printload");
	displayCmd("reloadcmds   ", "Reprocesses loadcommands.txt", "reloadcmds");
#ifdef OFFTHERECORD
	displayCmd("respawn      ", "Respawns previously spawned enemies (Process: \"respawn\")", "respawn [respawnTime] [numToSpawn] [maxSpawns]");
	displayCmd("respawn2     ", "Respawns previously spawned bosses (Process: \"respawn2\")", "respawn2 [respawnTime] [numToSpawn] [maxSpawns]");
#endif
#ifdef OFFTHERECORD
	displayCmd("revivetorch  ", "Revives all party members", "revivetorch");
#endif
#ifndef PUBLIC
	displayCmd("SetCursorPos ", "Moves the mouse to the specified location", "SetCursorPos [x] [y]");
#endif
#ifndef PUBLIC
	displayCmd("showlog      ", "Shows debug output", "showlog");
#endif
#ifndef PUBLIC
	displayCmd("spawncmds    ", "Toggles spawn commands on/off (Default on)", "spawncmds");
	displayCmd("spawncmdsfile", "Sets the file to use as a list of spawn commands.", "spawncmdsfile (filename)");
#endif
#ifdef OFFTHERECORD
	displayCmd("stam         ", "Infinite stamina", "stam");
#endif
#ifndef PUBLIC
	displayCmd("superember   ", "Max thrust applied to Evie amber", "superember [0/1]");
#endif
	displayCmd("superloot    ", "Picks up 10 items from far away", "superloot");
#ifdef OFFTHERECORD
	displayCmd("thecrazies   ", "Enemies attack each other", "thecrazies");
#endif
	displayCmd("useskill     ", "Uses a skill from the skill list", "useskill [skillName]");

}

#ifndef PUBLIC

void docks(void)
{
	SendCommand("force_state_transition_to_purgetowharf");
}

void mode(void)
{
	if (strcmp(pEngineClient->Cmd_Argv(1), "minecraft") == 0) {
		if (atoi(pEngineClient->Cmd_Argv(2)) == 1) {
			SendCommand("mat_showlowresimage 1");
		} else if (atoi(pEngineClient->Cmd_Argv(2)) == 0) {
			SendCommand("mat_showlowresimage 0");
		} else {
			_cprintf_s("mode: Invalid value: \"%s\".\n", pEngineClient->Cmd_Argv(2));
		}
	} else 	if (strcmp(pEngineClient->Cmd_Argv(1), "ice") == 0) {
		if (atoi(pEngineClient->Cmd_Argv(2)) == 1) {
			SendCommand("sv_friction -1");
		} else if (atoi(pEngineClient->Cmd_Argv(2)) == 0) {
			SendCommand("sv_friction 4");
		} else {
			_cprintf_s("mode: Invalid value: \"%s\".\n", pEngineClient->Cmd_Argv(2));
		}

	} else if (strcmp(pEngineClient->Cmd_Argv(1), "bw") == 0) {
		if (atoi(pEngineClient->Cmd_Argv(2)) == 1) {
			SendCommand("mat_yuv 1");
		} else if (atoi(pEngineClient->Cmd_Argv(2)) == 0) {
			SendCommand("mat_yuv 0");
		} else {
			_cprintf_s("mode: Invalid value: \"%s\".\n", pEngineClient->Cmd_Argv(2));
		}
	} else {
		_cprintf_s("mode: Invalid parameter: \"%s\".\n", pEngineClient->Cmd_Argv(1));
	}
}

void superember(void)
{
	int val = atoi(pEngineClient->Cmd_Argv(1));
	switch (val) {
		case 0:
			SendCommand("evy_bubble_ball_init_speed 100");
			break;
		case 1:
			SendCommand("evy_bubble_ball_init_speed 2000");
			break;
		default:
			_cprintf_s("superember: Invalid argument: \"%s\".\n", pEngineClient->Cmd_Argv(1));
			break;
	}
}

void kill2(void)
{
	CBaseEntity *timer = myCreateEntityByName("logic_timer",-1);
	if(!timer){
		_cprintf_s("Unable to execute kill2.\n");
	}else{
		SetKeyValue(timer,"startdisabled","0");
		SetKeyValue(timer,"refiretime","0.1");
		SetKeyValue(timer,"targetname", "kill2");
		SetKeyValue(timer,"OnTimer","*,sethealth,0");
		myDispatchSpawn(timer);
	}
}

void brk(void)
{
	CBaseEntity *timer = myCreateEntityByName("logic_timer",-1);
	if(!timer){
		_cprintf_s("Unable to execute brk.\n");
	}else{
		SetKeyValue(timer,"startdisabled","0");
		SetKeyValue(timer,"refiretime","0.1");
		SetKeyValue(timer,"OnTimer","prop_*,break");
		SetKeyValue(timer,"OnTimer","prop_*,sethealth,0");
		SetKeyValue(timer,"OnTimer","!self,kill,,0.01");
		myDispatchSpawn(timer);
	}
}

void god2_noevy(void)
{
	int i;
	edict_t *edt;
	CBaseEntity* ent;

	for(i=0;i<2048;i++){
		edt = pEngineServer->PEntityOfEntIndex(i);
		if(edt && edt->GetIServerEntity()){
			ent = edt->GetIServerEntity()->GetBaseEntity();
			if (
				strcmp(ent->GetClassName(),"CHeroesPlayerLethita")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerKalok")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerFiona")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerKay")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerVella")==0 )
			{
				int* arm = (((int*)ent)+0xB67); //+0xA46);
				*arm = 1000;
			}
		}
	}
}

void god2(void)
{
	int i;
	edict_t *edt;
	CBaseEntity* ent;

	for(i=0;i<2048;i++){
		edt = pEngineServer->PEntityOfEntIndex(i);
		if(edt && edt->GetIServerEntity()){
			ent = edt->GetIServerEntity()->GetBaseEntity();
			if (
				strcmp(ent->GetClassName(),"CHeroesPlayerLethita")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerEvy")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerKalok")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerFiona")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerKay")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerVella")==0 )
			{
				int* arm = (((int*)ent)+0xB67); //+0xA46);
				*arm = 1000;
			}
		}
	}
}

void ohk2(void)
{
	int i;
	edict_t *edt;
	CBaseEntity* ent;

	for(i=0;i<2048;i++){
		edt = pEngineServer->PEntityOfEntIndex(i);
		if(edt && edt->GetIServerEntity()){
			ent = edt->GetIServerEntity()->GetBaseEntity();
			if (
				strcmp(ent->GetClassName(),"CHeroesPlayerLethita")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerEvy")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerKalok")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerFiona")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerKay")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerVella")==0 )
			{
				float* dmg = (((float*)ent)+0x905); //+0x816);
				*dmg = 100.0;
			}
		}
	}
}

void DamageMultiplier(void)
{
	int i;
	edict_t *edt;
	CBaseEntity* ent;

	for(i=0;i<2048;i++){
		edt = pEngineServer->PEntityOfEntIndex(i);
		if(edt && edt->GetIServerEntity()){
			ent = edt->GetIServerEntity()->GetBaseEntity();
			if (
				strcmp(ent->GetClassName(),"CHeroesPlayerLethita")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerEvy")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerKalok")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerFiona")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerKay")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerVella")==0 )
			{
				float* dmg = (((float*)ent)+0x905); //+0x816);
				*dmg = atof(pEngineClient->Cmd_Argv(1));
			}
		}
	}
}

void stam(void)
{
	int i;
	edict_t *edt;
	CBaseEntity* ent;

	for(i=0;i<2048;i++){
		edt = pEngineServer->PEntityOfEntIndex(i);
		if(edt && edt->GetIServerEntity()){
			ent = edt->GetIServerEntity()->GetBaseEntity();
			if (
				strcmp(ent->GetClassName(),"CHeroesPlayerLethita")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerEvy")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerKalok")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerFiona")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerKay")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerVella")==0 )
			{
				int* mult = (((int*)ent)+0x61C); //+0x5D0);
				*mult = 0;
			}
		}
	}
}

#ifdef NICO
void StartSta(void)
{
	int i;
	edict_t *edt;
	CBaseEntity* ent;
//	char buf[32];

	for(i=0;i<2048;i++){
			edt = pEngineServer->PEntityOfEntIndex(i);
			if(edt && edt->GetIServerEntity()){
				ent = edt->GetIServerEntity()->GetBaseEntity();
				//if(strcmp(ent->GetServerClass()->GetName(),"CHeroesPlayerLethita")==0 || strcmp(ent->GetServerClass()->GetName(),"CHeroesPlayerEvy")==0 || strcmp(ent->GetServerClass()->GetName(),"CHeroesPlayerKalok")==0 || strcmp(ent->GetServerClass()->GetName(),"CHeroesPlayerFiona")==0)
				if (strcmp(ent->GetClassName(),"CHeroesPlayerLethita")==0 || strcmp(ent->GetClassName(),"CHeroesPlayerEvy")==0 || strcmp(ent->GetClassName(),"CHeroesPlayerKalok")==0 || strcmp(ent->GetClassName(),"CHeroesPlayerFiona")==0)
				{
					/*int *sta = (((int*)ent)+0x258); //MakePointerGEN<int>(ent,0x960);
					//*sta = 10;
					int *stam = (((int*)ent)+0x25A); 
					//sprintf(buf,"%i",*sta);
					//centerMsg(buf);
					*sta += 100;
					*stam += 100;
					//MessageBoxA(0,IntToStr(*sta),"stamina",0);*/

					int* mult = (((int*)ent)+0x5D0);
					*mult = 0;

					//float* crit = (((float*)ent)+0x78E);
					//*crit = 1;

					//int* inv = (((int*)ent)+0x8BB);
					//*inv = 100;

					int* arm = (((int*)ent)+0xA46);
					*arm = 1000;

					float* dmg = (((float*)ent)+0x816);
					*dmg = 1000.0;//atof(engine->Cmd_Argv(1));
				}
			}
		}
	//DWORD id;
	//CreateThread(0,0,(LPTHREAD_START_ROUTINE)StaTh,0,0,&id);

}
#endif

void getServerVarPlayer_Cst(void)
{
	
}

string getServerVarPlayer(void)
{
	int i;
	edict_t *edt;
	CBaseEntity* ent;
	string s = string("");
	char c[1024];

	for(i=0;i<2048;i++){
		edt = pEngineServer->PEntityOfEntIndex(i);
		if(edt && edt->GetIServerEntity()){
			ent = edt->GetIServerEntity()->GetBaseEntity();
			if (
				strcmp(ent->GetClassName(),"CHeroesPlayerLethita")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerEvy")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerKalok")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerFiona")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerKay")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerVella")==0 )
			{
				int offset = strtol(pEngineClient->Cmd_Argv(1), NULL, 16) / 4;
				char type[255];
				strcpy(type, pEngineClient->Cmd_Argv(2));

				if (strcmp(type, "i") == 0)
				{
					int* val = (((int*)ent)+offset); //+0x5D0);
					_stprintf_s(c, "Value: %i\n", *val);
					//s += 
				}  else if (strcmp(type, "f") == 0)
				{
					float* val = (((float*)ent)+offset); //+0x5D0);
					_stprintf_s(c, "Value: %f\n", *val);
				} else if (strcmp(type, "s") == 0)
				{
					//char* val = (((char*)ent)+offset); //+0x5D0);
					char* val = MakePointerGEN<char>(ent, strtol(pEngineClient->Cmd_Argv(1), NULL, 16));
					_stprintf_s(c, 1024, "Value: %s\n", *val);
				}
			}
		}
	}
	return c;
}

void setServerVarPlayer(void)
{
	int i;
	edict_t *edt;
	CBaseEntity* ent;

	for(i=0;i<2048;i++){
		edt = pEngineServer->PEntityOfEntIndex(i);
		if(edt && edt->GetIServerEntity()){
			ent = edt->GetIServerEntity()->GetBaseEntity();
			if (
				strcmp(ent->GetClassName(),"CHeroesPlayerLethita")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerEvy")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerKalok")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerFiona")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerKay")==0 ||
				strcmp(ent->GetClassName(),"CHeroesPlayerVella")==0 )
			{
				int offset = strtol(pEngineClient->Cmd_Argv(1), NULL, 16) / 4;
				char type[255];
				strcpy(type, pEngineClient->Cmd_Argv(2));

				if (strcmp(type, "i") == 0)
				{
					int* val = (((int*)ent)+offset); //+0x5D0);
					*val = atoi(pEngineClient->Cmd_Argv(3));
				}  else if (strcmp(type, "f") == 0)
				{
					float* val = (((float*)ent)+offset); //+0x5D0);
					*val = atof(pEngineClient->Cmd_Argv(3));
				}
			}
		}
	}
}

void getServerVarNPC(void)
{
	int i;
	edict_t *edt;
	CBaseEntity* ent;

	for(i=0;i<2048;i++){
		edt = pEngineServer->PEntityOfEntIndex(i);
		if(edt && edt->GetIServerEntity()){
			ent = edt->GetIServerEntity()->GetBaseEntity();
			if (
				strcmp(ent->GetClassName(),"CHeroesPlayerLethita")!=0 &&
				strcmp(ent->GetClassName(),"CHeroesPlayerEvy")!=0 &&
				strcmp(ent->GetClassName(),"CHeroesPlayerKalok")!=0 &&
				strcmp(ent->GetClassName(),"CHeroesPlayerFiona")!=0 &&
				strcmp(ent->GetClassName(),"CHeroesPlayerKay")!=0 &&
				strcmp(ent->GetClassName(),"CHeroesPlayerVella")!=0 )
			{
				int offset = strtol(pEngineClient->Cmd_Argv(1), NULL, 16) / 4;
				char type[255];
				strcpy(type, pEngineClient->Cmd_Argv(2));

				if (strcmp(type, "i") == 0)
				{
					int* val = (((int*)ent)+offset); //+0x5D0);
					_cprintf_s("Value: %i\n", *val);
				}  else if (strcmp(type, "f") == 0)
				{
					float* val = (((float*)ent)+offset); //+0x5D0);
					_cprintf_s("Value: %f\n", *val);
				} else if (strcmp(type, "s") == 0)
				{
					char* val = (((char*)ent)+offset);
					_cprintf_s("Value: %s\n", *val);
				}
			}
		}
	}
}

void setServerVarNPC(void)
{
	int i;
	edict_t *edt;
	CBaseEntity* ent;

	for(i=0;i<2048;i++){
		edt = pEngineServer->PEntityOfEntIndex(i);
		if(edt && edt->GetIServerEntity()){
			ent = edt->GetIServerEntity()->GetBaseEntity();
			if (
				strcmp(ent->GetClassName(),"CHeroesPlayerLethita")!=0 &&
				strcmp(ent->GetClassName(),"CHeroesPlayerEvy")!=0 &&
				strcmp(ent->GetClassName(),"CHeroesPlayerKalok")!=0 &&
				strcmp(ent->GetClassName(),"CHeroesPlayerFiona")!=0 &&
				strcmp(ent->GetClassName(),"CHeroesPlayerKay")!=0 &&
				strcmp(ent->GetClassName(),"CHeroesPlayerVella")!=0 )
			{
				int offset = strtol(pEngineClient->Cmd_Argv(1), NULL, 16) / 4;
				char type[255];
				strcpy(type, pEngineClient->Cmd_Argv(2));

				if (strcmp(type, "i") == 0)
				{
					int* val = (((int*)ent)+offset); //+0x5D0);
					*val = atoi(pEngineClient->Cmd_Argv(3));
				}  else if (strcmp(type, "f") == 0)
				{
					float* val = (((float*)ent)+offset); //+0x5D0);
					*val = atof(pEngineClient->Cmd_Argv(3));
				}
			}
		}
	}
}

void getNetVar(void)
{
	int offset = atoi(pEngineClient->Cmd_Argv(1));
	char type[255];
	strcpy(type, pEngineClient->Cmd_Argv(2));

	if (strcmp(type, "i") == 0) {
		int *val = (int*)pClientEntityList->GetClientEntity(pEngineClient->GetLocalPlayer())  + offset;
		_cprintf_s("Value: %i\n", *val);
	} else if (strcmp(type, "f") == 0) {
		float *val = (float*)pClientEntityList->GetClientEntity(pEngineClient->GetLocalPlayer())  + offset;
		_cprintf_s("Value: %f\n", *val);
	} else if (strcmp(type, "b") == 0) {
		bool *val = (bool*)pClientEntityList->GetClientEntity(pEngineClient->GetLocalPlayer())  + offset;
		_cprintf_s("Value: %c\n", (char)*val);
	}
}

void setNetVar(void)
{
	int offset = atoi(pEngineClient->Cmd_Argv(1));
	char type[255];
	strcpy(type, pEngineClient->Cmd_Argv(2));

	if (strcmp(type, "i") == 0) {
		int *val = (int*)pClientEntityList->GetClientEntity(pEngineClient->GetLocalPlayer())  + offset;
		*val = atoi(pEngineClient->Cmd_Argv(3));
		_cprintf_s("Value Set: %i\n", *val);
	} else if (strcmp(type, "f") == 0) {
		float *val = (float*)pClientEntityList->GetClientEntity(pEngineClient->GetLocalPlayer())  + offset;
		*val = atof(pEngineClient->Cmd_Argv(3));
		_cprintf_s("Value Set: %f\n", *val);
	} else if (strcmp(type, "b") == 0) {
		bool *val = (bool*)pClientEntityList->GetClientEntity(pEngineClient->GetLocalPlayer())  + offset;
		*val = atoi(pEngineClient->Cmd_Argv(3));
		_cprintf_s("Value Set: %c\n", (char)*val);
	}
}

void dumpNetVars(void)
{
	NetVars::Analyze(pBaseClient->GetAllClasses());
	NetVars::GenCode("NetVarDump.h");
}

void respawn(void)
{
	int maxnpc = atoi(pEngineClient->Cmd_Argv(2)), maxchild = atoi(pEngineClient->Cmd_Argv(3));
	char maxNpc[128], maxChild[128];
	sprintf(maxNpc,"npc_template_maker,addoutput,MaxNPCCount %i", maxnpc); sprintf(maxChild, "npc_template_maker,addoutput,MaxLiveChildren %i", maxchild); 
	CBaseEntity *pEnt = myCreateEntityByName("logic_timer",-1);
	if (!pEnt) {
		_cprintf_s("Unable to execute respawn.\n");
	} else {
		SetKeyValue(pEnt,"startdisabled","0");
		SetKeyValue(pEnt,"refiretime", pEngineClient->Cmd_Argv(1));
		SetKeyValue(pEnt,"OnTimer","npc_template_maker,enable");
		SetKeyValue(pEnt, "targetname", "respawn");
		SetKeyValue(pEnt,"OnTimer",maxNpc);
		SetKeyValue(pEnt,"OnTimer",maxChild);
		myDispatchSpawn(pEnt);
	}
}

void respawn2(void)
{
	int maxnpc = atoi(pEngineClient->Cmd_Argv(2)), maxchild = atoi(pEngineClient->Cmd_Argv(3));
	char maxNpc[128], maxChild[128];
	sprintf(maxNpc,"npc_template_maker,addoutput,MaxNPCCount %i", maxnpc); sprintf(maxChild, "npc_template_maker,addoutput,MaxLiveChildren %i", maxchild); 
	CBaseEntity *pEnt = myCreateEntityByName("logic_timer",-1);
	if (!pEnt) {
		_cprintf_s("Unable to execute respawn2.\n");
	} else {
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
		_cprintf_s("Unable to execute no_ai.\n");
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
		_cprintf_s("Unable to execute thecrazies.\n");
	}else{
		SetKeyValue(timer,"startdisabled","0");
		SetKeyValue(timer,"refiretime","0.1");
		SetKeyValue(timer,"targetname", "thecrazies");
		SetKeyValue(timer,"OnTimer","*,setrelationship,* D_HT 0");
		myDispatchSpawn(timer);
	}
}

void ReviveTorch(void)
{
	CBaseEntity *rTorch = myCreateEntityByName("prop_revive_torch",-1);
	if (!rTorch) {
		_cprintf_s("Unable to execute revivetorch.\n");
	} else {
		SetKeyValue(rTorch, "model", "models/error.mdl");
		myDispatchSpawn(rTorch);
	}
}

void killtimer(void)
{
	char targetname[128];sprintf(targetname, "%s,kill,,0.01", pEngineClient->Cmd_Argv(1)); 
	CBaseEntity *pEnt = myCreateEntityByName("logic_timer",-1);
	if (!pEnt) {
		_cprintf_s("Unable to execute killprocess.\n");
	} else {
		SetKeyValue(pEnt,"startdisabled","0");
		SetKeyValue(pEnt,"refiretime","0.1");
		SetKeyValue(pEnt,"OnTimer",targetname);
		SetKeyValue(pEnt,"OnTimer","!self,kill,,0.01");
		myDispatchSpawn(pEnt);
	}
}

void origin(void)
{
	char Cpos[128];sprintf(Cpos,"player,addoutput,origin %i %i %i",atoi(pEngineClient->Cmd_Argv(1)), atoi(pEngineClient->Cmd_Argv(2)), atoi(pEngineClient->Cmd_Argv(3)));
	char Cang[128];sprintf(Cang,"player,addoutput,angles %i %i %i",atoi(pEngineClient->Cmd_Argv(4)), atoi(pEngineClient->Cmd_Argv(5)), atoi(pEngineClient->Cmd_Argv(6)));
	CBaseEntity *pEnt = myCreateEntityByName("logic_timer",-1);
	if (!pEnt) {
		_cprintf_s("Unable to execute origin.\n");
	} else {
		SetKeyValue(pEnt,"startdisabled","0");
		SetKeyValue(pEnt,"refiretime","0.01");
		SetKeyValue(pEnt,"OnTimer",Cpos);
		SetKeyValue(pEnt,"OnTimer",Cang);
		SetKeyValue(pEnt,"OnTimer","!self,kill,,0.01");
		myDispatchSpawn(pEnt);
	}
}

void speedmod(void)
{
	char modifier[128];
	sprintf(modifier,"player_speedmod,ModifySpeed,%f", atof(pEngineClient->Cmd_Argv(1)));
	CBaseEntity *timer = myCreateEntityByName("logic_timer",-1);
	if (!timer) {
		_cprintf_s("Unable to execute speedmod.\n");
	} else {
		SetKeyValue(timer,"startdisabled","0");
		SetKeyValue(timer,"refiretime","0.1");
		SetKeyValue(timer,"OnTimer", modifier);
		SetKeyValue(timer,"OnTimer","!self,kill,,0.01");
		myDispatchSpawn(timer);
	}
}

void DumpCmds(void)
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

	if (bConReady) {printf("Wrote %i lines to dumpcmds.csv\n", count);}
}

void DumpEntities(void)
{
	int numents = pClientEntityList->NumberOfEntities(true);
	for (int i = 0; i <= (numents - 1); i++) {
		IClientEntity *ent = pClientEntityList->GetClientEntity(i);
		//ent->
	}
	int i;
	edict_t *edt;
	CBaseEntity* ent;

	for(i=0;i<2048;i++){
		edt = pEngineServer->PEntityOfEntIndex(i);
		if(edt && edt->GetIServerEntity())
		{
			ent = edt->GetIServerEntity()->GetBaseEntity();
			{
				string sClassName = ent->GetClassName();
				string sEntityName = string();
				if (sClassName.substr(0, 7) != "CHeroes")
				{
					//sEntityName = STRING(ent->GetEntityName());
				}

				_cprintf("Id:[%i],Class:[%s],Name:[%s],HP:[%i]\n", i, ent->GetClassName(), sEntityName, ent->GetHealth());
				//int* arm = (((int*)ent)+0xB67); //+0xA46);
				//*arm = 1000;
			}
		}
	}
}

void setcursorposcmd(void)
{
	RECT rt;
	GetWindowRect(FindWindow(NULL,"Vindictus"),&rt);
	SetCursorPos(rt.left+atoi(pEngineClient->Cmd_Argv(1)),rt.top+atoi(pEngineClient->Cmd_Argv(2)));
}

void m_left(void){mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);}

void showlog(void)
{
	bShowLog = TRUE;
}

void hidelog(void)
{
	bShowLog = FALSE;
}

#endif

void lua_run(void)
{
	char fname[256];
	strcpy(fname, pEngineClient->Cmd_Argv(1));

	int reps;
	string sReps;
	if (strcmp(pEngineClient->Cmd_Argv(2), "") != 0) {
		reps = stoi(pEngineClient->Cmd_Argv(2));
	} else {
		reps = 0;
	}
	if (reps == 0) {
		sReps = "unlimited";
	} else {
		sReps = pEngineClient->Cmd_Argv(2);
		sReps = sReps + " times";
	}

	int time;
	if (strcmp(pEngineClient->Cmd_Argv(3), "") != 0) {
		time = stoi(pEngineClient->Cmd_Argv(3));
	} else {
		time = 0;
	}
	_cprintf_s("Starting script: %s (%s)(%ims delay)\n", pEngineClient->Cmd_Argv(1), sReps, time);
}

void lua_info(void)
{
	PrintLuaStats();
}

void lua_killprocess(void)
{
}

void lua_killscript(void)
{
}

void lua_killall(void)
{
}
