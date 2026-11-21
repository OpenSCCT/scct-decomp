// Work item 0059: Versus RVA 0x134dc0-0x13504c (Engine, UnStatGraph.cpp).
// FStatGraph::Exec: handles the "GRAPH" console command (SHOW, KEY, LOCKSCALE,
// RESCALE, SHOWSTAT, XRANGE=, XSIZE=, YSIZE=, XPOS=, YPOS=, ALPHA=, FILTER=,
// ADDSTAT=, REMSTAT=).
//
// Built with VC7.0 /GL and linked /LTCG. Callees from Core and Engine are
// defined with their retail bodies so the linker assigns the same register
// conventions.

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

enum { INDEX_NONE = -1 };

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *S);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *A, const TCHAR *B);
extern "C" __declspec(dllimport) int __cdecl _wcsnicmp(const TCHAR *A, const TCHAR *B, unsigned int Count);
extern "C" __declspec(dllimport) double __cdecl atof(const char *S);
extern "C" __declspec(dllimport) int __cdecl _wtoi(const TCHAR *S);
void *appMemcpy(void *Dest, const void *Src, INT Count);
char *appToAnsi(const TCHAR *Str, char *Buffer);

inline INT appStrlen(const TCHAR *S) { return (INT)wcslen(S); }
inline INT appStricmp(const TCHAR *A, const TCHAR *B) { return _wcsicmp(A, B); }
inline INT appStrnicmp(const TCHAR *A, const TCHAR *B, INT Count) { return _wcsnicmp(A, B, Count); }
inline INT appAtoi(const TCHAR *S) { return _wtoi(S); }
inline UBOOL appIsDigit(TCHAR c) { return c >= '0' && c <= '9'; }
inline UBOOL appIsAlnum(TCHAR c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

extern const TCHAR Text_FStringTag[];   // L"FString::="
extern const TCHAR Text_FArrayTag[];    // L"FArray"
extern const TCHAR Text_NullString[];   // L""

// Literals retail keeps in writable .data.
extern const TCHAR TEXT_GRAPH[];        // L"GRAPH"
extern const TCHAR TEXT_SHOW[];         // L"SHOW"
extern const TCHAR TEXT_KEY[];          // L"KEY"
extern const TCHAR TEXT_LOCKSCALE[];    // L"LOCKSCALE"
extern const TCHAR TEXT_RESCALE[];      // L"RESCALE"
extern const TCHAR TEXT_SHOWSTAT[];     // L"SHOWSTAT"
extern const TCHAR TEXT_XRANGE[];       // L"XRANGE="
extern const TCHAR TEXT_XSIZE[];        // L"XSIZE="
extern const TCHAR TEXT_YSIZE[];        // L"YSIZE="
extern const TCHAR TEXT_XPOS[];         // L"XPOS="
extern const TCHAR TEXT_YPOS[];         // L"YPOS="
extern const TCHAR TEXT_ALPHA[];        // L"ALPHA="
extern const TCHAR TEXT_FILTER[];       // L"FILTER="
extern const TCHAR TEXT_None[];         // L"None"
extern const TCHAR TEXT_Empty[];        // L""
extern const TCHAR TEXT_ADDSTAT[];      // L"ADDSTAT="
extern const TCHAR TEXT_REMSTAT[];      // L"REMSTAT="

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event);
    virtual void Flush();
};

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    INT Add(INT Count, INT ElementSize);
    void Remove(INT Index, INT Count, INT ElementSize);
    INT Num() const { return ArrayNum; }

    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    TArray() {}
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
    INT Add(INT Count = 1) { return FArray::Add(Count, sizeof(T)); }
    void Remove(INT Index, INT Count = 1) { FArray::Remove(Index, Count, sizeof(T)); }
    INT FindItemIndex(const T &Item) const;
    __declspec(noinline) INT AddItem(const T &Item)
    {
        INT Index = Add(1);
        (*this)(Index) = Item;
        return Index;
    }
    __declspec(noinline) INT RemoveItem(const T &Item)
    {
        INT OriginalNum = ArrayNum;
        for (INT Index = 0; Index < ArrayNum; Index++)
            if (((T *)Data)[Index] == Item)
                Remove(Index--, 1);
        return OriginalNum - ArrayNum;
    }
};

