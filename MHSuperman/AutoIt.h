#ifndef _USE_MFC
	#include <Windows.h>
#else
	#include "stdafx.h"
#endif
;
class HS_SendKeys
{
public:
	// Functions
	HS_SendKeys();										// Constructor
	~HS_SendKeys();										// Destructor
	void	Init(void);									// Call this first to init the SendKeys engine

	void	Send(const char *szString, HWND hWnd = NULL);				// Send keystrokes
	void	SendRaw(const char *szSendKeys, HWND hWnd = NULL);			// Send keystrokes without interpretation

	void	SetKeyDelay(int n) { m_nKeyDelay = n; }						// Change delay between keypresses
	void	SetKeyDownDelay(int n) { m_nKeyDownDelay = n; }				// Change delay between keypresses
	void	SetStoreCapslockMode(bool b) {	m_bStoreCapslockMode = b; }	// Set capslock store mode
	void	SetAttachMode(bool b) {	m_bAttachMode = b; }				// Set attach mode
	bool	GetSingleVKandMods(const char *szString, UINT &vk, bool &bShift, bool &bControl, bool &bAlt, bool &bWin);
	void	MouseMove(int x, int y, int speed);
	void	MouseClick(char* button, int x, int y, int clicks, int speed);
	void	MouseClickDrag(char* button, int x1, int y1, int x2, int y2, int speed);
	int		MouseDown(char* szButton);
	int		MouseUp(char* szButton);

	// Variables
	int		m_nKeyDelay;								// Time in between keystrokes
	int		m_nKeyDownDelay;							// Delay after pressing the key down before releasing
	bool	m_bStoreCapslockMode;						// Store/restore capslock state
	bool	m_bAttachMode;								// Attach mode for Send()


private:
	// Variables
	int		m_nKeyMod;									// Key modifiers
	HWND	m_hWnd;										// Window to send to (NULL=active window)

	UINT	m_scanCtrl, m_scanAlt, m_scanShift, m_scanLWin;

	// Functions
	void	WinAttach(HWND hWnd, bool bAttach);
	inline void DoKeyDelay(void) { Sleep(m_nKeyDelay); }
	inline void DoKeyDownDelay(void) { Sleep(m_nKeyDownDelay); }
	bool	SetToggleState(UINT vk, bool bState);
	void	SendCh(char ch, int nRep);
	void	SendVk(UINT vk, int nRep, bool bForceExtended = false);
	void	SendSpecialCh(char ch);
	void	ResolveKeyModifiers(UINT vkres);
	bool	IsVKExtended(UINT key);
	void	SimModsUp();
	void	SimModsDown();
	void	SimKeyUp(UINT vk, bool bForceExtended = false);
	void	SimKeyDown(UINT vk, bool bForceExtended = false);
	void	SimKeystroke(UINT vk, bool bForceExtended = false);
	void	SendSpecial(char *szTemp);

	int		ReadToChar(char ch, const char *szLine, char *szResult, int &nPos);
	void	MouseMoveExecute(int x, int y, int nSpeed);

};
