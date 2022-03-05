#include <Windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include "VinHacks.h"
#include "MHSuperman.h"
extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}
#define lua_open()  luaL_newstate()
#define lua_baselibopen(lua_State) luaL_openlibs(lua_State)

using namespace std;

struct LuaMachineParams {
	lua_State* lVM;
	char filename[1024];
	char friendly[1024];
	int repeatMs;
	int repeatNum;
	bool running;
	bool completed;
	bool terminateFlag;
	bool started;
};

vector<LuaMachineParams>	Threads;
int							iMachineCount		= 0;
int							iMachineCompleted	= 0;
int							iMachineRunning		= 0;

void RunMachineThread(void)
{
	LuaMachineParams lmp;
	for(vector<LuaMachineParams>::iterator it = Threads.begin(); it != Threads.end(); ++it) {
		if (!it->started) {
			lmp = *it;
			break;
		}
	}
	lmp.running = true;
	iMachineRunning++;
	lmp.started = true;
	if (lmp.repeatNum != 0) {
		for (int i = 0; i < lmp.repeatNum; i++) {
			luaL_dofile(lmp.lVM, lmp.filename);
			Sleep(lmp.repeatMs);
		}
	} else {
		while (!lmp.terminateFlag) {
			luaL_dofile(lmp.lVM, lmp.filename);
			Sleep(lmp.repeatMs);
		}
	}
	_cprintf_s("Lua script: %s completed.\n", lmp.friendly);
	lua_close(lmp.lVM);
	iMachineRunning--;
	iMachineCompleted++;
	lmp.running = false;
	lmp.completed = true;
}

int lua_ConsoleCommand(lua_State *lVM)
{
	char* pCmd = (char*)luaL_checkstring(lVM, 1);
	ProcessCommand(pCmd);
	SendCommand(pCmd);
	return 0;
}

int lua_Print(lua_State *lVM)
{
	_cprintf_s("Lua: %s\n", lua_tostring(lVM, 1));
	return 0;
}

int lua_Sleep(lua_State *lVM)
{
	Sleep(lua_tonumber(lVM, 1));
	return 0;
}

void CreateLuaMachine(string filename, int repeatTime, int repeatCount)
{
	lua_State* lVM = lua_open();
	lua_baselibopen(lVM);
	luaopen_table(lVM);
	luaopen_io(lVM);
	luaopen_string(lVM);
	luaopen_math(lVM);

	lua_register(lVM, "cmd", lua_ConsoleCommand);
	lua_register(lVM, "wait", lua_Sleep);
	lua_register(lVM, "print", lua_Print);
	//lua_register(lVM, "keyDown", lua_CheckKeyDown);
	//lua_register(lVM, "keyDown_Press", lua_CheckKeyDownPress);
	//lua_register(lVM, "getCVar", lua_GetCVar);
	//lua_register(lVM, "setCVar", lua_SetCVar);

	//lua_register(lVM, "PixelGetColor", lua_PixelGetColor);
	//lua_register(lVM, "SendKey", lua_SendKey);
	//lua_register(lVM, "MouseMove", lua_MouseMove);
	//lua_register(lVM, "MouseClick", lua_MouseClick);

	char fqp[1024];
	GetModuleFileName(hCurrentModule, fqp, 1024);
	string spec = fqp;
	string path = spec.substr(0, spec.find_last_of("\\"));

	static LuaMachineParams lmp;
	lmp.lVM = lVM;
	strcpy(lmp.filename, ((string)(path + "\\" + filename)).c_str());
	strcpy(lmp.friendly, filename.c_str());
	lmp.repeatMs = repeatTime;
	lmp.repeatNum = repeatCount;
	lmp.running = false;
	lmp.completed = false;
	lmp.terminateFlag = false;
	lmp.started = false;

	ifstream fLua(lmp.filename);
	if (fLua.good()) {
		iMachineCount++;
		Threads.push_back(lmp);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RunMachineThread, NULL, 0, 0);
	} else {
		_cprintf_s("File not found: %s\n", lmp.friendly);
	}
}

void PrintLuaStats(void)
{
	_cprintf_s("Lua script statistics\n");
	_cprintf_s("       Scripts running: %i\n", iMachineRunning);
	_cprintf_s("     Scripts completed: %i\n", iMachineCompleted);
	_cprintf_s("         Scripts Total: %i\n", iMachineCount);
	_cprintf_s("Lua scripts (running)\n");
	if (iMachineRunning == 0) {
		_cprintf_s("    none\n\n");
	} else {
		int cnt = 0;
		for(vector<LuaMachineParams>::iterator it = Threads.begin(); it != Threads.end(); ++it) {
			if (it->running) {
				cnt++;
				_cprintf_s("    %i. %s\n", cnt, it->friendly);
			}
		}
		_cprintf_s("\n");
	}
}

