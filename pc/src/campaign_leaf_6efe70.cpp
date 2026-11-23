// campaign_leaf_6efe70.cpp -- constructor at VA 0x10fefe70 of a class whose vtable is at VA
// 0x1116fdd8, derived from the reference-counted root class (vtable VA 0x110c1d60; size kept at
// 0x04, 16-bit count at 0x06, starting at one). It keeps its first argument at 0x08 and its third
// at 0x10, takes a reference to the first and, when the second is set, keeps it at 0x0c and takes
// a reference to it; otherwise it creates a 0x0c-byte object with the constructor at VA 0x10e06190,
// allocated with tag 5 from the allocator at VA 0x1131b3d8, and keeps that. The class, method and
// member names are invented; the offsets and addresses are the binary's.

#include "campaign_global_1131b3d8.h"

class UnkType_110c1d60_6efe70
{
public:
    UnkType_110c1d60_6efe70()
    {
        unk_6 = 1;
    }

    virtual ~UnkType_110c1d60_6efe70()
    {
    }

    // guess: allocates the object with a tag and keeps its size at 0x04 for operator delete.
    void* operator new(unsigned int Size, int Tag)
    {
        UnkType_110c1d60_6efe70* Object;

        Object = (UnkType_110c1d60_6efe70*)GUnk_1131b3d8->VirtualSlot4(Size, Tag);
        Object->unk_4 = (unsigned short)Size;
        return Object;
    }

    // guess: takes one reference.
    void AddRef()
    {
        unk_6++;
    }

    unsigned short unk_4;
    unsigned short unk_6;
};

class UnkType_10fefe70_Member : public UnkType_110c1d60_6efe70
{
public:
    UnkType_10fefe70_Member();

private:
    int unk_8;
};

class UnkType_10fefe70 : public UnkType_110c1d60_6efe70
{
public:
    UnkType_10fefe70(UnkType_110c1d60_6efe70* First, UnkType_110c1d60_6efe70* Second, int Third);
    virtual ~UnkType_10fefe70();

private:
    UnkType_110c1d60_6efe70* unk_8;
    UnkType_110c1d60_6efe70* unk_c;
    int unk_10;
};

// UnkType_10fefe70::UnkType_10fefe70
UnkType_10fefe70::UnkType_10fefe70(UnkType_110c1d60_6efe70* First,
                                   UnkType_110c1d60_6efe70* Second, int Third)
    : unk_8(First), unk_10(Third)
{
    unk_8->AddRef();
    if ( Second )
    {
        unk_c = Second;
        unk_c->AddRef();
    }
    else
    {
        unk_c = new(5) UnkType_10fefe70_Member();
    }
}
