#ifndef VERSUS_UNICOWS_THUNKS_H
#define VERSUS_UNICOWS_THUNKS_H

#include "windows_dispatch_types.h"
#include "versus_unicows_resolve.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const char user32_dll[];
extern const char kernel32_dll[];
extern const char shell32_dll[];
extern const char gdi32_dll[];

LRESULT __stdcall user32_DispatchMessageW_Thunk(const MSG * lpMsg);
LRESULT __stdcall GodotFailDispatchMessageW(const MSG *);
extern const char name_DispatchMessageW[];
typedef LRESULT (__stdcall *DispatchMessageWProc)(const MSG *);
extern DispatchMessageWProc slot_DispatchMessageW;
extern UnicowsEntry override_DispatchMessageW;

HANDLE __stdcall kernel32_CreateMutexW_Thunk(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCWSTR lpName);
HANDLE __stdcall GodotFailCreateMutexW(LPSECURITY_ATTRIBUTES, BOOL, LPCWSTR);
extern const char name_CreateMutexW[];
typedef HANDLE (__stdcall *CreateMutexWProc)(LPSECURITY_ATTRIBUTES, BOOL, LPCWSTR);
extern CreateMutexWProc slot_CreateMutexW;
extern UnicowsEntry override_CreateMutexW;

HANDLE __stdcall kernel32_FindFirstFileW_Thunk(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);
HANDLE __stdcall GodotFailFindFirstFileW(LPCWSTR, LPWIN32_FIND_DATAW);
extern const char name_FindFirstFileW[];
typedef HANDLE (__stdcall *FindFirstFileWProc)(LPCWSTR, LPWIN32_FIND_DATAW);
extern FindFirstFileWProc slot_FindFirstFileW;
extern UnicowsEntry override_FindFirstFileW;

