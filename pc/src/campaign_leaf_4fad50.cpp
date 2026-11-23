// campaign_leaf_4fad50.cpp -- method at VA 0x10dfad50: fills a local object from the member at 0x14
// (function at VA 0x10dfb5e0), passes it to virtual slot 2, and stores at 0x228 the result of the
// method at VA 0x10dcddb0 called on the object the local's method at VA 0x10d9d680 returns. The
// class, method and member names are invented; the offsets, slot and addresses are the binary's.

class UnkType_10dfad50_Result
{
public:
    int Unk_10dcddb0();
};

class UnkType_10dfad50_Local
{
public:
    UnkType_10dfad50_Local();
    ~UnkType_10dfad50_Local();
    UnkType_10dfad50_Result* Unk_10d9d680();

    unsigned char unk_00[0x30];
};

class UnkType_10dfad50
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2(UnkType_10dfad50_Local* Local);

    void Unk_10dfad50();

    unsigned char unk_04[0x10];
    int unk_14;
    unsigned char unk_18[0x210];
    int unk_228;
};

void Unk_10dfb5e0(UnkType_10dfad50_Local* Local, int* Source);

// UnkType_10dfad50::Unk_10dfad50
void UnkType_10dfad50::Unk_10dfad50()
{
    UnkType_10dfad50_Local Local;
    Unk_10dfb5e0(&Local, &unk_14);
    VirtualSlot2(&Local);
    unk_228 = Local.Unk_10d9d680()->Unk_10dcddb0();
}
