#include "d3dx_settings.h"
#include <mmintrin.h>

/* Win32's 32-bit processor and address-space information. */
struct SYSTEM_INFO {
    union {
        DWORD dwOemId;
        struct {
            WORD wProcessorArchitecture;
            WORD wReserved;
        };
    };
    DWORD dwPageSize;
    LPVOID lpMinimumApplicationAddress;
    LPVOID lpMaximumApplicationAddress;
    DWORD dwActiveProcessorMask;
    DWORD dwNumberOfProcessors;
    DWORD dwProcessorType;
    DWORD dwAllocationGranularity;
    WORD wProcessorLevel;
    WORD wProcessorRevision;
};

extern "C" {
__declspec(dllimport) void __stdcall GetSystemInfo(SYSTEM_INFO *info);
__declspec(dllimport) LONG __stdcall RegOpenKeyA(HKEY key, LPCSTR subkey, PHKEY result);
__declspec(dllimport) LONG __stdcall RegQueryValueExA(
    HKEY key, LPCSTR name, LPDWORD reserved, LPDWORD type, LPBYTE data, LPDWORD size);
__declspec(dllimport) LONG __stdcall RegCloseKey(HKEY key);
}

#define HKEY_LOCAL_MACHINE ((HKEY)(LONG)0x80000002)
#define ERROR_SUCCESS 0L
#define REG_DWORD 4
#define PROCESSOR_ARCHITECTURE_INTEL 0

BOOL GetD3DRegValue(DWORD expectedType, LPSTR name, LPVOID data, DWORD size)
{
    HKEY key = 0;
    if (RegOpenKeyA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Direct3D", &key) != ERROR_SUCCESS)
        return 0;

    DWORD type;
    LONG result = RegQueryValueExA(key, name, 0, &type, static_cast<LPBYTE>(data), &size);
    RegCloseKey(key);
    return result == ERROR_SUCCESS && type == expectedType;
}

static int isMMX = -1;
int _asm_isMMX();
int isMMXprocessor()
{
    HKEY key;
    if (RegOpenKeyA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Direct3D", &key) == ERROR_SUCCESS) {
        DWORD type, disable;
        DWORD size = sizeof(disable);
        if (RegQueryValueExA(key, "DisableMMX", 0, &type,
                            reinterpret_cast<LPBYTE>(&disable), &size) == ERROR_SUCCESS
            && type == REG_DWORD && disable) {
            RegCloseKey(key);
            isMMX = 0;
            return 0;
        }
        RegCloseKey(key);
    }

    if (isMMX < 0) {
        SYSTEM_INFO info;
        isMMX = 0;
        GetSystemInfo(&info);
        if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL
            && info.wProcessorLevel >= 5 && _asm_isMMX()) {
            _mm_empty();
            isMMX = 1;
        }
    }
    return isMMX;
}
