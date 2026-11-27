/* Microsoft Layer for Unicode dispatch thunks. The modifiable slots initially call
   the thunks themselves. ResolveThunk installs the final target on first use. */
#include "versus_unicows_thunks.h"

LRESULT __stdcall user32_DispatchMessageW_Thunk(const MSG * lpMsg)
{
    ResolveThunk(user32_dll, name_DispatchMessageW, &slot_DispatchMessageW,
                 override_DispatchMessageW, (UnicowsEntry)GodotFailDispatchMessageW);
    return slot_DispatchMessageW(lpMsg);
}

HANDLE __stdcall kernel32_CreateMutexW_Thunk(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCWSTR lpName)
{
    ResolveThunk(kernel32_dll, name_CreateMutexW, &slot_CreateMutexW,
                 override_CreateMutexW, (UnicowsEntry)GodotFailCreateMutexW);
    return slot_CreateMutexW(lpMutexAttributes, bInitialOwner, lpName);
}

HANDLE __stdcall kernel32_FindFirstFileW_Thunk(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData)
{
    ResolveThunk(kernel32_dll, name_FindFirstFileW, &slot_FindFirstFileW,
                 override_FindFirstFileW, (UnicowsEntry)GodotFailFindFirstFileW);
    return slot_FindFirstFileW(lpFileName, lpFindFileData);
}

LRESULT __stdcall user32_SendMessageW_Thunk(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    ResolveThunk(user32_dll, name_SendMessageW, &slot_SendMessageW,
                 override_SendMessageW, (UnicowsEntry)GodotFailSendMessageW);
    return slot_SendMessageW(hWnd, Msg, wParam, lParam);
}

int __stdcall user32_MessageBoxW_Thunk(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
    ResolveThunk(user32_dll, name_MessageBoxW, &slot_MessageBoxW,
                 override_MessageBoxW, (UnicowsEntry)GodotFailMessageBoxW);
    return slot_MessageBoxW(hWnd, lpText, lpCaption, uType);
}

BOOL __stdcall kernel32_CreateDirectoryW_Thunk(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
    ResolveThunk(kernel32_dll, name_CreateDirectoryW, &slot_CreateDirectoryW,
                 override_CreateDirectoryW, (UnicowsEntry)GodotFailCreateDirectoryW);
    return slot_CreateDirectoryW(lpPathName, lpSecurityAttributes);
}

