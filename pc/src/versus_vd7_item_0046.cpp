// w4_item_0046.cpp -- Versus work item 0046 (AVolume::Encompasses)

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

struct FGuid;

struct FVector {
    FLOAT X;
    FLOAT Y;
    FLOAT Z;
};

class AActor;
class UPrimitive;
class UMaterial;

struct FCheckResult {
    FCheckResult *Next;
    AActor *Actor;
    FVector Location;
    FVector Normal;
    UPrimitive *Primitive;
    FLOAT Time;
    INT Item;
    UMaterial *Material;
    BYTE unk_30[0x8];

    FCheckResult(FLOAT InTime = 0.0f, FCheckResult *InNext = 0);
};

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();

    BYTE unk_04[0x24];
};

class UPrimitive : public UObject {
public:
    virtual ~UPrimitive();
    virtual UBOOL PointCheck(FCheckResult &Result, AActor *Owner, const FVector &Location,
                             const FVector &Extent, DWORD ExtraNodeFlags);
};

class UModel : public UPrimitive {
public:
    virtual ~UModel();
};

class AActor : public UObject {
public:
    virtual ~AActor();

    BYTE unk_28[0x210];
    UModel *Brush;
};

class ABrush : public AActor {
public:
    virtual ~ABrush();
};

class AVolume : public ABrush {
public:
    virtual ~AVolume();

    UBOOL Encompasses(FVector Point);
};

__declspec(dllimport) extern const FVector GMath_Zero;

// RVA 0x12eec0: AVolume::Encompasses
UBOOL AVolume::Encompasses(FVector Point)
{
    if (!Brush)
        return 0;

    FCheckResult Hit(1.0f);
    return !Brush->PointCheck(Hit, this, Point, GMath_Zero, 0);
}

// Scaffolding for the link, not part of the unit.
UBOOL Driver_12eec0(AVolume *V, FVector P, INT Mode)
{
    switch (Mode) {
    case 0:
        return V->Encompasses(P);
    case 1:
        return V->Encompasses(P) + 1;
    case 2:
        return V->Encompasses(P) + 2;
    case 3:
        return V->Encompasses(P) + 3;
    default:
        return V->Encompasses(P) + 4;
    }
}