LRESULT __stdcall user32_SendMessageW_Thunk(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall GodotFailSendMessageW(HWND, UINT, WPARAM, LPARAM);
extern const char name_SendMessageW[];
typedef LRESULT (__stdcall *SendMessageWProc)(HWND, UINT, WPARAM, LPARAM);
extern SendMessageWProc slot_SendMessageW;
extern UnicowsEntry override_SendMessageW;

int __stdcall user32_MessageBoxW_Thunk(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType);
int __stdcall GodotFailMessageBoxW(HWND, LPCWSTR, LPCWSTR, UINT);
extern const char name_MessageBoxW[];
typedef int (__stdcall *MessageBoxWProc)(HWND, LPCWSTR, LPCWSTR, UINT);
extern MessageBoxWProc slot_MessageBoxW;
extern UnicowsEntry override_MessageBoxW;

BOOL __stdcall kernel32_CreateDirectoryW_Thunk(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
BOOL __stdcall GodotFailCreateDirectoryW(LPCWSTR, LPSECURITY_ATTRIBUTES);
extern const char name_CreateDirectoryW[];
typedef BOOL (__stdcall *CreateDirectoryWProc)(LPCWSTR, LPSECURITY_ATTRIBUTES);
extern CreateDirectoryWProc slot_CreateDirectoryW;
extern UnicowsEntry override_CreateDirectoryW;

HWND __stdcall user32_CreateDialogParamW_Thunk(HINSTANCE hInstance, LPCWSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam);
HWND __stdcall GodotFailCreateDialogParamW(HINSTANCE, LPCWSTR, HWND, DLGPROC, LPARAM);
extern const char name_CreateDialogParamW[];
typedef HWND (__stdcall *CreateDialogParamWProc)(HINSTANCE, LPCWSTR, HWND, DLGPROC, LPARAM);
extern CreateDialogParamWProc slot_CreateDialogParamW;
extern UnicowsEntry override_CreateDialogParamW;

UINT __stdcall kernel32_GetSystemDirectoryW_Thunk(LPWSTR lpBuffer, UINT uSize);
UINT __stdcall GodotFailGetSystemDirectoryW(LPWSTR, UINT);
extern const char name_GetSystemDirectoryW[];
typedef UINT (__stdcall *GetSystemDirectoryWProc)(LPWSTR, UINT);
extern GetSystemDirectoryWProc slot_GetSystemDirectoryW;
extern UnicowsEntry override_GetSystemDirectoryW;

BOOL __stdcall user32_PeekMessageW_Thunk(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
BOOL __stdcall GodotFailPeekMessageW(LPMSG, HWND, UINT, UINT, UINT);
extern const char name_PeekMessageW[];
typedef BOOL (__stdcall *PeekMessageWProc)(LPMSG, HWND, UINT, UINT, UINT);
extern PeekMessageWProc slot_PeekMessageW;
extern UnicowsEntry override_PeekMessageW;

BOOL __stdcall kernel32_CopyFileW_Thunk(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, BOOL bFailIfExists);
BOOL __stdcall GodotFailCopyFileW(LPCWSTR, LPCWSTR, BOOL);
extern const char name_CopyFileW[];
typedef BOOL (__stdcall *CopyFileWProc)(LPCWSTR, LPCWSTR, BOOL);
extern CopyFileWProc slot_CopyFileW;
extern UnicowsEntry override_CopyFileW;

HICON __stdcall user32_LoadIconW_Thunk(HINSTANCE hInstance, LPCWSTR lpIconName);
HICON __stdcall GodotFailLoadIconW(HINSTANCE, LPCWSTR);
extern const char name_LoadIconW[];
typedef HICON (__stdcall *LoadIconWProc)(HINSTANCE, LPCWSTR);
extern LoadIconWProc slot_LoadIconW;
extern UnicowsEntry override_LoadIconW;

DWORD __stdcall kernel32_GetModuleFileNameW_Thunk(HMODULE hModule, LPWSTR lpFilename, DWORD nSize);
DWORD __stdcall GodotFailGetModuleFileNameW(HMODULE, LPWSTR, DWORD);
extern const char name_GetModuleFileNameW[];
typedef DWORD (__stdcall *GetModuleFileNameWProc)(HMODULE, LPWSTR, DWORD);
extern GetModuleFileNameWProc slot_GetModuleFileNameW;
extern UnicowsEntry override_GetModuleFileNameW;

HANDLE __stdcall kernel32_CreateFileW_Thunk(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
HANDLE __stdcall GodotFailCreateFileW(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
extern const char name_CreateFileW[];
typedef HANDLE (__stdcall *CreateFileWProc)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
extern CreateFileWProc slot_CreateFileW;
extern UnicowsEntry override_CreateFileW;

BOOL __stdcall user32_SetPropW_Thunk(HWND hWnd, LPCWSTR lpString, HANDLE hData);
BOOL __stdcall GodotFailSetPropW(HWND, LPCWSTR, HANDLE);
extern const char name_SetPropW[];
typedef BOOL (__stdcall *SetPropWProc)(HWND, LPCWSTR, HANDLE);
extern SetPropWProc slot_SetPropW;
extern UnicowsEntry override_SetPropW;

DWORD __stdcall kernel32_GetCurrentDirectoryW_Thunk(DWORD nBufferLength, LPWSTR lpBuffer);
DWORD __stdcall GodotFailGetCurrentDirectoryW(DWORD, LPWSTR);
extern const char name_GetCurrentDirectoryW[];
typedef DWORD (__stdcall *GetCurrentDirectoryWProc)(DWORD, LPWSTR);
extern GetCurrentDirectoryWProc slot_GetCurrentDirectoryW;
extern UnicowsEntry override_GetCurrentDirectoryW;

BOOL __stdcall kernel32_MoveFileW_Thunk(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName);
BOOL __stdcall GodotFailMoveFileW(LPCWSTR, LPCWSTR);
extern const char name_MoveFileW[];
typedef BOOL (__stdcall *MoveFileWProc)(LPCWSTR, LPCWSTR);
extern MoveFileWProc slot_MoveFileW;
extern UnicowsEntry override_MoveFileW;

HINSTANCE __stdcall shell32_ShellExecuteW_Thunk(HWND hwnd, LPCWSTR lpOperation, LPCWSTR lpFile, LPCWSTR lpParameters, LPCWSTR lpDirectory, INT nShowCmd);
HINSTANCE __stdcall GodotFailShellExecuteW(HWND, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, INT);
extern const char name_ShellExecuteW[];
typedef HINSTANCE (__stdcall *ShellExecuteWProc)(HWND, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, INT);
extern ShellExecuteWProc slot_ShellExecuteW;
extern UnicowsEntry override_ShellExecuteW;

BOOL __stdcall kernel32_SetCurrentDirectoryW_Thunk(LPCWSTR lpPathName);
BOOL __stdcall GodotFailSetCurrentDirectoryW(LPCWSTR);
extern const char name_SetCurrentDirectoryW[];
typedef BOOL (__stdcall *SetCurrentDirectoryWProc)(LPCWSTR);
extern SetCurrentDirectoryWProc slot_SetCurrentDirectoryW;
extern UnicowsEntry override_SetCurrentDirectoryW;

BOOL __stdcall kernel32_RemoveDirectoryW_Thunk(LPCWSTR lpPathName);
BOOL __stdcall GodotFailRemoveDirectoryW(LPCWSTR);
extern const char name_RemoveDirectoryW[];
typedef BOOL (__stdcall *RemoveDirectoryWProc)(LPCWSTR);
extern RemoveDirectoryWProc slot_RemoveDirectoryW;
extern UnicowsEntry override_RemoveDirectoryW;

UINT __stdcall user32_RegisterWindowMessageW_Thunk(LPCWSTR lpString);
UINT __stdcall GodotFailRegisterWindowMessageW(LPCWSTR);
extern const char name_RegisterWindowMessageW[];
typedef UINT (__stdcall *RegisterWindowMessageWProc)(LPCWSTR);
extern RegisterWindowMessageWProc slot_RegisterWindowMessageW;
extern UnicowsEntry override_RegisterWindowMessageW;

BOOL __stdcall kernel32_FindNextFileW_Thunk(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData);
BOOL __stdcall GodotFailFindNextFileW(HANDLE, LPWIN32_FIND_DATAW);
extern const char name_FindNextFileW[];
typedef BOOL (__stdcall *FindNextFileWProc)(HANDLE, LPWIN32_FIND_DATAW);
extern FindNextFileWProc slot_FindNextFileW;
extern UnicowsEntry override_FindNextFileW;

BOOL __stdcall kernel32_GetFileAttributesExW_Thunk(LPCWSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation);
BOOL __stdcall GodotFailGetFileAttributesExW(LPCWSTR, GET_FILEEX_INFO_LEVELS, LPVOID);
extern const char name_GetFileAttributesExW[];
typedef BOOL (__stdcall *GetFileAttributesExWProc)(LPCWSTR, GET_FILEEX_INFO_LEVELS, LPVOID);
extern GetFileAttributesExWProc slot_GetFileAttributesExW;
extern UnicowsEntry override_GetFileAttributesExW;

HANDLE __stdcall user32_RemovePropW_Thunk(HWND hWnd, LPCWSTR lpString);
HANDLE __stdcall GodotFailRemovePropW(HWND, LPCWSTR);
extern const char name_RemovePropW[];
typedef HANDLE (__stdcall *RemovePropWProc)(HWND, LPCWSTR);
extern RemovePropWProc slot_RemovePropW;
extern UnicowsEntry override_RemovePropW;

UINT __stdcall kernel32_GetWindowsDirectoryW_Thunk(LPWSTR lpBuffer, UINT uSize);
UINT __stdcall GodotFailGetWindowsDirectoryW(LPWSTR, UINT);
extern const char name_GetWindowsDirectoryW[];
typedef UINT (__stdcall *GetWindowsDirectoryWProc)(LPWSTR, UINT);
extern GetWindowsDirectoryWProc slot_GetWindowsDirectoryW;
extern UnicowsEntry override_GetWindowsDirectoryW;

BOOL __stdcall kernel32_DeleteFileW_Thunk(LPCWSTR lpFileName);
BOOL __stdcall GodotFailDeleteFileW(LPCWSTR);
extern const char name_DeleteFileW[];
typedef BOOL (__stdcall *DeleteFileWProc)(LPCWSTR);
extern DeleteFileWProc slot_DeleteFileW;
extern UnicowsEntry override_DeleteFileW;

BOOL __stdcall kernel32_SetFileAttributesW_Thunk(LPCWSTR lpFileName, DWORD dwFileAttributes);
BOOL __stdcall GodotFailSetFileAttributesW(LPCWSTR, DWORD);
extern const char name_SetFileAttributesW[];
typedef BOOL (__stdcall *SetFileAttributesWProc)(LPCWSTR, DWORD);
extern SetFileAttributesWProc slot_SetFileAttributesW;
extern UnicowsEntry override_SetFileAttributesW;

int __stdcall kernel32_WideCharToMultiByte_Thunk(UINT CodePage, DWORD dwFlags, LPCWCH lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar);
int __stdcall GodotFailWideCharToMultiByte(UINT, DWORD, LPCWCH, int, LPSTR, int, LPCCH, LPBOOL);
extern const char name_WideCharToMultiByte[];
typedef int (__stdcall *WideCharToMultiByteProc)(UINT, DWORD, LPCWCH, int, LPSTR, int, LPCCH, LPBOOL);
extern WideCharToMultiByteProc slot_WideCharToMultiByte;
extern UnicowsEntry override_WideCharToMultiByte;

int __stdcall kernel32_MultiByteToWideChar_Thunk(UINT CodePage, DWORD dwFlags, LPCCH lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);
int __stdcall GodotFailMultiByteToWideChar(UINT, DWORD, LPCCH, int, LPWSTR, int);
extern const char name_MultiByteToWideChar[];
typedef int (__stdcall *MultiByteToWideCharProc)(UINT, DWORD, LPCCH, int, LPWSTR, int);
extern MultiByteToWideCharProc slot_MultiByteToWideChar;
extern UnicowsEntry override_MultiByteToWideChar;

DWORD __stdcall kernel32_FormatMessageW_Thunk(DWORD dwFlags, LPCVOID lpSource, DWORD dwMessageId, DWORD dwLanguageId, LPWSTR lpBuffer, DWORD nSize, va_list * Arguments);
DWORD __stdcall GodotFailFormatMessageW(DWORD, LPCVOID, DWORD, DWORD, LPWSTR, DWORD, va_list *);
extern const char name_FormatMessageW[];
typedef DWORD (__stdcall *FormatMessageWProc)(DWORD, LPCVOID, DWORD, DWORD, LPWSTR, DWORD, va_list *);
extern FormatMessageWProc slot_FormatMessageW;
extern UnicowsEntry override_FormatMessageW;

HANDLE __stdcall user32_GetClipboardData_Thunk(UINT uFormat);
HANDLE __stdcall GodotFailGetClipboardData(UINT);
extern const char name_GetClipboardData[];
typedef HANDLE (__stdcall *GetClipboardDataProc)(UINT);
extern GetClipboardDataProc slot_GetClipboardData;
extern UnicowsEntry override_GetClipboardData;

BOOL __stdcall kernel32_GetVersionExW_Thunk(LPOSVERSIONINFOW lpVersionInformation);
BOOL __stdcall GodotFailGetVersionExW(LPOSVERSIONINFOW);
extern const char name_GetVersionExW[];
typedef BOOL (__stdcall *GetVersionExWProc)(LPOSVERSIONINFOW);
extern GetVersionExWProc slot_GetVersionExW;
extern UnicowsEntry override_GetVersionExW;

FARPROC __stdcall kernel32_GetProcAddress_Thunk(HMODULE hModule, LPCSTR lpProcName);
FARPROC __stdcall GodotFailGetProcAddress(HMODULE, LPCSTR);
extern const char name_GetProcAddress[];
typedef FARPROC (__stdcall *GetProcAddressProc)(HMODULE, LPCSTR);
extern GetProcAddressProc slot_GetProcAddress;
extern UnicowsEntry override_GetProcAddress;

BOOL __stdcall kernel32_CreateProcessW_Thunk(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);
BOOL __stdcall GodotFailCreateProcessW(LPCWSTR, LPWSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID, LPCWSTR, LPSTARTUPINFOW, LPPROCESS_INFORMATION);
extern const char name_CreateProcessW[];
typedef BOOL (__stdcall *CreateProcessWProc)(LPCWSTR, LPWSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID, LPCWSTR, LPSTARTUPINFOW, LPPROCESS_INFORMATION);
extern CreateProcessWProc slot_CreateProcessW;
extern UnicowsEntry override_CreateProcessW;

BOOL __stdcall kernel32_GetComputerNameW_Thunk(LPWSTR lpBuffer, LPDWORD nSize);
BOOL __stdcall GodotFailGetComputerNameW(LPWSTR, LPDWORD);
extern const char name_GetComputerNameW[];
typedef BOOL (__stdcall *GetComputerNameWProc)(LPWSTR, LPDWORD);
extern GetComputerNameWProc slot_GetComputerNameW;
extern UnicowsEntry override_GetComputerNameW;

HINSTANCE __stdcall shell32_FindExecutableW_Thunk(LPCWSTR lpFile, LPCWSTR lpDirectory, LPWSTR lpResult);
HINSTANCE __stdcall GodotFailFindExecutableW(LPCWSTR, LPCWSTR, LPWSTR);
extern const char name_FindExecutableW[];
typedef HINSTANCE (__stdcall *FindExecutableWProc)(LPCWSTR, LPCWSTR, LPWSTR);
extern FindExecutableWProc slot_FindExecutableW;
extern UnicowsEntry override_FindExecutableW;

HANDLE __stdcall kernel32_CreateEventW_Thunk(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCWSTR lpName);
HANDLE __stdcall GodotFailCreateEventW(LPSECURITY_ATTRIBUTES, BOOL, BOOL, LPCWSTR);
extern const char name_CreateEventW[];
typedef HANDLE (__stdcall *CreateEventWProc)(LPSECURITY_ATTRIBUTES, BOOL, BOOL, LPCWSTR);
extern CreateEventWProc slot_CreateEventW;
extern UnicowsEntry override_CreateEventW;

HRSRC __stdcall kernel32_FindResourceW_Thunk(HMODULE hModule, LPCWSTR lpName, LPCWSTR lpType);
HRSRC __stdcall GodotFailFindResourceW(HMODULE, LPCWSTR, LPCWSTR);
extern const char name_FindResourceW[];
typedef HRSRC (__stdcall *FindResourceWProc)(HMODULE, LPCWSTR, LPCWSTR);
extern FindResourceWProc slot_FindResourceW;
extern UnicowsEntry override_FindResourceW;

HRSRC __stdcall kernel32_FindResourceExW_Thunk(HMODULE hModule, LPCWSTR lpType, LPCWSTR lpName, WORD wLanguage);
HRSRC __stdcall GodotFailFindResourceExW(HMODULE, LPCWSTR, LPCWSTR, WORD);
extern const char name_FindResourceExW[];
typedef HRSRC (__stdcall *FindResourceExWProc)(HMODULE, LPCWSTR, LPCWSTR, WORD);
extern FindResourceExWProc slot_FindResourceExW;
extern UnicowsEntry override_FindResourceExW;

HCURSOR __stdcall user32_LoadCursorW_Thunk(HINSTANCE hInstance, LPCWSTR lpCursorName);
HCURSOR __stdcall GodotFailLoadCursorW(HINSTANCE, LPCWSTR);
extern const char name_LoadCursorW[];
typedef HCURSOR (__stdcall *LoadCursorWProc)(HINSTANCE, LPCWSTR);
extern LoadCursorWProc slot_LoadCursorW;
extern UnicowsEntry override_LoadCursorW;

LONG __stdcall user32_SetWindowLongW_Thunk(HWND hWnd, int nIndex, LONG dwNewLong);
LONG __stdcall GodotFailSetWindowLongW(HWND, int, LONG);
extern const char name_SetWindowLongW[];
typedef LONG (__stdcall *SetWindowLongWProc)(HWND, int, LONG);
extern SetWindowLongWProc slot_SetWindowLongW;
extern UnicowsEntry override_SetWindowLongW;

BOOL __stdcall user32_PostMessageW_Thunk(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL __stdcall GodotFailPostMessageW(HWND, UINT, WPARAM, LPARAM);
extern const char name_PostMessageW[];
typedef BOOL (__stdcall *PostMessageWProc)(HWND, UINT, WPARAM, LPARAM);
extern PostMessageWProc slot_PostMessageW;
extern UnicowsEntry override_PostMessageW;

int __stdcall user32_GetKeyNameTextW_Thunk(LONG lParam, LPWSTR lpString, int cchSize);
int __stdcall GodotFailGetKeyNameTextW(LONG, LPWSTR, int);
extern const char name_GetKeyNameTextW[];
typedef int (__stdcall *GetKeyNameTextWProc)(LONG, LPWSTR, int);
extern GetKeyNameTextWProc slot_GetKeyNameTextW;
extern UnicowsEntry override_GetKeyNameTextW;

UINT __stdcall user32_MapVirtualKeyW_Thunk(UINT uCode, UINT uMapType);
UINT __stdcall GodotFailMapVirtualKeyW(UINT, UINT);
extern const char name_MapVirtualKeyW[];
typedef UINT (__stdcall *MapVirtualKeyWProc)(UINT, UINT);
extern MapVirtualKeyWProc slot_MapVirtualKeyW;
extern UnicowsEntry override_MapVirtualKeyW;

LRESULT __stdcall user32_DefWindowProcW_Thunk(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall GodotFailDefWindowProcW(HWND, UINT, WPARAM, LPARAM);
extern const char name_DefWindowProcW[];
typedef LRESULT (__stdcall *DefWindowProcWProc)(HWND, UINT, WPARAM, LPARAM);
extern DefWindowProcWProc slot_DefWindowProcW;
extern UnicowsEntry override_DefWindowProcW;

LONG __stdcall user32_GetWindowLongW_Thunk(HWND hWnd, int nIndex);
LONG __stdcall GodotFailGetWindowLongW(HWND, int);
extern const char name_GetWindowLongW[];
typedef LONG (__stdcall *GetWindowLongWProc)(HWND, int);
extern GetWindowLongWProc slot_GetWindowLongW;
extern UnicowsEntry override_GetWindowLongW;

ATOM __stdcall kernel32_GlobalAddAtomW_Thunk(LPCWSTR lpString);
ATOM __stdcall GodotFailGlobalAddAtomW(LPCWSTR);
extern const char name_GlobalAddAtomW[];
typedef ATOM (__stdcall *GlobalAddAtomWProc)(LPCWSTR);
extern GlobalAddAtomWProc slot_GlobalAddAtomW;
extern UnicowsEntry override_GlobalAddAtomW;

BOOL __stdcall user32_SystemParametersInfoW_Thunk(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni);
BOOL __stdcall GodotFailSystemParametersInfoW(UINT, UINT, PVOID, UINT);
extern const char name_SystemParametersInfoW[];
typedef BOOL (__stdcall *SystemParametersInfoWProc)(UINT, UINT, PVOID, UINT);
extern SystemParametersInfoWProc slot_SystemParametersInfoW;
extern UnicowsEntry override_SystemParametersInfoW;

BOOL __stdcall user32_EnableWindow_Thunk(HWND hWnd, BOOL bEnable);
BOOL __stdcall GodotFailEnableWindow(HWND, BOOL);
extern const char name_EnableWindow[];
typedef BOOL (__stdcall *EnableWindowProc)(HWND, BOOL);
extern EnableWindowProc slot_EnableWindow;
extern UnicowsEntry override_EnableWindow;

LRESULT __stdcall user32_CallWindowProcW_Thunk(WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall GodotFailCallWindowProcW(WNDPROC, HWND, UINT, WPARAM, LPARAM);
extern const char name_CallWindowProcW[];
typedef LRESULT (__stdcall *CallWindowProcWProc)(WNDPROC, HWND, UINT, WPARAM, LPARAM);
extern CallWindowProcWProc slot_CallWindowProcW;
extern UnicowsEntry override_CallWindowProcW;

BOOL __stdcall user32_SetMenuItemInfoW_Thunk(HMENU hmenu, UINT item, BOOL fByPositon, LPCMENUITEMINFOW lpmii);
BOOL __stdcall GodotFailSetMenuItemInfoW(HMENU, UINT, BOOL, LPCMENUITEMINFOW);
extern const char name_SetMenuItemInfoW[];
typedef BOOL (__stdcall *SetMenuItemInfoWProc)(HMENU, UINT, BOOL, LPCMENUITEMINFOW);
extern SetMenuItemInfoWProc slot_SetMenuItemInfoW;
extern UnicowsEntry override_SetMenuItemInfoW;

HWND __stdcall user32_CreateWindowExW_Thunk(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
HWND __stdcall GodotFailCreateWindowExW(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
extern const char name_CreateWindowExW[];
typedef HWND (__stdcall *CreateWindowExWProc)(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
extern CreateWindowExWProc slot_CreateWindowExW;
extern UnicowsEntry override_CreateWindowExW;

LRESULT __stdcall user32_DefMDIChildProcW_Thunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall GodotFailDefMDIChildProcW(HWND, UINT, WPARAM, LPARAM);
extern const char name_DefMDIChildProcW[];
typedef LRESULT (__stdcall *DefMDIChildProcWProc)(HWND, UINT, WPARAM, LPARAM);
extern DefMDIChildProcWProc slot_DefMDIChildProcW;
extern UnicowsEntry override_DefMDIChildProcW;

HMODULE __stdcall kernel32_GetModuleHandleW_Thunk(LPCWSTR lpModuleName);
HMODULE __stdcall GodotFailGetModuleHandleW(LPCWSTR);
extern const char name_GetModuleHandleW[];
typedef HMODULE (__stdcall *GetModuleHandleWProc)(LPCWSTR);
extern GetModuleHandleWProc slot_GetModuleHandleW;
extern UnicowsEntry override_GetModuleHandleW;

HMODULE __stdcall kernel32_LoadLibraryW_Thunk(LPCWSTR lpLibFileName);
HMODULE __stdcall GodotFailLoadLibraryW(LPCWSTR);
extern const char name_LoadLibraryW[];
typedef HMODULE (__stdcall *LoadLibraryWProc)(LPCWSTR);
extern LoadLibraryWProc slot_LoadLibraryW;
extern UnicowsEntry override_LoadLibraryW;

HMENU __stdcall user32_LoadMenuW_Thunk(HINSTANCE hInstance, LPCWSTR lpMenuName);
HMENU __stdcall GodotFailLoadMenuW(HINSTANCE, LPCWSTR);
extern const char name_LoadMenuW[];
typedef HMENU (__stdcall *LoadMenuWProc)(HINSTANCE, LPCWSTR);
extern LoadMenuWProc slot_LoadMenuW;
extern UnicowsEntry override_LoadMenuW;

ATOM __stdcall user32_RegisterClassExW_Thunk(const WNDCLASSEXW * arg1);
ATOM __stdcall GodotFailRegisterClassExW(const WNDCLASSEXW *);
extern const char name_RegisterClassExW[];
typedef ATOM (__stdcall *RegisterClassExWProc)(const WNDCLASSEXW *);
extern RegisterClassExWProc slot_RegisterClassExW;
extern UnicowsEntry override_RegisterClassExW;

BOOL __stdcall user32_GetClassInfoExW_Thunk(HINSTANCE hInstance, LPCWSTR lpszClass, LPWNDCLASSEXW lpwcx);
BOOL __stdcall GodotFailGetClassInfoExW(HINSTANCE, LPCWSTR, LPWNDCLASSEXW);
extern const char name_GetClassInfoExW[];
typedef BOOL (__stdcall *GetClassInfoExWProc)(HINSTANCE, LPCWSTR, LPWNDCLASSEXW);
extern GetClassInfoExWProc slot_GetClassInfoExW;
extern UnicowsEntry override_GetClassInfoExW;

BOOL __stdcall user32_GetMenuItemInfoW_Thunk(HMENU hmenu, UINT item, BOOL fByPosition, LPMENUITEMINFOW lpmii);
BOOL __stdcall GodotFailGetMenuItemInfoW(HMENU, UINT, BOOL, LPMENUITEMINFOW);
extern const char name_GetMenuItemInfoW[];
typedef BOOL (__stdcall *GetMenuItemInfoWProc)(HMENU, UINT, BOOL, LPMENUITEMINFOW);
extern GetMenuItemInfoWProc slot_GetMenuItemInfoW;
extern UnicowsEntry override_GetMenuItemInfoW;

INT_PTR __stdcall user32_DialogBoxParamW_Thunk(HINSTANCE hInstance, LPCWSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam);
INT_PTR __stdcall GodotFailDialogBoxParamW(HINSTANCE, LPCWSTR, HWND, DLGPROC, LPARAM);
extern const char name_DialogBoxParamW[];
typedef INT_PTR (__stdcall *DialogBoxParamWProc)(HINSTANCE, LPCWSTR, HWND, DLGPROC, LPARAM);
extern DialogBoxParamWProc slot_DialogBoxParamW;
extern UnicowsEntry override_DialogBoxParamW;

BOOL __stdcall gdi32_GetTextExtentPoint32W_Thunk(HDC hdc, LPCWSTR lpString, int c, LPSIZE psizl);
BOOL __stdcall GodotFailGetTextExtentPoint32W(HDC, LPCWSTR, int, LPSIZE);
extern const char name_GetTextExtentPoint32W[];
typedef BOOL (__stdcall *GetTextExtentPoint32WProc)(HDC, LPCWSTR, int, LPSIZE);
extern GetTextExtentPoint32WProc slot_GetTextExtentPoint32W;
extern UnicowsEntry override_GetTextExtentPoint32W;

int __stdcall user32_DrawTextExW_Thunk(HDC hdc, LPWSTR lpchText, int cchText, LPRECT lprc, UINT format, LPDRAWTEXTPARAMS lpdtp);
int __stdcall GodotFailDrawTextExW(HDC, LPWSTR, int, LPRECT, UINT, LPDRAWTEXTPARAMS);
extern const char name_DrawTextExW[];
typedef int (__stdcall *DrawTextExWProc)(HDC, LPWSTR, int, LPRECT, UINT, LPDRAWTEXTPARAMS);
extern DrawTextExWProc slot_DrawTextExW;
extern UnicowsEntry override_DrawTextExW;

BOOL __stdcall gdi32_TextOutW_Thunk(HDC hdc, int x, int y, LPCWSTR lpString, int c);
BOOL __stdcall GodotFailTextOutW(HDC, int, int, LPCWSTR, int);
extern const char name_TextOutW[];
typedef BOOL (__stdcall *TextOutWProc)(HDC, int, int, LPCWSTR, int);
extern TextOutWProc slot_TextOutW;
extern UnicowsEntry override_TextOutW;

BOOL __stdcall user32_SetPropA_Thunk(HWND hWnd, LPCSTR lpString, HANDLE hData);
BOOL __stdcall GodotFailSetPropA(HWND, LPCSTR, HANDLE);
extern const char name_SetPropA[];
typedef BOOL (__stdcall *SetPropAProc)(HWND, LPCSTR, HANDLE);
extern SetPropAProc slot_SetPropA;
extern UnicowsEntry override_SetPropA;

HANDLE __stdcall user32_RemovePropA_Thunk(HWND hWnd, LPCSTR lpString);
HANDLE __stdcall GodotFailRemovePropA(HWND, LPCSTR);
extern const char name_RemovePropA[];
typedef HANDLE (__stdcall *RemovePropAProc)(HWND, LPCSTR);
extern RemovePropAProc slot_RemovePropA;
extern UnicowsEntry override_RemovePropA;

HMODULE __stdcall kernel32_LoadLibraryExW_Thunk(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);
HMODULE __stdcall GodotFailLoadLibraryExW(LPCWSTR, HANDLE, DWORD);
extern const char name_LoadLibraryExW[];
typedef HMODULE (__stdcall *LoadLibraryExWProc)(LPCWSTR, HANDLE, DWORD);
extern LoadLibraryExWProc slot_LoadLibraryExW;
extern UnicowsEntry override_LoadLibraryExW;

BOOL __stdcall advapi32_GetUserNameW_Thunk(LPWSTR lpBuffer, LPDWORD pcbBuffer);
BOOL __stdcall GodotFailGetUserNameW(LPWSTR, LPDWORD);
extern const char name_GetUserNameW[];
typedef BOOL (__stdcall *GetUserNameWProc)(LPWSTR, LPDWORD);
extern GetUserNameWProc slot_GetUserNameW;
extern UnicowsEntry override_GetUserNameW;

LONG __stdcall advapi32_RegQueryValueExW_Thunk(HKEY hKey, LPCWSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
LONG __stdcall GodotFailRegQueryValueExW(HKEY, LPCWSTR, LPDWORD, LPDWORD, LPBYTE, LPDWORD);
extern const char name_RegQueryValueExW[];
typedef LONG (__stdcall *RegQueryValueExWProc)(HKEY, LPCWSTR, LPDWORD, LPDWORD, LPBYTE, LPDWORD);
extern RegQueryValueExWProc slot_RegQueryValueExW;
extern UnicowsEntry override_RegQueryValueExW;

LONG __stdcall advapi32_RegCreateKeyW_Thunk(HKEY hKey, LPCWSTR lpSubKey, PHKEY phkResult);
LONG __stdcall GodotFailRegCreateKeyW(HKEY, LPCWSTR, PHKEY);
extern const char name_RegCreateKeyW[];
typedef LONG (__stdcall *RegCreateKeyWProc)(HKEY, LPCWSTR, PHKEY);
extern RegCreateKeyWProc slot_RegCreateKeyW;
extern UnicowsEntry override_RegCreateKeyW;

LONG __stdcall advapi32_RegSetValueExW_Thunk(HKEY hKey, LPCWSTR lpValueName, DWORD Reserved, DWORD dwType, const BYTE *lpData, DWORD cbData);
LONG __stdcall GodotFailRegSetValueExW(HKEY, LPCWSTR, DWORD, DWORD, const BYTE *, DWORD);
extern const char name_RegSetValueExW[];
typedef LONG (__stdcall *RegSetValueExWProc)(HKEY, LPCWSTR, DWORD, DWORD, const BYTE *, DWORD);
extern RegSetValueExWProc slot_RegSetValueExW;
extern UnicowsEntry override_RegSetValueExW;

LONG __stdcall advapi32_RegOpenKeyW_Thunk(HKEY hKey, LPCWSTR lpSubKey, PHKEY phkResult);
LONG __stdcall GodotFailRegOpenKeyW(HKEY, LPCWSTR, PHKEY);
extern const char name_RegOpenKeyW[];
typedef LONG (__stdcall *RegOpenKeyWProc)(HKEY, LPCWSTR, PHKEY);
extern RegOpenKeyWProc slot_RegOpenKeyW;
extern UnicowsEntry override_RegOpenKeyW;

LONG __stdcall user32_SetWindowLongA_Thunk(HWND hWnd, int nIndex, LONG dwNewLong);
LONG __stdcall GodotFailSetWindowLongA(HWND, int, LONG);
extern const char name_SetWindowLongA[];
typedef LONG (__stdcall *SetWindowLongAProc)(HWND, int, LONG);
extern SetWindowLongAProc slot_SetWindowLongA;
extern UnicowsEntry override_SetWindowLongA;

LONG __stdcall user32_GetWindowLongA_Thunk(HWND hWnd, int nIndex);
LONG __stdcall GodotFailGetWindowLongA(HWND, int);
extern const char name_GetWindowLongA[];
typedef LONG (__stdcall *GetWindowLongAProc)(HWND, int);
extern GetWindowLongAProc slot_GetWindowLongA;
extern UnicowsEntry override_GetWindowLongA;

int __stdcall user32_DrawTextW_Thunk(HDC hdc, LPCWSTR lpchText, int cchText, LPRECT lprc, UINT format);
int __stdcall GodotFailDrawTextW(HDC, LPCWSTR, int, LPRECT, UINT);
extern const char name_DrawTextW[];
typedef int (__stdcall *DrawTextWProc)(HDC, LPCWSTR, int, LPRECT, UINT);
extern DrawTextWProc slot_DrawTextW;
extern UnicowsEntry override_DrawTextW;

LRESULT __stdcall user32_CallWindowProcA_Thunk(WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall GodotFailCallWindowProcA(WNDPROC, HWND, UINT, WPARAM, LPARAM);
extern const char name_CallWindowProcA[];
typedef LRESULT (__stdcall *CallWindowProcAProc)(WNDPROC, HWND, UINT, WPARAM, LPARAM);
extern CallWindowProcAProc slot_CallWindowProcA;
extern UnicowsEntry override_CallWindowProcA;

#ifdef __cplusplus
}
#endif

#endif
