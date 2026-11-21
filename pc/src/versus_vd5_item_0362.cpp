// Work item 0362 (w3): Versus RVA 0x114fe0 and 0x115450.
// Both functions are link-time generated (VC7.0 /GL + /LTCG): register and
// stack-`this` calling conventions. Class names are neutral; no vtable label
// or string names them.
typedef unsigned long DWORD;
typedef int INT;

inline void *operator new(unsigned int, void *Mem) { return Mem; }

// Level-side data reached through Owner->+0x30->+0x1a4.
struct UnnamedGraph_090c0
{
    char Pad00[0xd8];
    INT Count;                              // +0xd8
    void Rebuild();                         // retail 0x10a090c0 (this in EAX)
};

struct UnnamedLevel_115450
{
    char Pad000[0x13c];
    UnnamedGraph_090c0 *Graph;              // +0x13c
    char Pad140[0x4ae0 - 0x140];
    INT Ready;                              // +0x4ae0
};
void __stdcall UnnamedPrepare_f5830(UnnamedLevel_115450 *Level);  // retail 0x109f5830

struct UnnamedLevelInfo_115450
{
    char Pad000[0x1a4];
    UnnamedLevel_115450 *Level;             // +0x1a4
};

struct UnnamedOwner_115450
{
    char Pad00[0x30];
    UnnamedLevelInfo_115450 *Info;          // +0x30
};

// Non-polymorphic base at +4 with a destructor.
struct UnnamedLink_115450
{
    UnnamedOwner_115450 *Owner;             // +0x04
    void *Context;                          // +0x08
    INT Field0C;                            // +0x0c
    INT Field10;                            // +0x10
    UnnamedLink_115450(void *InContext, UnnamedOwner_115450 *InOwner)
    {
        Field0C = 0;
        Owner = InOwner;
        Context = InContext;
        Field10 = 0;
    }
    ~UnnamedLink_115450();
};

// Vtable 0x10c03620.
class UnnamedClass_115450 : public UnnamedLink_115450
{
public:
    char Pad14[0x1bc - 0x14];
    UnnamedLevel_115450 *Level;             // +0x1bc
    UnnamedGraph_090c0 *Graph;              // +0x1c0
    INT Field1C4;                           // +0x1c4
    INT Field1C8;                           // +0x1c8
    INT Field1CC;                           // +0x1cc
    INT Field1D0;                           // +0x1d0
    UnnamedClass_115450(void *InContext, UnnamedOwner_115450 *InOwner);
    virtual ~UnnamedClass_115450();
    virtual void Slot1();
};

// RVA 0x115450
UnnamedClass_115450::UnnamedClass_115450(void *InContext, UnnamedOwner_115450 *InOwner)
    : UnnamedLink_115450(InContext, InOwner)
{
    Level = InOwner->Info->Level;
    Graph = Level->Graph;
    Field1C8 = -1;
    Field1CC = -1;
    Field1C4 = 0;
    Field1D0 = 0;
    if (Graph->Count == 0)
        Graph->Rebuild();
    if (Level->Ready == 0)
        UnnamedPrepare_f5830(Level);
}

// Scaffolding for the link, not part of the unit.
void Opaque(void *);
__declspec(noinline) void UnnamedGraph_090c0::Rebuild() { Opaque(this); Opaque(&Count); }
void Driver_115450(void *Mem, void *InContext, UnnamedOwner_115450 *InOwner)
{
    new (Mem) UnnamedClass_115450(InContext, InOwner);
}
