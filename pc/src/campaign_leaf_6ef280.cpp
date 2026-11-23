// campaign_leaf_6ef280.cpp -- thiscall method at VA 0x10fef280: copies the eight-byte global at VA
// 0x1116fe70 into a local and passes its address and 7 to virtual slot 2 of the object at 0x08. The
// class, method, member and global names are invented; the offsets and addresses are the binary's.

#include "campaign_global_1116fe70.h"

class UnkType_10fef280_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2(UnkType_1116fe70* Value, int Kind);
};

class UnkType_10fef280
{
public:
    void Unk_10fef280();

private:
    int unk_00;
    int unk_04;
    UnkType_10fef280_Target* unk_08;
};

// UnkType_10fef280::Unk_10fef280
void UnkType_10fef280::Unk_10fef280()
{
    UnkType_1116fe70 Value = GUnk_1116fe70;

    unk_08->VirtualSlot2(&Value, 7);
}
