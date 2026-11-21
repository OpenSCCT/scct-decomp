// Work item 0074 (LTCG retry): Core Parse() overloads from UnMisc.cpp.
// Compiled with VC7.0 /GL and linked /LTCG: Stream arrives in EAX, Match in
// EDI, the out-value on the stack (caller cleans).

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR*);
extern "C" __declspec(dllimport) double __cdecl atof(const char*);
extern "C" __declspec(dllimport) int __cdecl _wtoi(const TCHAR*);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR*, const TCHAR*);
extern "C" __declspec(dllimport) int __cdecl _wcsnicmp(const TCHAR*, const TCHAR*, unsigned int);
extern "C" __declspec(dllimport) TCHAR* __cdecl wcsncpy(TCHAR*, const TCHAR*, unsigned int);
extern "C" __declspec(dllimport) TCHAR* __cdecl wcsstr(const TCHAR*, const TCHAR*);

char* appToAnsi(const TCHAR* Str, char* Buffer);               // 0x14120
extern TCHAR GTrue[64];
// Literals retail keeps in writable .data.
extern const TCHAR TEXT_On[];      // L"On"   0x10c710fc
extern const TCHAR TEXT_True[];    // L"True" 0x10c71104
extern const TCHAR TEXT_1[];       // L"1"    0x10c71110
extern const TCHAR TEXT_Quote[];
extern const TCHAR TEXT_Space[];
extern const TCHAR TEXT_CR[];
extern const TCHAR TEXT_LF[];
extern const TCHAR TEXT_Tab[];
extern const TCHAR TEXT_Pipe[];
extern const TCHAR TEXT_Comma[];

// RVA 0x11f90 (defined here so the linker gives it its register convention).
const TCHAR* appStrfind(const TCHAR* Str, const TCHAR* Find)
{
    UBOOL Alnum  = 0;
    TCHAR f      = (*Find < 'a' || *Find > 'z') ? (*Find) : (TCHAR)(*Find + 'A' - 'a');
    INT   Length = (INT)wcslen(Find++) - 1;
    TCHAR c      = *Str++;
    while (c)
    {
        if (c >= 'a' && c <= 'z')
            c += 'A' - 'a';
        if (!Alnum && c == f && !_wcsnicmp(Str, Find, Length))
            return Str - 1;
        Alnum = (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
        c = *Str++;
    }
    return 0;
}

// RVA 0x120e0 (defined here for its register convention).
UBOOL Parse(const TCHAR* Stream, const TCHAR* Match, TCHAR* Value, INT MaxLen)
{
    const TCHAR* Found = appStrfind(Stream, Match);
    if (!Found)
        return 0;
    const TCHAR* Start = Found + wcslen(Match);
    TCHAR* Temp;
    if (*Start == '"')
    {
        wcsncpy(Value, Start + 1, MaxLen);
        Value[MaxLen - 1] = 0;
        Temp = wcsstr(Value, TEXT_Quote);
    }
    else
    {
        wcsncpy(Value, Start, MaxLen);
        Value[MaxLen - 1] = 0;
        Temp = wcsstr(Value, TEXT_Space); if (Temp) *Temp = 0;
        Temp = wcsstr(Value, TEXT_CR);    if (Temp) *Temp = 0;
        Temp = wcsstr(Value, TEXT_LF);    if (Temp) *Temp = 0;
        Temp = wcsstr(Value, TEXT_Tab);   if (Temp) *Temp = 0;
        Temp = wcsstr(Value, TEXT_Pipe);  if (Temp) *Temp = 0;
        Temp = wcsstr(Value, TEXT_Comma);
    }
    if (Temp) *Temp = 0;
    return 1;
}

// Retail keeps these two small overloads out of line at every call site.
#pragma auto_inline(off)
// RVA 0x12400
UBOOL Parse(const TCHAR* Stream, const TCHAR* Match, FLOAT& Value)
{
    const TCHAR* Temp = appStrfind(Stream, Match);
    if (Temp == 0)
        return 0;
    Temp += wcslen(Match);
    Value = (FLOAT)atof(appToAnsi(Temp, 0));
    return 1;
}

// RVA 0x12440
UBOOL Parse(const TCHAR* Stream, const TCHAR* Match, INT& Value)
{
    const TCHAR* Temp = appStrfind(Stream, Match);
    if (Temp == 0)
        return 0;
    Temp += wcslen(Match);
    Value = _wtoi(Temp);
    return 1;
}

#pragma auto_inline(on)
// RVA 0x12480
UBOOL ParseUBOOL(const TCHAR* Stream, const TCHAR* Match, UBOOL& OnOff)
{
    TCHAR TempStr[16];
    if (Parse(Stream, Match, TempStr, 16))
    {
        OnOff = !_wcsicmp(TempStr, TEXT_On)
             || !_wcsicmp(TempStr, TEXT_True)
             || !_wcsicmp(TempStr, GTrue)
             || !_wcsicmp(TempStr, TEXT_1);
        return 1;
    }
    return 0;
}

// Scaffolding for the link, not part of the unit.
extern "C" void Driver_12400(const TCHAR* S0, const TCHAR* S1, const TCHAR* S2, const TCHAR* M, FLOAT* X) { Parse(S0, M, X[0]); Parse(S1, M, X[1]); Parse(S2, M, X[2]); Parse(S0, M, X[3]); Parse(S1, M, X[4]); Parse(S2, M, X[5]); Parse(S0, M, X[6]); Parse(S1, M, X[7]); Parse(S2, M, X[8]); Parse(S0, M, X[9]); Parse(S1, M, X[10]); Parse(S2, M, X[11]); Parse(S0, M, X[12]); Parse(S1, M, X[13]); Parse(S2, M, X[14]); Parse(S0, M, X[15]); }
extern "C" void Driver_12440(const TCHAR* S0, const TCHAR* S1, const TCHAR* S2, const TCHAR* M, INT* X) { Parse(S0, M, X[0]); Parse(S1, M, X[1]); Parse(S2, M, X[2]); Parse(S0, M, X[3]); Parse(S1, M, X[4]); Parse(S2, M, X[5]); Parse(S0, M, X[6]); Parse(S1, M, X[7]); Parse(S2, M, X[8]); Parse(S0, M, X[9]); Parse(S1, M, X[10]); Parse(S2, M, X[11]); Parse(S0, M, X[12]); Parse(S1, M, X[13]); Parse(S2, M, X[14]); Parse(S0, M, X[15]); }
extern "C" void Driver_12480(const TCHAR* S, const TCHAR* M, UBOOL* B) { ParseUBOOL(S, M, B[0]); ParseUBOOL(M, S, B[1]); ParseUBOOL(S, S, B[2]); }
extern "C" void Driver_120e0(const TCHAR* S, const TCHAR* M, TCHAR* V, INT N) { Parse(S, M, V, N); Parse(M, S, V, N); }
