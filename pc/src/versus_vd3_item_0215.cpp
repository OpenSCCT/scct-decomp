// Work item 0215: UProperty (Core, UnProp.cpp), RVA 0x54140-0x54340.
// In this build ArrayDim and ElementSize are 16-bit fields at 0x30/0x32.
// Vtable slot numbers follow the reflected vtables listed in the item; slots
// not used here are placeholders.

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned short TCHAR;
typedef short SWORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum ECppProperty { EC_CppProperty };

enum EPropertyFlags
{
    CPF_Net       = 0x00000020,
    CPF_Native    = 0x00001000,
    CPF_Transient = 0x00002000,
};

enum { NAME_None = 0, NAME_Class = 0x2a5 };

class FName
{
public:
    INT Index;
    INT GetIndex() const { return Index; }
};

class UObject;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);                   // 1
    virtual void SerializeBits(void *V, INT LengthBits);           // 2
    virtual void SerializeInt(DWORD &Value, DWORD Max);            // 3
    virtual void Preload(UObject *Object);                         // 4
    virtual void CountBytes(DWORD InNum, DWORD InMax);             // 5
    // MSVC lays out overloaded virtuals in reverse declaration order:
    // operator<<(UObject*&) lands in slot 6, operator<<(FName&) in slot 7.
    virtual FArchive &operator<<(FName &N);                        // slot 7
    virtual FArchive &operator<<(UObject *&Res);                   // slot 6

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;  // 0x10

    UBOOL IsLoading() { return ArIsLoading; }
    FArchive &operator<<(DWORD &D) { Serialize(&D, sizeof(D)); return *this; }
    FArchive &operator<<(INT &I) { Serialize(&I, sizeof(I)); return *this; }
};

class UField;
class UProperty;

class UObject
{
public:
    virtual ~UObject();
    virtual void VSlot1(); virtual void VSlot2(); virtual void VSlot3();
    virtual void VSlot4(); virtual void VSlot5(); virtual void VSlot6(); virtual void VSlot7();
    virtual void VSlot8(); virtual void VSlot9();
    virtual void Serialize(FArchive &Ar);                          // 10
    virtual void VSlot11(); virtual void VSlot12(); virtual void VSlot13(); virtual void VSlot14();
    virtual void VSlot15(); virtual void VSlot16(); virtual void VSlot17(); virtual void VSlot18();
    virtual void VSlot19(); virtual void VSlot20(); virtual void VSlot21();
    virtual void AddCppProperty(UProperty *Property);              // 22 (UField)

    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;       // 0x18
    DWORD ObjectFlags;
    FName Name;           // 0x20
    void *Class;

    UObject *GetOuter() const { return Outer; }
    FName GetFName() const { return Name; }
};

class UField : public UObject
{
public:
    UField *SuperField;   // 0x28
    UField *Next;         // 0x2c

    UField(UField *InSuperField) : SuperField(InSuperField) {}
    virtual ~UField();
    void Serialize(FArchive &Ar);
};

class UProperty : public UField
{
public:
    SWORD ArrayDim;       // 0x30
    SWORD ElementSize;    // 0x32
    DWORD PropertyFlags;  // 0x34
    FName Category;       // 0x38
    INT Offset;           // 0x3c
    BYTE Pad40[8];
    UProperty *ConstructorLinkNext;   // 0x48
    UProperty *NextRef;               // 0x4c
    BYTE Pad50[4];
    _WORD RepOffset;                  // 0x54

    UProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags);

    virtual void VSlot23(); virtual void VSlot24(); virtual void VSlot25(); virtual void VSlot26();
    virtual void VSlot27(); virtual void VSlot28();
    virtual UBOOL Identical(const void *A, const void *B) const;                       // 29
    virtual UBOOL ExportCppItem(void *Out, BYTE *Data, BYTE *Delta) const;             // 30 (neutral name)
    virtual UBOOL ExportCppValue(void *Out, BYTE *Data, BYTE *Delta) const;            // 31
    virtual void ExportTextItem(TCHAR *ValueStr, BYTE *PropertyValue, BYTE *DefaultValue, INT PortFlags) const; // 32
    virtual void VSlot33();
    virtual UBOOL ExportText(INT Index, TCHAR *ValueStr, BYTE *Data, BYTE *Delta, INT PortFlags) const; // 34
    virtual void CopySingleValue(void *Dest, void *Src, UObject *SuperObject);       // 35
    virtual void VSlot36(); virtual void VSlot37();
    virtual UBOOL Port() const;                                                        // 38

    void Serialize(FArchive &Ar);

    INT GetSize() const { return ArrayDim * ElementSize; }
    UBOOL Matches(const void *A, const void *B, INT ArrayIndex) const
    {
        INT Ofs = Offset + ArrayIndex * ElementSize;
        return Identical((BYTE *)A + Ofs, B ? (BYTE *)B + Ofs : 0);
    }
    UField *GetOuterUField() const { return (UField *)GetOuter(); }
};

void appMemcpy(void *Dest, const void *Src, INT Count);

inline void UField::Serialize(FArchive &Ar)
{
    UObject::Serialize(Ar);
    Ar << (UObject *&)SuperField;
    Ar << (UObject *&)Next;
}

// RVA 0x54140 (LTCG: this on the stack, InFlags in ECX). Retail keeps it
// out of line; it has many callers (every property subclass constructor).
#pragma auto_inline(off)
UProperty::UProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags)
    : UField(0)
    , ArrayDim(1)
    , PropertyFlags(InFlags)
    , Category(InCategory)
    , Offset(InOffset)
    , NextRef(0)
{
    GetOuterUField()->AddCppProperty(this);
}
#pragma auto_inline(on)

// RVA 0x541a0
void UProperty::Serialize(FArchive &Ar)
{
    UField::Serialize(Ar);
    INT Dim = ArrayDim;
    Ar << Dim;
    ArrayDim = Dim;
    Ar << PropertyFlags << Category;
    if (PropertyFlags & CPF_Net)
        Ar.Serialize(&RepOffset, sizeof(RepOffset));
    if (Ar.IsLoading())
    {
        Offset = 0;
        ConstructorLinkNext = 0;
    }
}

// RVA 0x54230
UBOOL UProperty::ExportText(INT Index, TCHAR *ValueStr, BYTE *Data, BYTE *Delta, INT PortFlags) const
{
    ValueStr[0] = 0;
    if (Data == Delta || !Matches(Data, Delta, Index))
    {
        ExportTextItem(ValueStr, Data + Offset + Index * ElementSize,
                       Delta ? Delta + Offset + Index * ElementSize : 0, PortFlags);
        return 1;
    }
    return 0;
}

// RVA 0x542d0
void UProperty::CopySingleValue(void *Dest, void *Src, UObject *SuperObject)
{
    appMemcpy(Dest, Src, ElementSize);
}

// RVA 0x542f0: slot 31 of UNameProperty/UStrProperty. Forwards to slot 30
// with a null third argument and reports success. Neutral member names.
UBOOL UProperty::ExportCppValue(void *Out, BYTE *Data, BYTE *Delta) const
{
    ExportCppItem(Out, Delta, 0);
    return 1;
}

// RVA 0x54310
UBOOL UProperty::Port() const
{
    return GetSize()
        && (Category.GetIndex() != NAME_None || !(PropertyFlags & (CPF_Transient | CPF_Native)))
        && GetFName().GetIndex() != NAME_Class;
}

// Scaffolding for the link, not part of the unit: a derived property
// constructor calls the UProperty constructor the way retail subclasses do.
class UDriverProperty_54140 : public UProperty
{
public:
    UDriverProperty_54140(INT InOffset, FName InCategory, DWORD InFlags)
        : UProperty(EC_CppProperty, InOffset, InCategory, InFlags) {}
};
void Escape(void *);
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_54140(void *Mem, INT InOffset, FName InCategory, DWORD InFlags)
{
    new(Mem) UDriverProperty_54140(InOffset, InCategory, InFlags);
}
