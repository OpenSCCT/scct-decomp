// campaign_leaf_4024d0.cpp -- one function at file offset 0x4024d0, preferred VA 0x10d024d0. It
// clears nine counters, then walks the linked entries from 0x18 to the end at 0x1c and, for each
// entry with a nonzero 64-bit value whose halfword at 0xc is below the counter at 0x4, decays
// its word at 0x10 by a thirty-second; finally it advances the counter at 0x4. The class,
// method, structure and member names are invented; the offsets and the bytes are the binary's.

struct UnkType_10d024d0_Entry
{
    __int64 unk_0;
    int unk_8;
    unsigned short unk_c;
    unsigned short unk_e;
    int unk_10;
    UnkType_10d024d0_Entry* unk_14;
};

class UnkType_10d024d0
{
public:
    void Unk_10d024d0();

    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
    UnkType_10d024d0_Entry* unk_18;
    UnkType_10d024d0_Entry* unk_1c;
    unsigned char unk_20[0x10018];
    int unk_10038;
    int unk_1003c;
    int unk_10040;
    int unk_10044;
    int unk_10048;
    int unk_1004c;
    int unk_10050;
};

// UnkType_10d024d0::Unk_10d024d0
void UnkType_10d024d0::Unk_10d024d0()
{
    UnkType_10d024d0_Entry* Entry;

    unk_10038 = 0;
    unk_8 = 0;
    unk_c = 0;
    unk_10 = 0;
    unk_10050 = 0;
    unk_1004c = 0;
    unk_10048 = 0;
    unk_10040 = 0;
    unk_1003c = 0;
    for ( Entry = unk_18; Entry != unk_1c; Entry = Entry->unk_14 )
    {
        if ( Entry->unk_0 != 0 && unk_4 > Entry->unk_c )
        {
            Entry->unk_10 -= Entry->unk_10 >> 5;
        }
    }
    unk_4++;
}
