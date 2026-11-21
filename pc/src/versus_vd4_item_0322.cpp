// Work item 0322: AActor virtuals and helpers, RVA 0x8ee50-0x8f004.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;
typedef unsigned __int64 QWORD;

// UE2 Core template.
template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }

enum EName { NAME_None = 0 };

class FName
{
public:
    INT Index;
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
};

// UE2 FStateFrame: probe mask lives at +0x1c.
#pragma pack(push, 4)
struct FStateFrame
{
    BYTE Pad[0x1c];
    QWORD ProbeMask;
};
#pragma pack(pop)

class UFunction;
class AActor;

// Object at AActor+0x1bc (unnamed; FUN_109df4e0 is a thiscall on it).
class UnnamedHelper_1bc
{
public:
    class UnnamedTarget *Lookup(AActor *Actor);
};

class UnnamedTarget
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0c();
    virtual void V10(); virtual void V14(); virtual void V18(); virtual void V1c();
    virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2c();
    virtual void V30(); virtual void V34(); virtual void V38(); virtual void V3c();
    virtual void V40(); virtual void V44(); virtual void V48(); virtual void V4c();
    virtual void V50(); virtual void V54(); virtual void V58(); virtual void V5c();
    virtual void V60(); virtual void V64(); virtual void V68(); virtual void V6c();
    virtual void V70(); virtual void V74(); virtual void V78(); virtual void V7c();
    virtual void V80(); virtual void V84(); virtual void V88(); virtual void V8c();
    virtual void V90(INT A);
};

class UObject
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0c();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);

    INT Index;
    UObject *HashNext;
    FStateFrame *StateFrame;

    UFunction *FindFunctionChecked(FName InName, INT Global = 0);
};

// Object at AActor+0x1d4 (unnamed; vtable slots 0x94, 0xcc, 0xf8 used here).
class UnnamedObject_1d4
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c();
    virtual void V30();
    virtual void V34();
    virtual void V38();
    virtual void V3c();
    virtual void V40();
    virtual void V44();
    virtual void V48();
    virtual void V4c();
    virtual void V50();
    virtual void V54();
    virtual void V58();
    virtual void V5c();
    virtual void V60();
    virtual void V64();
    virtual void V68();
    virtual void V6c();
    virtual void V70();
    virtual void V74();
    virtual void V78();
    virtual void V7c();
    virtual void V80();
    virtual void V84();
    virtual void V88();
    virtual void V8c();
    virtual void V90();
    virtual void SetParams94(INT A, DWORD B, FLOAT C, FLOAT D, INT E, INT F, INT G, INT H);
    virtual void V98();
    virtual void V9c();
    virtual void Va0();
    virtual void Va4();
    virtual void Va8();
    virtual void Vac();
    virtual void Vb0();
    virtual void Vb4();
    virtual void Vb8();
    virtual void Vbc();
    virtual void Vc0();
    virtual void Vc4();
    virtual void Vc8();
    virtual INT Query_cc(INT A);
    virtual void Vd0();
    virtual void Vd4();
    virtual void Vd8();
    virtual void Vdc();
    virtual void Ve0();
    virtual void Ve4();
    virtual void Ve8();
    virtual void Vec();
    virtual void Vf0();
    virtual void Vf4();
    virtual void SetValue_f8(INT A, FLOAT B, INT C);
};

class UMaterial;

template<class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

class AActor : public UObject
{
public:
    BYTE Pad10[0x18c - 0x10];
    FLOAT Field18c;
    FLOAT Field190;
    BYTE Pad194[0x1bc - 0x194];
    UnnamedHelper_1bc *Helper1bc;
    BYTE Pad1c0[0x1d4 - 0x1c0];
    UnnamedObject_1d4 *Object1d4;
    BYTE Pad1d8[0x240 - 0x1d8];
    TArray<UMaterial *> Skins;
    BYTE Pad24c[0x2a8 - 0x24c];
    DWORD Field2a8;
    BYTE Byte2ac;
    BYTE Byte2ad;
    BYTE Byte2ae;
    BYTE Byte2af;
    BYTE Pad2b0[0x2d9 - 0x2b0];
    BYTE Byte2d9;
    BYTE Pad2da[0x2ec - 0x2da];
    DWORD Flags2ec;

    void Slot49(INT A);
    void UpdateObject1d4();
    INT QueryObject1d4(INT A);
    void eventProbe144(INT A);
    UMaterial *GetSkin(INT Index);
    FLOAT Slot27(INT A, FLOAT B, INT C);
};

// RVA 0x8ef30, AActor vtable slot 49 (unnamed).
void AActor::Slot49(INT A)
{
    if (Helper1bc)
        Helper1bc->Lookup(this)->V90(A);
}

// RVA 0x8ef50, AActor vtable slot 48: probe event for name index 0x144.
struct Probe144_Parms
{
    INT A;
};

void AActor::eventProbe144(INT A)
{
    if (!StateFrame || (StateFrame->ProbeMask & ((QWORD)1 << 24)))
    {
        Probe144_Parms Parms;
        Parms.A = A;
        ProcessEvent(FindFunctionChecked(FName((EName)0x144)), &Parms);
    }
}

// RVA 0x8efa0, AActor vtable slot 38.
UMaterial *AActor::GetSkin(INT Index)
{
    if (Index < Skins.Num())
        return Skins(Index);
    return 0;
}

// RVA 0x8efc0, AActor vtable slot 27 (unnamed).
FLOAT AActor::Slot27(INT A, FLOAT B, INT C)
{
    if (Flags2ec & 8)
    {
        return Min(Field18c * 0.1f, 1.0f) * Field190 * B;
    }
    return B * Field190;
}

// RVA 0x8ee50 (LTCG: this in ESI). Pushes the packed settings at +0x2a8 into
// the object at +0x1d4. Unnamed.
void AActor::UpdateObject1d4()
{
    Helper1bc->Lookup(this);
    Object1d4->SetParams94(0, Field2a8,
        (Byte2ad - 124.0f) * (1.0f / 31.0f),
        Byte2af * 0.25f,
        Byte2ac & ~0x80, 0, 0, 0);
    Object1d4->SetValue_f8(0, (Byte2ae - 127.0f) * (1.0f / 127.0f), 0);
}

// RVA 0x8ef00 (LTCG: this in ESI). Unnamed.
INT AActor::QueryObject1d4(INT A)
{
    if (Byte2d9 == 2 && Helper1bc)
    {
        Helper1bc->Lookup(this);
        return Object1d4->Query_cc(A);
    }
    return 0;
}

// Scaffolding for the LTCG link, not part of the unit.
void Driver_8ee50(AActor *A) { A->UpdateObject1d4(); }
INT Driver_8ef00(AActor *A, AActor *B, AActor *C, AActor *D, INT X) { return A->QueryObject1d4(X) + B->QueryObject1d4(0x16) + C->QueryObject1d4(X + 1) + D->QueryObject1d4(3); }
