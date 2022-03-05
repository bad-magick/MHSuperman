#include <string>

bool LoadDll(const wchar_t *procName, const wchar_t *dllName);
unsigned long GetTargetProcessIdFromProcname(const wchar_t *procName);
std::wstring GetTargetPathFromProcname(const wchar_t *procName);