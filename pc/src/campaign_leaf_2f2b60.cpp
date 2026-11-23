// campaign_leaf_2f2b60.cpp -- method at VA 0x10bf2b60: calls the method at VA 0x10a93120, then for
// every 12-byte entry of the array at 0x3fc (count at 0x400) whose pointer is set, calls the method
// at VA 0x10c17fe0 on that pointer with this object and whether the entry's byte at 0x04 is zero;
// finally sets bit 1 of the word at 0x34. The class, member and method names are invented; the
// offsets and the addresses are the binary's.

class UnkType_10bf2b60;

class UnkType_10bf2b60_Item
{
public:
    void Unk_10c17fe0(UnkType_10bf2b60* Owner, int Flag);
};

class UnkType_10bf2b60_Entry
{
public:
    UnkType_10bf2b60_Item* unk_00;
    unsigned char unk_04;
    unsigned char unk_05[0x0c - 0x05];
};

class UnkType_10bf2b60
{
public:
    void Unk_10bf2b60();
    void Unk_10a93120();

private:
    unsigned char unk_00[0x34];
    int unk_34;
    unsigned char unk_38[0x3fc - 0x38];
    UnkType_10bf2b60_Entry* unk_3fc;
    int unk_400;
};

// UnkType_10bf2b60::Unk_10bf2b60
void UnkType_10bf2b60::Unk_10bf2b60()
{
    Unk_10a93120();
    for ( int Index = 0; Index < unk_400; Index++ )
    {
        UnkType_10bf2b60_Entry& Entry = unk_3fc[Index];
        if ( Entry.unk_00 )
        {
            Entry.unk_00->Unk_10c17fe0(this, !Entry.unk_04);
        }
    }
    unk_34 |= 2;
}
