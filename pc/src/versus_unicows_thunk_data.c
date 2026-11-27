/* Names, first-call targets and optional function overrides for the Unicode thunks. */
#include "versus_unicows_thunks.h"

const char user32_dll[] = "user32.dll";
const char kernel32_dll[] = "kernel32.dll";
const char shell32_dll[] = "shell32.dll";
const char advapi32_dll[] = "advapi32.dll";
const char gdi32_dll[] = "gdi32.dll";

const char name_DispatchMessageW[] = "DispatchMessageW";
DispatchMessageWProc slot_DispatchMessageW = user32_DispatchMessageW_Thunk;
UnicowsEntry override_DispatchMessageW;

const char name_CreateMutexW[] = "CreateMutexW";
CreateMutexWProc slot_CreateMutexW = kernel32_CreateMutexW_Thunk;
UnicowsEntry override_CreateMutexW;

const char name_FindFirstFileW[] = "FindFirstFileW";
FindFirstFileWProc slot_FindFirstFileW = kernel32_FindFirstFileW_Thunk;
UnicowsEntry override_FindFirstFileW;

const char name_SendMessageW[] = "SendMessageW";
SendMessageWProc slot_SendMessageW = user32_SendMessageW_Thunk;
UnicowsEntry override_SendMessageW;

const char name_MessageBoxW[] = "MessageBoxW";
MessageBoxWProc slot_MessageBoxW = user32_MessageBoxW_Thunk;
UnicowsEntry override_MessageBoxW;

const char name_CreateDirectoryW[] = "CreateDirectoryW";
CreateDirectoryWProc slot_CreateDirectoryW = kernel32_CreateDirectoryW_Thunk;
UnicowsEntry override_CreateDirectoryW;

const char name_CreateDialogParamW[] = "CreateDialogParamW";
CreateDialogParamWProc slot_CreateDialogParamW = user32_CreateDialogParamW_Thunk;
UnicowsEntry override_CreateDialogParamW;

const char name_GetSystemDirectoryW[] = "GetSystemDirectoryW";
GetSystemDirectoryWProc slot_GetSystemDirectoryW = kernel32_GetSystemDirectoryW_Thunk;
UnicowsEntry override_GetSystemDirectoryW;

const char name_PeekMessageW[] = "PeekMessageW";
PeekMessageWProc slot_PeekMessageW = user32_PeekMessageW_Thunk;
UnicowsEntry override_PeekMessageW;

const char name_CopyFileW[] = "CopyFileW";
CopyFileWProc slot_CopyFileW = kernel32_CopyFileW_Thunk;
UnicowsEntry override_CopyFileW;

const char name_LoadIconW[] = "LoadIconW";
LoadIconWProc slot_LoadIconW = user32_LoadIconW_Thunk;
UnicowsEntry override_LoadIconW;

const char name_GetModuleFileNameW[] = "GetModuleFileNameW";
GetModuleFileNameWProc slot_GetModuleFileNameW = kernel32_GetModuleFileNameW_Thunk;
UnicowsEntry override_GetModuleFileNameW;

const char name_CreateFileW[] = "CreateFileW";
CreateFileWProc slot_CreateFileW = kernel32_CreateFileW_Thunk;
UnicowsEntry override_CreateFileW;

const char name_SetPropW[] = "SetPropW";
SetPropWProc slot_SetPropW = user32_SetPropW_Thunk;
UnicowsEntry override_SetPropW;

const char name_GetCurrentDirectoryW[] = "GetCurrentDirectoryW";
GetCurrentDirectoryWProc slot_GetCurrentDirectoryW = kernel32_GetCurrentDirectoryW_Thunk;
UnicowsEntry override_GetCurrentDirectoryW;

const char name_MoveFileW[] = "MoveFileW";
MoveFileWProc slot_MoveFileW = kernel32_MoveFileW_Thunk;
UnicowsEntry override_MoveFileW;

const char name_ShellExecuteW[] = "ShellExecuteW";
ShellExecuteWProc slot_ShellExecuteW = shell32_ShellExecuteW_Thunk;
UnicowsEntry override_ShellExecuteW;

