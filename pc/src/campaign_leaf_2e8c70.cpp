// campaign_leaf_2e8c70.cpp -- method at VA 0x10be8c70 taking one argument: clears the word at 0x36c,
// then walks the array of 24-byte entries at 0x360 (count at 0x364), removing each entry whose first
// word equals the argument through the array's method at VA 0x10be8bf0 and ORing the second word of
// every other entry into 0x36c. The class, member and method names are invented; the offsets and
// the address are the binary's.

class UnkType_10be8c70_Entry
{
public:
    int unk_00;
    int unk_04;
    unsigned char unk_08[0x18 - 0x08];
};

class UnkType_10be8c70_Array
{
public:
    void Unk_10be8bf0(int Index, int Count);

    UnkType_10be8c70_Entry* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10be8c70
{
public:
    void Unk_10be8c70(int Key);

private:
    unsigned char unk_00[0x360];
    UnkType_10be8c70_Array unk_360;
    int unk_36c;
};

// UnkType_10be8c70::Unk_10be8c70
void UnkType_10be8c70::Unk_10be8c70(int Key)
{
    unk_36c = 0;
    for ( int Index = 0; Index < unk_360.unk_04; Index++ )
    {
        if ( unk_360.unk_00[Index].unk_00 == Key )
        {
            unk_360.Unk_10be8bf0(Index, 1);
            Index--;
        }
        else
        {
            unk_36c |= unk_360.unk_00[Index].unk_04;
        }
    }
}
