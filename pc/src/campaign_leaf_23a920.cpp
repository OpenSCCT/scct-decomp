// campaign_leaf_23a920.cpp -- a member function at VA 0x10b3a920 that returns whether the member at
// VA 0x10b3a7a0, given the same argument, returns zero or more. The class, method and parameter
// names are invented; the addresses are the binary's.

class UnkType_10b3a920
{
public:
    int Unk_10b3a7a0(int Value);
    bool Unk_10b3a920(int Value);
};

// UnkType_10b3a920::Unk_10b3a920
bool UnkType_10b3a920::Unk_10b3a920(int Value)
{
    return Unk_10b3a7a0(Value) >= 0;
}
