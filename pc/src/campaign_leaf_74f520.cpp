// campaign_leaf_74f520.cpp -- one function at file offset 0x74f520, preferred VA 0x1104f520. It
// passes its four arguments, the first by reference, to the method at VA 0x1105a6b0 of the object
// returned by the function at VA 0x11056900 (which returns the address of the global at VA
// 0x1132ea08). The type and function names are invented; the offset and the addresses are the
// binary's.

class UnkType_1104f520_Manager
{
public:
    void Unk_1105a6b0(const int& First, int Second, int Third, int Fourth);
};

UnkType_1104f520_Manager* Unk_11056900();

// Unk_1104f520
void Unk_1104f520(int First, int Second, int Third, int Fourth)
{
    Unk_11056900()->Unk_1105a6b0(First, Second, Third, Fourth);
}
