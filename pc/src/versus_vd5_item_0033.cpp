// Work item 0033: RVA 0x6a2f0.
// Neutral names: the class owning this constructor is not identified yet.
// It builds a packed code list from a 16-group table of (a,b) pairs and
// links itself into the owner's list at owner+0x40b4.
#include "versus_shader_declaration.h"

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
    FShaderDeclaration Table;
    TArray<DWORD> Codes;
    INT Unknown454;
    FOwner_6a2f0 *Owner;
    UnnamedClass_6a2f0 *Next;

    UnnamedClass_6a2f0(FOwner_6a2f0 *InOwner, const FShaderDeclaration &InTable);
};

UnnamedClass_6a2f0::UnnamedClass_6a2f0(FOwner_6a2f0 *InOwner, const FShaderDeclaration &InTable)
{
    Owner = InOwner;
    Table = InTable;
    for (INT i = 0; i < Table.NumStreams; i++) {
        Codes.AddItem(i | 0x20000000);
        for (INT j = 0; j < Table.Streams[i].NumComponents; j++) {
            DWORD Hi = 0;
            DWORD Lo = 0;
            INT A = Table.Streams[i].Components[j].Type;
            if (A == 0) Hi = 3;
            else if (A == 1) Hi = 2;
            else if (A == 2) Hi = 1;
            else if (A == 3) Hi = 0;
            else if (A == 4) Hi = 4;
            INT B = Table.Streams[i].Components[j].Function;
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
void Driver_6a2f0(void *Mem, FOwner_6a2f0 *O, const FShaderDeclaration *T)
{
    Escape(&GMalloc);
    new (Mem) UnnamedClass_6a2f0(O, *T);
}
