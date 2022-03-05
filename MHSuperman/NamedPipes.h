#include <stdio.h>
#include <windows.h>
#include <string>

void InitPipes(void);
void SendSpew(char* pChr);
void SendMsg(char* pChr);
void SendDevMsg(char* pChr);
void SendWarning(char* pChr);
void SendData1(char* pChr);
void SendData1(std::string s);