class FString : public TArray<TCHAR>
{
public:
    FString() {}
    FString(const FString &Other);
    FString(const TCHAR *In);
    ~FString();
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : Text_NullString; }
    __declspec(noinline) UBOOL operator==(const FString &Other) const
    {
        return appStricmp(**this, *Other) == 0;
    }
    __declspec(noinline) FString &operator=(const TCHAR *Other)
    {
        if (Other != (const TCHAR *)Data)
        {
            if (*Other == 0)
            {
                if (Data)
                {
                    ArrayNum = 0;
                    ArrayMax = 0;
                    GMalloc->Free(Data);
                    Data = 0;
                }
            }
            else
            {
                if (Data == 0)
                {
                    ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                    Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), Text_FStringTag);
                }
                else
                {
                    ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                    Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), Text_FArrayTag);
                }
                appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
            }
        }
        return *this;
    }
};

// Core Parse helpers (from versus_vd3r_item_0073.cpp, 0074.cpp, versus_vd4_item_0342.cpp).
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find)
{
    UBOOL Alnum = 0;
    TCHAR f = (*Find < 'a' || *Find > 'z') ? (*Find) : (TCHAR)(*Find + 'A' - 'a');
    INT Length = (INT)wcslen(Find++) - 1;
    TCHAR c = *Str++;
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

__declspec(noinline) UBOOL ParseCommand(const TCHAR **Stream, const TCHAR *Match)
{
    while ((**Stream == ' ') || (**Stream == 9))
        (*Stream)++;
    if (appStrnicmp(*Stream, Match, appStrlen(Match)) == 0)
    {
        *Stream += appStrlen(Match);
        if (!appIsAlnum(**Stream))
        {
            while ((**Stream == ' ') || (**Stream == 9))
                (*Stream)++;
            return 1;
        }
        else
        {
            *Stream -= appStrlen(Match);
            return 0;
        }
    }
    else return 0;
}

__declspec(noinline) UBOOL Parse(const TCHAR *Stream, const TCHAR *Match, INT &Value)
{
    const TCHAR *Temp = appStrfind(Stream, Match);
    if (Temp == 0)
        return 0;
    Temp += wcslen(Match);
    Value = _wtoi(Temp);
    return 1;
}

__declspec(noinline) UBOOL Parse(const TCHAR *Stream, const TCHAR *Match, FLOAT &Value)
{
    const TCHAR *Temp = appStrfind(Stream, Match);
    if (Temp == 0)
        return 0;
    Temp += wcslen(Match);
    Value = (FLOAT)atof(appToAnsi(Temp, 0));
    return 1;
}

__declspec(noinline) UBOOL Parse(const TCHAR *Stream, const TCHAR *Match, BYTE &Value)
{
    const TCHAR *Temp = appStrfind(Stream, Match);
    if (Temp == 0)
        return 0;
    Temp += appStrlen(Match);
    Value = (BYTE)appAtoi(Temp);
    return Value != 0 || appIsDigit(Temp[0]);
}

UBOOL Parse(const TCHAR *Stream, const TCHAR *Match, FString &Value);

INT FindStatIndex(FString StatName);

struct FStatGraphLine
{
    INT unk_00;
    FLOAT *DataHistory;
    INT unk_08[7];
    FLOAT YRangeMin;
    FLOAT YRangeMax;
    INT unk_2c;
    UBOOL bAutoScale;
};

template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

class FStatGraph
{
public:
    UBOOL bHideGraph;               // 0x00
    UBOOL bLockScale;               // 0x04
    INT LineNameMap[5];             // 0x08 (TMap<FString, INT>)
    TArray<FStatGraphLine> Lines;   // 0x1c
    TArray<INT> GetData;            // 0x28
    FLOAT XSize;                    // 0x34
    FLOAT YSize;                    // 0x38
    FLOAT XPos;                     // 0x3c
    FLOAT YPos;                     // 0x40
    INT XRange;                     // 0x44
    UBOOL bHideKey;                 // 0x48
    INT unk_4c;                     // 0x4c
    BYTE BackgroundAlpha;           // 0x50
    FString FilterString;           // 0x54

    // RVA 0x134b80 (this in EBX)
    __declspec(noinline) void AutoScale()
    {
        for (INT i = 0; i < Lines.Num(); i++)
        {
            FStatGraphLine &Line = Lines(i);
            if (Line.bAutoScale)
            {
                Line.YRangeMin = 0.0f;
                Line.YRangeMax = 0.0f;
                for (INT j = 0; j < 256; j++)
                {
                    Line.YRangeMin = Min(Line.YRangeMin, Line.DataHistory[j]);
                    Line.YRangeMax = Max(Line.YRangeMax, Line.DataHistory[j]);
                }
            }
        }
    }

    // RVA 0x134800: link-time convention passes `this` on the stack (ret 0x10);
    // declared __stdcall because its body is not part of this unit.
    void __stdcall RemoveLine(FString LineName);

    // RVA 0x134dc0
    __declspec(noinline) UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar);
};

