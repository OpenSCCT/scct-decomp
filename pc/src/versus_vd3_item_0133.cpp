// Work item 0133: UStruct methods (Unreal Engine 2 Core, Versus build).
// 0x3ca50 is UStruct::Destroy (UStruct vtable slot 9), 0x3ca80 is
// UStruct::Serialize (slot 10), 0x3cb90 is UStruct vtable slot 31 (a pass
// over the property link chain at +0x58; name is a neutral guess).
// Versus FArchive puts operator<<(UObject*&) at slot 6 and
// operator<<(FName&) at slot 7.

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned short TCHAR;

class UObject;
struct FName { INT Index; };

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, INT Length);
    virtual void SerializeBits(void* V, INT LengthBits);
    virtual void SerializeInt(DWORD& Value, DWORD Max);
    virtual void Preload(UObject* Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    // MSVC lays overloaded virtuals out in reverse declaration order.
    virtual FArchive& operator<<(FName& N);
    virtual FArchive& operator<<(UObject*& Res);

    void ByteOrderSerialize(void* V, INT Length) { Serialize(V, Length); }
    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
};

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag);
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag);
    virtual void Free(void* Original);
};
extern FMalloc* GMalloc;

// Script bytecode buffer at UStruct+0x3c: SCCT's FSArray (data pointer and
// count, no capacity; allocation tags L"FSArray" and L"FSArray::Add").
struct FSArray
{
    BYTE* Data;
    INT Num;

    void Empty()
    {
        Num = 0;
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
        }
    }
    INT Add(INT Count);
};

extern const TCHAR FSArray_Tag[];      // L"FSArray"
extern const TCHAR FSArray_AddTag[];   // L"FSArray::Add"

// RVA 0x3e040 (work item 0139; defined here so the LTCG link sees it).
__declspec(noinline) INT FSArray::Add(INT Count)
{
    INT Index = Num;
    Num += Count;
    if (Data == 0) {
        Data = Num > 0 ? (BYTE*)GMalloc->Malloc(Num, FSArray_AddTag) : 0;
    } else {
        Data = (BYTE*)GMalloc->Realloc(Data, Num, FSArray_Tag);
    }
    return Index;
}

class UObject
{
public:
    virtual void vf00(); virtual void vf01(); virtual void vf02();
    virtual void vf03(); virtual void vf04(); virtual void vf05();
    virtual void vf06(); virtual void vf07(); virtual void vf08();
    virtual void Destroy();
    virtual void Serialize(FArchive& Ar);
    virtual void vf11(); virtual void vf12(); virtual void vf13();
    virtual void vf14(); virtual void vf15(); virtual void vf16();
    virtual void vf17(); virtual void vf18(); virtual void vf19();
    virtual void vf20(); virtual void vf21(); virtual void vf22();
    virtual void vf23(); virtual void vf24(); virtual void vf25();
    virtual void vf26();
    virtual void DestroyValue(void* Dest);          // slot 27 (on UProperty)
    virtual void Link(FArchive& Ar, UBOOL Props);   // slot 28
    virtual void vf29(); virtual void vf30();
    virtual void DestroyStructData(BYTE* Data);     // slot 31
    virtual void SerializeExpr(INT& iCode, FArchive& Ar); // slot 32

    BYTE ObjPad[0x28 - 4];
};

class UField : public UObject
{
public:
    void Destroy();
    void Serialize(FArchive& Ar);
};

class UProperty : public UField
{
public:
    BYTE PropPad[0x3c - 0x28];
    INT Offset;
    BYTE PropPad2[0x4c - 0x40];
    UProperty* PropertyLinkNext;
};

class UStruct : public UField
{
public:
    UStruct();
    void Destroy();
    void Serialize(FArchive& Ar);
    void DestroyStructData(BYTE* Data);

    UObject* SuperField;     // 0x28
    UObject* Children;       // 0x2c
    UObject* Field30;        // 0x30
    INT Field34;             // 0x34
    FName FriendlyName;      // 0x38
    FSArray Script;          // 0x3c
    UObject* Field44;        // 0x44
    UObject* Field48;        // 0x48
    INT Field4C;             // 0x4c
    INT Field50;             // 0x50
    BYTE Pad54[4];
    UProperty* PropertyLink; // 0x58
};

// RVA 0x3ca50
void UStruct::Destroy()
{
    Script.Empty();
    UField::Destroy();
}

// RVA 0x3ca80
void UStruct::Serialize(FArchive& Ar)
{
    UField::Serialize(Ar);
    Ar << SuperField;
    Ar << Children;
    Ar << Field44;
    Ar << Field30;
    Ar << FriendlyName;
    if (Ar.Ver() >= 120)
        Ar << Field48;
    Ar.ByteOrderSerialize(&Field50, sizeof(Field50));
    Ar.ByteOrderSerialize(&Field4C, sizeof(Field4C));
    INT ScriptSize = Script.Num;
    Ar.ByteOrderSerialize(&ScriptSize, sizeof(ScriptSize));
    if (Ar.IsLoading()) {
        Script.Empty();
        if (ScriptSize)
            Script.Add(ScriptSize);
    }
    INT iCode = 0;
    while (iCode < ScriptSize)
        SerializeExpr(iCode, Ar);
    if (Ar.IsLoading())
        Link(Ar, 1);
}

// RVA 0x3cb90
void UStruct::DestroyStructData(BYTE* Data)
{
    for (UProperty* P = PropertyLink; P; P = P->PropertyLinkNext)
        P->DestroyValue(Data + P->Offset);
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void*);
void* operator new(unsigned int);
UStruct::UStruct() {}
void Driver_3ca80(FArchive& Ar) { Escape(&GMalloc); UStruct* S = new UStruct; S->Serialize(Ar); }
