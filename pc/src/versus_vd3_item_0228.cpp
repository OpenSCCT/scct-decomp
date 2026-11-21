// Work item 0228: UArrayProperty / UMapProperty virtuals (UE2 UnProp.cpp).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned short _WORD;

#define CPF_Native       0x00001000
#define CPF_NeedCtorLink 0x00400000

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
void *appMemcpy(void *Dest, const void *Src, INT Count);

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    void Empty(INT ElementSize, INT Slack);
    INT Add(INT Count, INT ElementSize);
    INT __stdcall AddZeroed(INT ElementSize, INT Count);
};

class UObject;
class UClass;
class UField;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(UObject *Object);
};

class UObject
{
public:
    virtual ~UObject();
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    INT Name;
    UClass *Class;
    inline UBOOL IsA(UClass *SomeBase) const;
};

class UField : public UObject
{
public:
    UField *SuperField;
    UField *Next;
    virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25();
    virtual INT GetPropertiesSize();          // 0x68
};

class UStruct : public UField {};
class UClass : public UStruct {};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return SomeBase == 0;
}

class UProperty : public UField
{
public:
    _WORD ArrayDim;          // 0x30
    short ElementSize;       // 0x32
    DWORD PropertyFlags;     // 0x34
    INT Pad38;
    INT Offset;              // 0x3c
    BYTE Pad40[0x18];
    virtual void p1();
    virtual INT Link(FArchive &Ar, UProperty *Prev);                                  // 0x70
    virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6();
    virtual void p7(); virtual void p8(); virtual void p9();
    virtual void CopyCompleteValue(void *Dest, void *Src, UObject *SuperObject); // 0x90
    virtual void DestroyValue(void *Dest);                                         // 0x94
};

class UMapProperty : public UProperty
{
public:
    UProperty *Key;          // 0x58
    UProperty *Value;        // 0x5c
    INT Link(FArchive &Ar, UProperty *Prev);
};

inline INT Align(INT Ptr, INT Alignment) { return (Ptr + Alignment - 1) & ~(Alignment - 1); }

INT UMapProperty::Link(FArchive &Ar, UProperty *Prev)
{
    Ar.Preload(Key);
    Key->Link(Ar, 0);
    Ar.Preload(Value);
    Value->Link(Ar, 0);
    ElementSize = 0x14; // sizeof(TMap<BYTE,BYTE>)
    Offset = Align(((UField *)Outer)->GetPropertiesSize(), 4);
    if (!(PropertyFlags & CPF_Native))
        PropertyFlags |= CPF_NeedCtorLink;
    return Offset - ((UField *)Outer)->GetPropertiesSize();
}

// Class whose PrivateStaticClass lives at 0x10cc9b18 (not identified; neutral name).
class UnnamedClass_cc9b18 : public UClass
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

// Array whose destruction leaves ArrayMax alone (used when the owning
// property has flag 0x80000000 set; layout matches FArray).
struct FArrayNoMax
{
    BYTE *Data;
    INT ArrayNum;
    INT ArrayMax;
};

struct FArrayRaw
{
    BYTE *Data;
    INT ArrayNum;
    INT ArrayMax;
};

class UArrayProperty : public UProperty
{
public:
    UProperty *Inner;        // 0x58
    void CopyCompleteValue(void *Dest, void *Src, UObject *SuperObject);
    void DestroyValue(void *Dest);
};

