// campaign_leaf_35c770.cpp -- one function at file offset 0x35c770, preferred VA 0x10c5c770. It
// calls the method at 0x10bee290 and sets bit 7 of the word at 0x30 of the object at 0x404 when
// there is one. When the objects at 0x7c and 0x3fc are both set, it passes the first entry of
// the object at 0x7c's array at 0x28 with 0 to the method at 0x10a2e5f0 of the object at 0x3fc
// unless its method at 0x10a2c7a0 succeeds, calls its method at 0x10a2dbf0 with 0 and 1 and
// stores this object at its 0x114. It ends by setting the float at 0x470 to -1. The class,
// method, member and parameter names are invented; the offsets, the constants and the bytes are
// the binary's.

class UnkType_10c5c770;

class UnkType_10c5c770_Flags
{
public:
    unsigned char unk_0[0x30];
    int unk_30;
};

class UnkType_10c5c770_Level
{
public:
    unsigned char unk_0[0x28];
    int* unk_28;
};

class UnkType_10c5c770_Controller
{
public:
    int Unk_10a2c7a0();
    void Unk_10a2dbf0(int First, int Second);
    void Unk_10a2e5f0(int First, int Second);

    unsigned char unk_0[0x114];
    UnkType_10c5c770* unk_114;
};

class UnkType_10c5c770
{
public:
    void Unk_10bee290();
    void Unk_10c5c770();

    unsigned char unk_0[0x7c];
    UnkType_10c5c770_Level* unk_7c;
    unsigned char unk_80[0x37c];
    UnkType_10c5c770_Controller* unk_3fc;
    unsigned char unk_400[0x4];
    UnkType_10c5c770_Flags* unk_404;
    unsigned char unk_408[0x68];
    float unk_470;
};

// UnkType_10c5c770::Unk_10c5c770
void UnkType_10c5c770::Unk_10c5c770()
{
    Unk_10bee290();
    if ( unk_404 != 0 )
    {
        unk_404->unk_30 |= 0x80;
    }
    if ( unk_7c != 0 && unk_3fc != 0 )
    {
        if ( !unk_3fc->Unk_10a2c7a0() )
        {
            unk_3fc->Unk_10a2e5f0(unk_7c->unk_28[0], 0);
        }
        unk_3fc->Unk_10a2dbf0(0, 1);
        unk_3fc->unk_114 = this;
    }
    unk_470 = -1.0f;
}
