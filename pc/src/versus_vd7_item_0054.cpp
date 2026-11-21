// w4_item_0054.cpp -- AProjectile::execExplode and AProjectile::execNativeTouch

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef int UBOOL;
typedef DWORD BITFIELD;
typedef unsigned short TCHAR;

#define RESULT_DECL void *const Result
#define DECLARE_NATIVE(Name) void Name(FFrame &Stack, RESULT_DECL);

struct FGuid;
struct FFrame;
class UClass;

struct FVector {
    FLOAT X, Y, Z;

    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    UBOOL IsZero() const { return X == 0.0f && Y == 0.0f && Z == 0.0f; }
};

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
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

    INT     Index;
    BYTE    unk_8[0x1c];
    UClass *Class;

    __forceinline UBOOL IsA(UClass *SomeBase) const;
};

class UClass : public UObject {
public:
    BYTE  unk_28[0xe4];
    DWORD ClassPrime;         // +0x10c
    DWORD ClassPrimeProduct;  // +0x110
};

__forceinline UBOOL UObject::IsA(UClass *SomeBase) const
{
    return (!SomeBase || Class == SomeBase) ? 1 : ((Class->ClassPrimeProduct % SomeBase->ClassPrime) == 0);
}

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice {
    class UStruct *Node;
    UObject       *Object;
    BYTE          *Code;
    BYTE          *Locals;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_OBJECT(Cls, Var) Cls *Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_VECTOR(Var) FVector Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

class AActor : public UObject {
public:
    virtual ~AActor();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual void VirtualSlot45();
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void VirtualSlot52();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual void VirtualSlot55();
    virtual void VirtualSlot56();
    virtual void VirtualSlot57();
    virtual void VirtualSlot58();
    virtual void VirtualSlot59();
    virtual void VirtualSlot60();
    virtual void VirtualSlot61();
    virtual void VirtualSlot62();
    virtual void VirtualSlot63();
    virtual void VirtualSlot64();
    virtual void VirtualSlot65();
    virtual void VirtualSlot66();
    virtual void VirtualSlot67();
    virtual void VirtualSlot68();
    virtual void VirtualSlot69();
    virtual void VirtualSlot70();
    virtual void VirtualSlot71();
    virtual void VirtualSlot72();
    virtual void VirtualSlot73();
    virtual void VirtualSlot74();
    virtual void VirtualSlot75();
    virtual void VirtualSlot76();
    virtual void VirtualSlot77();

    BYTE     unk_28[0x58];
    FVector  Location;          // +0x80
    FVector  Velocity;          // +0x8c
    BYTE     unk_98[0x258];
    BITFIELD unk_2f0_0 : 14;    // +0x2f0
    BITFIELD bBlockActors : 1;  // 0x4000
    BITFIELD bBlockPlayers : 1; // 0x8000
    BITFIELD unk_2f0_16 : 1;    // 0x10000
    BITFIELD bProjTarget : 1;   // 0x20000
    BITFIELD unk_2f0_18 : 14;
    DWORD    unk_2f4;
};

// Engine.Mover (PrivateStaticClass at 0x10cc1680; super class of ASLift and ASLiftDoor)
class AMover : public AActor {
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

// Engine.Projectile: 0x324 bytes, 80 virtual functions
class AProjectile : public AActor {
public:
    virtual ~AProjectile();
    virtual void ProcessTouch(AActor *Other, const FVector &HitLocation, const FVector &HitNormal);
    virtual void Explode(const FVector &HitLocation, const FVector &HitNormal);

    BYTE unk_2f8[0x2c];

    DECLARE_NATIVE(execExplode)
    DECLARE_NATIVE(execNativeTouch)
};

// AProjectile::execExplode
void AProjectile::execExplode(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(HitLocation);
    P_GET_VECTOR(HitNormal);
    P_FINISH;
    Explode(HitLocation, HitNormal);
}

// AProjectile::execNativeTouch
void AProjectile::execNativeTouch(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(AActor, Other);
    P_GET_VECTOR(HitLocation);
    P_GET_VECTOR(HitNormal);
    P_FINISH;
    if (Other && (Other->bProjTarget || (Other->bBlockActors && Other->bBlockPlayers)))
    {
        if (Velocity.IsZero() || Other->IsA(AMover::StaticClass()))
        {
            ProcessTouch(Other, HitLocation, HitNormal);
            return;
        }
        ProcessTouch(Other, HitLocation, HitNormal);
    }
}
