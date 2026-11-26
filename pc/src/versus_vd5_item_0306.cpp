// Work item 0306: Versus RVA 0x1064b0-0x106672.
// 0x1064b0: destructor of an unnamed UObject-derived class with two extra
//   interface bases (vtables at +0x28 / +0x2c) and a TArray<void*> member at
//   +0x58. Its parent destructor is retail 0x915ee0; the TArray<void*>
//   destructor is retail 0x7bf30 (LTCG, `this` on the stack).
// 0x106540: UFlicFlocEmitter vtable slot 27, the particle-emitter
//   SpawnParticles(OldLeftover, Rate, DeltaTime) override.
#include "versus_build.h"
#include "unreal_object.h"

typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short TCHAR;
typedef float FLOAT;

enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }
template<class T> inline T Clamp(const T X, const T Min, const T Max_) { return X < Min ? Min : X < Max_ ? X : Max_; }

extern "C" __declspec(dllimport) double __cdecl floor(double);
inline INT appFloor(FLOAT F) { return (INT)floor(F); }

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FArray
{
public:
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayMax = 0;
        ArrayNum = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);

    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    __declspec(noinline) ~TArray()
    {
        Remove(0, ArrayNum);
    }
    void Remove(INT Index, INT Count = 1)
    {
        FArray::Remove(Index, Count, sizeof(T));
    }
};

// Parent class (retail destructor 0x915ee0, matched or open elsewhere).
class UnnamedClass_915ee0 : public UObject { public: virtual ~UnnamedClass_915ee0(); };

// Interface bases with their own vtables (names not recovered).
class UnnamedInterface_1064b0_A { public: virtual void InterfaceSlot0(); };
class UnnamedInterface_1064b0_B { public: virtual void InterfaceSlot0(); };

class UnnamedClass_1064b0
    : public UnnamedClass_915ee0, public UnnamedInterface_1064b0_A, public UnnamedInterface_1064b0_B
{
public:
    virtual ~UnnamedClass_1064b0();
    DWORD Unknown30[10];
    TArray<void *> Pointers; // +0x58
};

// Retail RVA 0x1064b0.
UnnamedClass_1064b0::~UnnamedClass_1064b0()
{
    ConditionalDestroy();
}

// UFlicFlocEmitter: only the members SpawnParticles touches.
class UFlicFlocEmitter : public UObject
{
public:
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
    virtual void NetDirty(UProperty *Property);
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual FLOAT SpawnParticles(FLOAT OldLeftover, FLOAT Rate, FLOAT DeltaTime);
    virtual void SpawnParticle(INT Index, FLOAT SpawnTime, INT Flags, INT SpawnFlags, DWORD Extra);

    DWORD Unknown28[(0x39c - 0x28) / 4];
    INT Enabled;            // 0x39c
    DWORD Unknown3a0[3];
    INT ParticleIndex;      // 0x3ac
    INT ActiveParticles;    // 0x3b0
    DWORD Unknown3b4[(0x3c8 - 0x3b4) / 4];
    INT MaxActiveParticles; // 0x3c8
    DWORD Unknown3cc[(0x3e4 - 0x3cc) / 4];
    INT ParticlesRemaining; // 0x3e4
    DWORD Unknown3e8[(0x41c - 0x3e8) / 4];
    INT MaxParticles;       // 0x41c
};

extern DWORD GSpawnParticleExtra; // retail 0x10ccacc0, meaning unknown

// Retail RVA 0x106540.
FLOAT UFlicFlocEmitter::SpawnParticles(FLOAT OldLeftover, FLOAT Rate, FLOAT DeltaTime)
{
    if (Rate <= 0.f || !Enabled)
        return 0.f;

    FLOAT NewLeftover = OldLeftover + DeltaTime * Rate;
    INT Number = appFloor(NewLeftover);
    NewLeftover -= Number;
    FLOAT Increment = 1.f / Rate;
    FLOAT StartTime = DeltaTime + OldLeftover * Increment - Increment;

    Number = Clamp(Number, 0, MaxActiveParticles);
    if (ParticlesRemaining) {
        Number = Clamp(Number, 0, ParticlesRemaining);
        ParticlesRemaining -= Number;
    }
    for (INT i = 0; i < Number; i++) {
        SpawnParticle(ParticleIndex, StartTime - i * Increment, 4, 0, GSpawnParticleExtra);
        ActiveParticles = Max(ActiveParticles, ParticleIndex + 1);
        ParticleIndex = (ParticleIndex + 1) % MaxParticles;
    }
    return NewLeftover;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_1064b0(UnnamedClass_1064b0 *O) { Escape(&GMalloc); O->UnnamedClass_1064b0::~UnnamedClass_1064b0(); }
