// campaign_leaf_2735e0.cpp -- a member function at VA 0x10b735e0 that returns, by value, a string
// built from the wide-character array at 0x0c (constructor at VA 0x1090ba00). The destructor at VA
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

class UnkType_10b735e0
{
public:
    UnkType_1090ba00 Unk_10b735e0();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    unsigned short unk_0c[16];
};

// UnkType_10b735e0::Unk_10b735e0
UnkType_1090ba00 UnkType_10b735e0::Unk_10b735e0()
{
    return unk_0c;
}
