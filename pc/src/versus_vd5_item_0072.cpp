// Work item 0072 (wave 3): Versus RVA 0xa8830-0xa8b96.
//
// 0xa8830 is the destructor of the class whose deleting destructor is
// @delete_UModel@8 at 0xa8800, so it is UModel::~UModel. UModel derives from
// UPrimitive (destructor at 0x97350). The members it destroys are TArrays; their
// element types are not recovered, so they carry neutral names after their size
// (FModelElement5C and so on). 0xa8980, 0xa8a60 and 0xa8ae0 are TArray<T>
// destructors and 0xa89f0 / 0xa8b50 are TArray<T>::Remove; the object was
// compiled /GL, so the linker gave these custom calling conventions (this on
// the stack, Index in EDI, this in EBX).
//
// try_ltcg.py /O2 /Gy /GX, roots Driver_a8830 and Driver_a89f0: 0xa8a60, 0xa8ae0
// and 0xa8b50 MATCH. 0xa8830 differs in 4 bytes (register choice for two member
// addresses, eax in retail) and the tool flags the devirtualised Destroy call
// [vtable+0x24] as a differing constant. 0xa8980 differs because the compiler
// inlines TArray<FModelElement5C>::Remove (0xa89f0), which retail keeps out of line.

typedef unsigned short TCHAR;
typedef unsigned short WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
    ~TArray();
};
template <class T> TArray<T>::~TArray() { Remove(0, ArrayNum); }

// Array class at UModel+0x114 (Data and ArrayNum only); its destructor (0x207e50)
// uses its own Remove.
class FArray114
{
public:
    void *Data;
    INT ArrayNum;
    ~FArray114()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);
};
class TArray114 : public FArray114
{
public:
    ~TArray114() { Remove(0, ArrayNum, 16); }
};

class UObject
{
public:
    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    INT Index;
    unsigned Reserved[5];
    unsigned ObjectFlags;
    int ConditionalDestroy()
    {
        if (Index != -1 && !(ObjectFlags & 0x00800000))
        {
            ObjectFlags = (ObjectFlags & ~(0x80000000 | 0x00800000)) | 0x00800000;
            Destroy();
            return 1;
        }
        return 0;
    }
};

class UPrimitive : public UObject
{
public:
    unsigned PrimitiveData[13];
    virtual ~UPrimitive();
};

// Element types (sizes from the Remove strides).
struct FModelVector { INT X, Y, Z; };          // 0xc, destructor out of line (0x86750)
struct FModelElement18 { INT A[6]; };          // 0x18
struct FModelElement2C                         // 0x2c
{
    INT Unknown0[8];
    void *Buffer;                              // +0x20, freed by the destructor
    INT Unknown24[2];
    ~FModelElement2C()
    {
        if (Buffer)
            GMalloc->Free(Buffer);
    }
};
struct FModelElement5C                         // 0x5c
{
    INT Unknown0[16];
    TArray<INT> Items;                         // +0x40
    INT Unknown4C[4];
    __declspec(noinline) ~FModelElement5C() {}
};
struct FModelElement38                         // 0x38
{
    TArray<INT> Items;
    INT Unknown0C[11];
    __declspec(noinline) ~FModelElement38() {}
};
struct FModelElement70                         // 0x70
{
    TArray<INT> Items;
    INT Unknown0C[25];
    __declspec(noinline) ~FModelElement70() {}
};
struct FModelElementA4                         // 0xa4
{
    TArray<INT> Items;
    INT UnknownC[38];
    __declspec(noinline) ~FModelElementA4() {}
};

// Instantiations retail calls as ordinary thiscall functions from other objects.
// (only their destructors are needed here).
template <> class TArray<UObject *> : public FArray
{
public:
    ~TArray();
};
template <> class TArray<FModelVector> : public FArray
{
public:
    ~TArray();
};

class UModel : public UPrimitive
{
public:
    TArray<FModelElement5C> Elements5C;    // 0x54
    INT Unknown60;
    TArray<WORD> Words;                    // 0x64
    INT Unknown70;
    TArray<FModelVector> Vectors;          // 0x74
    INT Unknown80;
    TArray<FModelVector> Points;           // 0x84
    INT Unknown90;
    TArray<FModelElement2C> Elements2C;    // 0x94
    INT UnknownA0;
    TArray<FModelElement18> Elements18;    // 0xa4
    TArray<UObject *> ObjectsB0;           // 0xb0
    TArray<INT> IntsBC;                    // 0xbc
    TArray<INT> IntsC8;                    // 0xc8
    TArray<FModelElement38> Elements38;    // 0xd4
    TArray<FModelElement70> Elements70;    // 0xe0
    TArray<FModelElementA4> ElementsA4;    // 0xec
    TArray<UObject *> ObjectsF8;           // 0xf8
    INT Unknown104[4];
    TArray114 Array114;                    // 0x114
    virtual ~UModel();
};

UModel::~UModel()
{
    ConditionalDestroy();
}

// Scaffolding for the link, not part of the unit.
void Driver_a8830(UModel *M) { M->UModel::~UModel(); }
// Other retail users of the element arrays (UModel's empty/rebuild paths).
void Driver_a89f0(UModel *M, INT Index, INT Count)
{
    M->Elements5C.Remove(Index, Count);
    M->Elements2C.Remove(Index, Count);
}
