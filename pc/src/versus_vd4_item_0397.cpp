// Work item 0397: AProjector editor/attachment virtuals (RVA 0xa7850-0xa78ea).
// Slot names follow Unreal Engine 2 AProjector (PostEditChange -> Detach(1); Attach()).
// VirtualSlotN entries stand for engine virtual methods not used here.
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef int INT;

struct FVector { FLOAT X, Y, Z; };

class AActor
{
public:
    virtual ~AActor();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void PostEditChange();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void PostEditMove();
    virtual void PostEditLoad();
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
    virtual void SetZone(UBOOL bTest, UBOOL bForceRefresh);
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
    virtual void Attach();
    virtual void Detach(UBOOL bForce);

    char Pad004[0x7C];
    FVector Location;            // 0x80
};

class AProjector : public AActor
{
public:
    void PostEditChange();
    void PostEditMove();
    void PostEditLoad();

    char Pad08C[0x438 - 0x8C];
    FVector OldLocation;         // 0x438
};

// RVA 0xa7850
void AProjector::PostEditChange()
{
    AActor::PostEditChange();
    Detach(1);
    Attach();
}

// RVA 0xa7870
void AProjector::PostEditMove()
{
    if (OldLocation.X != Location.X || OldLocation.Y != Location.Y || OldLocation.Z != Location.Z)
    {
        Detach(1);
        Attach();
    }
}

// RVA 0xa78d0
void AProjector::PostEditLoad()
{
    SetZone(0, 0);
    Attach();
}
