// campaign_leaf_4a4bb0.cpp -- one function at file offset 0x4a4bb0, preferred VA 0x10da4bb0.
// The constructor runs the base constructor at 0x10db4400, installs the vtable at 0x1113e810 and
// builds the member at offset 0x44 with the constructor at 0x10dd5340. The class and member names
// are invented; the offset and the bytes are the binary's.

class UnkType_10da4bb0_Base
{
public:
    unsigned char unk_4[0x40];

    UnkType_10da4bb0_Base();

    virtual void VirtualSlot0();
};

class UnkType_10da4bb0_Member
{
public:
    int unk_0;

    UnkType_10da4bb0_Member();
};

class UnkType_10da4bb0 : public UnkType_10da4bb0_Base
{
public:
    UnkType_10da4bb0_Member unk_44;

    UnkType_10da4bb0();

    virtual void VirtualSlot0();
};

// UnkType_10da4bb0::UnkType_10da4bb0
UnkType_10da4bb0::UnkType_10da4bb0()
{
}
