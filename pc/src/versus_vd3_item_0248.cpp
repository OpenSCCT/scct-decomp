// Work item 0248: Versus RVA 0x5b060-0x5b2c2.
// IMPLEMENT_CLASS output for an unidentified UObject subclass of size 0x30fc0:
//   0x5b060  dynamic initializer of its PrivateStaticClass (UClass native ctor)
//   0x5b0c0  InternalConstructor: new((EInternal*)X) TClass
//   0x5b100  the class's default constructor (LTCG: this on the stack, ret 4)
// Class names are not recovered; neutral names are used. Name and package are
// passed as name indices converted implicitly to FName (constructed in place);
// the config name comes from an inline StaticConfigName() returning FName.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned int size_t;
extern "C" void *memset(void *, int, size_t);
#pragma intrinsic(memset)

enum ENativeConstructor { EC_NativeConstructor };
enum EInternal { EC_Internal };

inline void *operator new(size_t Size, EInternal *Mem) { return (void *)Mem; }
inline void operator delete(void *Object, EInternal *Mem) {}

struct FGuid
{
    DWORD A, B, C, D;
    FGuid(DWORD InA, DWORD InB, DWORD InC, DWORD InD) : A(InA), B(InB), C(InC), D(InD) {}
};

// In this build native class and package names are passed as name indices.
struct FName
{
    INT Index;
    FName(INT InIndex) : Index(InIndex) {}
};

class UClass;

class __declspec(novtable) UObject
{
public:
    UObject() {}
    virtual void Vf00();
    INT Fields[9];          // 0x04..0x28
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
    void StaticConstructor();
};

class UClass
{
public:
    UClass(ENativeConstructor, DWORD InSize, DWORD InClassFlags, UClass *InSuperClass, UClass *InWithinClass,
           FGuid InGuid, FName InName, FName InPackageName, FName InConfigName, DWORD InFlags,
           void (*InClassConstructor)(void *), void (UObject::*InClassStaticConstructor)());
    char Pad[0x10c];
};

template <class T> class TArray
{
public:
    TArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~TArray() { Destroy(); }
    void Destroy();
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
};

// Secondary base at +0x28 (vtable 0x10c0e71c; unidentified interface).
class UnnamedBase_5b100
{
public:
    UnnamedBase_5b100() {}
    virtual ~UnnamedBase_5b100();
    INT Unknown04;
    INT Unknown08;
    TArray<INT> Items;      // +0x0c
};

class UnnamedObject_5b100;

// Member at +0x46dc, constructed with its owner (ctor at 0x608c0).
class UnnamedMember_608c0
{
public:
    __declspec(noinline) UnnamedMember_608c0(UnnamedObject_5b100 *InOwner);
    ~UnnamedMember_608c0();
    char Pad[0x2fb4c - 0x46dc];
};

class UnnamedSuper_5b060
{
public:
    static UClass PrivateStaticClass;
};

class UnnamedObject_5b100 : public UObject, public UnnamedBase_5b100
{
public:
    __declspec(noinline) UnnamedObject_5b100();
    char Pad40[0x4644 - 0x40];
    TArray<INT> ArrayA;             // +0x4644
    char Pad4650[0x466c - 0x4650];
    TArray<INT> ArrayB;             // +0x466c
    char Pad4678[0x46dc - 0x4678];
    UnnamedMember_608c0 Member;     // +0x46dc
    TArray<INT> ArrayC;             // +0x2fb4c
    char Pad2fb58[0x30d40 - 0x2fb58];
    INT Slots[0x36];                // +0x30d40
    char Pad30e18[0x30e44 - 0x30e18];
    INT IndexA[6];                  // +0x30e44
    char Pad30e5c[0x30e8c - 0x30e5c];
    INT CountA;                     // +0x30e8c
    INT CountB;                     // +0x30e90
    char Pad30e94[0x30ea8 - 0x30e94];
    INT CountC;                     // +0x30ea8
    char Pad30eac[0x30f2c - 0x30eac];
    INT IndexB[10];                 // +0x30f2c
    INT IndexC[3];                  // +0x30f54
    INT IndexD[2];                  // +0x30f60
    INT IndexE[22];                 // +0x30f68

    static UClass PrivateStaticClass;
    static FName StaticConfigName() { return FName(0x256); }
    static void InternalConstructor(void *X) { new((EInternal *)X) UnnamedObject_5b100; }
};

// 0x5b060: IMPLEMENT_CLASS
UClass UnnamedObject_5b100::PrivateStaticClass(
    EC_NativeConstructor, sizeof(UnnamedObject_5b100), 4,
    &UnnamedSuper_5b060::PrivateStaticClass, UObject::StaticClass(),
    FGuid(0, 0, 0, 0), 0xc8, 0xbf, UnnamedObject_5b100::StaticConfigName(), 0x4084004,
    UnnamedObject_5b100::InternalConstructor,
    (void (UObject::*)())&UObject::StaticConstructor);

// 0x5b100
UnnamedObject_5b100::UnnamedObject_5b100()
    : Member(this)
{
    memset(Slots, 0xff, sizeof(Slots));
    CountC = 0;
    IndexB[0] = -1; IndexB[1] = -1; IndexB[2] = -1; IndexB[3] = -1; IndexB[4] = -1;
    IndexB[5] = -1; IndexB[6] = -1; IndexB[7] = -1; IndexB[8] = -1; IndexB[9] = -1;
    IndexD[0] = -1; IndexD[1] = -1;
    IndexC[0] = -1; IndexC[1] = -1; IndexC[2] = -1;
    IndexE[0] = -1; IndexE[1] = -1; IndexE[2] = -1; IndexE[3] = -1; IndexE[4] = -1;
    IndexE[5] = -1; IndexE[6] = -1; IndexE[7] = -1; IndexE[8] = -1; IndexE[9] = -1;
    IndexE[10] = -1; IndexE[11] = -1; IndexE[12] = -1; IndexE[13] = -1; IndexE[14] = -1;
    IndexE[15] = -1; IndexE[16] = -1; IndexE[17] = -1; IndexE[18] = -1; IndexE[19] = -1;
    IndexE[20] = -1; IndexE[21] = -1;
    IndexA[0] = -1; IndexA[1] = -1; IndexA[2] = -1; IndexA[3] = -1; IndexA[4] = -1;
    CountA = 0;
    CountB = 0;
    IndexA[5] = -1;
}

void StandIn_608c0(UnnamedMember_608c0 *Member, INT *A, INT *B, INT *C);
// Stand-in body so the LTCG link gives 0x608c0 retail's ESI convention (not part of the unit).
UnnamedMember_608c0::UnnamedMember_608c0(UnnamedObject_5b100 *InOwner)
{
    INT *P = (INT *)Pad;
    for (INT i = 0; i < 0x80; i++)
        StandIn_608c0(this, P + i, P + i * 3, P + i * 5);
    StandIn_608c0(this, P + 1, P + 2, P + 3);
    *(UnnamedObject_5b100 **)Pad = InOwner;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_5b0c0() { Escape((void *)&UnnamedObject_5b100::InternalConstructor); }