const char name_SetCurrentDirectoryW[] = "SetCurrentDirectoryW";
SetCurrentDirectoryWProc slot_SetCurrentDirectoryW = kernel32_SetCurrentDirectoryW_Thunk;
UnicowsEntry override_SetCurrentDirectoryW;

const char name_RemoveDirectoryW[] = "RemoveDirectoryW";
RemoveDirectoryWProc slot_RemoveDirectoryW = kernel32_RemoveDirectoryW_Thunk;
UnicowsEntry override_RemoveDirectoryW;

const char name_RegisterWindowMessageW[] = "RegisterWindowMessageW";
RegisterWindowMessageWProc slot_RegisterWindowMessageW = user32_RegisterWindowMessageW_Thunk;
UnicowsEntry override_RegisterWindowMessageW;

const char name_FindNextFileW[] = "FindNextFileW";
FindNextFileWProc slot_FindNextFileW = kernel32_FindNextFileW_Thunk;
UnicowsEntry override_FindNextFileW;

const char name_GetFileAttributesExW[] = "GetFileAttributesExW";
GetFileAttributesExWProc slot_GetFileAttributesExW = kernel32_GetFileAttributesExW_Thunk;
UnicowsEntry override_GetFileAttributesExW;

const char name_RemovePropW[] = "RemovePropW";
RemovePropWProc slot_RemovePropW = user32_RemovePropW_Thunk;
UnicowsEntry override_RemovePropW;

const char name_GetWindowsDirectoryW[] = "GetWindowsDirectoryW";
GetWindowsDirectoryWProc slot_GetWindowsDirectoryW = kernel32_GetWindowsDirectoryW_Thunk;
UnicowsEntry override_GetWindowsDirectoryW;

const char name_DeleteFileW[] = "DeleteFileW";
DeleteFileWProc slot_DeleteFileW = kernel32_DeleteFileW_Thunk;
UnicowsEntry override_DeleteFileW;

const char name_SetFileAttributesW[] = "SetFileAttributesW";
SetFileAttributesWProc slot_SetFileAttributesW = kernel32_SetFileAttributesW_Thunk;
UnicowsEntry override_SetFileAttributesW;

const char name_WideCharToMultiByte[] = "WideCharToMultiByte";
WideCharToMultiByteProc slot_WideCharToMultiByte = kernel32_WideCharToMultiByte_Thunk;
UnicowsEntry override_WideCharToMultiByte;

const char name_MultiByteToWideChar[] = "MultiByteToWideChar";
MultiByteToWideCharProc slot_MultiByteToWideChar = kernel32_MultiByteToWideChar_Thunk;
UnicowsEntry override_MultiByteToWideChar;

const char name_FormatMessageW[] = "FormatMessageW";
FormatMessageWProc slot_FormatMessageW = kernel32_FormatMessageW_Thunk;
UnicowsEntry override_FormatMessageW;

const char name_GetClipboardData[] = "GetClipboardData";
GetClipboardDataProc slot_GetClipboardData = user32_GetClipboardData_Thunk;
UnicowsEntry override_GetClipboardData;

const char name_GetVersionExW[] = "GetVersionExW";
GetVersionExWProc slot_GetVersionExW = kernel32_GetVersionExW_Thunk;
UnicowsEntry override_GetVersionExW;

const char name_GetProcAddress[] = "GetProcAddress";
GetProcAddressProc slot_GetProcAddress = kernel32_GetProcAddress_Thunk;
UnicowsEntry override_GetProcAddress;

const char name_CreateProcessW[] = "CreateProcessW";
CreateProcessWProc slot_CreateProcessW = kernel32_CreateProcessW_Thunk;
UnicowsEntry override_CreateProcessW;

const char name_GetComputerNameW[] = "GetComputerNameW";
GetComputerNameWProc slot_GetComputerNameW = kernel32_GetComputerNameW_Thunk;
UnicowsEntry override_GetComputerNameW;

const char name_FindExecutableW[] = "FindExecutableW";
FindExecutableWProc slot_FindExecutableW = shell32_FindExecutableW_Thunk;
UnicowsEntry override_FindExecutableW;

const char name_CreateEventW[] = "CreateEventW";
CreateEventWProc slot_CreateEventW = kernel32_CreateEventW_Thunk;
UnicowsEntry override_CreateEventW;

