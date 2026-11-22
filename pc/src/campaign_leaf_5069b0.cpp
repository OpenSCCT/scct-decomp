// campaign_leaf_5069b0.cpp -- one function at file offset 0x5069b0, preferred VA 0x10e069b0. It
// clears bit Second in the word at 0x1c + 4 * First and bit First in the word at
// 0x1c + 4 * Second. The class, method, member and parameter names are invented; the offsets and
// the bytes are the binary's.

class UnkType_10e069b0
{
public:
    void Unk_10e069b0(int First, int Second);

    unsigned char unk_0[0x1c];
    unsigned int unk_1c[32];
};

// UnkType_10e069b0::Unk_10e069b0
void UnkType_10e069b0::Unk_10e069b0(int First, int Second)
{
    unk_1c[First] &= ~( 1 << Second );
    unk_1c[Second] &= ~( 1 << First );
}
