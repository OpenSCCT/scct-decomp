// campaign_leaf_4abcc0.cpp -- one function at file offset 0x4abcc0, preferred VA 0x10dabcc0. A
// constructor: it stores three words at 0x0-0x8, a four-word structure at 0x10 and a byte at
// 0x20, and clears the byte at 0x21. The class, structure, member and parameter names are
// invented; the offsets and the bytes are the binary's.

struct UnkType_10dabcc0_Quad
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
};

class UnkType_10dabcc0
{
public:
    UnkType_10dabcc0(int First, int Second, int Third, const UnkType_10dabcc0_Quad& Fourth,
                     unsigned char Fifth);

    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    UnkType_10dabcc0_Quad unk_10;
    unsigned char unk_20;
    unsigned char unk_21;
};

// UnkType_10dabcc0::UnkType_10dabcc0
UnkType_10dabcc0::UnkType_10dabcc0(int First, int Second, int Third,
                                   const UnkType_10dabcc0_Quad& Fourth, unsigned char Fifth)
{
    unk_0 = First;
    unk_4 = Second;
    unk_8 = Third;
    unk_10 = Fourth;
    unk_20 = Fifth;
    unk_21 = 0;
}
