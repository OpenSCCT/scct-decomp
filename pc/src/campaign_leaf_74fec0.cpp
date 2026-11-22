// campaign_leaf_74fec0.cpp -- free function at VA 0x1104fec0: calls the method at VA 0x11058830 with its
// argument on the object returned by VA 0x11056900. All names are invented.

class UnkType_11056900
{
public:
    void Unk_11058830(int Value);
};

UnkType_11056900* Unk_11056900();

// Unk_1104fec0
void Unk_1104fec0(int Value)
{
    Unk_11056900()->Unk_11058830(Value);
}
