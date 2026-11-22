// campaign_leaf_506820.cpp -- one function at file offset 0x506820, preferred VA 0x10e06820. It
// copies the word at 0x18 and the 32 words at 0x1c out into the argument. The class, method, structure and member names are invented; the offsets and
// the bytes are the binary's.

struct UnkBlock_10e06820
{
    int unk_0;
    int unk_4[32];
};

class UnkType_10e06820
{
public:
    void Unk_10e06820(UnkBlock_10e06820& Out) const;

    unsigned char unk_0[0x18];
    int unk_18;
    int unk_1c[32];
};

// UnkType_10e06820::Unk_10e06820
void UnkType_10e06820::Unk_10e06820(UnkBlock_10e06820& Out) const
{
    int Index;

    for ( Index = 0; Index < 32; Index++ )
    {
        Out.unk_4[Index] = unk_1c[Index];
    }
    Out.unk_0 = unk_18;
}
