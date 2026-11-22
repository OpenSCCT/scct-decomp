// campaign_leaf_74f950.cpp -- free function at VA 0x1104f950: calls the method at VA 0x1105a610 with its
// argument on the object returned by VA 0x11056900. All names are invented.

class UnkType_11056900
{
public:
    void Unk_1105a610(int Value);
};

UnkType_11056900* Unk_11056900();

// Unk_1104f950
void Unk_1104f950(int Value)
{
    Unk_11056900()->Unk_1105a610(Value);
}
