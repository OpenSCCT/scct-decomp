// campaign_leaf_74f6c0.cpp -- one function at file offset 0x74f6c0, preferred VA 0x1104f6c0. It
// passes its argument and the result of the function at VA 0x1105c910 on that argument to the
// method at VA 0x110576c0 of the object returned by the function at VA 0x11056900 (which returns
// the address of the global at VA 0x1132ea08). The type and function names are invented; the
// offset and the addresses are the binary's.

class UnkType_1104f6c0_Manager
{
public:
    void Unk_110576c0(int Value, int Result);
};

UnkType_1104f6c0_Manager* Unk_11056900();
int Unk_1105c910(int Value);

// Unk_1104f6c0
void Unk_1104f6c0(int Value)
{
    Unk_11056900()->Unk_110576c0(Value, Unk_1105c910(Value));
}
