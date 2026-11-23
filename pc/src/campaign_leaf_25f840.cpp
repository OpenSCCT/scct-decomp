// campaign_leaf_25f840.cpp -- a member function at VA 0x10b5f840: when the byte at 0x3c is already
// set it returns true; otherwise, when the member at VA 0x10b64590 accepts its argument, it clears
// bit 0 of the byte at 0x18 of the objects the pointers at 0x5c, 0x6c and 0x70 refer to, sets the
// byte at 0xb6 of the object the pointer at 0x60 refers to and takes the result of the member at
// VA 0x10b5f6c0. It stores and returns that result. The class, method and member names are
// invented; the offsets and addresses are the binary's.

class UnkType_10b5f840_Item
{
public:
    unsigned char unk_00[0x18];
    unsigned char unk_18;
};

class UnkType_10b5f840_Target
{
public:
    unsigned char unk_00[0xb6];
    bool unk_b6;
};

class UnkType_10b5f840
{
public:
    bool Unk_10b64590(int Value);
    bool Unk_10b5f6c0();
    bool Unk_10b5f840(int Value);

private:
    unsigned char unk_00[0x3c];
    bool unk_3c;
    unsigned char unk_3d[0x5c - 0x3d];
    UnkType_10b5f840_Item* unk_5c;
    UnkType_10b5f840_Target* unk_60;
    unsigned char unk_64[0x6c - 0x64];
    UnkType_10b5f840_Item* unk_6c;
    UnkType_10b5f840_Item* unk_70;
};

// UnkType_10b5f840::Unk_10b5f840
bool UnkType_10b5f840::Unk_10b5f840(int Value)
{
    if ( unk_3c )
    {
        return true;
    }
    bool Result = false;
    if ( Unk_10b64590(Value) )
    {
        unk_5c->unk_18 &= ~1;
        unk_6c->unk_18 &= ~1;
        unk_70->unk_18 &= ~1;
        unk_60->unk_b6 = true;
        Result = Unk_10b5f6c0();
    }
    unk_3c = Result;
    return Result;
}
