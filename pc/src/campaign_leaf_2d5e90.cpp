// campaign_leaf_2d5e90.cpp -- method at VA 0x10bd5e90: for every 0x58-byte entry of the array at
// 0x2b4 (count at 0x2b8) whose pointer at 0x0c is set, passes the address of this object's 12
// bytes at 0xe8 and 0 to the method at VA 0x10990230 of that pointer, then the address of the 12
// bytes at 0xf4 to its method at VA 0x109903e0. The class, member and method names are invented;
// the offsets and the addresses are the binary's.

class UnkType_10bd5e90_0c
{
public:
    void Unk_10990230(int* First, int Flag);
    void Unk_109903e0(int* Second);
};

class UnkType_10bd5e90_Entry
{
public:
    unsigned char unk_00[0x0c];
    UnkType_10bd5e90_0c* unk_0c;
    unsigned char unk_10[0x58 - 0x10];
};

class UnkType_10bd5e90
{
public:
    void Unk_10bd5e90();

private:
    unsigned char unk_00[0xe8];
    int unk_e8[3];
    int unk_f4[3];
    unsigned char unk_100[0x2b4 - 0x100];
    UnkType_10bd5e90_Entry* unk_2b4;
    int unk_2b8;
};

// UnkType_10bd5e90::Unk_10bd5e90
void UnkType_10bd5e90::Unk_10bd5e90()
{
    for ( int Index = 0; Index < unk_2b8; Index++ )
    {
        UnkType_10bd5e90_Entry* Entry = &unk_2b4[Index];
        if ( Entry->unk_0c )
        {
            Entry->unk_0c->Unk_10990230(unk_e8, 0);
            Entry->unk_0c->Unk_109903e0(unk_f4);
        }
    }
}
