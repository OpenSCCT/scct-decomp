// Work item w3 0025: Versus RVA 0x58130.
// Builds a dotted path string for an entry of a parent-linked table.
// Class identity unknown, hence the neutral name UnnamedClass_58130.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef short SWORD;

extern "C" __declspec(dllimport) TCHAR* __cdecl wcscat(TCHAR* Dest, const TCHAR* Src);
INT appSprintf(TCHAR* Dest, const TCHAR* Fmt, ...);

class FString {
public:
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FString(const TCHAR* In);                         // RVA 0x46c0
    ~FString();                                       // RVA 0x48b0
    FString& operator=(const FString& Other);         // RVA 0x4800
    FString operator+(const TCHAR* Str) const;        // RVA 0x4990
    FString operator+(const FString& Str) const;      // RVA 0xca00
protected:
    TCHAR* Data;
    INT ArrayNum;
    INT ArrayMax;
};

struct FNameEntry {
    INT Index;
    DWORD Flags;
    FNameEntry* HashNext;
    TCHAR Name[1];
};
extern FNameEntry** FName_Names;                     // FName::Names.Data

class UObject {
public:
    void GetPathName(UObject* StopOuter, TCHAR* Str) const;   // RVA 0x15d90
    const TCHAR* GetName() const { return FName_Names[Name]->Name; }
    void* VTable;
    INT Index;
    UObject* HashNext;
    void* StateFrame;
    void* _Linker;
    INT _LinkerIndex;
    UObject* Outer;
    DWORD ObjectFlags;
    INT Name;
    UObject* Class;
};

// Was a function-local static result buffer.
extern TCHAR UnnamedClass_58130_PathResult[];
extern const TCHAR Str_Dot[];          // 0x10c6f8e8
extern const TCHAR Str_None[];         // 0x10c6f8ec
extern const TCHAR Str_58130_A[];      // 0x10c92568
extern const TCHAR Str_58130_B[];      // 0x10c51378
extern const TCHAR Str_58130_C[];      // 0x10c5137c
extern const TCHAR Str_58130_D[];      // 0x10c51380

__forceinline const TCHAR* GetObjectPath(UObject* Obj)
{
    if (Obj)
    {
        UnnamedClass_58130_PathResult[0] = 0;
        if (Obj->Outer)
        {
            Obj->Outer->GetPathName(0, UnnamedClass_58130_PathResult);
            wcscat(UnnamedClass_58130_PathResult, Str_Dot);
        }
        const TCHAR* ObjName = Obj->GetName();
        wcscat(UnnamedClass_58130_PathResult, ObjName);
    }
    else
    {
        appSprintf(UnnamedClass_58130_PathResult, Str_None);
    }
    return UnnamedClass_58130_PathResult;
}

struct FEntry_1c {
    SWORD Type;
    SWORD Pad02;
    SWORD Parent;
    SWORD Pad06;
    INT Name;
    INT Pad[4];
};

struct FEntry_18 {
    INT Pad[3];
    INT Name;
    INT Pad2[2];
};

class UnnamedClass_58130 {
public:
    FString GetEntryPath(INT Index, const TCHAR* Prefix);
    char Pad00[0x28];
    UObject* Owner;              // 0x28
    char Pad2C[0x78 - 0x2c];
    FEntry_18* Array78;          // 0x78
    char Pad7C[0x84 - 0x7c];
    FEntry_1c* Entries;          // 0x84
};

FString UnnamedClass_58130::GetEntryPath(INT Index, const TCHAR* Prefix)
{
    FString Result;
    for (INT i = Index + 1; i != 0; i = Entries[i - 1].Parent)
    {
        if (i != Index + 1)
            Result = FString(Str_58130_A) + Str_58130_B + Result;
        Result = FString(FName_Names[Entries[i - 1].Name]->Name) + Result;
    }
    INT Type = Entries[Index].Type;
    INT* NamePtr;
    if (Type > 0)
        NamePtr = &Entries[Type - 1].Name;
    else if (Type < 0)
        NamePtr = &Array78[-Type - 1].Name;
    else
    {
        Index = 0x2a5;
        NamePtr = &Index;
    }
    INT TypeName = *NamePtr;
    if (!Prefix)
        Prefix = GetObjectPath(Owner);
    return FString(FName_Names[TypeName]->Name) + Str_58130_C + Prefix + Str_58130_D + Result;
}
