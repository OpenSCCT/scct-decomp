// campaign_leaf_74f9f0.cpp -- free function at VA 0x1104f9f0: calls the method at VA 0x11056db0 with its
// argument on the object returned by VA 0x11056900. All names are invented.

class UnkType_11056900
{
public:
    void Unk_11056db0(int Value);
};

UnkType_11056900* Unk_11056900();

// Unk_1104f9f0
void Unk_1104f9f0(int Value)
{
    Unk_11056900()->Unk_11056db0(Value);
}
