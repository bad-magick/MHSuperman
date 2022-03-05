#pragma once //prevent the compiler from regenerating symbols for this file(important when included in multiple .cpp files)
#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"psapi.lib")

#define GAME_DLL

/*
HL2_EPISODIC
HL2_DLL
GAME_DLL
NDEBUG
NO_STRING_T
_WINDOWS
VECTOR
_WIN32
PROTECTED_THINGS_ENABLE
OFFTHERECORD
*/

#ifdef EATSHIT
/*#include "dlls/cbase.h"
#include "server_class.h"
#include "interface.h"
#include "filesystem.h"
#include "engine/iserverplugin.h"
#include "dlls/iplayerinfo.h"
#include "eiface.h"
#include "igameevents.h"
#include "convar.h"
#include "Color.h"
#include "vstdlib/random.h"
#include "engine/IEngineTrace.h"
#include "cdll_int.h"
#include "icvar.h"
#include "threadtools.h"*/

#include "dlls/cbase.h"
#include "server_class.h"
#include "cdll_int.h"			//IVEngineClient and IBaseClientDLL interfaces
#include "icliententitylist.h"	//IClientEntityList interface
#include "icvar.h"				//ICvar interface

#include "icliententity.h"		//IClientEntity class
#include "convar.h"				//ConVar and ConCommand classes
#include "inputsystem/iinputsystem.h"
#include "eiface.h"
#else
#include "interface.h"
#include "filesystem.h"
#include "engine/iserverplugin.h"
#include "dlls/iplayerinfo.h"
#include "eiface.h"
#include "igameevents.h"
#include "convar.h"
#include "Color.h"
#include "vstdlib/random.h"
#include "engine/IEngineTrace.h"
#include "cdll_int.h"
#include "icvar.h"
#include <conio.h>
#include <ctime>
#include "dlls/cbase.h"
#include "server_class.h"
#include "datacache/imdlcache.h"
#include "icliententity.h"
#include "icliententitylist.h"
#include "dt_recv.h"
#include "dt_send.h"
#include "networkstringtabledefs.h"
#include "cl_dll/input.h"
#include "client_class.h"
#include "dlls/variant_t.h"
#include "dlls/eventqueue.h"
//IMDLCache* mdlcache;
//#include "igamesystem.h"
//#include "igamesystem.cpp"
//#include "gamestringpool.h"
//#include "gamestringpool.cpp"

#include "eiface.h"
#include "inputsystem/iinputsystem.h"

#endif

#undef CreateThread	
#undef GetAsyncKeyState
#undef ARRAYSIZE
#undef GetCommandLine
#undef ReadConsoleInput
#undef RegCreateKey
#undef RegCreateKeyEx
#undef RegOpenKey
#undef RegOpenKeyEx
#undef RegQueryValue
#undef RegQueryValueEx
#undef RegSetValue
#undef RegSetValueEx

#ifdef _USE_MFC
	#undef ASSERT
	#undef THREAD_LOCAL
	//#undef CThreadLocal
#endif
//The source engine makes some funny defines, so we have to undefine them or we won't be able to use windows' functions with those names
//#undef CreateThread	
//#undef GetAsyncKeyState

