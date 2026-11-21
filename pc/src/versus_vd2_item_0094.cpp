// Work item 0094: UObject core helpers (RVA 0x15cb0-0x15e6c).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

#define RF_Destroyed 0x80000000
#define INDEX_NONE -1

class UObject;
class UClass;
class UProperty;

struct FObjectExport
{
    BYTE Pad0[0x14];
    UObject *_Object;
    BYTE Pad1[0x1c - 0x18];
};

class ULinkerLoad
{
public:
    BYTE Pad[0x84];
    FObjectExport *ExportMap;
};

struct FNameEntry
{
    BYTE Pad[0xc];
    TCHAR Name[1];
};

extern UObject **GObjObjects_Data;   // UObject::GObjObjects.Data
extern INT GObjObjects_Num;          // UObject::GObjObjects.ArrayNum
extern FNameEntry **GNames_Data;     // FName::Names.Data
extern TCHAR appStaticString1024_Result[1024]; // was a local static
int appSprintf(TCHAR *Dest, const TCHAR *Fmt, ...);
extern "C" __declspec(dllimport) TCHAR *wcscat(TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) TCHAR *wcscpy(TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) unsigned int wcslen(const TCHAR *);

class UObject
{
public:
    virtual ~UObject();
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    ULinkerLoad *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    INT Name;
    UClass *Class;

    virtual void Destroy();
    const TCHAR *GetPathName(UObject *StopOuter = 0, TCHAR *Str = 0) const;
    const TCHAR *GetFullName(TCHAR *Str = 0) const;
    const TCHAR *GetName() const { return GNames_Data[Name]->Name; }
    void SetLinker(ULinkerLoad *L, INT I);
    static UBOOL __fastcall IsValid(UObject *Obj);
};

class UProperty
{
public:
    virtual void Dummy();
    BYTE Pad[0x3c - 4];
    INT Offset;
    BYTE Pad2[0x48 - 0x40];
    UProperty *ConstructorLinkNext;
    void DestroyValueSlot();
};

class UClass
{
public:
    BYTE Pad[0x64];
    UProperty *ConstructorLink;
};

// Virtual call through vtable slot 0x94 (UProperty::DestroyValue).
class UPropertyV
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29(); virtual void V30(); virtual void V31();
    virtual void V32(); virtual void V33(); virtual void V34(); virtual void V35();
    virtual void V36();
    virtual void DestroyValue(void *Dest) const;
    BYTE Pad[0x3c - 4];
    INT Offset;
    BYTE Pad2[0x48 - 0x40];
    UPropertyV *ConstructorLinkNext;
};

__declspec(noinline) UBOOL __fastcall UObject::IsValid(UObject *Obj)
{
    UObject *Found = 0;
    if (Obj && Obj->Index >= 0 && Obj->Index < GObjObjects_Num)
        Found = GObjObjects_Data[Obj->Index];
    if (!Found)
        return 0;
    return Found == Obj;
}

__declspec(noinline) void UObject::SetLinker(ULinkerLoad *L, INT I)
{
    if (_Linker)
        _Linker->ExportMap[_LinkerIndex]._Object = 0;
    _Linker = L;
    _LinkerIndex = I;
}

inline void ExitProperties(BYTE *Data, UClass *Class)
{
    for (UPropertyV *P = (UPropertyV *)Class->ConstructorLink; P; P = P->ConstructorLinkNext)
        P->DestroyValue(Data + P->Offset);
}

void UObject::Destroy()
{
    ObjectFlags |= RF_Destroyed;
    ExitProperties((BYTE *)this, Class);
    // Unhook from the linker: SetLinker(NULL, INDEX_NONE), inlined here
    // in retail while other callers use the out-of-line copy at 0x15d60.
    if (_Linker)
        _Linker->ExportMap[_LinkerIndex]._Object = 0;
    _Linker = 0;
    _LinkerIndex = INDEX_NONE;
    _LinkerIndex = Outer ? Outer->Index : 0;
}

const TCHAR *UObject::GetPathName(UObject *StopOuter, TCHAR *Str) const
{
    TCHAR *Result = Str ? Str : appStaticString1024_Result;
    if (this != StopOuter) {
        *Result = 0;
        if (Outer != StopOuter) {
            Outer->GetPathName(StopOuter, Result);
            wcscat(Result, L".");
        }
        wcscat(Result, GetName());
    } else {
        appSprintf(Result, L"None");
    }
    return Result;
}

__declspec(noinline) const TCHAR *UObject::GetFullName(TCHAR *Str) const
{
    TCHAR *Result = Str ? Str : appStaticString1024_Result;
    if (this) {
        appSprintf(Result, L"%s.", ((UObject *)Class)->GetName());
        GetPathName(0, Result + wcslen(Result));
    } else {
        wcscpy(Result, L"None");
    }
    return Result;
}

// Scaffolding for the LTCG link, not part of the unit.
// (__declspec(noinline) above stands in for retail call sites the LTCG inliner
// declined; the drivers below only provide the callers.)
void Escape(void *);
UObject::~UObject() {}
void Driver_15cb0(UObject *A, UObject *B, UObject *C)
{
    Escape(&GObjObjects_Data); Escape(&GObjObjects_Num);
    if (UObject::IsValid(A)) Escape(A);
    if (UObject::IsValid(B)) Escape(B);
    if (UObject::IsValid(C)) Escape(C);
}
void Driver_15d60(UObject *O, ULinkerLoad *L, INT I, UObject *P, ULinkerLoad *M, INT J)
{
    O->SetLinker(L, I); Escape(O);
    P->SetLinker(M, J); Escape(P);
    O->SetLinker(M, I); Escape(L);
    P->SetLinker(L, J); Escape(M);
    O->SetLinker(0, J); Escape(P);
    P->SetLinker(L, 0); Escape(O);
    O->SetLinker(M, 5); Escape(L);
}
void Driver_15e10(UObject *O, TCHAR *T, UObject *P, TCHAR *U)
{
    Escape(&GNames_Data);
    Escape((void *)O->GetFullName(T));
    Escape((void *)P->GetFullName(U));
    Escape((void *)O->GetFullName(U));
    Escape((void *)P->GetFullName(T));
    Escape((void *)O->GetFullName(0));
    Escape((void *)P->GetFullName(0));
}
