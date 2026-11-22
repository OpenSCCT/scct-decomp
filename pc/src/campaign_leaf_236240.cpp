// campaign_leaf_236240.cpp -- a member function at VA 0x10b36240: when the byte at 0x28 is set it
// passes its argument to the member at VA 0x10b35e10; it stores that result, or false, in the byte
// at 0x14 of the object the pointer at 0x10 refers to and returns it. The class, method and member
// names are invented; the offsets and addresses are the binary's.

class UnkType_10b36240_Item
{
public:
    unsigned char unk_00[0x14];
    bool unk_14;
};

class UnkType_10b36240
{
public:
    bool Unk_10b35e10(int Value);
    bool Unk_10b36240(int Value);

private:
    unsigned char unk_00[0x10];
    UnkType_10b36240_Item* unk_10;
    unsigned char unk_14[0x28 - 0x14];
    bool unk_28;
};

// UnkType_10b36240::Unk_10b36240
bool UnkType_10b36240::Unk_10b36240(int Value)
{
    bool Result = false;
    if ( unk_28 )
    {
        Result = Unk_10b35e10(Value);
    }
    unk_10->unk_14 = Result;
    return Result;
}
