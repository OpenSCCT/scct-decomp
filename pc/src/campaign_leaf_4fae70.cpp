// campaign_leaf_4fae70.cpp -- method at VA 0x10dfae70: when the handle at 0x10 is set, fills a
// local object from the member at 0x14 (function at VA 0x10dfb5e0), passes it to virtual slot 2,
// and returns whether virtual slot 4 of the handle, called with 0, the word at 0x228 and the result
// of the method at VA 0x10dcdda0 on the local's 0x10d9d680 result, returns that word. The class,
// method and member names are invented; the offsets, slots and addresses are the binary's.

class UnkType_10dfae70_Result
{
public:
    int Unk_10dcdda0();
};

class UnkType_10dfae70_Local
{
public:
    UnkType_10dfae70_Local();
    ~UnkType_10dfae70_Local();
    UnkType_10dfae70_Result* Unk_10d9d680();

    unsigned char unk_00[0x30];
};

class UnkType_10dfae70_Device
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual int VirtualSlot4(int Arg0, int Arg1, int Arg2);
};

class UnkType_10dfae70
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2(UnkType_10dfae70_Local* Local);

    bool Unk_10dfae70();

    unsigned char unk_04[0x0c];
    UnkType_10dfae70_Device* unk_10;
    int unk_14;
    unsigned char unk_18[0x210];
    int unk_228;
};

void Unk_10dfb5e0(UnkType_10dfae70_Local* Local, int* Source);

// UnkType_10dfae70::Unk_10dfae70
bool UnkType_10dfae70::Unk_10dfae70()
{
    if ( !unk_10 )
    {
        return false;
    }
    UnkType_10dfae70_Local Local;
    Unk_10dfb5e0(&Local, &unk_14);
    VirtualSlot2(&Local);
    return unk_10->VirtualSlot4(0, unk_228, Local.Unk_10d9d680()->Unk_10dcdda0()) == unk_228;
}
