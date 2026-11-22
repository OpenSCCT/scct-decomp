// campaign_leaf_53e9c0.cpp -- one function at file offset 0x53e9c0, preferred VA 0x10e3e9c0. It
// clears the 32 words at 0x38. The class, method and member names are invented; the offsets and
// the bytes are the binary's.

class UnkType_10e3e9c0
{
public:
    void Unk_10e3e9c0();

    unsigned char unk_0[0x38];
    int unk_38[32];
};

// UnkType_10e3e9c0::Unk_10e3e9c0
void UnkType_10e3e9c0::Unk_10e3e9c0()
{
    int Index;

    for ( Index = 0; Index < 32; Index++ )
    {
        unk_38[Index] = 0;
    }
}
