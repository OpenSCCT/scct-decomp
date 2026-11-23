// campaign_leaf_74fc80.cpp -- one function at file offset 0x74fc80, preferred VA 0x1104fc80. It
// passes its four arguments to the method at VA 0x11058960 of the object returned by the function
// at VA 0x11056900 (which returns the address of the global at VA 0x1132ea08). The type and
// function names are invented; the offset and the addresses are the binary's.

class UnkType_1104fc80_Manager
{
public:
    void Unk_11058960(int First, int Second, int Third, int Fourth);
};

UnkType_1104fc80_Manager* Unk_11056900();

// Unk_1104fc80
void Unk_1104fc80(int First, int Second, int Third, int Fourth)
{
    Unk_11056900()->Unk_11058960(First, Second, Third, Fourth);
}
