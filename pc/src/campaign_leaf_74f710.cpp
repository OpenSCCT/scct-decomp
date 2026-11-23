// campaign_leaf_74f710.cpp -- one function at file offset 0x74f710, preferred VA 0x1104f710. It
// passes its argument to the function at VA 0x1105ca60 and then to the method at VA 0x11057750 of
// the object returned by the function at VA 0x11056900 (which returns the address of the global
// at VA 0x1132ea08). The type and function names are invented; the offset and the addresses are
// the binary's.

class UnkType_1104f710_Manager
{
public:
    void Unk_11057750(int Value);
};

UnkType_1104f710_Manager* Unk_11056900();
void Unk_1105ca60(int Value);

// Unk_1104f710
void Unk_1104f710(int Value)
{
    Unk_1105ca60(Value);
    Unk_11056900()->Unk_11057750(Value);
}
