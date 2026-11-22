// campaign_leaf_34acf0.cpp -- a member function at VA 0x10c4acf0 that calls the member at VA
// 0x10bf18b0 and then the member at VA 0x10c4abb0 with the address of a local int set to 0. The
// class, method and local names are invented; the addresses are the binary's.

class UnkType_10c4acf0
{
public:
    void Unk_10bf18b0();
    void Unk_10c4abb0(int* Result);
    void Unk_10c4acf0();
};

// UnkType_10c4acf0::Unk_10c4acf0
void UnkType_10c4acf0::Unk_10c4acf0()
{
    Unk_10bf18b0();
    int Result = 0;
    Unk_10c4abb0(&Result);
}