HWND __stdcall user32_CreateDialogParamW_Thunk(HINSTANCE hInstance, LPCWSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
    ResolveThunk(user32_dll, name_CreateDialogParamW, &slot_CreateDialogParamW,
                 override_CreateDialogParamW, (UnicowsEntry)GodotFailCreateDialogParamW);
    return slot_CreateDialogParamW(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

UINT __stdcall kernel32_GetSystemDirectoryW_Thunk(LPWSTR lpBuffer, UINT uSize)
{
    ResolveThunk(kernel32_dll, name_GetSystemDirectoryW, &slot_GetSystemDirectoryW,
                 override_GetSystemDirectoryW, (UnicowsEntry)GodotFailGetSystemDirectoryW);
    return slot_GetSystemDirectoryW(lpBuffer, uSize);
}

BOOL __stdcall user32_PeekMessageW_Thunk(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
    ResolveThunk(user32_dll, name_PeekMessageW, &slot_PeekMessageW,
                 override_PeekMessageW, (UnicowsEntry)GodotFailPeekMessageW);
    return slot_PeekMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

BOOL __stdcall kernel32_CopyFileW_Thunk(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, BOOL bFailIfExists)
{
    ResolveThunk(kernel32_dll, name_CopyFileW, &slot_CopyFileW,
                 override_CopyFileW, (UnicowsEntry)GodotFailCopyFileW);
    return slot_CopyFileW(lpExistingFileName, lpNewFileName, bFailIfExists);
}

HICON __stdcall user32_LoadIconW_Thunk(HINSTANCE hInstance, LPCWSTR lpIconName)
{
    ResolveThunk(user32_dll, name_LoadIconW, &slot_LoadIconW,
                 override_LoadIconW, (UnicowsEntry)GodotFailLoadIconW);
    return slot_LoadIconW(hInstance, lpIconName);
}

DWORD __stdcall kernel32_GetModuleFileNameW_Thunk(HMODULE hModule, LPWSTR lpFilename, DWORD nSize)
{
    ResolveThunk(kernel32_dll, name_GetModuleFileNameW, &slot_GetModuleFileNameW,
                 override_GetModuleFileNameW, (UnicowsEntry)GodotFailGetModuleFileNameW);
    return slot_GetModuleFileNameW(hModule, lpFilename, nSize);
}

HANDLE __stdcall kernel32_CreateFileW_Thunk(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    ResolveThunk(kernel32_dll, name_CreateFileW, &slot_CreateFileW,
                 override_CreateFileW, (UnicowsEntry)GodotFailCreateFileW);
    return slot_CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

BOOL __stdcall user32_SetPropW_Thunk(HWND hWnd, LPCWSTR lpString, HANDLE hData)
{
    ResolveThunk(user32_dll, name_SetPropW, &slot_SetPropW,
                 override_SetPropW, (UnicowsEntry)GodotFailSetPropW);
    return slot_SetPropW(hWnd, lpString, hData);
}

DWORD __stdcall kernel32_GetCurrentDirectoryW_Thunk(DWORD nBufferLength, LPWSTR lpBuffer)
{
    ResolveThunk(kernel32_dll, name_GetCurrentDirectoryW, &slot_GetCurrentDirectoryW,
                 override_GetCurrentDirectoryW, (UnicowsEntry)GodotFailGetCurrentDirectoryW);
    return slot_GetCurrentDirectoryW(nBufferLength, lpBuffer);
}

BOOL __stdcall kernel32_MoveFileW_Thunk(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName)
{
    ResolveThunk(kernel32_dll, name_MoveFileW, &slot_MoveFileW,
                 override_MoveFileW, (UnicowsEntry)GodotFailMoveFileW);
    return slot_MoveFileW(lpExistingFileName, lpNewFileName);
}

HINSTANCE __stdcall shell32_ShellExecuteW_Thunk(HWND hwnd, LPCWSTR lpOperation, LPCWSTR lpFile, LPCWSTR lpParameters, LPCWSTR lpDirectory, INT nShowCmd)
{
    ResolveThunk(shell32_dll, name_ShellExecuteW, &slot_ShellExecuteW,
                 override_ShellExecuteW, (UnicowsEntry)GodotFailShellExecuteW);
    return slot_ShellExecuteW(hwnd, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd);
}

BOOL __stdcall kernel32_SetCurrentDirectoryW_Thunk(LPCWSTR lpPathName)
{
    ResolveThunk(kernel32_dll, name_SetCurrentDirectoryW, &slot_SetCurrentDirectoryW,
                 override_SetCurrentDirectoryW, (UnicowsEntry)GodotFailSetCurrentDirectoryW);
    return slot_SetCurrentDirectoryW(lpPathName);
}

BOOL __stdcall kernel32_RemoveDirectoryW_Thunk(LPCWSTR lpPathName)
{
    ResolveThunk(kernel32_dll, name_RemoveDirectoryW, &slot_RemoveDirectoryW,
                 override_RemoveDirectoryW, (UnicowsEntry)GodotFailRemoveDirectoryW);
    return slot_RemoveDirectoryW(lpPathName);
}

UINT __stdcall user32_RegisterWindowMessageW_Thunk(LPCWSTR lpString)
{
    ResolveThunk(user32_dll, name_RegisterWindowMessageW, &slot_RegisterWindowMessageW,
                 override_RegisterWindowMessageW, (UnicowsEntry)GodotFailRegisterWindowMessageW);
    return slot_RegisterWindowMessageW(lpString);
}

BOOL __stdcall kernel32_FindNextFileW_Thunk(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData)
{
    ResolveThunk(kernel32_dll, name_FindNextFileW, &slot_FindNextFileW,
                 override_FindNextFileW, (UnicowsEntry)GodotFailFindNextFileW);
    return slot_FindNextFileW(hFindFile, lpFindFileData);
}

BOOL __stdcall kernel32_GetFileAttributesExW_Thunk(LPCWSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation)
{
    ResolveThunk(kernel32_dll, name_GetFileAttributesExW, &slot_GetFileAttributesExW,
                 override_GetFileAttributesExW, (UnicowsEntry)GodotFailGetFileAttributesExW);
    return slot_GetFileAttributesExW(lpFileName, fInfoLevelId, lpFileInformation);
}

HANDLE __stdcall user32_RemovePropW_Thunk(HWND hWnd, LPCWSTR lpString)
{
    ResolveThunk(user32_dll, name_RemovePropW, &slot_RemovePropW,
                 override_RemovePropW, (UnicowsEntry)GodotFailRemovePropW);
    return slot_RemovePropW(hWnd, lpString);
}

UINT __stdcall kernel32_GetWindowsDirectoryW_Thunk(LPWSTR lpBuffer, UINT uSize)
{
    ResolveThunk(kernel32_dll, name_GetWindowsDirectoryW, &slot_GetWindowsDirectoryW,
                 override_GetWindowsDirectoryW, (UnicowsEntry)GodotFailGetWindowsDirectoryW);
    return slot_GetWindowsDirectoryW(lpBuffer, uSize);
}

BOOL __stdcall kernel32_DeleteFileW_Thunk(LPCWSTR lpFileName)
{
    ResolveThunk(kernel32_dll, name_DeleteFileW, &slot_DeleteFileW,
                 override_DeleteFileW, (UnicowsEntry)GodotFailDeleteFileW);
    return slot_DeleteFileW(lpFileName);
}

BOOL __stdcall kernel32_SetFileAttributesW_Thunk(LPCWSTR lpFileName, DWORD dwFileAttributes)
{
    ResolveThunk(kernel32_dll, name_SetFileAttributesW, &slot_SetFileAttributesW,
                 override_SetFileAttributesW, (UnicowsEntry)GodotFailSetFileAttributesW);
    return slot_SetFileAttributesW(lpFileName, dwFileAttributes);
}

int __stdcall kernel32_WideCharToMultiByte_Thunk(UINT CodePage, DWORD dwFlags, LPCWCH lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar)
{
    ResolveThunk(kernel32_dll, name_WideCharToMultiByte, &slot_WideCharToMultiByte,
                 override_WideCharToMultiByte, (UnicowsEntry)GodotFailWideCharToMultiByte);
    return slot_WideCharToMultiByte(CodePage, dwFlags, lpWideCharStr, cchWideChar, lpMultiByteStr, cbMultiByte, lpDefaultChar, lpUsedDefaultChar);
}

int __stdcall kernel32_MultiByteToWideChar_Thunk(UINT CodePage, DWORD dwFlags, LPCCH lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar)
{
    ResolveThunk(kernel32_dll, name_MultiByteToWideChar, &slot_MultiByteToWideChar,
                 override_MultiByteToWideChar, (UnicowsEntry)GodotFailMultiByteToWideChar);
    return slot_MultiByteToWideChar(CodePage, dwFlags, lpMultiByteStr, cbMultiByte, lpWideCharStr, cchWideChar);
}

DWORD __stdcall kernel32_FormatMessageW_Thunk(DWORD dwFlags, LPCVOID lpSource, DWORD dwMessageId, DWORD dwLanguageId, LPWSTR lpBuffer, DWORD nSize, va_list * Arguments)
{
    ResolveThunk(kernel32_dll, name_FormatMessageW, &slot_FormatMessageW,
                 override_FormatMessageW, (UnicowsEntry)GodotFailFormatMessageW);
    return slot_FormatMessageW(dwFlags, lpSource, dwMessageId, dwLanguageId, lpBuffer, nSize, Arguments);
}

HANDLE __stdcall user32_GetClipboardData_Thunk(UINT uFormat)
{
    ResolveThunk(user32_dll, name_GetClipboardData, &slot_GetClipboardData,
                 override_GetClipboardData, (UnicowsEntry)GodotFailGetClipboardData);
    return slot_GetClipboardData(uFormat);
}

BOOL __stdcall kernel32_GetVersionExW_Thunk(LPOSVERSIONINFOW lpVersionInformation)
{
    ResolveThunk(kernel32_dll, name_GetVersionExW, &slot_GetVersionExW,
                 override_GetVersionExW, (UnicowsEntry)GodotFailGetVersionExW);
    return slot_GetVersionExW(lpVersionInformation);
}

FARPROC __stdcall kernel32_GetProcAddress_Thunk(HMODULE hModule, LPCSTR lpProcName)
{
    ResolveThunk(kernel32_dll, name_GetProcAddress, &slot_GetProcAddress,
                 override_GetProcAddress, (UnicowsEntry)GodotFailGetProcAddress);
    return slot_GetProcAddress(hModule, lpProcName);
}

BOOL __stdcall kernel32_CreateProcessW_Thunk(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)
{
    ResolveThunk(kernel32_dll, name_CreateProcessW, &slot_CreateProcessW,
                 override_CreateProcessW, (UnicowsEntry)GodotFailCreateProcessW);
    return slot_CreateProcessW(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
}

BOOL __stdcall kernel32_GetComputerNameW_Thunk(LPWSTR lpBuffer, LPDWORD nSize)
{
    ResolveThunk(kernel32_dll, name_GetComputerNameW, &slot_GetComputerNameW,
                 override_GetComputerNameW, (UnicowsEntry)GodotFailGetComputerNameW);
    return slot_GetComputerNameW(lpBuffer, nSize);
}

HINSTANCE __stdcall shell32_FindExecutableW_Thunk(LPCWSTR lpFile, LPCWSTR lpDirectory, LPWSTR lpResult)
{
    ResolveThunk(shell32_dll, name_FindExecutableW, &slot_FindExecutableW,
                 override_FindExecutableW, (UnicowsEntry)GodotFailFindExecutableW);
    return slot_FindExecutableW(lpFile, lpDirectory, lpResult);
}

HANDLE __stdcall kernel32_CreateEventW_Thunk(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCWSTR lpName)
{
    ResolveThunk(kernel32_dll, name_CreateEventW, &slot_CreateEventW,
                 override_CreateEventW, (UnicowsEntry)GodotFailCreateEventW);
    return slot_CreateEventW(lpEventAttributes, bManualReset, bInitialState, lpName);
}

HRSRC __stdcall kernel32_FindResourceW_Thunk(HMODULE hModule, LPCWSTR lpName, LPCWSTR lpType)
{
    ResolveThunk(kernel32_dll, name_FindResourceW, &slot_FindResourceW,
                 override_FindResourceW, (UnicowsEntry)GodotFailFindResourceW);
    return slot_FindResourceW(hModule, lpName, lpType);
}

HRSRC __stdcall kernel32_FindResourceExW_Thunk(HMODULE hModule, LPCWSTR lpType, LPCWSTR lpName, WORD wLanguage)
{
    ResolveThunk(kernel32_dll, name_FindResourceExW, &slot_FindResourceExW,
                 override_FindResourceExW, (UnicowsEntry)GodotFailFindResourceExW);
    return slot_FindResourceExW(hModule, lpType, lpName, wLanguage);
}

HCURSOR __stdcall user32_LoadCursorW_Thunk(HINSTANCE hInstance, LPCWSTR lpCursorName)
{
    ResolveThunk(user32_dll, name_LoadCursorW, &slot_LoadCursorW,
                 override_LoadCursorW, (UnicowsEntry)GodotFailLoadCursorW);
    return slot_LoadCursorW(hInstance, lpCursorName);
}

LONG __stdcall user32_SetWindowLongW_Thunk(HWND hWnd, int nIndex, LONG dwNewLong)
{
    ResolveThunk(user32_dll, name_SetWindowLongW, &slot_SetWindowLongW,
                 override_SetWindowLongW, (UnicowsEntry)GodotFailSetWindowLongW);
    return slot_SetWindowLongW(hWnd, nIndex, dwNewLong);
}

BOOL __stdcall user32_PostMessageW_Thunk(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    ResolveThunk(user32_dll, name_PostMessageW, &slot_PostMessageW,
                 override_PostMessageW, (UnicowsEntry)GodotFailPostMessageW);
    return slot_PostMessageW(hWnd, Msg, wParam, lParam);
}

int __stdcall user32_GetKeyNameTextW_Thunk(LONG lParam, LPWSTR lpString, int cchSize)
{
    ResolveThunk(user32_dll, name_GetKeyNameTextW, &slot_GetKeyNameTextW,
                 override_GetKeyNameTextW, (UnicowsEntry)GodotFailGetKeyNameTextW);
    return slot_GetKeyNameTextW(lParam, lpString, cchSize);
}

UINT __stdcall user32_MapVirtualKeyW_Thunk(UINT uCode, UINT uMapType)
{
    ResolveThunk(user32_dll, name_MapVirtualKeyW, &slot_MapVirtualKeyW,
                 override_MapVirtualKeyW, (UnicowsEntry)GodotFailMapVirtualKeyW);
    return slot_MapVirtualKeyW(uCode, uMapType);
}

LRESULT __stdcall user32_DefWindowProcW_Thunk(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    ResolveThunk(user32_dll, name_DefWindowProcW, &slot_DefWindowProcW,
                 override_DefWindowProcW, (UnicowsEntry)GodotFailDefWindowProcW);
    return slot_DefWindowProcW(hWnd, Msg, wParam, lParam);
}

LONG __stdcall user32_GetWindowLongW_Thunk(HWND hWnd, int nIndex)
{
    ResolveThunk(user32_dll, name_GetWindowLongW, &slot_GetWindowLongW,
                 override_GetWindowLongW, (UnicowsEntry)GodotFailGetWindowLongW);
    return slot_GetWindowLongW(hWnd, nIndex);
}

ATOM __stdcall kernel32_GlobalAddAtomW_Thunk(LPCWSTR lpString)
{
    ResolveThunk(kernel32_dll, name_GlobalAddAtomW, &slot_GlobalAddAtomW,
                 override_GlobalAddAtomW, (UnicowsEntry)GodotFailGlobalAddAtomW);
    return slot_GlobalAddAtomW(lpString);
}

BOOL __stdcall user32_SystemParametersInfoW_Thunk(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni)
{
    ResolveThunk(user32_dll, name_SystemParametersInfoW, &slot_SystemParametersInfoW,
                 override_SystemParametersInfoW, (UnicowsEntry)GodotFailSystemParametersInfoW);
    return slot_SystemParametersInfoW(uiAction, uiParam, pvParam, fWinIni);
}

BOOL __stdcall user32_EnableWindow_Thunk(HWND hWnd, BOOL bEnable)
{
    ResolveThunk(user32_dll, name_EnableWindow, &slot_EnableWindow,
                 override_EnableWindow, (UnicowsEntry)GodotFailEnableWindow);
    return slot_EnableWindow(hWnd, bEnable);
}

LRESULT __stdcall user32_CallWindowProcW_Thunk(WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    ResolveThunk(user32_dll, name_CallWindowProcW, &slot_CallWindowProcW,
                 override_CallWindowProcW, (UnicowsEntry)GodotFailCallWindowProcW);
    return slot_CallWindowProcW(lpPrevWndFunc, hWnd, Msg, wParam, lParam);
}

BOOL __stdcall user32_SetMenuItemInfoW_Thunk(HMENU hmenu, UINT item, BOOL fByPositon, LPCMENUITEMINFOW lpmii)
{
    ResolveThunk(user32_dll, name_SetMenuItemInfoW, &slot_SetMenuItemInfoW,
                 override_SetMenuItemInfoW, (UnicowsEntry)GodotFailSetMenuItemInfoW);
    return slot_SetMenuItemInfoW(hmenu, item, fByPositon, lpmii);
}

HWND __stdcall user32_CreateWindowExW_Thunk(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
    ResolveThunk(user32_dll, name_CreateWindowExW, &slot_CreateWindowExW,
                 override_CreateWindowExW, (UnicowsEntry)GodotFailCreateWindowExW);
    return slot_CreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

LRESULT __stdcall user32_DefMDIChildProcW_Thunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    ResolveThunk(user32_dll, name_DefMDIChildProcW, &slot_DefMDIChildProcW,
                 override_DefMDIChildProcW, (UnicowsEntry)GodotFailDefMDIChildProcW);
    return slot_DefMDIChildProcW(hWnd, uMsg, wParam, lParam);
}

HMODULE __stdcall kernel32_GetModuleHandleW_Thunk(LPCWSTR lpModuleName)
{
    ResolveThunk(kernel32_dll, name_GetModuleHandleW, &slot_GetModuleHandleW,
                 override_GetModuleHandleW, (UnicowsEntry)GodotFailGetModuleHandleW);
    return slot_GetModuleHandleW(lpModuleName);
}

HMODULE __stdcall kernel32_LoadLibraryW_Thunk(LPCWSTR lpLibFileName)
{
    ResolveThunk(kernel32_dll, name_LoadLibraryW, &slot_LoadLibraryW,
                 override_LoadLibraryW, (UnicowsEntry)GodotFailLoadLibraryW);
    return slot_LoadLibraryW(lpLibFileName);
}

HMENU __stdcall user32_LoadMenuW_Thunk(HINSTANCE hInstance, LPCWSTR lpMenuName)
{
    ResolveThunk(user32_dll, name_LoadMenuW, &slot_LoadMenuW,
                 override_LoadMenuW, (UnicowsEntry)GodotFailLoadMenuW);
    return slot_LoadMenuW(hInstance, lpMenuName);
}

ATOM __stdcall user32_RegisterClassExW_Thunk(const WNDCLASSEXW * arg1)
{
    ResolveThunk(user32_dll, name_RegisterClassExW, &slot_RegisterClassExW,
                 override_RegisterClassExW, (UnicowsEntry)GodotFailRegisterClassExW);
    return slot_RegisterClassExW(arg1);
}

BOOL __stdcall user32_GetClassInfoExW_Thunk(HINSTANCE hInstance, LPCWSTR lpszClass, LPWNDCLASSEXW lpwcx)
{
    ResolveThunk(user32_dll, name_GetClassInfoExW, &slot_GetClassInfoExW,
                 override_GetClassInfoExW, (UnicowsEntry)GodotFailGetClassInfoExW);
    return slot_GetClassInfoExW(hInstance, lpszClass, lpwcx);
}

BOOL __stdcall user32_GetMenuItemInfoW_Thunk(HMENU hmenu, UINT item, BOOL fByPosition, LPMENUITEMINFOW lpmii)
{
    ResolveThunk(user32_dll, name_GetMenuItemInfoW, &slot_GetMenuItemInfoW,
                 override_GetMenuItemInfoW, (UnicowsEntry)GodotFailGetMenuItemInfoW);
    return slot_GetMenuItemInfoW(hmenu, item, fByPosition, lpmii);
}

INT_PTR __stdcall user32_DialogBoxParamW_Thunk(HINSTANCE hInstance, LPCWSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
    ResolveThunk(user32_dll, name_DialogBoxParamW, &slot_DialogBoxParamW,
                 override_DialogBoxParamW, (UnicowsEntry)GodotFailDialogBoxParamW);
    return slot_DialogBoxParamW(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

BOOL __stdcall gdi32_GetTextExtentPoint32W_Thunk(HDC hdc, LPCWSTR lpString, int c, LPSIZE psizl)
{
    ResolveThunk(gdi32_dll, name_GetTextExtentPoint32W, &slot_GetTextExtentPoint32W,
                 override_GetTextExtentPoint32W, (UnicowsEntry)GodotFailGetTextExtentPoint32W);
    return slot_GetTextExtentPoint32W(hdc, lpString, c, psizl);
}

int __stdcall user32_DrawTextExW_Thunk(HDC hdc, LPWSTR lpchText, int cchText, LPRECT lprc, UINT format, LPDRAWTEXTPARAMS lpdtp)
{
    ResolveThunk(user32_dll, name_DrawTextExW, &slot_DrawTextExW,
                 override_DrawTextExW, (UnicowsEntry)GodotFailDrawTextExW);
    return slot_DrawTextExW(hdc, lpchText, cchText, lprc, format, lpdtp);
}

BOOL __stdcall gdi32_TextOutW_Thunk(HDC hdc, int x, int y, LPCWSTR lpString, int c)
{
    ResolveThunk(gdi32_dll, name_TextOutW, &slot_TextOutW,
                 override_TextOutW, (UnicowsEntry)GodotFailTextOutW);
    return slot_TextOutW(hdc, x, y, lpString, c);
}

BOOL __stdcall user32_SetPropA_Thunk(HWND hWnd, LPCSTR lpString, HANDLE hData)
{
    ResolveThunk(user32_dll, name_SetPropA, &slot_SetPropA,
                 override_SetPropA, (UnicowsEntry)GodotFailSetPropA);
    return slot_SetPropA(hWnd, lpString, hData);
}

HANDLE __stdcall user32_RemovePropA_Thunk(HWND hWnd, LPCSTR lpString)
{
    ResolveThunk(user32_dll, name_RemovePropA, &slot_RemovePropA,
                 override_RemovePropA, (UnicowsEntry)GodotFailRemovePropA);
    return slot_RemovePropA(hWnd, lpString);
}

HMODULE __stdcall kernel32_LoadLibraryExW_Thunk(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
{
    ResolveThunk(kernel32_dll, name_LoadLibraryExW, &slot_LoadLibraryExW,
                 override_LoadLibraryExW, (UnicowsEntry)GodotFailLoadLibraryExW);
    return slot_LoadLibraryExW(lpLibFileName, hFile, dwFlags);
}

BOOL __stdcall advapi32_GetUserNameW_Thunk(LPWSTR lpBuffer, LPDWORD pcbBuffer)
{
    ResolveThunk(advapi32_dll, name_GetUserNameW, &slot_GetUserNameW,
                 override_GetUserNameW, (UnicowsEntry)GodotFailGetUserNameW);
    return slot_GetUserNameW(lpBuffer, pcbBuffer);
}

LONG __stdcall advapi32_RegQueryValueExW_Thunk(HKEY hKey, LPCWSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
{
    ResolveThunk(advapi32_dll, name_RegQueryValueExW, &slot_RegQueryValueExW,
                 override_RegQueryValueExW, (UnicowsEntry)GodotFailRegQueryValueExW);
    return slot_RegQueryValueExW(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
}

LONG __stdcall advapi32_RegCreateKeyW_Thunk(HKEY hKey, LPCWSTR lpSubKey, PHKEY phkResult)
{
    ResolveThunk(advapi32_dll, name_RegCreateKeyW, &slot_RegCreateKeyW,
                 override_RegCreateKeyW, (UnicowsEntry)GodotFailRegCreateKeyW);
    return slot_RegCreateKeyW(hKey, lpSubKey, phkResult);
}

LONG __stdcall advapi32_RegSetValueExW_Thunk(HKEY hKey, LPCWSTR lpValueName, DWORD Reserved, DWORD dwType, const BYTE *lpData, DWORD cbData)
{
    ResolveThunk(advapi32_dll, name_RegSetValueExW, &slot_RegSetValueExW,
                 override_RegSetValueExW, (UnicowsEntry)GodotFailRegSetValueExW);
    return slot_RegSetValueExW(hKey, lpValueName, Reserved, dwType, lpData, cbData);
}

LONG __stdcall advapi32_RegOpenKeyW_Thunk(HKEY hKey, LPCWSTR lpSubKey, PHKEY phkResult)
{
    ResolveThunk(advapi32_dll, name_RegOpenKeyW, &slot_RegOpenKeyW,
                 override_RegOpenKeyW, (UnicowsEntry)GodotFailRegOpenKeyW);
    return slot_RegOpenKeyW(hKey, lpSubKey, phkResult);
}

LONG __stdcall user32_SetWindowLongA_Thunk(HWND hWnd, int nIndex, LONG dwNewLong)
{
    ResolveThunk(user32_dll, name_SetWindowLongA, &slot_SetWindowLongA,
                 override_SetWindowLongA, (UnicowsEntry)GodotFailSetWindowLongA);
    return slot_SetWindowLongA(hWnd, nIndex, dwNewLong);
}

LONG __stdcall user32_GetWindowLongA_Thunk(HWND hWnd, int nIndex)
{
    ResolveThunk(user32_dll, name_GetWindowLongA, &slot_GetWindowLongA,
                 override_GetWindowLongA, (UnicowsEntry)GodotFailGetWindowLongA);
    return slot_GetWindowLongA(hWnd, nIndex);
}

int __stdcall user32_DrawTextW_Thunk(HDC hdc, LPCWSTR lpchText, int cchText, LPRECT lprc, UINT format)
{
    ResolveThunk(user32_dll, name_DrawTextW, &slot_DrawTextW,
                 override_DrawTextW, (UnicowsEntry)GodotFailDrawTextW);
    return slot_DrawTextW(hdc, lpchText, cchText, lprc, format);
}

LRESULT __stdcall user32_CallWindowProcA_Thunk(WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    ResolveThunk(user32_dll, name_CallWindowProcA, &slot_CallWindowProcA,
                 override_CallWindowProcA, (UnicowsEntry)GodotFailCallWindowProcA);
    return slot_CallWindowProcA(lpPrevWndFunc, hWnd, Msg, wParam, lParam);
}
