// Work item 0229: UStructProperty::DestroyValue (0x565f0) and UStructProperty::Link (0x56630).
// Layouts trimmed to the fields these functions touch (UE2 UProperty / UStruct).

typedef int INT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;

#define CPF_Native        0x00001000
#define CPF_NeedCtorLink  0x00400000

class UObject;
class UProperty;

class FArchive
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void Preload(UObject *Object);
};

class UObject
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19();
    virtual INT GetPropertiesSize();          // slot 26 (0x68)
    virtual void v1b(); virtual void v1c(); virtual void v1d(); virtual void v1e();
    virtual void DestroyStruct(BYTE *Data);   // slot 31 (0x7c)

    BYTE Pad04[0x18 - 0x04];
    UObject *Outer;                           // 0x18
};

class UStruct : public UObject
{
public:
    BYTE Pad1C[0x34 - 0x1C];
    short PropertiesSize;                     // 0x34
    BYTE Pad36[0x64 - 0x36];
    UProperty *ConstructorLink;               // 0x64
};

class UProperty : public UObject
{
public:
    BYTE Pad1C[0x30 - 0x1C];
    short ArrayDim;                           // 0x30
    short ElementSize;                        // 0x32
    DWORD PropertyFlags;                      // 0x34
    BYTE Pad38[0x3C - 0x38];
    INT Offset;                               // 0x3c
};

class UStructProperty : public UProperty
{
public:
    BYTE Pad40[0x58 - 0x40];
    UStruct *Struct;                          // 0x58

    void DestroyValue(void *Dest);
    INT Link(FArchive &Ar, UProperty *Prev);
};

void UStructProperty::DestroyValue(void *Dest)
{
    for (INT i = 0; i < ArrayDim; i++)
        Struct->DestroyStruct((BYTE *)Dest + i * ElementSize);
}

INT UStructProperty::Link(FArchive &Ar, UProperty *Prev)
{
    Ar.Preload(Struct);
    ElementSize = Struct->PropertiesSize;
    INT Alignment = ElementSize == 2 ? 2 : (ElementSize >= 4 ? 4 : 1);
    Offset = (Outer->GetPropertiesSize() + Alignment - 1) & ~(Alignment - 1);
    if (Struct->ConstructorLink && !(PropertyFlags & CPF_Native))
        PropertyFlags |= CPF_NeedCtorLink;
    return Offset - Outer->GetPropertiesSize();
}
