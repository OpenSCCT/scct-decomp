// Work item 0135: UClass::Destroy and UClass::PostLoad (RVA 0x3d010-0x3d142).
// Slots 9 and 8 of the UClass vtable at 0x30d838.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    void Empty()
    {
        ArrayNum = 0;
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
};

class FString : public FArray
{
public:
    FString &operator=(const TCHAR *Other);
};

extern const TCHAR EmptyString[]; // TEXT("")
extern "C" unsigned int wcslen(const TCHAR *);
void appMemcpy(void *Dest, const void *Src, INT Count);

// Defined here so the link gives it retail's register convention (0x4750).
FString &FString::operator=(const TCHAR *Other)
{
    if (Other != (const TCHAR *)Data) {
        if (*Other == 0) {
            if (Data) { ArrayNum = 0; ArrayMax = 0; GMalloc->Free(Data); Data = 0; }
        } else {
            if (Data == 0) {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), L"FString::=");
            } else {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), L"FArray");
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}

class UProperty
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
    UProperty *ConstructorLinkNext;
};

// Called with no arguments when the class has flag 0x100 (unidentified).
void UnnamedFunction_16f70();

class UObject
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void PostLoad();
    virtual void Destroy();
    virtual void V10(); virtual void V11(); virtual void V12(); virtual void V13();
    virtual void V14(); virtual void V15(); virtual void V16(); virtual void V17();
    virtual void V18(); virtual void V19(); virtual void V20(); virtual void V21();
    virtual void V22(); virtual void V23();
    virtual void Bind();
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    INT Name;
    UObject *Class;
};

class UState : public UObject
{
public:
    UObject *SuperField;              // 0x28
    BYTE Pad2c[0x64 - 0x2c];
    UProperty *ConstructorLink;       // 0x64
    BYTE Pad68[0xa0 - 0x68];
    void Destroy();
};

class UClass : public UState
{
public:
    FArray NetFields;                 // 0xa0
    FArray Defaults;                  // 0xac
    BYTE PadB8[0xc8 - 0xb8];
    FString DefaultPropText;          // 0xc8
    FArray Dependencies;              // 0xd4
    FArray PackageImports;            // 0xe0

    UClass();
    void Destroy();
    void PostLoad();
};
inline void *operator new(unsigned int, void *P) { return P; }

void UClass::Destroy()
{
    NetFields.Empty();
    Dependencies.Empty();
    PackageImports.Empty();
    if (Defaults.Num())
    {
        BYTE *Data = (BYTE *)Defaults.Data;
        for (UProperty *P = ConstructorLink; P; P = P->ConstructorLinkNext)
            P->DestroyValue(Data + P->Offset);
        Defaults.Empty();
    }
    DefaultPropText = EmptyString;
    UState::Destroy();
}

void UClass::PostLoad()
{
    ObjectFlags |= 0x20000000;
    if (ObjectFlags & 0x100)
        UnnamedFunction_16f70();
    Bind();
    UObject *Super = SuperField;
    if (Super && (Super->ObjectFlags & 0x01000000))
    {
        Super->ObjectFlags &= ~0x21000000;
        Super->PostLoad();
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
UClass::UClass() {}
void Driver_3d010(UClass *C) { Escape(&GMalloc); new (C) UClass; C->UClass::Destroy(); }
void Driver_3d100(UClass *C) { C->UClass::PostLoad(); }
