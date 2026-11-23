// campaign_leaf_254d20.cpp -- a member function at VA 0x10b54d20: when the byte at 0x3c is already
// set it returns true; otherwise, when the member at VA 0x10b65b30 accepts its argument, it calls
// the member at VA 0x10d2a530 of the object the pointer at 0x40 refers to with 1 and 1, sets that
// object's byte at 0xb5 and calls its member at VA 0x10d2a830 with 1, 0 and 0. It stores and
// returns whether that happened. The class, method and member names are invented; the offsets and
// addresses are the binary's.

class UnkType_10b54d20_Target
{
public:
    void Unk_10d2a530(int First, int Second);
    void Unk_10d2a830(int First, int Second, int Third);

    unsigned char unk_00[0xb5];
    bool unk_b5;
};

class UnkType_10b54d20
{
public:
    bool Unk_10b65b30(int Value);
    bool Unk_10b54d20(int Value);

private:
    unsigned char unk_00[0x3c];
    bool unk_3c;
    unsigned char unk_3d[3];
    UnkType_10b54d20_Target* unk_40;
};

// UnkType_10b54d20::Unk_10b54d20
bool UnkType_10b54d20::Unk_10b54d20(int Value)
{
    if ( unk_3c )
    {
        return true;
    }
    bool Result = false;
    if ( Unk_10b65b30(Value) )
    {
        Result = true;
        unk_40->Unk_10d2a530(1, 1);
        unk_40->unk_b5 = true;
        unk_40->Unk_10d2a830(1, 0, 0);
    }
    unk_3c = Result;
    return Result;
}
