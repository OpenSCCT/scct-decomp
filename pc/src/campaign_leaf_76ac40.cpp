// campaign_leaf_76ac40.cpp -- one function at file offset 0x76ac40, preferred VA 0x1106ac40. It
// calls the method at VA 0x1105eef0 on the object at 0x68 and the method at VA 0x11067db0 on the
// object at 0x70. The class, method and member names are invented; the offset and the addresses
// are the binary's.

class UnkType_1105eef0
{
public:
    void Unk_1105eef0();
};

class UnkType_11067db0
{
public:
    void Unk_11067db0();
};

class UnkType_1106ac40
{
public:
    void Unk_1106ac40();

    unsigned char unk_0[0x68];
    UnkType_1105eef0* unk_68;
    int unk_6c;
    UnkType_11067db0* unk_70;
};

// UnkType_1106ac40::Unk_1106ac40
void UnkType_1106ac40::Unk_1106ac40()
{
    unk_68->Unk_1105eef0();
    unk_70->Unk_11067db0();
}
