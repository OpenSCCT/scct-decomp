// Versus RVA 0xe020: FFileManagerWindows-style GetFileAgeDays (UE2 FileManagerWindows.h).
// Link-time generated: the linker passes Filename in ECX. The ANSI fallback of
// TCHAR_CALL_OS is dead (GUnicodeOS is 1 in this build) but its _alloca still
// gives the function the EBP frame and `lea esp, [ebp-0x2c]` epilogue retail has.
// Written as a free function; no symbol evidence ties it to a class here.
typedef unsigned short TCHAR;
typedef char ANSICHAR;
typedef int INT;
typedef long time_t;

struct _stat
{
    unsigned int   st_dev;
    unsigned short st_ino;
    unsigned short st_mode;
    short          st_nlink;
    short          st_uid;
    short          st_gid;
    unsigned int   st_rdev;
    long           st_size;
    time_t         st_atime;
    time_t         st_mtime;
    time_t         st_ctime;
};

extern "C" {
__declspec(dllimport) int __cdecl _wstat(const TCHAR *Path, struct _stat *Buffer);
__declspec(dllimport) int __cdecl _stat(const ANSICHAR *Path, struct _stat *Buffer);
__declspec(dllimport) time_t __cdecl time(time_t *Timer);
__declspec(dllimport) double __cdecl difftime(time_t Time1, time_t Time0);
void *__cdecl _alloca(unsigned int);
}

#define GUnicodeOS 1
INT winGetSizeANSI(const TCHAR *Str);
ANSICHAR *winToANSI(ANSICHAR *ACh, const TCHAR *InUCh, INT Count);
#define TCHAR_TO_ANSI(str) winToANSI((ANSICHAR *)_alloca(winGetSizeANSI(str)), str, winGetSizeANSI(str))
#define TCHAR_CALL_OS(funcW, funcA) (GUnicodeOS ? (funcW) : (funcA))

INT GetFileAgeDays(const TCHAR *Filename)
{
    struct _stat FileInfo;
    if (TCHAR_CALL_OS(_wstat(Filename, &FileInfo), _stat(TCHAR_TO_ANSI(Filename), &FileInfo)) == 0)
    {
        time_t FileTime = FileInfo.st_mtime;
        time_t CurrentTime;
        time(&CurrentTime);
        return (INT)(difftime(CurrentTime, FileTime) / (60.0 * 60.0 * 24.0));
    }
    return 0;
}

// Scaffolding for the link, not part of the unit.
INT Driver_e020(const TCHAR *A, const TCHAR *B) { return GetFileAgeDays(A) + GetFileAgeDays(B); }