const char name_FindResourceW[] = "FindResourceW";
FindResourceWProc slot_FindResourceW = kernel32_FindResourceW_Thunk;
UnicowsEntry override_FindResourceW;

const char name_FindResourceExW[] = "FindResourceExW";
FindResourceExWProc slot_FindResourceExW = kernel32_FindResourceExW_Thunk;
UnicowsEntry override_FindResourceExW;

const char name_LoadCursorW[] = "LoadCursorW";
LoadCursorWProc slot_LoadCursorW = user32_LoadCursorW_Thunk;
UnicowsEntry override_LoadCursorW;

const char name_SetWindowLongW[] = "SetWindowLongW";
SetWindowLongWProc slot_SetWindowLongW = user32_SetWindowLongW_Thunk;
UnicowsEntry override_SetWindowLongW;

const char name_PostMessageW[] = "PostMessageW";
PostMessageWProc slot_PostMessageW = user32_PostMessageW_Thunk;
UnicowsEntry override_PostMessageW;

const char name_GetKeyNameTextW[] = "GetKeyNameTextW";
GetKeyNameTextWProc slot_GetKeyNameTextW = user32_GetKeyNameTextW_Thunk;
UnicowsEntry override_GetKeyNameTextW;

const char name_MapVirtualKeyW[] = "MapVirtualKeyW";
MapVirtualKeyWProc slot_MapVirtualKeyW = user32_MapVirtualKeyW_Thunk;
UnicowsEntry override_MapVirtualKeyW;

const char name_DefWindowProcW[] = "DefWindowProcW";
DefWindowProcWProc slot_DefWindowProcW = user32_DefWindowProcW_Thunk;
UnicowsEntry override_DefWindowProcW;

const char name_GetWindowLongW[] = "GetWindowLongW";
GetWindowLongWProc slot_GetWindowLongW = user32_GetWindowLongW_Thunk;
UnicowsEntry override_GetWindowLongW;

const char name_GlobalAddAtomW[] = "GlobalAddAtomW";
GlobalAddAtomWProc slot_GlobalAddAtomW = kernel32_GlobalAddAtomW_Thunk;
UnicowsEntry override_GlobalAddAtomW;

const char name_SystemParametersInfoW[] = "SystemParametersInfoW";
SystemParametersInfoWProc slot_SystemParametersInfoW = user32_SystemParametersInfoW_Thunk;
UnicowsEntry override_SystemParametersInfoW;

const char name_EnableWindow[] = "EnableWindow";
EnableWindowProc slot_EnableWindow = user32_EnableWindow_Thunk;
UnicowsEntry override_EnableWindow;

const char name_CallWindowProcW[] = "CallWindowProcW";
CallWindowProcWProc slot_CallWindowProcW = user32_CallWindowProcW_Thunk;
UnicowsEntry override_CallWindowProcW;

const char name_SetMenuItemInfoW[] = "SetMenuItemInfoW";
SetMenuItemInfoWProc slot_SetMenuItemInfoW = user32_SetMenuItemInfoW_Thunk;
UnicowsEntry override_SetMenuItemInfoW;

const char name_CreateWindowExW[] = "CreateWindowExW";
CreateWindowExWProc slot_CreateWindowExW = user32_CreateWindowExW_Thunk;
UnicowsEntry override_CreateWindowExW;

const char name_DefMDIChildProcW[] = "DefMDIChildProcW";
DefMDIChildProcWProc slot_DefMDIChildProcW = user32_DefMDIChildProcW_Thunk;
UnicowsEntry override_DefMDIChildProcW;

const char name_GetModuleHandleW[] = "GetModuleHandleW";
GetModuleHandleWProc slot_GetModuleHandleW = kernel32_GetModuleHandleW_Thunk;
UnicowsEntry override_GetModuleHandleW;

const char name_LoadLibraryW[] = "LoadLibraryW";
LoadLibraryWProc slot_LoadLibraryW = kernel32_LoadLibraryW_Thunk;
UnicowsEntry override_LoadLibraryW;

const char name_LoadMenuW[] = "LoadMenuW";
LoadMenuWProc slot_LoadMenuW = user32_LoadMenuW_Thunk;
UnicowsEntry override_LoadMenuW;

