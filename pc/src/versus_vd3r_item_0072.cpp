// Work item 0072 (LTCG retry): Versus RVA 0x11ec0, 0x11f50, 0x11f90, 0x120e0.
// UE2 Core string helpers (UnMisc.cpp): appStrfind and Parse, plus two
// unnamed neighbours. The one-character strings live in writable .data in
// retail (VC7.0 keeps literals there), so they are declared as externs named
// after their text; each literal is a separate copy, hence the numbered names.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern "C" __declspec(dllimport) TCHAR *__cdecl wcsstr(const TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcsncpy(TCHAR *, const TCHAR *, unsigned int);
extern "C" __declspec(dllimport) int __cdecl _wcsnicmp(const TCHAR *, const TCHAR *, unsigned int);
extern "C" __declspec(dllimport) TCHAR *__cdecl _itow(int, TCHAR *, int);
extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

inline TCHAR *appStrstr(const TCHAR *String, const TCHAR *Find) { return wcsstr(String, Find); }
inline INT appStrlen(const TCHAR *String) { return (INT)wcslen(String); }
inline TCHAR *appStrncpy(TCHAR *Dest, const TCHAR *Src, INT MaxLen) { return wcsncpy(Dest, Src, MaxLen); }
inline INT appStrnicmp(const TCHAR *A, const TCHAR *B, INT Count) { return _wcsnicmp(A, B, Count); }

extern const TCHAR Text_Colon_1[];   // ":"  0x10c710c0
extern const TCHAR Text_Colon_2[];   // ":"  0x10c710c4
extern const TCHAR Text_Slash_1[];   // "/"  0x10c710c8
extern const TCHAR Text_Slash_2[];   // "/"  0x10c710cc
extern const TCHAR Text_Dot_1[];     // "."  0x10c710d0
extern const TCHAR Text_Dot_2[];     // "."  0x10c710d4
extern const TCHAR Text_Quote[];     // "\"" 0x10c710d8
extern const TCHAR Text_Space[];     // " "  0x10c710dc
extern const TCHAR Text_CR[];        // "\r" 0x10c710e0
extern const TCHAR Text_LF[];        // "\n" 0x10c710e4
extern const TCHAR Text_Tab[];       // "\t" 0x10c710e8
extern const TCHAR Text_Comma[];     // ","  0x10c710ec

// RVA 0x11ec0: skips past a "xxx:" prefix, then past every '/' and '.'.
// Neutral name (no string or caller names it).
const TCHAR *UnnamedStripPath_11ec0(const TCHAR *Str)
{
    if (appStrstr(Str, Text_Colon_1))
        Str = appStrstr(Str, Text_Colon_2) + 1;
    while (appStrstr(Str, Text_Slash_1))
        Str = appStrstr(Str, Text_Slash_2) + 1;
    while (appStrstr(Str, Text_Dot_1))
        Str = appStrstr(Str, Text_Dot_2) + 1;
    return Str;
}

// RVA 0x11f50: formats an integer into a shared buffer (VA 0x10d4f670,
// 20 TCHARs; it was a local static). Neutral name.
// Near miss: retail clears the buffer with the generic rep stosd / rep stosb
// pair (count 0x28 in ECX, remainder in EBX); every compile tried folds the
// constant size to rep stosd x10.
extern TCHAR UnnamedIntToString_11f50_Buffer[20];
inline void appMemzero(void *Dest, INT Count) { memset(Dest, 0, Count); }

void UnnamedIntToString_11f50(INT Value)
{
    appMemzero(UnnamedIntToString_11f50_Buffer, sizeof(UnnamedIntToString_11f50_Buffer));
    _itow(Value, UnnamedIntToString_11f50_Buffer, 10);
}

// RVA 0x11f90: appStrfind - case-insensitive search for Find at a word start.
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find)
{
    UBOOL Alnum  = 0;
    TCHAR f      = (*Find < 'a' || *Find > 'z') ? (*Find) : (*Find + 'A' - 'a');
    INT   Length = appStrlen(Find++) - 1;
    TCHAR c      = *Str++;
    while (c)
    {
        if (c >= 'a' && c <= 'z')
            c += 'A' - 'a';
        if (!Alnum && c == f && !appStrnicmp(Str, Find, Length))
            return Str - 1;
        Alnum = (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
        c = *Str++;
    }
    return 0;
}

// RVA 0x120e0: Parse a string value "Match=Value" from a stream.
UBOOL Parse(const TCHAR *Stream, const TCHAR *Match, TCHAR *Value, INT MaxLen)
{
    const TCHAR *Found = appStrfind(Stream, Match);
    const TCHAR *Start;
    if (Found)
    {
        Start = Found + appStrlen(Match);
        if (*Start == '\x22')
        {
            // Quoted string with spaces.
            appStrncpy(Value, Start + 1, MaxLen);
            Value[MaxLen - 1] = 0;
            TCHAR *Temp = appStrstr(Value, Text_Quote);
            if (Temp != 0)
                *Temp = 0;
        }
        else
        {
            // Non-quoted string without spaces.
            appStrncpy(Value, Start, MaxLen);
            Value[MaxLen - 1] = 0;
            TCHAR *Temp;
            Temp = appStrstr(Value, Text_Space); if (Temp) *Temp = 0;
            Temp = appStrstr(Value, Text_CR);    if (Temp) *Temp = 0;
            Temp = appStrstr(Value, Text_LF);    if (Temp) *Temp = 0;
            Temp = appStrstr(Value, Text_Tab);   if (Temp) *Temp = 0;
            Temp = appStrstr(Value, Text_Comma); if (Temp) *Temp = 0;
        }
        return 1;
    }
    else return 0;
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_11ec0(const TCHAR *A, const TCHAR *B, const TCHAR **Out)
{
    Out[0] = UnnamedStripPath_11ec0(A);
    Out[1] = UnnamedStripPath_11ec0(B);
}
// Retail callers live in other objects; taking the address keeps it out of line.
void Driver_11f50(INT V)
{
    Escape((void *)&UnnamedIntToString_11f50);
    UnnamedIntToString_11f50(V);
}
UBOOL Driver_120e0(const TCHAR *S, const TCHAR *M, TCHAR *V, INT N, TCHAR *V2)
{
    return Parse(S, M, V, N) + Parse(S, M, V2, 64);
}
