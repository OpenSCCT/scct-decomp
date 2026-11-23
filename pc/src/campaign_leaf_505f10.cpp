// campaign_leaf_505f10.cpp -- constructor at VA 0x10e05f10: its base sets the count at 0x06 to 1;
// allocates an empty array at 0x08 (twelve bytes, tag 6, through virtual slot 4 of the allocator
// at VA 0x1131b3d8), holds a reference to its first argument at 0x0c and to its second at 0x10,
// or, when the second is null, to a new twelve-byte object (tag 5, constructor at VA 0x10e06190)
// whose size word at 0x04 its allocation sets. The class, member and parameter names are
// invented; the offsets, the tags, the vtable and the addresses are the binary's.

#include "campaign_global_1131b3d8.h"

class UnkType_10e05f10_Counted
{
public:
    UnkType_10e05f10_Counted()
        : unk_06(1)
    {
    }
    virtual ~UnkType_10e05f10_Counted();

    void AddRef()
    {
        unk_06++;
    }

    unsigned short unk_04;
    unsigned short unk_06;
};

class UnkType_10e05f10_Array
{
public:
    UnkType_10e05f10_Array()
        : Data(0), Num(0), Max(0x80000000)
    {
    }

    void* operator new(unsigned int Size)
    {
        return GUnk_1131b3d8->VirtualSlot4(Size, 6);
    }

    void* Data;
    int Num;
    unsigned int Max;
};

class UnkType_10e05f10_Object : public UnkType_10e05f10_Counted
{
public:
    UnkType_10e05f10_Object();

    void* operator new(unsigned int Size)
    {
        UnkType_10e05f10_Object* Object =
            (UnkType_10e05f10_Object*)GUnk_1131b3d8->VirtualSlot4(Size, 5);
        Object->unk_04 = (unsigned short)Size;
        return Object;
    }

    int unk_08;
};

class UnkType_10e05f10 : public UnkType_10e05f10_Counted
{
public:
    UnkType_10e05f10(UnkType_10e05f10_Counted* First, UnkType_10e05f10_Counted* Second);

    UnkType_10e05f10_Array* unk_08;
    UnkType_10e05f10_Counted* unk_0c;
    UnkType_10e05f10_Counted* unk_10;
};

// UnkType_10e05f10::UnkType_10e05f10
UnkType_10e05f10::UnkType_10e05f10(UnkType_10e05f10_Counted* First,
                                   UnkType_10e05f10_Counted* Second)
{
    unk_08 = new UnkType_10e05f10_Array;
    unk_0c = First;
    unk_0c->AddRef();
    if ( Second != 0 )
    {
        unk_10 = Second;
        unk_10->AddRef();
    }
    else
    {
        unk_10 = new UnkType_10e05f10_Object;
    }
}
