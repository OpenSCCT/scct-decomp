// campaign_leaf_763ff0.cpp -- one function at file offset 0x763ff0, preferred VA 0x11063ff0. It
// calls the method at VA 0x1106cdf0 on the object at 0x68 and the method at VA 0x1106c8f0 on the
// object at 0x6c, each only when its pointer is set. The class, method and member names are
// invented; the offsets and the addresses are the binary's.

class UnkType_11063ff0_First
{
public:
    void Unk_1106cdf0();
};

class UnkType_11063ff0_Second
{
public:
    void Unk_1106c8f0();
};

class UnkType_11063ff0
{
public:
    void Unk_11063ff0();

    unsigned char unk_0[0x68];
    UnkType_11063ff0_First* unk_68;
    UnkType_11063ff0_Second* unk_6c;
};

// UnkType_11063ff0::Unk_11063ff0
void UnkType_11063ff0::Unk_11063ff0()
{
    if ( unk_68 != 0 )
    {
        unk_68->Unk_1106cdf0();
    }
    if ( unk_6c != 0 )
    {
        unk_6c->Unk_1106c8f0();
    }
}
