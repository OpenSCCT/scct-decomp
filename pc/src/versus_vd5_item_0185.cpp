// Work item 0185: Versus RVA 0xe1b50-0xe1c52. All five functions come from an
// LTCG object (register calling conventions), matched with try_ltcg.py.
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef short SWORD;

enum EName { NAME_None };
struct FName
{
    INT Index;
    FName(EName N) : Index(N) {}
};

class UFunction;
class UClass;

class UObject
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0); // slot 4
    INT Index;          // 0x04
    BYTE PadObj[0x24 - 0x08];
    UClass *Class;      // 0x24
    UFunction *FindFunctionChecked(FName InName, INT Global = 0); // retail 0x16830
    inline int IsA(UClass *SomeBase) const;
};

class UField : public UObject
{
public:
    UField *SuperField; // 0x28
};
class UClass : public UField {};

inline int UObject::IsA(UClass *SomeBase) const
{
    for (UClass *C = Class; C; C = (UClass *)C->SuperField)
        if (C == SomeBase)
            return 1;
    return SomeBase == 0;
}

// ---------------------------------------------------------------------------
// 0xe1b50: walk a chain of scopes, each holding a TMap<UObject*,INT>, and
// return the first non-zero value stored for Key. Neutral names: the owning
// class is not identified.
struct TMapPair_e1b50
{
    INT HashNext;
    UObject *Key;
    INT Value;
};

inline DWORD GetTypeHash(const UObject *O) { return O ? O->Index : 0; }

struct TMap_e1b50
{
    TMapPair_e1b50 *Pairs;  // 0x18
    INT PairNum;            // 0x1c
    INT PairMax;            // 0x20
    INT *Hash;              // 0x24
    INT HashCount;          // 0x28
    INT FindRef(UObject *Key)
    {
        for (INT i = Hash[GetTypeHash(Key) & (HashCount - 1)]; i != -1; )
        {
            TMapPair_e1b50 *Pair = &Pairs[i];
            if (Pair->Key == Key)
                return Pair->Value;
            i = Pair->HashNext;
        }
        return 0;
    }
};

struct UnnamedScope_e1b50
{
    INT Pad0;
    UnnamedScope_e1b50 *Next;   // 0x04
    BYTE Pad8[0x18 - 0x08];
    TMap_e1b50 Map;             // 0x18
};

INT FindScopeValue_e1b50(UnnamedScope_e1b50 *Scope, UObject *Key)
{
    INT Result = 0;
    for (; Scope; Scope = Scope->Next)
    {
        Result = Scope->Map.FindRef(Key);
        if (Result)
            break;
    }
    return Result;
}

// ---------------------------------------------------------------------------
// 0xe1ba0 / 0xe1bc0: script event thunks (names 0x9da and 0xa3e not decoded).
class UEventObject_e1ba0 : public UObject
{
public:
    void eventUnnamed_9da();
    void eventUnnamed_a3e();
};
#pragma auto_inline(off)
void UEventObject_e1ba0::eventUnnamed_9da() { ProcessEvent(FindFunctionChecked((EName)0x9da), 0); }
void UEventObject_e1ba0::eventUnnamed_a3e() { ProcessEvent(FindFunctionChecked((EName)0xa3e), 0); }

// ---------------------------------------------------------------------------
// 0xe1be0: find the 8-byte entry for Index in a chain of ranged blocks.
struct FRangeBlock_e1be0
{
    SWORD Base;                 // 0x00
    SWORD Pad2;
    FRangeBlock_e1be0 *Next;    // 0x04
    INT Pad8;
    BYTE (*Data)[8];            // 0x0c
    INT Count;                  // 0x10
};

void *FindRangeEntry_e1be0(FRangeBlock_e1be0 *Block, INT Index)
{
    for (; Block; Block = Block->Next)
        if (Index >= Block->Base && Index < Block->Base + Block->Count)
            return Block->Data[Index - Block->Base];
    return 0;
}

// ---------------------------------------------------------------------------
// 0xe1c10: follow the +0x104 chain to the topmost actor; return it when its
// flag bit is set and it is of the class at 0x10cc6ce8 (class unidentified).
extern UClass GUnnamedClass_e1c10;  // static class object at 0x10cc6ce8

class AActor_e1c10 : public UObject
{
public:
    BYTE Pad28[0x104 - 0x28];
    AActor_e1c10 *Owner104;     // 0x104
    BYTE Pad108[0x2f6 - 0x108];
    BYTE Flags2f6;              // 0x2f6
};

AActor_e1c10 *GetTopOwner_e1c10(AActor_e1c10 *A)
{
    while (A->Owner104)
        A = A->Owner104;
    if ((A->Flags2f6 & 1) && A->IsA(&GUnnamedClass_e1c10))
        return A;
    return 0;
}

// ---------------------------------------------------------------------------
#pragma auto_inline(on)
// Scaffolding for the link, not part of the unit.
void Escape(void *);
INT Driver_e1b50(UnnamedScope_e1b50 *S, UnnamedScope_e1b50 *T, UObject *K)
{
    if (FindScopeValue_e1b50(S, K))
        return FindScopeValue_e1b50(T, K);
    return 0;
}
void Driver_e1ba0(UEventObject_e1ba0 *O) { O->eventUnnamed_9da(); }
void Driver_e1bc0(UEventObject_e1ba0 *O) { O->eventUnnamed_a3e(); }
void *Driver_e1be0(FRangeBlock_e1be0 *B, INT I) { return FindRangeEntry_e1be0(B, I); }
AActor_e1c10 *Driver_e1c10(AActor_e1c10 *A) { return GetTopOwner_e1c10(A); }
