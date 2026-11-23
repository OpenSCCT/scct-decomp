// campaign_leaf_4bbe20.cpp -- one function at file offset 0x4bbe20, preferred VA 0x10dbbe20.
// It calls the method at 0x10d998b0 on each of the members at offsets 0x18, 0x2c and 0x40. The
// class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10dbbe20_Member
{
public:
    unsigned char unk_0[0x14];

    void Unk_10d998b0();
};

class UnkType_10dbbe20
{
public:
    unsigned char unk_0[0x18];
    UnkType_10dbbe20_Member unk_18;
    UnkType_10dbbe20_Member unk_2c;
    UnkType_10dbbe20_Member unk_40;

    void Unk_10dbbe20();
};

// UnkType_10dbbe20::Unk_10dbbe20
void UnkType_10dbbe20::Unk_10dbbe20()
{
    unk_18.Unk_10d998b0();
    unk_2c.Unk_10d998b0();
    unk_40.Unk_10d998b0();
}
