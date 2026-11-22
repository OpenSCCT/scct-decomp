// campaign_leaf_74f8b0.cpp -- free function at VA 0x1104f8b0: calls the method at VA 0x110579d0 with its
// argument on the object returned by VA 0x11056900. All names are invented.

class UnkType_11056900
{
public:
    void Unk_110579d0(int Value);
};

UnkType_11056900* Unk_11056900();

// Unk_1104f8b0
void Unk_1104f8b0(int Value)
{
    Unk_11056900()->Unk_110579d0(Value);
}
