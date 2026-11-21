// Work item 0132: Versus RVA 0x3c4d0, UStruct::SerializeBin (UE2 UnClass.cpp, LTCG code).
// Vtable slot 29 (+0x74) of UStruct/UState/UClass/UFunction. Calls
// TFieldIterator<UProperty>::IterateToNext (RVA 0x1f850, this in ESI).
// Old packages (ArVer < 0x73) of the TerrainInfo-like "DecorationLayer" struct skip the
// LitDirectional and DisregardTerrainLighting members that were added later.
typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef short SWORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum { CLASS_IsAUProperty = 0x8000 };
enum
{
    CPF_Native     = 0x00001000,
    CPF_Transient  = 0x00002000,
    CPF_NoSaveTrans = 0x20000000,   // neutral name; skipped when saving or transacting
};

// These literals live in writable .data in retail (VC7.0 /GL), so they are bound as externs.
extern const TCHAR Name_DecorationLayer[];          // 0x10c52f58 L"DecorationLayer"
extern const TCHAR Name_LitDirectional[];           // 0x10c52f78 L"LitDirectional"
extern const TCHAR Name_DisregardTerrainLighting[]; // 0x10c52f98 L"DisregardTerrainLighting"

extern "C" __declspec(dllimport) INT __cdecl wcscmp(const TCHAR *, const TCHAR *);
inline INT appStrcmp(const TCHAR *A, const TCHAR *B) { return wcscmp(A, B); }

struct FNameEntry
{
    INT Index;
    DWORD Flags;
    FNameEntry *HashNext;
    TCHAR Name[64];
};

template <class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    T &operator()(INT i) { return Data[i]; }
};

class FName
{
public:
    INT Index;
    const TCHAR *operator*() const { return Names(Index)->Name; }
    static TArray<FNameEntry *> Names;
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(void *Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual FArchive &operator<<(FName &N);
    virtual FArchive &operator<<(void *&Res);
    virtual INT MapName(FName *Name);
    virtual INT MapObject(void *Object);
    virtual INT Tell();
    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }
    UBOOL IsTrans() { return ArIsTrans; }
    UBOOL IsPersistent() { return ArIsPersistent; }
    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    UBOOL ArIsTrans;
    UBOOL ArIsPersistent;
};

class UClass;
class UStruct;
class UObject
{
public:
    virtual void Slot00();
    BYTE Pad04[0x20 - 0x04];
    FName Name;             // +0x20
    UClass *Class;          // +0x24
    const TCHAR *GetName() const { return *Name; }
};
class UField : public UObject
{
public:
    UField *SuperField;     // +0x28
    UField *Next;           // +0x2c
};
class UProperty : public UField
{
public:
    SWORD ArrayDim;         // +0x30
    SWORD ElementSize;      // +0x32
    DWORD PropertyFlags;    // +0x34
    BYTE Pad38[4];
    INT Offset;             // +0x3c
    virtual void V01(); virtual void V02(); virtual void V03(); virtual void V04();
    virtual void V05(); virtual void V06(); virtual void V07(); virtual void V08();
    virtual void V09(); virtual void V10(); virtual void V11(); virtual void V12();
    virtual void V13(); virtual void V14(); virtual void V15(); virtual void V16();
    virtual void V17(); virtual void V18(); virtual void V19(); virtual void V20();
    virtual void V21(); virtual void V22(); virtual void V23(); virtual void V24();
    virtual void V25(); virtual void V26(); virtual void V27(); virtual void V28();
    virtual void V29();
    virtual void SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes);
};
class UStruct : public UField
{
public:
    UField *Children;       // +0x30
    UStruct *GetInheritanceSuper();
    void SerializeBin(FArchive &Ar, BYTE *Data, INT MaxReadBytes);
};

class UClass : public UStruct
{
public:
    BYTE Pad34[0x88 - 0x34];
    DWORD ClassFlags;       // +0x88
};

class TFieldIterator_UProperty
{
public:
    UStruct *Struct;
    UField *Field;
    TFieldIterator_UProperty(UStruct *InStruct)
        : Struct(InStruct), Field(InStruct ? InStruct->Children : 0)
    {
        IterateToNext();
    }
    void operator++() { Field = Field->Next; IterateToNext(); }
    operator UBOOL() { return Field != 0; }
    UProperty *operator*() { return (UProperty *)Field; }
    void IterateToNext();
};

// RVA 0x1f850, bound separately (published with item 0098); defined so the link
// gives it its retail register convention (this in ESI).
void TFieldIterator_UProperty::IterateToNext()
{
    while (Struct) {
        while (Field) {
            if (Field->Class->ClassFlags & CLASS_IsAUProperty)
                return;
            Field = Field->Next;
        }
        Struct = Struct->GetInheritanceSuper();
        if (Struct)
            Field = Struct->Children;
    }
}

void UStruct::SerializeBin(FArchive &Ar, BYTE *Data, INT MaxReadBytes)
{
    INT StartPos = Ar.Tell() + MaxReadBytes;
    UBOOL OldDecorationLayer = Ar.Ver() < 0x73 && appStrcmp(GetName(), Name_DecorationLayer) == 0;
    for (TFieldIterator_UProperty It(this); It; ++It)
    {
        UProperty *Property = *It;
        FName PropertyName = Property->Name;
        if (OldDecorationLayer
            && (appStrcmp(*PropertyName, Name_LitDirectional) == 0
                || appStrcmp(*PropertyName, Name_DisregardTerrainLighting) == 0))
            continue;
        if (Property->PropertyFlags & CPF_Native)
            continue;
        if ((Property->PropertyFlags & CPF_Transient) && Ar.IsPersistent())
            continue;
        if ((Property->PropertyFlags & CPF_NoSaveTrans) && (Ar.IsSaving() || Ar.IsTrans()))
            continue;
        for (INT Index = 0; Index < Property->ArrayDim; Index++)
        {
            if (Ar.Ver() < 0x76 && MaxReadBytes && Ar.IsLoading() && Ar.Tell() >= StartPos)
                continue;
            Property->SerializeItem(Ar, Data + Property->Offset + Index * Property->ElementSize, 0);
        }
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_3c4d0(UStruct *S, FArchive &Ar, BYTE *Data, INT Max)
{
    void (UStruct::*Fn)(FArchive &, BYTE *, INT) = &UStruct::SerializeBin;
    Escape(&Fn);
    Escape(&FName::Names);
    S->SerializeBin(Ar, Data, Max);
}
