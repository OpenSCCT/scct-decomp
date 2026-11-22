// campaign_leaf_26ee10.cpp -- a member function at VA 0x10b6ee10 that clears the byte at 0x15 and,
// when the int at 0x1c is not zero, passes it and three zeros to the member at VA 0x10ad5820 of the
// object the pointer at 0x10 refers to; it returns true. The class, method and member names are
// invented; the offsets and addresses are the binary's.

class UnkType_10ad5820
{
public:
    void Unk_10ad5820(int Value, int First, int Second, int Third);
};

class UnkType_10b6ee10
{
public:
    bool Unk_10b6ee10();

private:
    unsigned char unk_00[0x10];
    UnkType_10ad5820* unk_10;
    unsigned char unk_14;
    unsigned char unk_15;
    unsigned char unk_16[0x1c - 0x16];
    int unk_1c;
};

// UnkType_10b6ee10::Unk_10b6ee10
bool UnkType_10b6ee10::Unk_10b6ee10()
{
    unk_15 = 0;
    if ( unk_1c )
    {
        unk_10->Unk_10ad5820(unk_1c, 0, 0, 0);
    }
    return true;
}
