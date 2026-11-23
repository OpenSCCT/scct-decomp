// campaign_leaf_6eff70.cpp -- constructor at VA 0x10feff70 of a class whose vtable is at VA
// 0x1116fff0: runs the base constructor at VA 0x10e066f0 with its second argument, then creates
// a 0x10-byte object with the constructor at VA 0x11091af0 and its first argument, and keeps it at
// 0x0c. Both classes share the base's operator new, which allocates with tag 6 from the allocator
// at VA 0x1131b3d8 and keeps the size at 0x04. The class and member names are invented; the
// offsets and addresses are the binary's.

#include "campaign_global_1131b3d8.h"

class UnkType_10feff70_Base
{
public:
    UnkType_10feff70_Base(int First);
    virtual ~UnkType_10feff70_Base();

    // guess: allocates the object and keeps its size at 0x04 for operator delete.
    void* operator new(unsigned int Size)
    {
        UnkType_10feff70_Base* Object;

        Object = (UnkType_10feff70_Base*)GUnk_1131b3d8->VirtualSlot4(Size, 6);
        Object->unk_4 = (unsigned short)Size;
        return Object;
    }

private:
    unsigned short unk_4;
    unsigned short unk_6;
    int unk_8;
};

class UnkType_10feff70_Member : public UnkType_10feff70_Base
{
public:
    UnkType_10feff70_Member(int First);

private:
    int unk_c;
};

class UnkType_10feff70 : public UnkType_10feff70_Base
{
public:
    UnkType_10feff70(int First, int Second);
    virtual ~UnkType_10feff70();

private:
    UnkType_10feff70_Member* unk_c;
};

// UnkType_10feff70::UnkType_10feff70
UnkType_10feff70::UnkType_10feff70(int First, int Second)
    : UnkType_10feff70_Base(Second)
{
    unk_c = new UnkType_10feff70_Member(First);
}
