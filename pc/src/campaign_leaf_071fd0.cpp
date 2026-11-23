// campaign_leaf_071fd0.cpp -- constructor at VA 0x10971fd0 of a class whose vtable is at VA
// 0x110c0b10: runs the base constructor at VA 0x10cd7930; constructs the array member at 0x28
// cleared, with its data allocated for its capacity of 0 through virtual slot 1 of the allocator
// the global at VA 0x111c88a0 points to, tagged "FArray"; and stores this object at 0x34. The
// class and member names are invented; the offsets, the tag and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10971fd0_Base
{
public:
    UnkType_10971fd0_Base();
    virtual void Malloc();

private:
    unsigned char unk_04[0x24];
};

class UnkType_111c88a0_071fd0
{
public:
    UnkType_111c88a0_071fd0()
    : unk_00(0)
    , unk_04(0)
    , unk_08(0)
    {
        unk_00 = GUnk_111c88a0->Realloc(unk_00, unk_08 * 4, L"FArray");
    }

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10971fd0 : public UnkType_10971fd0_Base
{
public:
    UnkType_10971fd0();
    virtual void Malloc();

private:
    UnkType_111c88a0_071fd0 unk_28;
    UnkType_10971fd0* unk_34;
};

// UnkType_10971fd0::UnkType_10971fd0
UnkType_10971fd0::UnkType_10971fd0()
: unk_34(this)
{
}
