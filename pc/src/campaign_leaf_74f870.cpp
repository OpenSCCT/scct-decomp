// campaign_leaf_74f870.cpp -- free function at VA 0x1104f870: calls the method at VA 0x1105a5f0 with its two
// arguments on the object returned by VA 0x11056900. All names are invented.

class UnkType_11056900
{
public:
    void Unk_1105a5f0(int First, int Second);
};

UnkType_11056900* Unk_11056900();

// Unk_1104f870
void Unk_1104f870(int First, int Second)
{
    Unk_11056900()->Unk_1105a5f0(First, Second);
}
