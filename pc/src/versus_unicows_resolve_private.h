#ifndef VERSUS_UNICOWS_RESOLVE_PRIVATE_H
#define VERSUS_UNICOWS_RESOLVE_PRIVATE_H

#include "versus_unicows_resolve.h"

typedef struct UnicowsImageExportDirectory {
    unsigned long Characteristics;
    unsigned long TimeDateStamp;
    unsigned short MajorVersion;
    unsigned short MinorVersion;
    unsigned long Name;
    unsigned long Base;
    unsigned long NumberOfFunctions;
    unsigned long NumberOfNames;
    unsigned long AddressOfFunctions;
    unsigned long AddressOfNames;
    unsigned long AddressOfNameOrdinals;
} UnicowsImageExportDirectory;

typedef struct UnicowsMemoryBasicInformation {
    void *BaseAddress;
    void *AllocationBase;
    unsigned long AllocationProtect;
    unsigned long RegionSize;
    unsigned long State;
    unsigned long Protect;
    unsigned long Type;
} UnicowsMemoryBasicInformation;

typedef struct UnicowsModuleCache {
    const char *Name;
    void *Handle;
} UnicowsModuleCache;

typedef int (__stdcall *UnicowsCompareStringA)(unsigned long, unsigned long,
                                                const char *, int, const char *, int);
typedef void *(__stdcall *UnicowsLoadLibraryA)(const char *);
typedef unsigned long (__stdcall *UnicowsGetModuleFileNameA)(void *, char *, unsigned long);
typedef void *(__stdcall *UnicowsGetModuleHandleA)(const char *);
typedef unsigned long (__stdcall *UnicowsGetSystemDirectoryA)(char *, unsigned long);
typedef unsigned long (__stdcall *UnicowsGetWindowsDirectoryA)(char *, unsigned long);
typedef int (__stdcall *UnicowsFreeLibrary)(void *);
typedef long (__stdcall *UnicowsInterlockedExchange)(long *, long);
typedef unsigned long (__stdcall *UnicowsGetVersion)(void);
typedef unsigned long (__stdcall *UnicowsVirtualQuery)(const void *,
                                                        UnicowsMemoryBasicInformation *,
                                                        unsigned long);
typedef int (__stdcall *UnicowsFlushInstructionCache)(void *, const void *, unsigned long);
typedef long (__stdcall *UnicowsRegOpenKeyExA)(void *, const char *, unsigned long,
                                               unsigned long, void **);
typedef long (__stdcall *UnicowsRegCloseKey)(void *);
typedef long (__stdcall *UnicowsRegQueryValueExA)(void *, const char *, unsigned long *,
                                                   unsigned long *, unsigned char *,
                                                   unsigned long *);
typedef void *(__cdecl *UnicowsLoadHook)(void);

#ifdef __cplusplus
extern "C" {
#endif

extern UnicowsCompareStringA g_unicowsCompareStringA;
extern UnicowsLoadLibraryA g_unicowsLoadLibraryA;
extern UnicowsGetModuleFileNameA g_unicowsGetModuleFileNameA;
extern UnicowsGetModuleHandleA g_unicowsGetModuleHandleA;
extern UnicowsGetSystemDirectoryA g_unicowsGetSystemDirectoryA;
extern UnicowsGetWindowsDirectoryA g_unicowsGetWindowsDirectoryA;
extern UnicowsFreeLibrary g_unicowsFreeLibrary;
extern UnicowsInterlockedExchange g_unicowsInterlockedExchange;
extern UnicowsGetVersion g_unicowsGetVersion;
extern UnicowsVirtualQuery g_unicowsVirtualQuery;
extern UnicowsFlushInstructionCache g_unicowsFlushInstructionCache;
extern UnicowsRegCloseKey g_unicowsRegCloseKey;
extern UnicowsModuleCache g_unicowsModuleCache[];
// volatile: retail reloads this shared state after writing its version result.
extern volatile unsigned long g_unicowsPlatformState;
extern void *unk_374c84;
extern UnicowsLoadHook unk_2d1b20;
extern const char s_windows_current_version[];
extern const char s_common_files_dir[];
extern const char s_mslu_directory_suffix[];
extern const char s_reg_open_key_ex_a[];
extern const char s_reg_query_value_ex_a[];

unsigned short __stdcall GetOrdinal(const char *, int, const unsigned char *,
                                    const unsigned long *, const unsigned short *);
unsigned char *__stdcall ImageEntryToDataC(const unsigned char *, unsigned short,
                                           unsigned long *);
int __stdcall strcmpiC(const char *, const char *);
char *__stdcall strncpyC(char *, const char *, unsigned int);
void *__stdcall GetProcAddressInternal(void *, const char *);
void __stdcall driveandpathC(const char *, char *, char *);
void *LoadGodot(void);

int __cdecl strcmp(const char *, const char *);
unsigned int __cdecl strlen(const char *);
void *__cdecl memset(void *, int, unsigned int);
void *__cdecl memcpy(void *, const void *, unsigned int);
char *__cdecl strcat(char *, const char *);
char *__cdecl strcpy(char *, const char *);

#ifdef __cplusplus
}
#endif

#pragma intrinsic(strcmp, strlen, memset, memcpy, strcpy, strcat)

#endif
