// campaign_leaf_4f5c90.cpp -- method at VA 0x10df5c90: passes itself to the method at VA 0x10df8a20
// of its member at 0x844 and then to the method at VA 0x10df9c10 of its member at 0x48. The class,
// method and parameter names are invented; the offsets and the addresses are the binary's.

class UnkType_10df5c90;

class UnkType_10df5c90_Stream;

class UnkType_10df5c90_Part48
{
public:
    void Unk_10df9c10(UnkType_10df5c90* Owner);
};

class UnkType_10df5c90_Part844
{
public:
    void Unk_10df8a20(UnkType_10df5c90* Owner);
};

class UnkType_10df5c90
{
public:
    void Unk_10df5c90();

    unsigned char unk_00[0x48];
    UnkType_10df5c90_Part48 unk_48;
    unsigned char unk_49[0x844 - 0x49];
    UnkType_10df5c90_Part844 unk_844;
};

// UnkType_10df5c90::Unk_10df5c90
void UnkType_10df5c90::Unk_10df5c90()
{
    unk_844.Unk_10df8a20(this);
    unk_48.Unk_10df9c10(this);
}
