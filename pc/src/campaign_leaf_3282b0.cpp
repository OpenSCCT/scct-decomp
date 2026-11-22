// campaign_leaf_3282b0.cpp -- a member function at VA 0x10c282b0 that passes the empty wide
// string to the member at VA 0x10992290 of the object at 0xe0. The class, method and member names
// are invented; the offsets and addresses are the binary's.

class UnkType_10992290
{
public:
    void Unk_10992290(const unsigned short* Text);
};

class UnkType_10c282b0
{
public:
    void Unk_10c282b0();

private:
    unsigned char unk_00[0xe0];
    UnkType_10992290 unk_e0;
};

// UnkType_10c282b0::Unk_10c282b0
void UnkType_10c282b0::Unk_10c282b0()
{
    unk_e0.Unk_10992290(L"");
}
