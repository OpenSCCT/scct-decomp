/* sound_win32.h -- the Win32 declarations the sound sources use */
#ifndef SOUND_WIN32_H
#define SOUND_WIN32_H

/* The rebuild has no Windows SDK headers. Functions, structures, members and constants carry
   the SDK's names. The SDK's scalar typedefs are spelled out: DWORD is unsigned long, WORD is
   unsigned short, UINT is unsigned int, BOOL is int, HANDLE is void * and LARGE_INTEGER
   is __int64. */

#define INVALID_HANDLE_VALUE ((void *)-1)
#define INVALID_SET_FILE_POINTER ((unsigned long)-1)
#define ERROR_NEGATIVE_SEEK 131

#define INFINITE      0xffffffff
#define WAIT_OBJECT_0 0

#define FILE_BEGIN   0
#define FILE_CURRENT 1
#define FILE_END     2

#define VER_PLATFORM_WIN32_NT 2

#define WAVE_MAPPER ((unsigned int)-1)

#define WAVE_FORMAT_1M08 0x00000001
#define WAVE_FORMAT_1S08 0x00000002
#define WAVE_FORMAT_1M16 0x00000004
#define WAVE_FORMAT_1S16 0x00000008
#define WAVE_FORMAT_2M08 0x00000010
#define WAVE_FORMAT_2S08 0x00000020
#define WAVE_FORMAT_2M16 0x00000040
#define WAVE_FORMAT_2S16 0x00000080
#define WAVE_FORMAT_4M08 0x00000100
#define WAVE_FORMAT_4S08 0x00000200
#define WAVE_FORMAT_4M16 0x00000400
#define WAVE_FORMAT_4S16 0x00000800

typedef struct _RTL_CRITICAL_SECTION CRITICAL_SECTION;

typedef struct _FILETIME {
    unsigned long dwLowDateTime;
    unsigned long dwHighDateTime;
} FILETIME;

typedef struct _WIN32_FIND_DATAA {
    unsigned long dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    unsigned long nFileSizeHigh;
    unsigned long nFileSizeLow;
    unsigned long dwReserved0;
    unsigned long dwReserved1;
    char cFileName[260];
    char cAlternateFileName[14];
} WIN32_FIND_DATAA;

typedef struct _OSVERSIONINFOA {
    unsigned long dwOSVersionInfoSize;
    unsigned long dwMajorVersion;
    unsigned long dwMinorVersion;
    unsigned long dwBuildNumber;
    unsigned long dwPlatformId;
    char szCSDVersion[128];
} OSVERSIONINFOA;

typedef struct tagWAVEOUTCAPSA {
    unsigned short wMid;
    unsigned short wPid;
    unsigned int vDriverVersion;
    char szPname[32];
    unsigned long dwFormats;
    unsigned short wChannels;
    unsigned short wReserved1;
    unsigned long dwSupport;
} WAVEOUTCAPSA;

typedef struct tWAVEFORMATEX {
    unsigned short wFormatTag;
    unsigned short nChannels;
    unsigned long nSamplesPerSec;
    unsigned long nAvgBytesPerSec;
    unsigned short nBlockAlign;
    unsigned short wBitsPerSample;
    unsigned short cbSize;
} WAVEFORMATEX;

__declspec(dllimport) int __stdcall ReadFile(void *hFile, void *lpBuffer,
                                             unsigned long nNumberOfBytesToRead,
                                             unsigned long *lpNumberOfBytesRead, void *lpOverlapped);
__declspec(dllimport) int __stdcall WriteFile(void *hFile, const void *lpBuffer,
                                              unsigned long nNumberOfBytesToWrite,
                                              unsigned long *lpNumberOfBytesWritten,
                                              void *lpOverlapped);
__declspec(dllimport) unsigned long __stdcall SetFilePointer(void *hFile, long lDistanceToMove,
                                                             long *lpDistanceToMoveHigh,
                                                             unsigned long dwMoveMethod);
__declspec(dllimport) unsigned long __stdcall GetFileSize(void *hFile, unsigned long *lpFileSizeHigh);
__declspec(dllimport) unsigned long __stdcall GetLastError(void);
__declspec(dllimport) int __stdcall CloseHandle(void *hObject);
__declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *hHandle,
                                                                  unsigned long dwMilliseconds);
__declspec(dllimport) int __stdcall DeleteFileA(const char *lpFileName);
__declspec(dllimport) void *__stdcall FindFirstFileA(const char *lpFileName,
                                                     WIN32_FIND_DATAA *lpFindFileData);
__declspec(dllimport) int __stdcall FindClose(void *hFindFile);
__declspec(dllimport) void *__stdcall CreateMutexA(void *lpMutexAttributes, int bInitialOwner,
                                                   const char *lpName);
__declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *lpCriticalSection);
__declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *lpCriticalSection);
__declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *lpPerformanceCount);
__declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64 *lpFrequency);
__declspec(dllimport) int __stdcall GetVersionExA(OSVERSIONINFOA *lpVersionInformation);
__declspec(dllimport) unsigned int __stdcall waveOutGetDevCapsA(unsigned int uDeviceID,
                                                                WAVEOUTCAPSA *pwoc,
                                                                unsigned int cbwoc);

#endif
