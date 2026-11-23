// campaign_leaf_140480.cpp -- one function at file offset 0x140480, preferred VA 0x10a40480.
// guess: adds a pointer to an array unless the array already holds it, growing the array through
// the allocator at VA 0x111c88a0 (tag "FArray") when it is full.
// The class, function, parameter and member names are invented; the offset and the bytes are the
// binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a40480_Item;

class UnkType_10a40480
{
public:
    UnkType_10a40480_Item** Data;
    int ArrayNum;
    int ArrayMax;
};

// Unk_10a40480
void Unk_10a40480(UnkType_10a40480_Item* Item, UnkType_10a40480& Array)
{
    for ( int i = 0; i < Array.ArrayNum; i++ )
    {
        if ( Array.Data[i] == Item )
        {
            return;
        }
    }
    int Index = Array.ArrayNum++;
    if ( Array.ArrayNum > Array.ArrayMax )
    {
        Array.ArrayMax = Array.ArrayNum + 3 * Array.ArrayNum / 8 + 2;
        Array.Data = (UnkType_10a40480_Item**)GUnk_111c88a0->Realloc(Array.Data,
            Array.ArrayMax * sizeof(UnkType_10a40480_Item*), L"FArray");
    }
    Array.Data[Index] = Item;
}
