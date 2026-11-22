// campaign_leaf_06b100.cpp -- one function at file offset 0x6b100, preferred VA 0x1096b100. It
// returns 1 when bit 0 of the byte at offset 0xa0 is set and the low 16 bits of any of the words at
// offsets 0x94, 0x98 and 0x9c are set, and 0 otherwise. The class and method names are invented;
// the offset and the bytes are the binary's.

class UnkType_1096b100
{
public:
    int UnkMatches() const;

private:
    unsigned char unk_00[0x94];     // not read by this function
    int unk_94;                     // low 16 bits tested
    int unk_98;                     // low 16 bits tested
    int unk_9c;                     // low 16 bits tested
    unsigned char unk_a0;           // bit 0 tested
};

// UnkType_1096b100::UnkMatches
int UnkType_1096b100::UnkMatches() const
{
    if ( ( unk_a0 & 1 ) != 0 )
    {
        if ( ( unk_94 & 0xffff ) != 0 || ( unk_98 & 0xffff ) != 0 || ( unk_9c & 0xffff ) != 0 )
        {
            return 1;
        }
    }
    return 0;
}
