// campaign_leaf_761a30.cpp -- one function at file offset 0x761a30, preferred VA 0x11061a30. It
// calls the method at VA 0x1105eef0 on the object at 0x4c and the method at VA 0x11067db0 on the
// object at 0x44, then stores 1 in the word at 0x8 of the record at 0x48. The class, method and
// member names are invented; the offsets and the addresses are the binary's.

class UnkType_11061a30_First
{
public:
    void Unk_11067db0();
};

class UnkType_11061a30_Second
{
public:
    void Unk_1105eef0();
};

struct UnkType_11061a30_Record
{
    int unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_11061a30
{
public:
    void Unk_11061a30();

    unsigned char unk_0[0x44];
    UnkType_11061a30_First* unk_44;
    UnkType_11061a30_Record* unk_48;
    UnkType_11061a30_Second* unk_4c;
};

// UnkType_11061a30::Unk_11061a30
void UnkType_11061a30::Unk_11061a30()
{
    unk_4c->Unk_1105eef0();
    unk_44->Unk_11067db0();
    unk_48->unk_8 = 1;
}
