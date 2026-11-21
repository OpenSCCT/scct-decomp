// Work item 0129: Versus RVA 0x3b9b0-0x3bd38 (Core UnClass.h FPropertyTag).
// Both functions come from the LTCG link and take arguments in registers:
//   0x3b9b0 FPropertyTag::FPropertyTag (tag in ESI, Property in ECX)
//   0x3bb30 operator<<(FArchive&, FPropertyTag&) (Ar in ESI, Tag in EDI)
typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;

extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);
inline TCHAR *appStrcpy(TCHAR *Dest, const TCHAR *Src) { return wcscpy(Dest, Src); }

enum EName { NAME_None = 0, NAME_BoolProperty = 3, NAME_StructProperty = 10 };
enum { NAME_SIZE = 64 };

struct FNameEntry
{
    INT Index;
    DWORD Flags;
    FNameEntry *HashNext;
    TCHAR Name[NAME_SIZE];
};

template <class T> struct TArray
{
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    T &operator()(INT i) { return Data[i]; }
};

class FName
{
public:
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    INT GetIndex() const { return Index; }
    const TCHAR *operator*() const { return Names(Index)->Name; }
    bool operator==(EName N) const { return Index == N; }
    static TArray<FNameEntry *> Names; // 0x10cc9e5c
};

class FArchive
{
public:
    FArchive()
        : ArVer(0xaf), ArNetVer(0x7d0), ArLicenseeVer(0), ArIsLoading(0), ArIsSaving(0)
        , ArIsTrans(0), ArIsPersistent(0), ArForEdit(1), ArForClient(1), ArForServer(1)
        , ArIsError(0)
    {
        ArUnknown[0] = 0; ArUnknown[1] = 3; ArUnknown[2] = 0; ArUnknown[3] = -1;
    }
    virtual ~FArchive() {}
    virtual void Serialize(void *V, INT Length);          // +0x04
    virtual void Slot08();
    virtual void Slot0C();
    virtual void Slot10();
    virtual void Slot14();
    virtual void Slot18();
    virtual FArchive &operator<<(FName &N);               // +0x1c
    UBOOL IsLoading() const { return ArIsLoading; }
    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, _WORD &W) { Ar.Serialize(&W, 2); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, INT &I) { Ar.Serialize(&I, 4); return Ar; }
    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    UBOOL ArIsTrans;
    UBOOL ArIsPersistent;
    UBOOL ArForEdit;
    UBOOL ArForClient;
    UBOOL ArForServer;
    UBOOL ArIsError;
    INT ArUnknown[4];       // fields not yet identified; FArchive is 0x40 bytes here
};

// Counts the bytes serialized into it; constructor at 0x3b8d0 (LTCG: this in
// EAX, source archive in EDX). That constructor belongs to work item 0128 and is
// defined here only so the link gives it its retail register convention.
class FArchiveCountMem : public FArchive
{
public:
    FArchiveCountMem(FArchive *InSrc);
    INT GetNum() { return Num; }
protected:
    INT Num;
    FArchive *Src;
};

FArchiveCountMem::FArchiveCountMem(FArchive *InSrc)
    : Num(0), Src(InSrc)
{
    ArIsSaving = Src ? Src->ArIsSaving : 0;
    ArIsPersistent = Src ? Src->ArIsPersistent : 0;
}

class UClass;
class UObject
{
public:
    virtual ~UObject();
    INT ObjectInternal[7];  // 0x04-0x1f
    FName Name;             // 0x20
    UClass *Class;          // 0x24
    UClass *GetClass() const { return Class; }
    FName GetFName() const { return Name; }
    template <class T> UBOOL IsA() const;
};

class UField : public UObject
{
public:
    UField *SuperField;     // 0x28
};

class UStruct : public UField
{
public:
    INT StructInternal[11]; // 0x2c-0x57
};

class UClass : public UStruct
{
public:
};

class UProperty : public UField
{
public:
    // Vtable slots used here; the rest are placeholders.
    virtual void V04(); virtual void V08(); virtual void V0C(); virtual void V10();
    virtual void V14(); virtual void V18(); virtual void V1C(); virtual void V20();
    virtual void V24(); virtual void V28(); virtual void V2C(); virtual void V30();
    virtual void V34(); virtual void V38(); virtual void V3C(); virtual void V40();
    virtual void V44(); virtual void V48(); virtual void V4C(); virtual void V50();
    virtual void V54(); virtual void V58(); virtual void V5C(); virtual void V60();
    virtual void V64(); virtual void V68(); virtual void V6C(); virtual void V70();
    virtual void V74();
    virtual void SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const; // +0x78
    virtual void V7C(); virtual void V80(); virtual void V84(); virtual void V88();
    virtual void V8C(); virtual void V90(); virtual void V94(); virtual void V98();
    virtual BYTE GetID() const;                                                   // +0x9c
    INT PropertyInternal[11]; // 0x2c-0x57
};

class UBoolProperty : public UProperty
{
public:
    BITFIELD BitMask;       // 0x58
    static UClass PrivateStaticClass; // 0x10cc8a70
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class UStructProperty : public UProperty
{
public:
    UStruct *Struct;        // 0x58
    static UClass PrivateStaticClass; // 0x10cc9448
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

template <class T> inline UBOOL UObject::IsA() const
{
    for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == T::StaticClass())
            return 1;
    return 0;
}

template <class T> inline T *Cast(UObject *Src)
{
    return Src && Src->IsA<T>() ? (T *)Src : 0;
}

// PrevTag was a function-local static in operator<<(FArchive&, FPropertyTag&).
extern TCHAR FPropertyTag_PrevTag[NAME_SIZE]; // 0x10ccadb0

struct FPropertyTag
{
    BYTE Type;
    BYTE Info;
    FName Name;
    FName ItemName;
    INT Size;
    INT ArrayIndex;

