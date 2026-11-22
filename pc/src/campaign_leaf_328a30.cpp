// campaign_leaf_328a30.cpp -- a member function at VA 0x10c28a30 that returns, by value, a copy of
// the 12-byte string member at 0xe0 (copy constructor at VA 0x1090b9a0). The destructor at VA
// 0x1090ba70 names the string class. The class, method and member names are invented; the offsets
// and addresses are the binary's.

class UnkType_1090ba00
{
public:
    UnkType_1090ba00(const unsigned short* Text);
    UnkType_1090ba00(const UnkType_1090ba00& Other);
    ~UnkType_1090ba00();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10c28a30
{
public:
    UnkType_1090ba00 Unk_10c28a30();

private:
    unsigned char unk_00[0xe0];
    UnkType_1090ba00 unk_e0;
};

// UnkType_10c28a30::Unk_10c28a30
UnkType_1090ba00 UnkType_10c28a30::Unk_10c28a30()
{
    return unk_e0;
}
