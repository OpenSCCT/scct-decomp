// campaign_leaf_74fa40.cpp -- one function at file offset 0x74fa40, preferred VA 0x1104fa40, with
// the same body as the one at 0x74f520. It passes its four arguments, the first by reference, to
// the method at VA 0x1105a6b0 of the object returned by the function at VA 0x11056900 (which
// returns the address of the global at VA 0x1132ea08). The type and function names are invented;
// the offset and the addresses are the binary's.

class UnkType_1104fa40_Manager
{
public:
    void Unk_1105a6b0(const int& First, int Second, int Third, int Fourth);
};

UnkType_1104fa40_Manager* Unk_11056900();

// Unk_1104fa40
void Unk_1104fa40(int First, int Second, int Third, int Fourth)
{
    Unk_11056900()->Unk_1105a6b0(First, Second, Third, Fourth);
}
