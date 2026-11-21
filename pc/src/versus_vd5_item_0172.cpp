// Work item 0172 (wave 3): Versus RVA 0xcdb30-0xcdee6, link-time code generation.
//   0xcdb30 UStaticMesh::~UStaticMesh  (vtable 0x10c04820, next to the published
//           UStaticMesh deleting destructor at 0xcdb00)
//   0xcdcc0 UnnamedStruct_cdcc0::~UnnamedStruct_cdcc0  (this on the stack, ret 4)
//   0xcdde0 UnnamedStruct_cdcc0::UnnamedStruct_cdcc0   (this on the stack, ret 4)
// Element types are named by their size only (UnnamedElement_<size>); the array
// destructors they instantiate are the retail LTCG functions listed beside them.
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

inline void *operator new(unsigned int, void *Mem) { return Mem; }
inline void operator delete(void *, void *) {}

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
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
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
    void Remove(INT Index, INT Count, INT ElementSize); // RVA 0x119c0

    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray();
    void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&((T *)Data)[i])->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
};

template<class T> TArray<T>::~TArray()
{
    Remove(0, ArrayNum);
}

// Versus array without a capacity field (unnamed in the retail build).
class FSimpleArray
{
public:
    FSimpleArray() : Data(0), ArrayNum(0) {}
    ~FSimpleArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize); // RVA 0x11aa0

    void *Data;
    INT ArrayNum;
};

template<class T> class TSimpleArray : public FSimpleArray
{
public:
    ~TSimpleArray()
    {
        Remove(0, ArrayNum);
    }
    void Remove(INT Index, INT Count = 1)
    {
        FSimpleArray::Remove(Index, Count, sizeof(T));
    }
};

struct UnnamedElement_4   { BYTE Pad[0x4]; };
struct UnnamedElement_8   { BYTE Pad[0x8]; };
struct UnnamedElement_C   { BYTE Pad[0xc]; };
struct UnnamedElement_10  { BYTE Pad[0x10]; };
struct UnnamedElement_14  { BYTE Pad[0x14]; };
struct UnnamedElement_18  { BYTE Pad[0x18]; };
struct UnnamedElement_104 { BYTE Pad[0x104]; };
struct UnnamedElement_274 { BYTE Pad[0x274]; };
// Elements with their own destructors (arrays at RVA 0xcd990 and 0xdef50).
struct UnnamedElement_cd990 { ~UnnamedElement_cd990(); INT Value; };
struct UnnamedElement_def50 { ~UnnamedElement_def50(); INT Value; };
// Twelve-byte element of the fixed array of lists (constructor 0x4630,
// destructor 0x86750, both ordinary thiscall code outside this unit).
struct UnnamedElement_86750 { BYTE Pad[0xc]; };

class FString;
// Destructors compiled elsewhere as ordinary thiscall functions.
// TArray<TCHAR>::~TArray is RVA 0xc4e0, TArray<FString>::~TArray RVA 0xc5f0,
// TArray<UnnamedElement_86750>::~TArray RVA 0x86750.
extern template class TArray<TCHAR>;
extern template class TArray<FString>;
extern template class TArray<UnnamedElement_86750>;

class FString : public TArray<TCHAR>
{
};

// UObject (Core): only what the destructor touches.
enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

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
    DWORD Reserved[5];
    DWORD ObjectFlags;
    INT ConditionalDestroy()
    {
        if (Index != INDEX_NONE && !(ObjectFlags & RF_Destroyed))
        {
            ObjectFlags = (ObjectFlags & ~(RF_DebugDestroy | RF_Destroyed)) | RF_Destroyed;
            Destroy();
            return 1;
        }
        return 0;
    }
};

class UPrimitive : public UObject
{
public:
    virtual ~UPrimitive(); // RVA 0x97350
    BYTE PrimitivePad[0x50 - 0x20];
};

// Owner interface notified when the resource below goes away (slot 17).
class FUnnamedResourceOwner
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void ResourceDestroyed(class FUnnamedResource *Resource);
};

