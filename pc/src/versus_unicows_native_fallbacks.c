#include "versus_unicows_thunks.h"

__declspec(dllimport) HMODULE __stdcall GetModuleHandleA(LPCSTR name);
__declspec(dllimport) void __stdcall SetLastError(DWORD error);

#define ERROR_PROC_NOT_FOUND 127L
#define ERROR_CALL_NOT_IMPLEMENTED 120L

/* Failure.obj forwards through an unprototyped Win32 procedure. In particular, the C
   call promotes the language WORD passed by FindResourceExW. */
HRSRC __stdcall GodotFailFindResourceW(HMODULE hModule, LPCWSTR lpName, LPCWSTR lpType)
{
    FARPROC proc = (FARPROC)GetProcAddressInternal(
        GetModuleHandleA(kernel32_dll), "FindResourceW");
    if (proc)
        return (HRSRC)proc(hModule, lpName, lpType);
    SetLastError(ERROR_PROC_NOT_FOUND);
    return 0;
}

HRSRC __stdcall GodotFailFindResourceExW(HMODULE hModule, LPCWSTR lpType, LPCWSTR lpName, WORD wLanguage)
{
    FARPROC proc = (FARPROC)GetProcAddressInternal(
        GetModuleHandleA(kernel32_dll), "FindResourceExW");
    if (proc)
        return (HRSRC)proc(hModule, lpType, lpName, wLanguage);
    SetLastError(ERROR_PROC_NOT_FOUND);
    return 0;
}

FARPROC __stdcall GodotFailGetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
    return (FARPROC)GetProcAddressInternal(hModule, lpProcName);
}

int __stdcall GodotFailMultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCCH lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar)
{
    FARPROC proc = (FARPROC)GetProcAddressInternal(
        GetModuleHandleA(kernel32_dll), "MultiByteToWideChar");
    if (proc)
        return proc(CodePage, dwFlags, lpMultiByteStr, cbMultiByte, lpWideCharStr, cchWideChar);
    SetLastError(ERROR_PROC_NOT_FOUND);
    return 0;
}

int __stdcall GodotFailWideCharToMultiByte(UINT CodePage, DWORD dwFlags, LPCWCH lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar)
{
    FARPROC proc = (FARPROC)GetProcAddressInternal(
        GetModuleHandleA(kernel32_dll), "WideCharToMultiByte");
    if (proc)
        return proc(CodePage, dwFlags, lpWideCharStr, cchWideChar, lpMultiByteStr, cbMultiByte, lpDefaultChar, lpUsedDefaultChar);
    SetLastError(ERROR_PROC_NOT_FOUND);
    return 0;
}

BOOL __stdcall GodotFailEnableWindow(HWND hWnd, BOOL bEnable)
{
    FARPROC proc = (FARPROC)GetProcAddressInternal(
        GetModuleHandleA(user32_dll), "EnableWindow");
    if (proc)
        return proc(hWnd, bEnable);
    SetLastError(ERROR_PROC_NOT_FOUND);
    return 0;
}

HANDLE __stdcall GodotFailGetClipboardData(UINT uFormat)
{
    FARPROC proc = (FARPROC)GetProcAddressInternal(
        GetModuleHandleA(user32_dll), "GetClipboardData");
    if (proc)
        return (HANDLE)proc(uFormat);
    SetLastError(ERROR_PROC_NOT_FOUND);
    return 0;
}

LONG __stdcall GodotFailGetWindowLongA(HWND hWnd, int nIndex)
{
    FARPROC proc = (FARPROC)GetProcAddressInternal(
        GetModuleHandleA(user32_dll), "GetWindowLongA");
    if (proc)
        return proc(hWnd, nIndex);
    SetLastError(ERROR_PROC_NOT_FOUND);
    return 0;
}

int __stdcall GodotFailMessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
    FARPROC proc = (FARPROC)GetProcAddressInternal(
        GetModuleHandleA(user32_dll), "MessageBoxW");
    if (proc)
        return proc(hWnd, lpText, lpCaption, uType);
    SetLastError(ERROR_PROC_NOT_FOUND);
    return 0;
}

HANDLE __stdcall GodotFailRemovePropA(HWND hWnd, LPCSTR lpString)
{
    FARPROC proc = (FARPROC)GetProcAddressInternal(
        GetModuleHandleA(user32_dll), "RemovePropA");
    if (proc)
        return (HANDLE)proc(hWnd, lpString);
    SetLastError(ERROR_PROC_NOT_FOUND);
    return 0;
}

BOOL __stdcall GodotFailSetPropA(HWND hWnd, LPCSTR lpString, HANDLE hData)
{
    FARPROC proc = (FARPROC)GetProcAddressInternal(
        GetModuleHandleA(user32_dll), "SetPropA");
    if (proc)
        return proc(hWnd, lpString, hData);
    SetLastError(ERROR_PROC_NOT_FOUND);
    return 0;
}

LONG __stdcall GodotFailSetWindowLongA(HWND hWnd, int nIndex, LONG dwNewLong)
{
    FARPROC proc = (FARPROC)GetProcAddressInternal(
        GetModuleHandleA(user32_dll), "SetWindowLongA");
    if (proc)
        return proc(hWnd, nIndex, dwNewLong);
    SetLastError(ERROR_PROC_NOT_FOUND);
    return 0;
}

BOOL __stdcall GodotFailGetTextExtentPoint32W(HDC hdc, LPCWSTR lpString, int c, LPSIZE psizl)
{
    FARPROC proc = (FARPROC)GetProcAddressInternal(
        GetModuleHandleA(gdi32_dll), "GetTextExtentPoint32W");
    if (proc)
        return proc(hdc, lpString, c, psizl);
    SetLastError(ERROR_PROC_NOT_FOUND);
    return 0;
}

BOOL __stdcall GodotFailTextOutW(HDC hdc, int x, int y, LPCWSTR lpString, int c)
{
    FARPROC proc = (FARPROC)GetProcAddressInternal(
        GetModuleHandleA(gdi32_dll), "TextOutW");
    if (proc)
        return proc(hdc, x, y, lpString, c);
    SetLastError(ERROR_PROC_NOT_FOUND);
    return 0;
}

LONG __stdcall GodotFailRegCreateKeyW(HKEY hKey, LPCWSTR lpSubKey, PHKEY phkResult)
{
    return ERROR_CALL_NOT_IMPLEMENTED;
}

LONG __stdcall GodotFailRegQueryValueExW(HKEY hKey, LPCWSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
{
    return ERROR_CALL_NOT_IMPLEMENTED;
}
