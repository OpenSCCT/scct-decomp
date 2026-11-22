// campaign_leaf_277cc0.cpp -- a member function at VA 0x10b77cc0: when the byte at 0x22 is set it
// calls the member at VA 0x10b77850 with 1; it stores whether it did in the byte at 0x14 of the
// object the pointer at 0x1c refers to and returns it. It does not read its argument. The class,
// method and member names are invented; the offsets and addresses are the binary's.

class UnkType_10b77cc0_Item
{
public:
    unsigned char unk_00[0x14];
    bool unk_14;
};

class UnkType_10b77cc0
{
public:
    void Unk_10b77850(int Value);
    bool Unk_10b77cc0(int Unused);

private:
    unsigned char unk_00[0x1c];
    UnkType_10b77cc0_Item* unk_1c;
    unsigned char unk_20[2];
    bool unk_22;
};

// UnkType_10b77cc0::Unk_10b77cc0
bool UnkType_10b77cc0::Unk_10b77cc0(int Unused)
{
    bool Result = false;
    if ( unk_22 )
    {
        Unk_10b77850(1);
        Result = true;
    }
    unk_1c->unk_14 = Result;
    return Result;
}
