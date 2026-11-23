// campaign_leaf_2f2f20.cpp -- method at VA 0x10bf2f20 taking one argument: sets bit 1 of the word at
// 0x41c when the argument is nonzero and clears it otherwise, then calls the method at VA
// 0x10c173d0 on the pointer of every 12-byte entry of the array at 0x3fc (count at 0x400) that is
// set. The class, member and method names are invented; the offsets and the address are the
// binary's.

class UnkType_10bf2f20_Item
{
public:
    void Unk_10c173d0();
};

class UnkType_10bf2f20_Entry
{
public:
    UnkType_10bf2f20_Item* unk_00;
    unsigned char unk_04[0x0c - 0x04];
};

class UnkType_10bf2f20
{
public:
    void Unk_10bf2f20(int Enable);

private:
    unsigned char unk_00[0x3fc];
    UnkType_10bf2f20_Entry* unk_3fc;
    int unk_400;
    unsigned char unk_404[0x41c - 0x404];
    unsigned int unk_41c;
};

// UnkType_10bf2f20::Unk_10bf2f20
void UnkType_10bf2f20::Unk_10bf2f20(int Enable)
{
    if ( Enable )
    {
        unk_41c |= 2;
    }
    else
    {
        unk_41c &= ~2;
    }
    for ( int Index = 0; Index < unk_400; Index++ )
    {
        UnkType_10bf2f20_Entry* Entry = &unk_3fc[Index];
        if ( Entry->unk_00 )
        {
            Entry->unk_00->Unk_10c173d0();
        }
    }
}
