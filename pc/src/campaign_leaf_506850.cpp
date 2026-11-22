// campaign_leaf_506850.cpp -- one function at file offset 0x506850, preferred VA 0x10e06850. It
// copies the word at 0x0 and the 32 words at 0x4 of the argument in, to 0x18 and 0x1c. The class, method, structure and member names are invented; the offsets and
// the bytes are the binary's.

struct UnkBlock_10e06850
{
    int unk_0;
    int unk_4[32];
};

class UnkType_10e06850
{
public:
    void Unk_10e06850(const UnkBlock_10e06850& Out);

    unsigned char unk_0[0x18];
    int unk_18;
    int unk_1c[32];
};

// UnkType_10e06850::Unk_10e06850
void UnkType_10e06850::Unk_10e06850(const UnkBlock_10e06850& Out)
{
    int Index;

    for ( Index = 0; Index < 32; Index++ )
    {
        unk_1c[Index] = Out.unk_4[Index];
    }
    unk_18 = Out.unk_0;
}
