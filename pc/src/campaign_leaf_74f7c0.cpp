// campaign_leaf_74f7c0.cpp -- free function at VA 0x1104f7c0: calls the method at VA 0x11057270 on
// the object returned by VA 0x11056900, then calls VA 0x110550f0. All names are invented.

class UnkType_11057270
{
public:
    void Unk_11057270();
};

UnkType_11057270* Unk_11056900();
void Unk_110550f0();

// Unk_1104f7c0
void Unk_1104f7c0()
{
    Unk_11056900()->Unk_11057270();
    Unk_110550f0();
}
