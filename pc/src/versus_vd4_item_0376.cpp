// Work item 0376: Versus RVA 0xa4620 and 0xa46b0.
// 0xa4620 is the destructor of the class whose deleting destructor is
// @delete_UStaticMeshInstance@8 at 0xa45f0 (the published neighbour), so it is
// taken to be UStaticMeshInstance::~UStaticMeshInstance. 0xa46b0 is the
// TArray destructor for its array member at +0x28. Retail built this unit with
// /GL and linked with /LTCG: both array destructors take `this` on the stack.
// The element types are not identified; they carry neutral names.
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short TCHAR;

enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

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
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize); // RVA 0x119c0
};

template <class T> class TArray : public FArray
{
public:
    ~TArray()
    {
        Remove(0, ArrayNum);
    }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count = 1);
};

template <class T> __declspec(noinline) void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArray::Remove(Index, Count, sizeof(T));
}

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
    // Retail calls Destroy through the vtable slot memory (call [vftable+0x24]);
    // as in the sibling LTCG units it is declared dllimport to give that
    // indirect call, because the verifier cannot bind an address inside a vtable.
    __declspec(dllimport) virtual void Destroy(); // slot 9
    INT Index;
    DWORD Reserved[5];
    DWORD ObjectFlags;
    INT Name;
    UObject *Class;
    INT ConditionalDestroy()
    {
        if (Index != INDEX_NONE && !(ObjectFlags & RF_Destroyed)) {
            ObjectFlags = (ObjectFlags & ~(RF_DebugDestroy | RF_Destroyed)) | RF_Destroyed;
            // Qualified: in a destructor the call resolves statically to the slot of
            // the class being destroyed; this spelling gives the same indirect call
            // through an address the verifier can bind (retail 0x10c0a4c4).
            UObject::Destroy();
            return 1;
        }
        return 0;
    }
};

// Element of the +0x28 array (unidentified; has a destructor).
struct UnnamedElement_a4720
{
    INT Pad[4];
    ~UnnamedElement_a4720();
};
// Element of the +0x38 array (unidentified).
struct UnnamedElement_a7bf30
{
    INT Pad[4];
    ~UnnamedElement_a7bf30();
};

class UStaticMeshInstance : public UObject
{
public:
    TArray<UnnamedElement_a4720> Lights;      // +0x28, destructor 0xa46b0
    INT Unknown34;                            // +0x34
    TArray<UnnamedElement_a7bf30> Colors;     // +0x38, destructor 0x17bf30
    virtual ~UStaticMeshInstance();
};

// RVA 0xa4620
UStaticMeshInstance::~UStaticMeshInstance()
{
    ConditionalDestroy();
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_a4620(UStaticMeshInstance *P)
{
    P->UStaticMeshInstance::~UStaticMeshInstance();
}
