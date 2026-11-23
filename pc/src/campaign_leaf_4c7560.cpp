// campaign_leaf_4c7560.cpp -- one function at file offset 0x4c7560, preferred VA 0x10dc7560.
// The constructor runs the base constructor at 0x10dc1560 with Value, installs the vtable at
// 0x1113df08, clears the int at offset 0x64 and calls the method at 0x10dc14d0 with 0. The class,
// method, member and parameter names are invented; the offset and the bytes are the binary's.

class UnkType_10dc7560_Base
{
public:
    unsigned char unk_4[0x60];

    UnkType_10dc7560_Base(int Value);

    virtual void VirtualSlot0();

    void Unk_10dc14d0(int State);
};

class UnkType_10dc7560 : public UnkType_10dc7560_Base
{
public:
    int unk_64;

    UnkType_10dc7560(int Value);

    virtual void VirtualSlot0();
};

// UnkType_10dc7560::UnkType_10dc7560
UnkType_10dc7560::UnkType_10dc7560(int Value)
    : UnkType_10dc7560_Base(Value)
{
    unk_64 = 0;
    Unk_10dc14d0(0);
}