void UArrayProperty::DestroyValue(void *Dest)
{
    if (Offset == 0 && Outer->IsA(UnnamedClass_cc9b18::StaticClass()))
        return;
    if (PropertyFlags & 0x80000000)
    {
        FArrayNoMax *DestArray = (FArrayNoMax *)Dest;
        if (Inner->PropertyFlags & CPF_NeedCtorLink)
        {
            INT Size = Inner->ElementSize;
            BYTE *DestData = DestArray->Data;
            for (INT i = DestArray->ArrayNum; i > 0; i--)
            {
                Inner->DestroyValue(DestData);
                DestData += Size;
            }
        }
        if (DestArray->Data)
        {
            GMalloc->Free(DestArray->Data);
            DestArray->Data = 0;
        }
        DestArray->ArrayNum = 0;
    }
    else
    {
        FArrayRaw *DestArray = (FArrayRaw *)Dest;
        if (Inner->PropertyFlags & CPF_NeedCtorLink)
        {
            INT Size = Inner->ElementSize;
            BYTE *DestData = DestArray->Data;
            for (INT i = DestArray->ArrayNum; i > 0; i--)
            {
                Inner->DestroyValue(DestData);
                DestData += Size;
            }
        }
        if (DestArray->Data)
        {
            GMalloc->Free(DestArray->Data);
            DestArray->Data = 0;
        }
        DestArray->ArrayNum = DestArray->ArrayMax = 0;
    }
}

// ---- CopyCompleteValue (0x562d0) ----
// FSArray: the array form used when the property has flag 0x80000000
// (name from the retail tag string "FSArray::Add").
extern const TCHAR FSArray_Add_Tag[];   // L"FSArray::Add"
extern const TCHAR FArray_Tag[];        // L"FArray"

struct FSArray
{
    BYTE *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);
    INT __stdcall AddZeroed(INT ElementSize, INT Count);
    void Empty()
    {
        ArrayNum = 0;
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
    }
};

__declspec(noinline) INT FSArray::Add(INT Count, INT ElementSize)
{
    INT Index = ArrayNum;
    ArrayNum += Count;
    INT Bytes = ArrayNum * ElementSize;
    if (Data == 0)
    {
        Data = Bytes > 0 ? (BYTE *)GMalloc->Malloc(Bytes, FSArray_Add_Tag) : 0;
    }
    else
        Data = (BYTE *)GMalloc->Realloc(Data, Bytes, FArray_Tag);
    return Index;
}

void UArrayProperty::CopyCompleteValue(void *Dest, void *Src, UObject *SuperObject)
{
    INT Size = Inner->ElementSize;
    if (PropertyFlags & 0x80000000)
    {
        FSArray *SrcArray = (FSArray *)Src;
        FSArray *DestArray = (FSArray *)Dest;
        DestArray->Empty();
        if (Inner->PropertyFlags & CPF_NeedCtorLink)
        {
            DestArray->AddZeroed(Size, SrcArray->ArrayNum);
            BYTE *SrcData = SrcArray->Data;
            BYTE *DestData = DestArray->Data;
            for (INT i = DestArray->ArrayNum; i > 0; i--)
            {
                Inner->CopyCompleteValue(DestData, SrcData, SuperObject);
                DestData += Size;
                SrcData += Size;
            }
        }
        else
        {
            DestArray->Add(SrcArray->ArrayNum, Size);
            appMemcpy(DestArray->Data, SrcArray->Data, SrcArray->ArrayNum * Size);
        }
    }
    else
    {
        FArray *SrcArray = (FArray *)Src;
        FArray *DestArray = (FArray *)Dest;
        DestArray->Empty(Size, SrcArray->ArrayNum);
        if (Inner->PropertyFlags & CPF_NeedCtorLink)
        {
            DestArray->AddZeroed(Size, SrcArray->ArrayNum);
            BYTE *SrcData = (BYTE *)SrcArray->Data;
            BYTE *DestData = (BYTE *)DestArray->Data;
            for (INT i = DestArray->ArrayNum; i > 0; i--)
            {
                Inner->CopyCompleteValue(DestData, SrcData, SuperObject);
                DestData += Size;
                SrcData += Size;
            }
        }
        else
        {
            DestArray->Add(SrcArray->ArrayNum, Size);
            appMemcpy(DestArray->Data, SrcArray->Data, SrcArray->ArrayNum * Size);
        }
    }
}

// Scaffolding for the link, not part of the unit: further FSArray::Add
// callers, as retail has many.
void Driver_562d0(FSArray *A, INT Count, INT Size)
{
    for (INT i = 0; i < Count; i++)
        A[i].Add(i, Size);
}
