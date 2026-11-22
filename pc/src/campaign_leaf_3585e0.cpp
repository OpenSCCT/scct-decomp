// campaign_leaf_3585e0.cpp -- a member function at VA 0x10c585e0 that passes its argument to the
// member at VA 0x10c56640 and then, when the int at 0x4ec is not zero, calls the member at VA
// 0x10993770. The class, method and member names are invented; the offsets and addresses are the
// binary's.

class UnkType_10c585e0
{
public:
    void Unk_10c56640(int Value);
    void Unk_10993770();
    void Unk_10c585e0(int Value);

private:
    unsigned char unk_000[0x4ec];
    int unk_4ec;
};

// UnkType_10c585e0::Unk_10c585e0
void UnkType_10c585e0::Unk_10c585e0(int Value)
{
    Unk_10c56640(Value);
    if ( unk_4ec )
    {
        Unk_10993770();
    }
}
