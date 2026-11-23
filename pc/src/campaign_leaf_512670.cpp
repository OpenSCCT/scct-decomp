// campaign_leaf_512670.cpp -- destructor at VA 0x10e12670: destroys the three arrays at 0x20, 0x14
// and 0x08 (elements of 1, 16 and 4 bytes), each of which frees its data through virtual slot 5 of
// the allocator at VA 0x1131b3d8 with the tag 0x12 unless its capacity word is negative. The class
// and member names are invented; the offsets, slot, tag and addresses are the binary's.

#include "campaign_global_1131b3d8.h"

template<class T> class UnkType_10e12670_Array
{
public:
    ~UnkType_10e12670_Array()
    {
        if ( !( Max & 0x80000000 ) )
        {
            GUnk_1131b3d8->VirtualSlot5(Data, ( Max & 0x7fffffff ) * sizeof(T), 0x12);
        }
    }

    T* Data;
    int Num;
    unsigned int Max;
};

class UnkType_10e12670_Item
{
public:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

class UnkType_10e12670
{
public:
    ~UnkType_10e12670();

    int unk_00;
    int unk_04;
    UnkType_10e12670_Array<int> unk_08;
    UnkType_10e12670_Array<UnkType_10e12670_Item> unk_14;
    UnkType_10e12670_Array<unsigned char> unk_20;
};

// UnkType_10e12670::~UnkType_10e12670
UnkType_10e12670::~UnkType_10e12670()
{
}
