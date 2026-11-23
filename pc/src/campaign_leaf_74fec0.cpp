// campaign_leaf_74fec0.cpp -- one function at file offset 0x74fec0, preferred VA 0x1104fec0. It
// calls the method at VA 0x11058830 with its argument on the object returned by the function at
// VA 0x11056900 (which returns the address of the global at VA 0x1132ea08). The class and
// function names are invented; the offset and the addresses are the binary's.

class UnkType_11056900
{
public:
    void Unk_11056950(int First, int Second);
    void Unk_11056d70(int Value);
    void Unk_11056db0(int Value);
    void Unk_11057640(int Value);
    void Unk_11057680(int Value);
    void Unk_11057790(int Value);
    void Unk_11057830(int Value);
    void Unk_11057870(int Value);
    void Unk_110579d0(int Value);
    void Unk_11057b20(int Value);
    void Unk_11057b30(int Value);
    void Unk_110587a0(int Value);
    void Unk_11058830(int Value);
    void Unk_1105a5f0(int First, int Second);
    void Unk_1105a610(int Value);
};

UnkType_11056900* Unk_11056900();

// Unk_1104fec0
void Unk_1104fec0(int Value)
{
    Unk_11056900()->Unk_11058830(Value);
}
