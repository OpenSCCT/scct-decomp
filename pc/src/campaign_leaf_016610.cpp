// campaign_leaf_016610.cpp -- method at VA 0x10916610: returns by value what the method at VA
// 0x10d09ff0 of the member at 0x40 of the object at 0x08 returns for the value the method at VA
// 0x10d0a520 of that member returns for this object. The class, member and method names are
// invented; the offsets and the addresses are the binary's.

class UnkType_10d09ff0_016610
{
public:
    UnkType_10d09ff0_016610(const UnkType_10d09ff0_016610& Other);
    ~UnkType_10d09ff0_016610();

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10916610;

class UnkType_10d0a520_016610
{
public:
    int Unk_10d0a520(UnkType_10916610* Object);
    UnkType_10d09ff0_016610 Unk_10d09ff0(int Value);
};

class UnkType_10916610_08
{
public:
    unsigned char unk_00[0x40];
    UnkType_10d0a520_016610 unk_40;
};

class UnkType_10916610
{
public:
    UnkType_10d09ff0_016610 Unk_10916610();

private:
    unsigned char unk_00[0x08];
    UnkType_10916610_08* unk_08;
};

// UnkType_10916610::Unk_10916610
UnkType_10d09ff0_016610 UnkType_10916610::Unk_10916610()
{
    return unk_08->unk_40.Unk_10d09ff0(unk_08->unk_40.Unk_10d0a520(this));
}
