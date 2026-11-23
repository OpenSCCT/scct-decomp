// campaign_leaf_74fb80.cpp -- one function at file offset 0x74fb80, preferred VA 0x1104fb80, with
// the same body as the one at 0x74f520. It passes its four arguments, the first by reference, to
// the method at VA 0x1105a6b0 of the object returned by the function at VA 0x11056900 (which
// returns the address of the global at VA 0x1132ea08). The type and function names are invented;
// the offset and the addresses are the binary's.

class UnkType_1104fb80_Manager
{
public:
    void Unk_1105a6b0(const int& First, int Second, int Third, int Fourth);
};

UnkType_1104fb80_Manager* Unk_11056900();

// Unk_1104fb80
void Unk_1104fb80(int First, int Second, int Third, int Fourth)
{
    Unk_11056900()->Unk_1105a6b0(First, Second, Third, Fourth);
}
