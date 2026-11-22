// campaign_leaf_4ead10.cpp -- one function at file offset 0x4ead10, preferred VA 0x10dead10. A
// constructor: it loads the four MD5 initial chaining values into the words at 0x0-0xc and zeroes the words at
// 0x10 and 0x14 and the byte at 0x68. The class, method and member names are invented; the
// offsets, the constants and the bytes are the binary's.

class UnkType_10dead10
{
public:
    UnkType_10dead10();

    unsigned int unk_0[4];
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned char unk_18[0x50];
    unsigned char unk_68;
};

// UnkType_10dead10::UnkType_10dead10
// guess: an MD5 context's initialisation (the constants are MD5's).
UnkType_10dead10::UnkType_10dead10()
{
    unk_68 = 0;
    unk_10 = 0;
    unk_14 = 0;
    unk_0[0] = 0x67452301;
    unk_0[1] = 0xefcdab89;
    unk_0[2] = 0x98badcfe;
    unk_0[3] = 0x10325476;
}
