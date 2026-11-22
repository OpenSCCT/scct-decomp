// Work item 0026 (LTCG retry): Versus RVA 0x6140.
// Constructor of a record derived from the base whose destructor is retail
// 0x5b50 (see item 0024), holding at +0x3c the three-FString record whose copy
// constructor is retail 0x6260 (see item 0027). Names are neutral: no vtable
// label or string identifies these classes.
#include "versus_build.h"
#include "unreal_containers.h"
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

// Record held at +0x3c: implicit copy constructor is retail 0x6260,
// implicit destructor 0x6200.
struct UnnamedRecord_6200 {
    FString A;      // +0x00
    FString B;      // +0x0c
    FString C;      // +0x18
    DWORD D;        // +0x24
    DWORD E;        // +0x28
};

// First base (vtable at +0); its destructor is retail 0x216f50.
class UnnamedObject_216f50 {
public:
    virtual ~UnnamedObject_216f50();
};

// Second base (vtable at +4).
class UnnamedInterface_5b50 {
public:
    virtual void Unnamed0();
};

// Base part; destructor is retail 0x5b50.
class UnnamedBase_5b50 : public UnnamedObject_216f50, public UnnamedInterface_5b50 {
public:
    virtual ~UnnamedBase_5b50();
    virtual void Unnamed1();
    INT A;          // +0x08
    INT B;          // +0x0c
    INT C;          // +0x10
    INT D;          // +0x14
    INT E;          // +0x18
    INT F;          // +0x1c
    INT G;          // +0x20
    TArray<INT> H;  // +0x24
    TArray<INT> I;  // +0x30
    UnnamedBase_5b50(INT InA, INT InB) : A(InA), B(InB), C(1), D(0), E(1), F(0), G(0) {}
};

// Constructor is retail 0x6140 (vtables 0x10c0e2f0 / 0x10c0e2e0).
class UnnamedEntry_6140 : public UnnamedBase_5b50 {
public:
    UnnamedRecord_6200 Record;  // +0x3c
    UnnamedEntry_6140(INT InA, INT InB, const UnnamedRecord_6200 &InRecord);
    virtual void Unnamed1();
};

UnnamedEntry_6140::UnnamedEntry_6140(INT InA, INT InB, const UnnamedRecord_6200 &InRecord)
    : UnnamedBase_5b50(InA, InB), Record(InRecord)
{
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void *operator new(unsigned int Size);
struct UnnamedOwner { INT Pad0, Pad1; INT A; };
void Driver_6140(UnnamedOwner *O, const UnnamedRecord_6200 *R)
{
    Escape(new UnnamedEntry_6140(O->A, (INT)O, *R));
}
