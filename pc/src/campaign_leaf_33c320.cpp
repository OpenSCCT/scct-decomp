// campaign_leaf_33c320.cpp -- one function at file offset 0x33c320, preferred VA 0x10c3c320. When
// the method at 0x10befc90 returns 1 for the member at 0xe8 of Other and 0, it copies the 12-byte
// block at 0x578 to 0x510; otherwise it copies the one at 0x56c. The class, method, structure,
// member and parameter names are invented; the offsets and the bytes are the binary's.

struct UnkType_10c3c320_Vector
{
    float unk_0;
    float unk_4;
    float unk_8;
};

class UnkType_10c3c320_Other
{
public:
    unsigned char unk_0[0xe8];
    int unk_e8;
};

class UnkType_10c3c320
{
public:
    int Unk_10befc90(int* Value, int Flags);
    void Unk_10c3c320(UnkType_10c3c320_Other* Other);

    unsigned char unk_0[0x510];
    UnkType_10c3c320_Vector unk_510;
    unsigned char unk_51c[0x50];
    UnkType_10c3c320_Vector unk_56c;
    UnkType_10c3c320_Vector unk_578;
};

// UnkType_10c3c320::Unk_10c3c320
void UnkType_10c3c320::Unk_10c3c320(UnkType_10c3c320_Other* Other)
{
    if ( Unk_10befc90(&Other->unk_e8, 0) == 1 )
    {
        unk_510 = unk_578;
    }
    else
    {
        unk_510 = unk_56c;
    }
}
