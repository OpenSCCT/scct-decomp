// Work item 0063 (LTCG retry): Versus RVA 0x103a0, 0x10420, 0x10480.
// Link-time code generation gave these destructors/constructors `this` on the
// stack with `ret 4`. Class names are neutral (no string names them).

typedef int INT;
typedef unsigned long DWORD;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const unsigned short *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const unsigned short *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;
// Unreal's global operator delete (appFree through GMalloc).
inline void operator delete(void *Ptr) { GMalloc->Free(Ptr); }

inline void *operator new(unsigned int, void *Mem) { return Mem; }

// ---- RVA 0x103a0: destructor of a holder whose buffer lives at +0xc.
// FArray layout as in Unreal Engine 2 (Data, ArrayNum, ArrayMax).
class FArray {
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

// Base destructor is RVA 0x14b60 (also LTCG, this on the stack): a TArray
// destructor that destroys its elements (RVA 0x14f40) and then frees the
// FArray storage. Written out so the linker sees it as a local function with
// an exception frame, which is what gives it the stack `this` convention.
class UnnamedBase_014b60 : public FArray {
public:
    __declspec(noinline) ~UnnamedBase_014b60() { DestroyElements(this, ArrayNum); }
    static void DestroyElements(UnnamedBase_014b60 *Array, INT Count);
};

class UnnamedHolder_0103a0 : public UnnamedBase_014b60 {
public:
    ~UnnamedHolder_0103a0();
    void *Data;
    INT ArrayNum;
};

UnnamedHolder_0103a0::~UnnamedHolder_0103a0()
{
    if (Data)
        GMalloc->Free(Data);
    Data = 0;
    ArrayNum = 0;
}

// ---- RVA 0x10420 / 0x10480: class with vtable 0x10c0d2a0 over 0x10c0d248.
// The primary base (vtable 0x10c0d248, all slots pure except the virtual
// destructor, deleting destructor RVA 0x11720) has only the vtable. The
// TMap-like second base sits at +4 (constructor RVA 0x14520, destructor
// RVA 0x116a0, both LTCG with this on the stack); then two TArrays
// (destructor RVA 0x48b0). Cleanup (RVA 0x10770) is vtable slot 11 in retail,
// called directly from the destructor. The deleting destructor is RVA 0x11670.
class UnnamedMap_014520 {
public:
    __declspec(noinline) UnnamedMap_014520() : Hash(0), HashCount(8) { Rehash(this); }
    __declspec(noinline) ~UnnamedMap_014520()
    {
        if (Hash)
            GMalloc->Free(Hash);
        Hash = 0;
        HashCount = 0;
    }
    static void Rehash(UnnamedMap_014520 *Map);
    FArray Pairs;
    INT *Hash;
    INT HashCount;
};

class UnnamedTArray_0048b0 {
public:
    UnnamedTArray_0048b0() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~UnnamedTArray_0048b0();
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

class UnnamedClass_30D248 {
public:
    UnnamedClass_30D248() {}
    virtual ~UnnamedClass_30D248() {}
};

class UnnamedClass_30D2A0 : public UnnamedClass_30D248, public UnnamedMap_014520 {
public:
    UnnamedClass_30D2A0();
    ~UnnamedClass_30D2A0();   // virtual through the base; not re-declared virtual (needed for the match)
    void Cleanup(INT A, INT B);
    UnnamedTArray_0048b0 ListA;
    UnnamedTArray_0048b0 ListB;
};

UnnamedClass_30D2A0::UnnamedClass_30D2A0()
{
}

UnnamedClass_30D2A0::~UnnamedClass_30D2A0()
{
    Cleanup(1, 0);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_103a0(UnnamedHolder_0103a0 *H) { Escape(&GMalloc); H->~UnnamedHolder_0103a0(); }
void *Driver_10420(void *Mem) { Escape(Mem); return new (Mem) UnnamedClass_30D2A0; }
void Driver_10480(UnnamedClass_30D2A0 *A, UnnamedClass_30D2A0 *B)
{
    Escape(&GMalloc);
    A->UnnamedClass_30D2A0::~UnnamedClass_30D2A0();
    B->UnnamedClass_30D2A0::~UnnamedClass_30D2A0();
    Escape(A);
}
