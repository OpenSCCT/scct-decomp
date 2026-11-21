// Work item 0324: Versus RVA 0x8f8f0-0x8fb9b.
// AActor vtable slots 36 and 37 and three overrides. The slot names are not
// recovered, so they are called VirtualSlot36/37; the argument record is
// likewise unnamed (UnnamedRecord_8f1b0).

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

enum EName { NAME_Unnamed_10b7 = 0x10b7 };

class FName {
public:
    INT Index;
    FName(EName N) : Index(N) {}
};

struct FVector { FLOAT X, Y, Z; };
struct FRotator { INT Pitch, Yaw, Roll; };

inline UBOOL operator!=(const FVector &A, const FVector &B)
{
    return A.X != B.X || A.Y != B.Y || A.Z != B.Z;
}
inline UBOOL operator!=(const FRotator &A, const FRotator &B)
{
    return A.Pitch != B.Pitch || A.Yaw != B.Yaw || A.Roll != B.Roll;
}

// Out-of-line vector compare at 0x92e40. Its object was built with /GL, so
// LTCG passes A in EDX and B in ECX.
#pragma auto_inline(off)
UBOOL VectorsDiffer_92e40(const FVector &A, const FVector &B)
{
    return A.X != B.X || A.Y != B.Y || A.Z != B.Z;
}
#pragma auto_inline(on)

// Argument record of slot 36 (unnamed).
struct UnnamedRecord_8f1b0 {
    BYTE Pad0[0x18];
    FVector Vector18;      // 0x18
    BYTE Pad24[0x60 - 0x24];
    class AActor *Actor60; // 0x60
    FVector Location;      // 0x64
    FRotator Rotation;     // 0x70
    FVector Velocity;      // 0x7c
};

class UFunction;
class AActor;

class ULevel {
public:
    // 0x11b4b0
    UBOOL Unnamed_11b4b0(AActor *Actor, void *Arg, UBOOL A, UBOOL B, UBOOL C);
};

extern INT GUnnamed_3cacbc;

class AActor {
public:
    virtual void Vf00();
    virtual void Vf04();
    virtual void Vf08();
    virtual void Vf0c();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    virtual void Vf14();
    virtual void Vf18();
    virtual void Vf1c();
    virtual void Vf20();
    virtual void Vf24();
    virtual void Vf28();
    virtual void Vf2c();
    virtual void Vf30();
    virtual void Vf34();
    virtual void Vf38();
    virtual void Vf3c();
    virtual void Vf40();
    virtual void Vf44();
    virtual void Vf48();
    virtual void Vf4c();
    virtual void Vf50();
    virtual void Vf54();
    virtual void Vf58();
    virtual void Vf5c();
    virtual void Vf60();
    virtual void Vf64();
    virtual void Vf68();
    virtual void Vf6c();
    virtual void Vf70();
    virtual void Vf74();
    virtual void Vf78();
    virtual void Vf7c();
    virtual void Vf80();
    virtual void Vf84();
    virtual void Vf88();
    virtual void Vf8c();
    virtual void Vf90();
    virtual void Vf94();
    virtual void Vf98();
    virtual void Vf9c();
    virtual void Vfa0();
    virtual void Vfa4();
    virtual void Vfa8();
    virtual void Vfac();
    virtual void Vfb0();
    virtual void Vfb4();
    virtual void Vfb8();
    virtual void Vfbc();
    virtual void Vfc0();
    virtual void Vfc4();
    virtual void Vfc8();
    virtual void Vfcc();
    virtual void Vfd0();
    virtual void Vfd4();
    virtual void Vfd8();
    virtual void Vfdc();
    virtual void Vfe0();
    virtual void Vfe4();
    virtual void Vfe8();
    virtual void Vfec();
    virtual void Vff0();
    virtual void Vff4();
    virtual void Vff8();
    virtual void VirtualSlot63(INT A, INT B, INT C); // 0xfc

    UFunction *FindFunctionChecked(FName Name, UBOOL Global = 0); // 0x16830

    BYTE Pad4[0x80 - 4];
    FVector Location;      // 0x80
    FVector Velocity;      // 0x8c
    BYTE Pad98[0xe0 - 0x98];
    FRotator Rotation;     // 0xe0
    BYTE PadEC[0x1a4 - 0xec];
    ULevel *XLevel;        // 0x1a4
    BYTE Pad1a8[0x2d8 - 0x1a8];
    BYTE Physics;          // 0x2d8
    BYTE Pad2d9[5];
    BYTE Role;             // 0x2de
    BYTE Pad2df[0x2f0 - 0x2df];
    DWORD Flags2f0;        // 0x2f0
    DWORD Flags2f4;        // 0x2f4

