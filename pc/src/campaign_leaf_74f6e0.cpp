// campaign_leaf_74f6e0.cpp -- one function at file offset 0x74f6e0, preferred VA 0x1104f6e0. It
// passes its two arguments to the function at VA 0x1105c9f0 and then to the method at VA
// 0x11057710 of the object returned by the function at VA 0x11056900 (which returns the address of
// the global at VA 0x1132ea08). The type and function names are invented; the offset and the
// addresses are the binary's.

class UnkType_1104f6e0_Manager
{
public:
    void Unk_11057710(int First, int Second);
};

UnkType_1104f6e0_Manager* Unk_11056900();
void Unk_1105c9f0(int First, int Second);

// Unk_1104f6e0
void Unk_1104f6e0(int First, int Second)
{
    Unk_1105c9f0(First, Second);
    Unk_11056900()->Unk_11057710(First, Second);
}
