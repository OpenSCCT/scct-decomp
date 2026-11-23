// campaign_leaf_02cb60.cpp -- method at VA 0x1092cb60: calls the method at VA 0x10b8f950 of its
// base class; then, when the object at 0x3f8 is set and the value at 0x31c of its object at 0x424
// equals its value at 0x41c, clears that value. The class, member and method names are invented;
// the offsets and the address are the binary's.

class UnkType_1092cb60_424
{
public:
    unsigned char unk_000[0x31c];
    int unk_31c;
};

class UnkType_1092cb60_3f8
{
public:
    unsigned char unk_000[0x41c];
    int unk_41c;
    unsigned char unk_420[0x424 - 0x420];
    UnkType_1092cb60_424* unk_424;
};

class UnkType_1092cb60_Base
{
public:
    void Unk_10b8f950();

private:
    unsigned char unk_000[0x3f8];
};

class UnkType_1092cb60 : public UnkType_1092cb60_Base
{
public:
    void Unk_1092cb60();

private:
    UnkType_1092cb60_3f8* unk_3f8;
};

// UnkType_1092cb60::Unk_1092cb60
void UnkType_1092cb60::Unk_1092cb60()
{
    Unk_10b8f950();
    if ( unk_3f8 && unk_3f8->unk_424->unk_31c == unk_3f8->unk_41c )
    {
        unk_3f8->unk_424->unk_31c = 0;
    }
}
