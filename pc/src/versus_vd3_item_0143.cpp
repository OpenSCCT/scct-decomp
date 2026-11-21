// Work item 0143: Versus RVA 0x3e450 and 0x3e520.
// 0x3e450 is the destructor of an unnamed UObject-derived class (vtable 0x10c0c530)
// whose parent's destructor lives at RVA 0x15ee0. 0x3e520 is its default constructor
// (an LTCG function: `this` on the stack, ret 4). The class holds a 0x40-byte block
// at 0x2c that zeroes itself (with a TArray at its end), four further arrays and a
// string. Class and member names were not recovered.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

extern "C" void *__cdecl memset(void *Dest, int Value, unsigned int Count);
#pragma intrinsic(memset)
inline void appMemzero(void *Dest, INT Count) { memset(Dest, 0, Count); }

enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

// Releases an array member's storage; arrays that share a helper share one declaration.
template<unsigned Helper> void __stdcall ReleaseArray(void *Array);

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
};

// An array whose destructor hands its storage to helper number Helper.
template<unsigned Helper> class TReleasedArray : public FArray {
public:
    ~TReleasedArray() { ReleaseArray<Helper>(this); }
};

// An array whose destructor is an out-of-line thiscall function.
class FStringArray : public FArray {
public:
    ~FStringArray();
};

class FString : public FArray {
public:
    ~FString();
};

class UObject {
public:
    UObject() {}
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
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    INT Name;
    void *Class;
    INT ConditionalDestroy()
    {
        if (Index != INDEX_NONE && !(ObjectFlags & RF_Destroyed)) {
            ObjectFlags = (ObjectFlags & ~(RF_DebugDestroy | RF_Destroyed)) | RF_Destroyed;
            Destroy();
            return 1;
        }
        return 0;
    }
};

// Parent class whose destructor lives at RVA 0x15ee0 (name not recovered).
class UnnamedBase_15ee0 : public UObject {
public:
    UnnamedBase_15ee0() {}
    virtual ~UnnamedBase_15ee0();
};

// A 0x40-byte block that clears itself on construction (name not recovered).
struct UnnamedBlock_3e520 {
    unsigned char Bytes[0x34];
    TReleasedArray<0> Items;
    UnnamedBlock_3e520() { appMemzero(this, sizeof(*this)); }
};

// Name not recovered; vtable 0x10c0c530.
class UnnamedClass_3e450 : public UnnamedBase_15ee0 {
public:
    INT Field28;
    UnnamedBlock_3e520 Block;       // 0x2c
    FStringArray Strings;           // 0x6c
    TReleasedArray<1> ArrayA;       // 0x78
    TReleasedArray<2> ArrayB;       // 0x84
    INT Field90;
    FString Text;                   // 0x94
    UnnamedClass_3e450();
    virtual ~UnnamedClass_3e450();
};

// RVA 0x3e520 (near miss): retail is LTCG code with `this` on the stack (ret 4) that
// keeps all three vtable stores and an unfolded memset; VC7.0 /GL folds them away.
UnnamedClass_3e450::UnnamedClass_3e450() {}

UnnamedClass_3e450::~UnnamedClass_3e450()
{
    ConditionalDestroy();
}

// Scaffolding for the LTCG link of the constructor, not part of the unit. Retail calls it
// from the class's InternalConstructor (0x3e510) and from a subclass constructor (0x3e8c0).
enum EInternal { EC_Internal };
inline void *operator new(unsigned int, EInternal *Mem) { return Mem; }
class UnnamedSubclass_3e8c0 : public UnnamedClass_3e450 {
public:
    INT Extra[4];
    UnnamedSubclass_3e8c0() { Extra[0] = Extra[1] = Extra[2] = Extra[3] = 0; }
};
void Driver_3e520(void *X)
{
    new((EInternal *)X) UnnamedClass_3e450;
}
void Driver2_3e520(void *X)
{
    new((EInternal *)X) UnnamedSubclass_3e8c0;
}
