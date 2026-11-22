// campaign_leaf_2f18b0.cpp -- a member function at VA 0x10bf18b0 that calls the member at VA
// 0x10bf1800 with 0 and the address of a local int set to 0. The class, method and local names are
// invented; the addresses are the binary's.

class UnkType_10bf18b0
{
public:
    void Unk_10bf1800(int Value, int* Result);
    void Unk_10bf18b0();
};

// UnkType_10bf18b0::Unk_10bf18b0
void UnkType_10bf18b0::Unk_10bf18b0()
{
    int Result = 0;
    Unk_10bf1800(0, &Result);
}