// Render-resource-like member with vtable 0x10c048e0; destructor RVA 0xcd930.
class FUnnamedResource
{
public:
    virtual void VirtualSlot0();
    ~FUnnamedResource();
    FUnnamedResourceOwner *Owner;
    INT Unknown08;
    TArray<UnnamedElement_104> Items;
};

#pragma auto_inline(off)
FUnnamedResource::~FUnnamedResource()
{
    if (Owner)
        Owner->ResourceDestroyed(this);
}
#pragma auto_inline(on)

class UStaticMesh : public UPrimitive
{
public:
    virtual ~UStaticMesh();

    TArray<UnnamedElement_14> Array50;          // 0x50, 0x1f20d0
    INT Pad5C;
    TArray<UnnamedElement_18> Array60;          // 0x60, 0x1edf20
    INT Pad6C[4];
    TArray<UnnamedElement_4> Array7C;           // 0x7c, 0x17bf30
    INT Pad88[4];
    TArray<UnnamedElement_4> Array98;           // 0x98, 0x17bf30
    INT PadA4[3];
    TArray<UnnamedElement_cd990> ArrayB0;       // 0xb0, 0xcd990
    INT PadBC[2];
    TArray<TCHAR> TextC4;                       // 0xc4, 0xc4e0
    INT PadD0[3];
    TArray<UnnamedElement_C> ArrayDC;           // 0xdc, 0x1eecc0
    TSimpleArray<UnnamedElement_10> ArrayE8;    // 0xe8, 0x207e50
    TSimpleArray<UnnamedElement_8> ArrayF0;     // 0xf0, 0xa28e0
    TArray<UnnamedElement_C> ArrayF8;           // 0xf8, 0x1eecc0
    INT Pad104[2];
    TArray<UnnamedElement_18> Array10C;         // 0x10c, 0x1edf20
    INT Pad118[3];
    TSimpleArray<UnnamedElement_10> Array124;   // 0x124, 0x207e50
    TSimpleArray<UnnamedElement_8> Array12C;    // 0x12c, 0xa28e0
    TArray<UnnamedElement_C> Array134;          // 0x134, 0x1eecc0
    INT Pad140[3];
    FUnnamedResource Resource14C;               // 0x14c, 0xcd930
    FUnnamedResource Resource164;               // 0x164, 0xcd930
    INT Pad17C[4];
    TSimpleArray<UnnamedElement_274> Array18C;  // 0x18c, 0xcd8c0
};

UStaticMesh::~UStaticMesh()
{
    ConditionalDestroy();
}

class UnnamedStruct_cdcc0
{
public:
    UnnamedStruct_cdcc0()
    {
        for (INT i = 0; i < 8; i++)
            Values[i] = 0;
    }
    ~UnnamedStruct_cdcc0() {}

    INT Unknown00;
    INT Values[8];                              // 0x04
    TArray<UnnamedElement_4> Array24;           // 0x24
    TArray<UnnamedElement_4> Array30;           // 0x30
    TArray<FString> Strings3C;                  // 0x3c
    TArray<FString> Strings48;                  // 0x48
    TArray<UnnamedElement_4> Array54;           // 0x54
    TArray<UnnamedElement_4> Array60;           // 0x60
    TArray<FString> Strings6C;                  // 0x6c
    TArray<FString> Strings78;                  // 0x78
    TArray<FString> Strings84;                  // 0x84
    TArray<FString> Strings90;                  // 0x90
    TArray<FString> Strings9C;                  // 0x9c
    TArray<FString> StringsA8;                  // 0xa8
    TArray<UnnamedElement_86750> Lists[8];      // 0xb4
    TArray<UnnamedElement_def50> Array114;      // 0x114
};

// Scaffolding for the link, not part of the unit.
void Driver_cdb30(UStaticMesh *Mesh)
{
    Mesh->UStaticMesh::~UStaticMesh();
}
void Driver_cdcc0(UnnamedStruct_cdcc0 *S)
{
    S->~UnnamedStruct_cdcc0();
}
UnnamedStruct_cdcc0 *Driver_cdde0(void *Mem)
{
    return new(Mem) UnnamedStruct_cdcc0;
}
