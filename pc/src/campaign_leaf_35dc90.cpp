// campaign_leaf_35dc90.cpp -- one function at file offset 0x35dc90, preferred VA 0x10c5dc90. By
// the byte at 0x428 it either copies the words at 0x414, 0x41c and 0x420 from the object at
// 0x29c of the object at 0x24 (kind 0) or sets them to 180, 175.0 and 0.1 (kind 1); it then
// passes the float at 0x41c twice and 0 to the method at 0x10995a00. The class, method, member
// and local names are invented; the offsets, the constants and the bytes are the binary's.

class UnkType_10c5dc90_Defaults
{
public:
    unsigned char unk_0[0x414];
    int unk_414;
    unsigned char unk_418[0x4];
    float unk_41c;
    float unk_420;
};

class UnkType_10c5dc90_Owner
{
public:
    unsigned char unk_0[0x29c];
    UnkType_10c5dc90_Defaults* unk_29c;
};

class UnkType_10c5dc90
{
public:
    void Unk_10995a00(float First, float Second, int Third);
    void Unk_10c5dc90();

    unsigned char unk_0[0x24];
    UnkType_10c5dc90_Owner* unk_24;
    unsigned char unk_28[0x3ec];
    int unk_414;
    unsigned char unk_418[0x4];
    float unk_41c;
    float unk_420;
    unsigned char unk_424[0x4];
    unsigned char unk_428;
};

// UnkType_10c5dc90::Unk_10c5dc90
void UnkType_10c5dc90::Unk_10c5dc90()
{
    UnkType_10c5dc90_Defaults* Defaults = unk_24->unk_29c;

    switch ( unk_428 )
    {
    case 0:
        unk_414 = Defaults->unk_414;
        unk_41c = Defaults->unk_41c;
        unk_420 = Defaults->unk_420;
        break;
    case 1:
        unk_414 = 180;
        unk_41c = 175.0f;
        unk_420 = 0.1f;
        break;
    }
    Unk_10995a00(unk_41c, unk_41c, 0);
}