const char name_RegisterClassExW[] = "RegisterClassExW";
RegisterClassExWProc slot_RegisterClassExW = user32_RegisterClassExW_Thunk;
UnicowsEntry override_RegisterClassExW;

const char name_GetClassInfoExW[] = "GetClassInfoExW";
GetClassInfoExWProc slot_GetClassInfoExW = user32_GetClassInfoExW_Thunk;
UnicowsEntry override_GetClassInfoExW;

const char name_GetMenuItemInfoW[] = "GetMenuItemInfoW";
GetMenuItemInfoWProc slot_GetMenuItemInfoW = user32_GetMenuItemInfoW_Thunk;
UnicowsEntry override_GetMenuItemInfoW;

const char name_DialogBoxParamW[] = "DialogBoxParamW";
DialogBoxParamWProc slot_DialogBoxParamW = user32_DialogBoxParamW_Thunk;
UnicowsEntry override_DialogBoxParamW;

const char name_GetTextExtentPoint32W[] = "GetTextExtentPoint32W";
GetTextExtentPoint32WProc slot_GetTextExtentPoint32W = gdi32_GetTextExtentPoint32W_Thunk;
UnicowsEntry override_GetTextExtentPoint32W;

const char name_DrawTextExW[] = "DrawTextExW";
DrawTextExWProc slot_DrawTextExW = user32_DrawTextExW_Thunk;
UnicowsEntry override_DrawTextExW;

const char name_TextOutW[] = "TextOutW";
TextOutWProc slot_TextOutW = gdi32_TextOutW_Thunk;
UnicowsEntry override_TextOutW;

const char name_SetPropA[] = "SetPropA";
SetPropAProc slot_SetPropA = user32_SetPropA_Thunk;
UnicowsEntry override_SetPropA;

const char name_RemovePropA[] = "RemovePropA";
RemovePropAProc slot_RemovePropA = user32_RemovePropA_Thunk;
UnicowsEntry override_RemovePropA;

const char name_LoadLibraryExW[] = "LoadLibraryExW";
LoadLibraryExWProc slot_LoadLibraryExW = kernel32_LoadLibraryExW_Thunk;
UnicowsEntry override_LoadLibraryExW;

const char name_GetUserNameW[] = "GetUserNameW";
GetUserNameWProc slot_GetUserNameW = advapi32_GetUserNameW_Thunk;
UnicowsEntry override_GetUserNameW;

const char name_RegQueryValueExW[] = "RegQueryValueExW";
RegQueryValueExWProc slot_RegQueryValueExW = advapi32_RegQueryValueExW_Thunk;
UnicowsEntry override_RegQueryValueExW;

const char name_RegCreateKeyW[] = "RegCreateKeyW";
RegCreateKeyWProc slot_RegCreateKeyW = advapi32_RegCreateKeyW_Thunk;
UnicowsEntry override_RegCreateKeyW;

const char name_RegSetValueExW[] = "RegSetValueExW";
RegSetValueExWProc slot_RegSetValueExW = advapi32_RegSetValueExW_Thunk;
UnicowsEntry override_RegSetValueExW;

const char name_RegOpenKeyW[] = "RegOpenKeyW";
RegOpenKeyWProc slot_RegOpenKeyW = advapi32_RegOpenKeyW_Thunk;
UnicowsEntry override_RegOpenKeyW;

const char name_SetWindowLongA[] = "SetWindowLongA";
SetWindowLongAProc slot_SetWindowLongA = user32_SetWindowLongA_Thunk;
UnicowsEntry override_SetWindowLongA;

const char name_GetWindowLongA[] = "GetWindowLongA";
GetWindowLongAProc slot_GetWindowLongA = user32_GetWindowLongA_Thunk;
UnicowsEntry override_GetWindowLongA;

const char name_DrawTextW[] = "DrawTextW";
DrawTextWProc slot_DrawTextW = user32_DrawTextW_Thunk;
UnicowsEntry override_DrawTextW;

const char name_CallWindowProcA[] = "CallWindowProcA";
CallWindowProcAProc slot_CallWindowProcA = user32_CallWindowProcA_Thunk;
UnicowsEntry override_CallWindowProcA;
