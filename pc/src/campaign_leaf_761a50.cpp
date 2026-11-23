// campaign_leaf_761a50.cpp -- one function at file offset 0x761a50, preferred VA 0x11061a50. It
// clears the word at 0x8 of the record at 0x48, then calls the method at VA 0x11067df0 on the
// object at 0x44 and the method at VA 0x1105ef00 on the object at 0x4c. The class, method and
// member names are invented; the offsets and the addresses are the binary's.

class UnkType_11061a50_First
{
public:
    void Unk_11067df0();
};

class UnkType_11061a50_Second
{
public:
    void Unk_1105ef00();
};

struct UnkType_11061a50_Record
{
    int unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_11061a50
{
public:
    void Unk_11061a50();

    unsigned char unk_0[0x44];
    UnkType_11061a50_First* unk_44;
    UnkType_11061a50_Record* unk_48;
    UnkType_11061a50_Second* unk_4c;
};

// UnkType_11061a50::Unk_11061a50
void UnkType_11061a50::Unk_11061a50()
{
    unk_48->unk_8 = 0;
    unk_44->Unk_11067df0();
    unk_4c->Unk_1105ef00();
}
