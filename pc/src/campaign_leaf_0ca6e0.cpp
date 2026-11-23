// campaign_leaf_0ca6e0.cpp -- method at VA 0x109ca6e0: when the float at 0x68 is zero or Force is
// set, copies the float at 0x5c to 0x60, stores First at 0x64 and Second at 0x68, and clears the
// float at 0x6c. The class, member, method and parameter names are invented; the offsets are the
// binary's.

class UnkType_109ca6e0
{
public:
    void Unk_109ca6e0(float First, float Second, bool Force);

private:
    char unk_0[0x5c];
    float unk_5c;
    float unk_60;
    float unk_64;
    float unk_68;
    float unk_6c;
};

// UnkType_109ca6e0::Unk_109ca6e0
void UnkType_109ca6e0::Unk_109ca6e0(float First, float Second, bool Force)
{
    if ( unk_68 == 0.0f || Force )
    {
        unk_60 = unk_5c;
        unk_64 = First;
        unk_68 = Second;
        unk_6c = 0.0f;
    }
}
