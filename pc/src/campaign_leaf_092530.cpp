// campaign_leaf_092530.cpp -- method at VA 0x10992530 taking an output array: unless bit 8 of the
// flags at 0x28 and bit 1 of the flags at 0x30 are both set, zeroes the output's count at 0x04 and
// passes it, for every index in the array at 0xb8 (count at 0xbc), the 20-byte record at that index
// of the array at 0xd8 of the object reached through 0x7c and 0x80, through the method at VA
// 0x1094baa0. The class, member and method names are invented; the offsets and the address are
// the binary's.

struct UnkType_10992530_Record
{
    unsigned char unk_00[0x14];
};

class UnkType_10992530_Output
{
public:
    void Unk_1094baa0(const UnkType_10992530_Record& Record);

    void* unk_00;
    int unk_04;
};

class UnkType_10992530_Table
{
public:
    unsigned char unk_00[0xd8];
    UnkType_10992530_Record* unk_d8;
};

class UnkType_10992530_Level
{
public:
    unsigned char unk_00[0x80];
    UnkType_10992530_Table* unk_80;
};

class UnkType_10992530
{
public:
    void Unk_10992530(UnkType_10992530_Output& Output);

private:
    unsigned char unk_00[0x28];
    unsigned int unk_28;
    unsigned char unk_2c[0x30 - 0x2c];
    unsigned int unk_30;
    unsigned char unk_34[0x7c - 0x34];
    UnkType_10992530_Level* unk_7c;
    unsigned char unk_80[0xb8 - 0x80];
    int* unk_b8;
    int unk_bc;
};

// UnkType_10992530::Unk_10992530
void UnkType_10992530::Unk_10992530(UnkType_10992530_Output& Output)
{
    if ( (unk_28 & 8) && (unk_30 & 1) )
    {
        return;
    }
    Output.unk_04 = 0;
    for ( int i = 0; i < unk_bc; i++ )
    {
        Output.Unk_1094baa0(unk_7c->unk_80->unk_d8[unk_b8[i]]);
    }
}
