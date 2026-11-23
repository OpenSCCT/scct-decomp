// campaign_leaf_2f2eb0.cpp -- method at VA 0x10bf2eb0 taking a flag and a pointer: sets bit 0 of the
// word at 0x41c when the flag is nonzero and clears it otherwise, sets bit 2 when the word the
// pointer addresses is 0x50, then calls the method at VA 0x10c173d0 on the pointer of every
// 12-byte entry of the array at 0x3fc (count at 0x400) that is set. The class, member and method
// names are invented; the offsets and the address are the binary's.

class UnkType_10bf2eb0_Item
{
public:
    void Unk_10c173d0();
};

class UnkType_10bf2eb0_Entry
{
public:
    UnkType_10bf2eb0_Item* unk_00;
    unsigned char unk_04[0x0c - 0x04];
};

class UnkType_10bf2eb0_Kind
{
public:
    int unk_00;
};

class UnkType_10bf2eb0
{
public:
    void Unk_10bf2eb0(int Enable, UnkType_10bf2eb0_Kind* Kind);

private:
    unsigned char unk_00[0x3fc];
    UnkType_10bf2eb0_Entry* unk_3fc;
    int unk_400;
    unsigned char unk_404[0x41c - 0x404];
    unsigned int unk_41c;
};

// UnkType_10bf2eb0::Unk_10bf2eb0
void UnkType_10bf2eb0::Unk_10bf2eb0(int Enable, UnkType_10bf2eb0_Kind* Kind)
{
    if ( Enable )
    {
        unk_41c |= 1;
    }
    else
    {
        unk_41c &= ~1;
    }
    if ( Kind->unk_00 == 0x50 )
    {
        unk_41c |= 4;
    }
    for ( int Index = 0; Index < unk_400; Index++ )
    {
        UnkType_10bf2eb0_Entry* Entry = &unk_3fc[Index];
        if ( Entry->unk_00 )
        {
            Entry->unk_00->Unk_10c173d0();
        }
    }
}
