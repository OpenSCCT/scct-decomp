// campaign_leaf_546880.cpp -- one function at file offset 0x546880, preferred VA 0x10e46880. It
// clears the byte at 0x58, moves the last of the six-byte entries at 0x20 (count at 0x54) into
// the slot Index and drops the count by one. Its second and third parameters are unused. The
// class, method, structure and member names are invented; the offsets and the bytes are the
// binary's.

struct UnkType_10e46880_Entry
{
    unsigned short unk_0;
    unsigned short unk_2;
    unsigned short unk_4;
};

class UnkType_10e46880
{
public:
    void Unk_10e46880(int Index, int, int);

    unsigned char unk_0[0x20];
    UnkType_10e46880_Entry unk_20[6];
    unsigned char unk_44[0x10];
    int unk_54;
    unsigned char unk_58;
};

// UnkType_10e46880::Unk_10e46880
void UnkType_10e46880::Unk_10e46880(int Index, int, int)
{
    unk_58 = 0;
    unk_20[Index] = unk_20[unk_54 - 1];
    unk_54--;
}
