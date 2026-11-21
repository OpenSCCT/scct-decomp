// Work item 0332: Versus RVA 0x91be0-0x91e8e.
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef int INT;

// 0x91be0: a 56-byte plain struct assigned by value (14 dwords).
// Neutral name: no evidence for the real type.
struct UnnamedStruct_91be0
{
    DWORD A, B, C, D, E, F, G, H, I, J, K, L, M, N;
    UnnamedStruct_91be0(const UnnamedStruct_91be0 &O);
};

class UClass;
class AActor;

// The single argument passed to FUN_10992b40 (0x10cc1568); an object whose
// address is pushed, likely a class/name descriptor. Neutral name.
extern char Unnamed_10cc1568;

struct UnnamedArray
{
    AActor **Data;
};

struct ULevel_partial
{
    char Pad0[0x2c];
    AActor **Actors;    // Actors(0) is the level info
};

// AActor, reflected vtable slot 43 is AActor::ShouldTrace (UE2).
class AActor
{
public:
    virtual void VSlot0();
    char Pad004[0x100 - 4];
    void *Ptr100;
    char Pad104[0x1a4 - 0x104];
    ULevel_partial *XLevel;
    char Pad1a8[0x1bc - 0x1a8];
    void *Ptr1bc;
    char Pad1c0[0x2d9 - 0x1c0];
    unsigned char Physics;
    char Pad2da[0x2e8 - 0x2da];
    DWORD Flags2e8;
    DWORD Flags2ec;
    // Bitfield DWORD at 0x2f0 (UE2 actor bool flags; names unknown).
    DWORD Bits2f0_Pad0 : 14;
    DWORD bFlag2f0_14 : 1;
    DWORD bFlag2f0_15 : 1;
    DWORD Bits2f0_Pad16 : 1;
    DWORD bFlag2f0_17 : 1;
    DWORD Bits2f0_Pad18 : 6;
    DWORD bFlag2f0_24 : 1;
    DWORD Bits2f0_Pad25 : 7;

    UBOOL IsA_92b40(void *Class);   // FUN_10992b40
    UBOOL ShouldTrace(AActor *SourceActor, DWORD TraceFlags);
};

// Same layout; the volume override (ABlockingVolume/AVolume slot 43).
class AVolume : public AActor
{
public:
    UBOOL ShouldTrace(AActor *SourceActor, DWORD TraceFlags);
};

// Source actor class used only for the vtable call at +0x68.
class ATraceSource : public AActor
{
};

struct UnnamedVTableCaller
{
    virtual void S0(); virtual void S1(); virtual void S2(); virtual void S3();
    virtual void S4(); virtual void S5(); virtual void S6(); virtual void S7();
    virtual void S8(); virtual void S9(); virtual void S10(); virtual void S11();
    virtual void S12(); virtual void S13(); virtual void S14(); virtual void S15();
    virtual void S16(); virtual void S17(); virtual void S18(); virtual void S19();
    virtual void S20(); virtual void S21(); virtual void S22(); virtual void S23();
    virtual void S24(); virtual void S25();
    virtual UBOOL Slot26(AActor *Other);   // vtable +0x68
};

UBOOL AActor::ShouldTrace(AActor *SourceActor, DWORD TraceFlags)
{
    if (XLevel && this != XLevel->Actors[0] && !(Flags2ec & 0x4000000) && (TraceFlags & 0x100))
        return 0;
    if (SourceActor && (SourceActor->Flags2e8 & 0x8000000))
        return 0;
    DWORD Flags = Flags2e8;
    if ((Flags & 0x8000000) && SourceActor && !SourceActor->IsA_92b40(&Unnamed_10cc1568))
        return 0;
    if ((TraceFlags & 0x10000) && !bFlag2f0_24)
        return 0;
    if (TraceFlags & 0x8000)
        return (Flags >> 25) & 1;
    if (TraceFlags & 0x2000)
    {
        if ((Ptr100 && Physics == 8) || (Ptr1bc && Physics == 2))
            return 1;
    }
    if (TraceFlags & 0x100)
        return (Flags2ec >> 26) & 1;
    if (Flags & 0x1000000)
    {
        if (Ptr100 && Physics == 8 && SourceActor && SourceActor->IsA_92b40(&Unnamed_10cc1568) && (TraceFlags & 0x80))
            return bFlag2f0_15;
        return TraceFlags & 0x80;
    }
    if (TraceFlags & 0x10)
    {
        if (TraceFlags & 0x20)
        {
            if (bFlag2f0_17 || (bFlag2f0_14 && bFlag2f0_15))
                return 1;
        }
        else if (TraceFlags & 0x40)
        {
            if (SourceActor && ((UnnamedVTableCaller *)SourceActor)->Slot26(this))
                return 1;
        }
        else
            return 1;
    }
    return 0;
}

UBOOL AVolume::ShouldTrace(AActor *SourceActor, DWORD TraceFlags)
{
    if (!(Flags2ec & 0x4000000) && (TraceFlags & 0x100))
        return 0;
    if (SourceActor && (SourceActor->Flags2e8 & 0x8000000))
        return 0;
    DWORD Flags = Flags2e8;
    if ((Flags & 0x8000000) && SourceActor && !SourceActor->IsA_92b40(&Unnamed_10cc1568))
        return 0;
    if ((Flags & 0x1000000) && (TraceFlags & 0x80))
        return 1;
    if (TraceFlags & 0x8)
    {
        if (TraceFlags & 0x20)
        {
            if (bFlag2f0_17 || (bFlag2f0_14 && bFlag2f0_15))
                return 1;
        }
        else if (TraceFlags & 0x40)
        {
            if (SourceActor && ((UnnamedVTableCaller *)SourceActor)->Slot26(this))
                return 1;
        }
        else
            return 1;
    }
    return 0;
}

// 0x91be0: copy constructor, compiled with LTCG (this in EAX, source in
// ECX). Retail callers construct into storage from an array allocator
// (placement new of a 0x38-byte element).
UnnamedStruct_91be0::UnnamedStruct_91be0(const UnnamedStruct_91be0 &O)
    : A(O.A), B(O.B), C(O.C), D(O.D), E(O.E), F(O.F), G(O.G), H(O.H),
      I(O.I), J(O.J), K(O.K), L(O.L), M(O.M), N(O.N)
{
}

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void *ArrayAlloc(void *Array, INT Size, INT Count);
void Escape(void *);
void Driver_91be0(void *Array, UnnamedStruct_91be0 *Item)
{
    void *Mem = ArrayAlloc(Array, 0x38, 1);
    Escape(Mem ? new(Mem) UnnamedStruct_91be0(*Item) : 0);
}
