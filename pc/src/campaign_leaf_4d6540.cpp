// campaign_leaf_4d6540.cpp -- one function at file offset 0x4d6540, preferred VA 0x10dd6540.
// The constructor installs the vtable at 0x11145208 and builds the member at offset 4, whose
// inline constructor stores the result of its method at 0x10dd6030 at its offset 4 and clears its
// offset 8. The class, method and member names are invented; the offset and the bytes are the
// binary's.

class UnkType_10dd6030
{
public:
    int unk_0;
    int unk_4;
    int unk_8;

    UnkType_10dd6030()
    {
        unk_4 = Unk_10dd6030();
        unk_8 = 0;
    }

    int Unk_10dd6030();
};

class UnkType_10dd6540
{
public:
    UnkType_10dd6030 unk_4;

    UnkType_10dd6540();

    virtual void VirtualSlot0();
};

// UnkType_10dd6540::UnkType_10dd6540
UnkType_10dd6540::UnkType_10dd6540()
{
}
