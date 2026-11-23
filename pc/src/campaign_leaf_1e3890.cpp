// campaign_leaf_1e3890.cpp -- thiscall method at VA 0x10ae3890. For every entry of the pointer
// vector at 0x30 whose object at 0x04 has bit 0x2000000 set in its word at 0x30, it appends that
// object to the array at 0x40 (grown through the allocator at VA 0x111c88a0, tag "FArray"), then
// sorts the array's 4-byte items through the function at VA 0x10ccaf10 with the comparison at VA
// 0x10ae31f0. The class, method and member names are invented; the vector is the compiler's
// library.

#include <vector>

#include "campaign_global_111c88a0.h"

struct UnkType_10ae3890_Object
{
    char unk_00[0x30];
    int unk_30;
};

struct UnkType_10ae3890_Entry
{
    int unk_00;
    UnkType_10ae3890_Object* unk_04;
};

void Unk_10ccaf10(void* Data, int Count, int Size, int (*Compare)(const void*, const void*));
int Unk_10ae31f0(const void* First, const void* Second);

template<class T> class UnkType_10ae3890_Array
{
public:
    T* Data;
    int ArrayNum;
    int ArrayMax;

    // UnkType_10ae3890_Array::AddItem
    int AddItem(const T& Item)
    {
        int Index = ArrayNum;
        if ( ++ArrayNum > ArrayMax )
        {
            ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 2;
            Data = (T*)GUnk_111c88a0->Realloc(Data, ArrayMax * sizeof(T), L"FArray");
        }
        Data[Index] = Item;
        return Index;
    }
};

class UnkType_10ae3890
{
public:
    void Unk_10ae3890();

private:
    char unk_00[0x30];
    std::vector<UnkType_10ae3890_Entry*> unk_30;
    UnkType_10ae3890_Array<UnkType_10ae3890_Object*> unk_40;
};

// UnkType_10ae3890::Unk_10ae3890
void UnkType_10ae3890::Unk_10ae3890()
{
    std::vector<UnkType_10ae3890_Entry*>::iterator It;

    for ( It = unk_30.begin(); It != unk_30.end(); ++It )
    {
        UnkType_10ae3890_Entry* Entry = *It;
        if ( Entry->unk_04->unk_30 & 0x2000000 )
        {
            unk_40.AddItem(Entry->unk_04);
        }
    }
    Unk_10ccaf10(unk_40.Data, unk_40.ArrayNum, sizeof(UnkType_10ae3890_Object*), Unk_10ae31f0);
}
