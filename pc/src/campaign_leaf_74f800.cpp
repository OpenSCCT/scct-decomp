// campaign_leaf_74f800.cpp -- free function at VA 0x1104f800: calls the method at VA 0x11057830 with its
// argument on the object returned by VA 0x11056900. All names are invented.

class UnkType_11056900
{
public:
    void Unk_11057830(int Value);
};

UnkType_11056900* Unk_11056900();

// Unk_1104f800
void Unk_1104f800(int Value)
{
    Unk_11056900()->Unk_11057830(Value);
}