// RVA 0x134dc0: FStatGraph::Exec
UBOOL FStatGraph::Exec(const TCHAR *Cmd, FOutputDevice &Ar)
{
    if (ParseCommand(&Cmd, TEXT_GRAPH))
    {
        if (ParseCommand(&Cmd, TEXT_SHOW))
        {
            bHideGraph = !bHideGraph;
            return 1;
        }
        else if (ParseCommand(&Cmd, TEXT_KEY))
        {
            bHideKey = !bHideKey;
            return 1;
        }
        else if (ParseCommand(&Cmd, TEXT_LOCKSCALE))
        {
            bLockScale = !bLockScale;
            return 1;
        }
        else if (ParseCommand(&Cmd, TEXT_RESCALE))
        {
            AutoScale();
            return 1;
        }
        else if (ParseCommand(&Cmd, TEXT_SHOWSTAT))
        {
            return 1;
        }
        else
        {
            Parse(Cmd, TEXT_XRANGE, XRange);
            Parse(Cmd, TEXT_XSIZE, XSize);
            Parse(Cmd, TEXT_YSIZE, YSize);
            Parse(Cmd, TEXT_XPOS, XPos);
            Parse(Cmd, TEXT_YPOS, YPos);
            Parse(Cmd, TEXT_ALPHA, BackgroundAlpha);
            Parse(Cmd, TEXT_FILTER, FilterString);

            if (FilterString == FString(TEXT_None))
                FilterString = TEXT_Empty;

            FString StatName;
            if (Parse(Cmd, TEXT_ADDSTAT, StatName))
            {
                INT StatIndex = FindStatIndex(StatName);
                if (StatIndex != INDEX_NONE)
                {
                    if (GetData.FindItemIndex(StatIndex) == INDEX_NONE)
                        GetData.AddItem(StatIndex);
                }
            }

            if (Parse(Cmd, TEXT_REMSTAT, StatName))
            {
                INT StatIndex = FindStatIndex(StatName);
                if (StatIndex != INDEX_NONE)
                {
                    GetData.RemoveItem(StatIndex);
                    RemoveLine(StatName);
                }
            }
        }
        return 1;
    }
    else
        return 0;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
extern FStatGraph *GStatGraph;
UBOOL Driver_134dc0(const TCHAR *Cmd, FOutputDevice *Ar)
{
    Escape(&GMalloc);
    Escape(&GStatGraph);
    UBOOL (FString::*EqPtr)(const FString &) const = &FString::operator==;
    Escape(*(void **)&EqPtr);
    if (GStatGraph)
        return GStatGraph->Exec(Cmd, *Ar);
    return 0;
}
