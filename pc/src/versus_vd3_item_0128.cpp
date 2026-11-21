// Work item 0128: Versus RVA 0x3b780-0x3b934.
// All three functions are LTCG (custom register conventions).
// Class and member names are neutral: the evidence does not name them.

typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef int INT;

// Object read at +0x34 for flag bits (0x3b780, passed in EAX).
struct UnnamedFlags_3b780
{
    char Pad[0x34];
    DWORD Flags;
};

// Object whose fields +0x14, +0x18, +0x1c are tested (0x3b780, passed in ECX).
struct UnnamedState_3b780
{
    char Pad[0x14];
    INT A;  // +0x14
    INT B;  // +0x18
    INT C;  // +0x1c
};

// 0x3b780
UBOOL IsUnused_3b780(UnnamedFlags_3b780 *Info, UnnamedState_3b780 *State)
{
    DWORD Flags = Info->Flags;
    UBOOL Used = (Flags & 0x1000)
              || ((Flags & 0x2000) && State->C)
              || ((Flags & 0x20000000) && (State->A || State->B));
    return !Used;
}

// 0x3b7d0: round up to the next power of two, up to 0x10000 (0 beyond).
DWORD RoundUpPow2_3b7d0(DWORD N)
{
    if (N <= 0) return 0;
    if (N <= 1) return 1;
    if (N <= 2) return 2;
    if (N <= 4) return 4;
    if (N <= 8) return 8;
    if (N <= 0x10) return 0x10;
    if (N <= 0x20) return 0x20;
    if (N <= 0x40) return 0x40;
    if (N <= 0x80) return 0x80;
    if (N <= 0x100) return 0x100;
    if (N <= 0x200) return 0x200;
    if (N <= 0x400) return 0x400;
    if (N <= 0x800) return 0x800;
    if (N <= 0x1000) return 0x1000;
    if (N <= 0x2000) return 0x2000;
    if (N <= 0x4000) return 0x4000;
    if (N <= 0x8000) return 0x8000;
    return N <= 0x10000 ? 0x10000 : 0;
}

// 0x3b8d0: constructor of an object with vtable 0x10c0cce0, copying two
// fields from the owner it is given.
struct UnnamedBase_3b8d0
{
    virtual void Unknown0();
    INT V04, V08, V0C, V10, V14, V18, V1C, V20, V24, V28, V2C, V30, V34, V38, V3C;
    UnnamedBase_3b8d0()
    {
        V14 = 0; V1C = 0;
        V04 = 0xaf; V08 = 2000;
        V0C = 0; V10 = 0; V18 = 0;
        V20 = 1; V24 = 1; V28 = 1;
        V2C = 0; V30 = 0;
        V34 = 3; V38 = 0; V3C = -1;
    }
};

struct UnnamedObj_3b8d0 : public UnnamedBase_3b8d0
{
    INT V40;
    UnnamedBase_3b8d0 *Owner;
    UnnamedObj_3b8d0(UnnamedBase_3b8d0 *InOwner);
    virtual void Unknown0();
};

UnnamedObj_3b8d0::UnnamedObj_3b8d0(UnnamedBase_3b8d0 *InOwner)
{
    V40 = 0;
    Owner = InOwner;
    V14 = InOwner->V14;
    V1C = InOwner->V1C;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *P) { return P; }
INT Driver_3b780(UnnamedFlags_3b780 *I, UnnamedState_3b780 *S) { return IsUnused_3b780(I, S); }
DWORD Driver_3b7d0(DWORD N) { return RoundUpPow2_3b7d0(N); }
void Driver_3b8d0(void *Mem, UnnamedBase_3b8d0 *O) { new (Mem) UnnamedObj_3b8d0(O); }
