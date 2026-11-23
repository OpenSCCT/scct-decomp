// campaign_leaf_76fb50.cpp -- one function at file offset 0x76fb50, preferred VA 0x1106fb50. It
// returns 1 when the version at 0x8c is 7, the word at 0x94 equals the count at 0x74, the word at
// 0x98 exceeds the word at 0x28, the words at 0x9c, 0xa4, 0xc8 and 0xa8 are set and the word at
// 0xa0 is four times the count plus 0xc. Otherwise it returns 0, first reporting "You have an old
// MultiTrack version. Rebuild your MultiTrack files!" through the stdcall function at VA
// 0x1103c7d0 when the version is not 7. The class and member names are invented; the offsets and
// the addresses are the binary's.

void __stdcall Unk_1103c7d0(int Level, const char* Message);

class UnkType_1106fb50
{
public:
    int Unk_1106fb50();

    unsigned char unk_0[0x28];
    unsigned int unk_28;
    unsigned char unk_2c[0x74 - 0x2c];
    unsigned int unk_74;
    unsigned char unk_78[0x8c - 0x78];
    int unk_8c;
    unsigned char unk_90[0x94 - 0x90];
    unsigned int unk_94;
    unsigned int unk_98;
    unsigned int unk_9c;
    unsigned int unk_a0;
    unsigned int unk_a4;
    unsigned int unk_a8;
    unsigned char unk_ac[0xc8 - 0xac];
    unsigned int unk_c8;
};

// UnkType_1106fb50::Unk_1106fb50
int UnkType_1106fb50::Unk_1106fb50()
{
    if ( unk_8c == 7 && unk_94 == unk_74 && unk_98 > unk_28 && unk_9c > 0
         && unk_a0 == unk_74 * 4 + 0xc && unk_a4 > 0 && unk_c8 > 0 && unk_a8 > 0 )
    {
        return 1;
    }
    if ( unk_8c != 7 )
    {
        Unk_1103c7d0(0xd, "You have an old MultiTrack version. Rebuild your MultiTrack files!");
    }
    return 0;
}
