// campaign_leaf_336d80.cpp -- a member function at VA 0x10c36d80 that passes its argument to the
// free function at VA 0x109014a0 and returns 0. It does not read this. The class, method and
// function names are invented; the addresses are the binary's.

void Unk_109014a0(int Value);

class UnkType_10c36d80
{
public:
    int Unk_10c36d80(int Value);
};

// UnkType_10c36d80::Unk_10c36d80
int UnkType_10c36d80::Unk_10c36d80(int Value)
{
    Unk_109014a0(Value);
    return 0;
}