    FPropertyTag(FArchive &InSaveAr, UProperty *Property, INT InIndex, BYTE *Value);

    // Serialize the tagged property's value.
    void SerializeTaggedProperty(FArchive &Ar, UProperty *Property, BYTE *Value, INT MaxReadBytes, BYTE *Defaults)
    {
        if (Property->GetClass() == UBoolProperty::StaticClass()) {
            UBoolProperty *Bool = (UBoolProperty *)Property;
            if (Ar.IsLoading()) {
                if (Info & 0x80) *(BITFIELD *)Value |= Bool->BitMask;
                else             *(BITFIELD *)Value &= ~Bool->BitMask;
            }
        } else {
            Property->SerializeItem(Ar, Value, MaxReadBytes);
        }
    }

    friend FArchive &operator<<(FArchive &Ar, FPropertyTag &Tag);
};

// RVA 0x3b9b0
FPropertyTag::FPropertyTag(FArchive &InSaveAr, UProperty *Property, INT InIndex, BYTE *Value)
    : Type(Property->GetID())
    , Info(Property->GetID())
    , Name(Property->GetFName())
    , ItemName(NAME_None)
    , Size(0)
    , ArrayIndex(InIndex)
{
    // Handle structs.
    UStructProperty *StructProperty = Cast<UStructProperty>(Property);
    if (StructProperty)
        ItemName = StructProperty->Struct->GetFName();

    // Set size.
    FArchiveCountMem ArCount(&InSaveAr);
    SerializeTaggedProperty(ArCount, Property, Value, 0, 0);
    Size = ArCount.GetNum();

    // Update info bits.
    Info |=
        (  Size == 1     ? 0x00
         : Size == 2     ? 0x10
         : Size == 4     ? 0x20
         : Size == 12    ? 0x30
         : Size == 16    ? 0x40
         : Size <= 255   ? 0x50
         : Size <= 65536 ? 0x60
         :                 0x70);
    UBoolProperty *Bool = Cast<UBoolProperty>(Property);
    if (ArrayIndex || (Bool && (*(BITFIELD *)Value & Bool->BitMask)))
        Info |= 0x80;
}

// RVA 0x3bb30
FArchive &operator<<(FArchive &Ar, FPropertyTag &Tag)
{
    BYTE SizeByte;
    _WORD SizeWord;
    INT SizeInt;

    // Name.
    Ar << Tag.Name;
    if (Tag.Name == NAME_None)
        return Ar;
    appStrcpy(FPropertyTag_PrevTag, *Tag.Name);

    // Packed info byte.
    Ar << Tag.Info;
    Tag.Type = Tag.Info & 0x0f;
    if (Tag.Type == NAME_StructProperty)
        Ar << Tag.ItemName;

    // Size.
    switch (Tag.Info & 0x70) {
    case 0x00: Tag.Size = 1; break;
    case 0x10: Tag.Size = 2; break;
    case 0x20: Tag.Size = 4; break;
    case 0x30: Tag.Size = 12; break;
    case 0x40: Tag.Size = 16; break;
    case 0x50: SizeByte = Tag.Size; Ar << SizeByte; Tag.Size = SizeByte; break;
    case 0x60: SizeWord = Tag.Size; Ar << SizeWord; Tag.Size = SizeWord; break;
    case 0x70: SizeInt = Tag.Size; Ar << SizeInt; Tag.Size = SizeInt; break;
    }

    // Array index, packed in one to four bytes.
    if ((Tag.Info & 0x80) && Tag.Type != NAME_BoolProperty) {
        BYTE B = (Tag.ArrayIndex <= 127) ? (Tag.ArrayIndex)
               : (Tag.ArrayIndex <= 16383) ? (Tag.ArrayIndex >> 8) + 0x80
               : (Tag.ArrayIndex >> 24) + 0xC0;
        Ar << B;
        if ((B & 0x80) == 0) {
            Tag.ArrayIndex = B;
        } else if ((B & 0xC0) == 0x80) {
            BYTE C = Tag.ArrayIndex & 255;
            Ar << C;
            Tag.ArrayIndex = ((INT)(B & 0x7F) << 8) + ((INT)C);
        } else {
            BYTE C = Tag.ArrayIndex >> 16;
            BYTE D = Tag.ArrayIndex >> 8;
            BYTE E = Tag.ArrayIndex;
            Ar << C << D << E;
            Tag.ArrayIndex = ((INT)(B & 0x3F) << 24) + ((INT)C << 16) + ((INT)D << 8) + ((INT)E);
        }
    } else {
        Tag.ArrayIndex = 0;
    }
    return Ar;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
FArchive &Driver_3bb30(FArchive &Ar, FPropertyTag &Tag) { Escape(&FName::Names); Escape(FPropertyTag_PrevTag); return Ar << Tag; }
void Use(FPropertyTag *);
void Driver_3b9b0(FArchive &Ar, UProperty *P, INT Index, BYTE *Value)
{
    Escape(&UStructProperty::PrivateStaticClass);
    Escape(&UBoolProperty::PrivateStaticClass);
    FPropertyTag Tag(Ar, P, Index, Value);
    Use(&Tag);
}
