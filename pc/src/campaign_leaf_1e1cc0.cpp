// campaign_leaf_1e1cc0.cpp -- destructor at VA 0x10ae1cc0 of a tree node. It deletes the child
// nodes at 0x20 and 0x24 (each destroyed by this destructor, its memory released through the
// function at VA 0x109014a0) and the array object at 0x1c: its method at VA 0x10ae0a90 removes all
// its 4-byte elements, its data and then the object itself are freed through slot 2 of the
// allocator at VA 0x111c88a0, and its three words are cleared in between. The class, method and
// member names are invented.

#include "campaign_global_111c88a0.h"

void operator delete(void* Original);

class UnkType_10ae1cc0_Array
{
public:
    // UnkType_10ae1cc0_Array::~UnkType_10ae1cc0_Array
    ~UnkType_10ae1cc0_Array()
    {
        Unk_10ae0a90(0, unk_4, 4);
        if ( unk_0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_4 = unk_8 = 0;
    }

    // UnkType_10ae1cc0_Array::operator delete
    void operator delete(void* Original)
    {
        GUnk_111c88a0->Free(Original);
    }

    void Unk_10ae0a90(int Index, int Count, int ElementSize);

private:
    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10ae1cc0
{
public:
    ~UnkType_10ae1cc0();

private:
    char unk_00[0x1c];
    UnkType_10ae1cc0_Array* unk_1c;
    UnkType_10ae1cc0* unk_20;
    UnkType_10ae1cc0* unk_24;
};

// UnkType_10ae1cc0::~UnkType_10ae1cc0
UnkType_10ae1cc0::~UnkType_10ae1cc0()
{
    delete unk_20;
    delete unk_24;
    delete unk_1c;
}
