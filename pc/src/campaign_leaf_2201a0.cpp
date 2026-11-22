// campaign_leaf_2201a0.cpp -- a member function at VA 0x10b201a0 that passes the result of the
// member at VA 0x10a0e2a0 to the member at VA 0x10b20010 and then its argument to the member at VA
// 0x10a0db20. The class, method and parameter names are invented; the addresses are the binary's.

class UnkType_10b201a0
{
public:
    int Unk_10a0e2a0();
    void Unk_10b20010(int Value);
    void Unk_10a0db20(int Value);
    void Unk_10b201a0(int Value);
};

// UnkType_10b201a0::Unk_10b201a0
void UnkType_10b201a0::Unk_10b201a0(int Value)
{
    Unk_10b20010(Unk_10a0e2a0());
    Unk_10a0db20(Value);
}
