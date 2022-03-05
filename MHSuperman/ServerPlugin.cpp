#define GAME_DLL  //need this at top

#include "engine/iserverplugin.h"
#include "igameevents.h"

BOOL bPluginLoaded = FALSE;
void (__cdecl *pRunSpawnCommands)(void) = (void (__cdecl *)(void))NULL;
//void RunSpawnCommands(void)0x0;

//need class.. I have in main cpp but can be in header or w/e
class CPlugin: public IServerPluginCallbacks, public IGameEventListener
{
public:
	CPlugin();
	~CPlugin();
	// IServerPluginCallbacks methods
	virtual bool			Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory);
	virtual void			Unload( void );
	virtual void			Pause( void );
	virtual void			UnPause( void );
	virtual const char     *GetPluginDescription( void );      
	virtual void			LevelInit( char const *pMapName );
	virtual void			ServerActivate( edict_t *pEdictList, int edictCount, int clientMax );
	virtual void			GameFrame( bool simulating );
	virtual void			LevelShutdown( void );
	virtual void			ClientActive( edict_t *pEntity );
	virtual void			ClientDisconnect( edict_t *pEntity );
	virtual void			ClientPutInServer( edict_t *pEntity, char const *playername );
	virtual void			SetCommandClient( int index );
	virtual void			ClientSettingsChanged( edict_t *pEdict );
	virtual PLUGIN_RESULT	ClientConnect( bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen );
	virtual PLUGIN_RESULT	ClientCommand( edict_t *pEntity );
	virtual PLUGIN_RESULT	NetworkIDValidated( const char *pszUserName, const char *pszNetworkID );
	// IGameEventListener Interface
	virtual void FireGameEvent( KeyValues * event );
	virtual int GetCommandIndex() { return m_iClientCommandIndex; }
private:
	int m_iClientCommandIndex;
};

CPlugin g_EmtpyServerPlugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CPlugin, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, g_EmtpyServerPlugin);
CPlugin::CPlugin() {}
CPlugin::~CPlugin() {}

//on load interface hooks
bool CPlugin::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory){
	bPluginLoaded = TRUE;
	return true;
}

//pretty much unused shit
void CPlugin::Unload(void) {}
void CPlugin::Pause(void) {}
void CPlugin::UnPause(void) {}
const char *CPlugin::GetPluginDescription(void) {return ".";}
void CPlugin::LevelInit(char const *pMapName) {}
void CPlugin::ServerActivate(edict_t *pEdictList, int edictCount, int clientMax) {}
void CPlugin::GameFrame(bool simulating) {}
void CPlugin::LevelShutdown(void) {}/////////////////
void CPlugin::ClientActive(edict_t *pEntity) {
	if (&pRunSpawnCommands != NULL) {
		pRunSpawnCommands();
	}
}
void CPlugin::ClientDisconnect(edict_t *pEntity) {}
void CPlugin::ClientPutInServer(edict_t *pEntity, char const *playername) {}
void CPlugin::SetCommandClient(int index) {}
void CPlugin::ClientSettingsChanged(edict_t *pEdict) {}
PLUGIN_RESULT CPlugin::ClientConnect(bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen) {return PLUGIN_CONTINUE;}
PLUGIN_RESULT CPlugin::ClientCommand(edict_t *pEntity) {return PLUGIN_CONTINUE;}
PLUGIN_RESULT CPlugin::NetworkIDValidated(const char *pszUserName, const char *pszNetworkID) {return PLUGIN_CONTINUE;}
void CPlugin::FireGameEvent(KeyValues * event){}

