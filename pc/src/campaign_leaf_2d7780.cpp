// campaign_leaf_2d7780.cpp -- method at VA 0x10bd7780: calls the method at VA 0x1098fd40, then for
// every 0x58-byte entry of the array at 0x2b4 (count at 0x2b8) whose word at 0x20 is set and whose
// word at 0x28 is zero, passes the address of the word at 0x20 to the method at VA 0x1099b960 of
// the entry's member at 0x24 and clears the word at 0x20. The class, member and method names are
// invented; the offsets and the addresses are the binary's.

class UnkType_10bd7780_24
{
public:
    void Unk_1099b960(int* Value);
};

class UnkType_10bd7780_Entry
{
public:
    unsigned char unk_00[0x20];
    int unk_20;
    UnkType_10bd7780_24 unk_24;
    unsigned char unk_25[0x28 - 0x25];
    int unk_28;
    unsigned char unk_2c[0x58 - 0x2c];
};

class UnkType_10bd7780
{
public:
    void Unk_10bd7780();
    void Unk_1098fd40();

private:
    unsigned char unk_00[0x2b4];
    UnkType_10bd7780_Entry* unk_2b4;
    int unk_2b8;
};

// UnkType_10bd7780::Unk_10bd7780
void UnkType_10bd7780::Unk_10bd7780()
{
    Unk_1098fd40();
    for ( int Index = 0; Index < unk_2b8; Index++ )
    {
        UnkType_10bd7780_Entry* Entry = &unk_2b4[Index];
        if ( Entry->unk_20 && !Entry->unk_28 )
        {
            Entry->unk_24.Unk_1099b960(&Entry->unk_20);
            Entry->unk_20 = 0;
        }
    }
}
