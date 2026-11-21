// Work item 0033: RVA 0x6a2f0.
// Neutral names: the class owning this constructor is not identified yet.
// It builds a packed code list from a 16-group table of (a,b) pairs and
// links itself into the owner's list at owner+0x40b4.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
};
extern FMalloc *GMalloc;

template<class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    TArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~TArray();
    INT Add()
    {
        INT Index = ArrayNum;
        if (++ArrayNum > ArrayMax) {
            ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 32;
            if (Data == 0)
                Data = (T *)GMalloc->Malloc(ArrayMax * sizeof(T), L"FArray::Add");
            else
                Data = (T *)GMalloc->Realloc(Data, ArrayMax * sizeof(T), L"FArray");
        }
        return Index;
    }
    INT AddItem(const T &Item)
    {
        INT Index = Add();
        Data[Index] = Item;
        return Index;
    }
};

struct FPair_6a2f0
{
    INT A;
    INT B;
    FPair_6a2f0(); // 0x68f30
};

struct FGroup_6a2f0
{
    FPair_6a2f0 Pairs[8];
    INT NumPairs;
    FGroup_6a2f0() : NumPairs(0) {}
};

// 0x444 bytes, initialised by its constructor (FUN_1096ac30).
class FTable_6a2f0
{
public:
    FGroup_6a2f0 Groups[16];
    INT NumGroups;
    FTable_6a2f0();
};

// RVA 0x6ac30 (not part of this item; defined here so the LTCG link gives it
// the same this-on-stack convention retail uses at the call site).
FTable_6a2f0::FTable_6a2f0()
{
    NumGroups = 0;
}

class UnnamedClass_6a2f0;

struct FOwner_6a2f0
{
    char Pad[0x40b4];
    UnnamedClass_6a2f0 *List;
};

class UnnamedClass_6a2f0
{
public:
    INT Unknown0;
    FTable_6a2f0 Table;
    TArray<DWORD> Codes;
    INT Unknown454;
    FOwner_6a2f0 *Owner;
    UnnamedClass_6a2f0 *Next;

    UnnamedClass_6a2f0(FOwner_6a2f0 *InOwner, const FTable_6a2f0 &InTable);
};

UnnamedClass_6a2f0::UnnamedClass_6a2f0(FOwner_6a2f0 *InOwner, const FTable_6a2f0 &InTable)
{
    Owner = InOwner;
    Table = InTable;
    for (INT i = 0; i < Table.NumGroups; i++) {
        Codes.AddItem(i | 0x20000000);
        for (INT j = 0; j < Table.Groups[i].NumPairs; j++) {
            DWORD Hi = 0;
            DWORD Lo = 0;
            INT A = Table.Groups[i].Pairs[j].A;
            if (A == 0) Hi = 3;
            else if (A == 1) Hi = 2;
            else if (A == 2) Hi = 1;
            else if (A == 3) Hi = 0;
            else if (A == 4) Hi = 4;
            INT B = Table.Groups[i].Pairs[j].B;
            if (B == 0) Lo = 0;
            else if (B == 1) Lo = 3;
            else if (B == 2) Lo = 5;
            else if (B == 3) Lo = 6;
            else if (B == 4) Lo = 7;
            else if (B == 5) Lo = 8;
            else if (B == 6) Lo = 9;
            else if (B == 7) Lo = 10;
            else if (B == 8) Lo = 11;
            else if (B == 9) Lo = 12;
            else if (B == 10) Lo = 13;
            else if (B == 11) Lo = 14;
            Codes.AddItem(((Hi | 0x4000) << 16) | Lo);
        }
    }
    Codes.AddItem(0xffffffff);
    Next = Owner->List;
    Owner->List = this;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *Mem) { return Mem; }
inline void operator delete(void *, void *) {}
void Driver_6a2f0(void *Mem, FOwner_6a2f0 *O, const FTable_6a2f0 *T)
{
    Escape(&GMalloc);
    new (Mem) UnnamedClass_6a2f0(O, *T);
}
