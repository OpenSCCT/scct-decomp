// campaign_leaf_559a10.cpp -- method at VA 0x10e59a10: builds a pair of Scale and its reciprocal
// and passes it to the methods at VA 0x10e587b0 and 0x10e589f0. The class, member, method and
// parameter names are invented; the addresses are the binary's.

class UnkType_10e59a10_Pair
{
public:
    float unk_0;
    float unk_4;
};

class UnkType_10e59a10
{
public:
    void Unk_10e587b0(UnkType_10e59a10_Pair* Pair);
    void Unk_10e589f0(UnkType_10e59a10_Pair* Pair);
    void Unk_10e59a10(float Scale);
};

// UnkType_10e59a10::Unk_10e59a10
void UnkType_10e59a10::Unk_10e59a10(float Scale)
{
    UnkType_10e59a10_Pair Pair;

    Pair.unk_0 = Scale;
    Pair.unk_4 = 1.0f / Scale;
    Unk_10e587b0(&Pair);
    Unk_10e589f0(&Pair);
}