    void VirtualSlot36(UnnamedRecord_8f1b0 *R); // 0x8f1b0
    void VirtualSlot37(void *Arg);              // 0x8f8f0
};

// RVA 0x8f8f0
void AActor::VirtualSlot37(void *Arg)
{
    XLevel->Unnamed_11b4b0(this, Arg, 0, 1, 1);
}

// Subclass of AActor at 0x8f910 (class not identified).
class UnnamedActor_8f910 : public AActor {
public:
    BYTE Pad2f8[0x358 - 0x2f8];
    FVector SavedLocation;  // 0x358
    FRotator SavedRotation; // 0x364
    FVector SavedVelocity;  // 0x370
    BYTE Pad37c[0x49c - 0x37c];
    AActor *Watched;        // 0x49c

    void VirtualSlot36(UnnamedRecord_8f1b0 *R);
    void eventUnnamed_10b7(AActor *A)
    {
        struct { AActor *A; } Parms;
        Parms.A = A;
        ProcessEvent(FindFunctionChecked(NAME_Unnamed_10b7), &Parms);
    }
};

// RVA 0x8f910
void UnnamedActor_8f910::VirtualSlot36(UnnamedRecord_8f1b0 *R)
{
    if (Role != 2) {
        if (R->Location != SavedLocation || R->Rotation != SavedRotation
            || VectorsDiffer_92e40(R->Velocity, SavedVelocity)) {
            if (Physics != 12) {
                if (Physics != 5 || (Flags2f4 & 0x1000)) {
                    Location = SavedLocation;
                    Rotation = SavedRotation;
                }
                Velocity = SavedVelocity;
            }
        }
    }
    AActor::VirtualSlot36(R);
    if (R->Actor60 != Watched && Watched)
        eventUnnamed_10b7(Watched);
}

class ASPawnAttaque : public AActor {
public:
    BYTE Pad2f8[0x4a8 - 0x2f8];
    DWORD Flags4a8; // 0x4a8
    void VirtualSlot37(void *Arg);
};

// RVA 0x8fa40
void ASPawnAttaque::VirtualSlot37(void *Arg)
{
    if (Role == 2) {
        if (Velocity.X == 0.f && Velocity.Y == 0.f && Velocity.Z == 0.f)
            Flags4a8 |= 0x4000000;
        else
            Flags4a8 &= ~0x4000000;
        return;
    }
    AActor::VirtualSlot37(Arg);
}

class AMover : public AActor {
public:
    FVector Vector2f8;      // 0x2f8
    FVector Vector304;      // 0x304
    BYTE Pad310[0x388 - 0x310];
    FVector Vector388;      // 0x388
    BYTE Pad394[0x418 - 0x394];
    FRotator Rotation418;   // 0x418
    BYTE Pad424[0x498 - 0x424];
    FLOAT Scaled498;        // 0x498
    FLOAT Scaled49c;        // 0x49c
    BYTE Pad4a0[0x4df - 0x4a0];
    BYTE Byte4df;           // 0x4df
    BYTE Byte4e0;           // 0x4e0

    void VirtualSlot36(UnnamedRecord_8f1b0 *R);
};

// RVA 0x8fac0
void AMover::VirtualSlot36(UnnamedRecord_8f1b0 *R)
{
    AActor::VirtualSlot36(R);
    if (R->Vector18 != Vector304) {
        Vector388 = Vector2f8;
        Scaled498 = Vector304.X * 0.01f;
        Scaled49c = Vector304.Y * 0.01f;
        Rotation418 = Rotation;
        INT Packed = (INT)Vector304.Z;
        Byte4df = (BYTE)Packed;
        Byte4e0 = (BYTE)(Packed >> 8);
        VirtualSlot63(15, 0, GUnnamed_3cacbc);
        Flags2f0 |= 0x20000000;
    }
}

// Scaffolding for the LTCG link of 0x8f910, not part of the unit.
void Escape(void *);
void Driver_8f910(UnnamedActor_8f910 *A, UnnamedRecord_8f1b0 *R)
{
    // Retail reaches it through vtables, so its address is taken.
    typedef void (UnnamedActor_8f910::*Slot36Fn)(UnnamedRecord_8f1b0 *);
    Slot36Fn Fn = &UnnamedActor_8f910::VirtualSlot36;
    Escape(&Fn);
    (A->*Fn)(R);
}
