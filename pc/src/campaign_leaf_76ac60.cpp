// campaign_leaf_76ac60.cpp -- one function at file offset 0x76ac60, preferred VA 0x1106ac60. It
// calls the method at VA 0x1105ef00 on the object at 0x68 and the method at VA 0x11067df0 on the
// object at 0x70, each only when its pointer is set. The class, method and member names are
// invented; the offsets and the addresses are the binary's.

class UnkType_1106ac60_First
{
public:
    void Unk_1105ef00();
};

class UnkType_1106ac60_Second
{
public:
    void Unk_11067df0();
};

class UnkType_1106ac60
{
public:
    void Unk_1106ac60();

    unsigned char unk_0[0x68];
    UnkType_1106ac60_First* unk_68;
    int unk_6c;
    UnkType_1106ac60_Second* unk_70;
};

// UnkType_1106ac60::Unk_1106ac60
void UnkType_1106ac60::Unk_1106ac60()
{
    if ( unk_68 != 0 )
    {
        unk_68->Unk_1105ef00();
    }
    if ( unk_70 != 0 )
    {
        unk_70->Unk_11067df0();
    }
}
