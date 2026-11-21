// Work item 0244: Versus RVA 0x5a890. Link-time optimised (/GL + /LTCG).
// The owning class and the key record are not recovered; names are neutral.
typedef int INT;
typedef unsigned long DWORD;

class UObject
{
public:
    virtual ~UObject();
    INT Index;
    INT GetIndex() const { return Index; }
};

inline DWORD GetTypeHash(const UObject* A) { return A ? A->GetIndex() : 0; }

// TMap<UObject*,INT> pair (12 bytes).
struct FObjectPair
{
    INT HashNext;
    UObject* Key;
    INT Value;
};

// TMap<UObject*,INT>; declarations follow work item 0246.
class FObjectMap
{
public:
    FObjectPair* Pairs;
    INT ArrayNum;
    INT ArrayMax;
    INT* Hash;
    INT HashCount;

    INT* Find(UObject* const& Key);
};

#pragma auto_inline(off)
// RVA 0x5abe0 (matched in item 0246; defined here so the LTCG link sees its body).
INT* FObjectMap::Find(UObject* const& Key)
{
    for (INT i = Hash[GetTypeHash(Key) & (HashCount - 1)]; i != -1; i = Pairs[i].HashNext)
        if (Pairs[i].Key == Key)
            return &Pairs[i].Value;
    return 0;
}
#pragma auto_inline(on)

// Entry of the array at +0x28 (0x44 bytes): a range Base..Base+Count.
struct UnnamedEntry_5a890
{
    char Pad0[0x28];
    INT  Base;      // +0x28
    INT  Count;     // +0x2c
    char Pad1[0x14];
};

// Record passed in: an object and an index relative to that object's range.
struct UnnamedKey_5a890
{
    char     Pad0[0x10];
    UObject* Object;    // +0x10
    INT      Index;     // +0x14
};

class TEntryArray_5a890
{
public:
    UnnamedEntry_5a890* Data;
    INT ArrayNum;
    INT ArrayMax;
    UnnamedEntry_5a890& operator()(INT i) { return Data[i]; }
};

class UnnamedClass_5a890
{
public:
    char                Pad0[0x28];
    TEntryArray_5a890   Entries;   // +0x28
    char                Pad1[0x14];
    FObjectMap          EntryMap;  // +0x48

    INT GetIndex(UnnamedKey_5a890* K);
};

#pragma auto_inline(off)
// RVA 0x5a890
INT UnnamedClass_5a890::GetIndex(UnnamedKey_5a890* K)
{
    // The object is read through an integer temporary; the plain pointer
    // ternary lets the compiler fold the null test into the branch.
    INT ObjectBits = K ? (INT)K->Object : 0;
    UObject* Object = (UObject*)ObjectBits;
    if (Object && K->Index != -1)
    {
        INT* Found = EntryMap.Find(Object);
        if (Found)
        {
            UnnamedEntry_5a890& Entry = Entries(*Found);
            if (K->Index < Entry.Count)
                return Entry.Base + K->Index;
        }
    }
    return -1;
}
#pragma auto_inline(on)

// Scaffolding for the LTCG link, not part of the unit. Retail GetIndex keeps
// the standard thiscall convention, so its address escapes here.
void Escape(void*);
INT Driver_5a890(UnnamedClass_5a890* C, UnnamedKey_5a890* K)
{
    INT (UnnamedClass_5a890::*Fn)(UnnamedKey_5a890*) = &UnnamedClass_5a890::GetIndex;
    Escape(&Fn);
    return C->GetIndex(K);
}
