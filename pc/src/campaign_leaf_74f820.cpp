// campaign_leaf_74f820.cpp -- free function at VA 0x1104f820: calls the method at VA 0x11057870 with its
// argument on the object returned by VA 0x11056900. All names are invented.

class UnkType_11056900
{
public:
    void Unk_11057870(int Value);
};

UnkType_11056900* Unk_11056900();

// Unk_1104f820
void Unk_1104f820(int Value)
{
    Unk_11056900()->Unk_11057870(Value);
}
