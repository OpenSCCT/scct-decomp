// Work item 0096: Versus RVA 0xadd10 (InternalConstructor) and 0xadd50 (constructor).
// The class is unidentified (vtable at 0x10c05170); neutral names are used.

enum EInternal { EC_Internal };
inline void *operator new(unsigned int, EInternal *Mem) { return Mem; }
inline void operator delete(void *, EInternal *) {}

// 12-byte element (likely FString/TArray): out-of-line ctor 0x10968f30, dtor 0x10a79000.
struct FElem_add50 {
    FElem_add50();
    ~FElem_add50();
    void *Data;
    int Num;
    int Max;
};

// Members with an empty constructor and a destructor: they only consume EH states (14 of them, states 0x0-0xd after the base).
struct FStateOnly_add50 {
    FStateOnly_add50() {}
    ~FStateOnly_add50();
};

class AActor {
public:
    // Stand-in body (retail _initialize_actor at 0x92100); defined so LTCG gives it the EAX convention.
    __declspec(noinline) AActor() { ActorFlags &= ~1u; }
    virtual ~AActor();
    unsigned char ActorData[0x2e4];
    unsigned int ActorFlags;
    unsigned char ActorRest[0x3f4 - 0x2ec];
};

class UnnamedClass_add50 : public AActor {
public:
    UnnamedClass_add50();
    virtual ~UnnamedClass_add50();
    static void InternalConstructor(void *X);
    FStateOnly_add50 S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13;
    unsigned char Pad[0x408 - 0x3f4 - 14];
    FElem_add50 A[11];
    FElem_add50 B[2];
};

UnnamedClass_add50::UnnamedClass_add50()
{
}

void UnnamedClass_add50::InternalConstructor(void *X)
{
    new((EInternal *)X) UnnamedClass_add50();
}

// Scaffolding for the link, not part of the unit.
void Driver_add10(void *X) { UnnamedClass_add50::InternalConstructor(X); }
