// campaign_leaf_74bab0.cpp -- one function at file offset 0x74bab0, preferred VA 0x1104bab0. When
// the word at 0x4 of the record is zero it passes the word at 0x10 to the method at VA 0x110572b0
// of the object returned by the function at VA 0x11056900 (which returns the address of the
// global at VA 0x1132ea08). The type and function names are invented; the offsets and the
// addresses are the binary's.

class UnkType_1104bab0_Manager
{
public:
    void Unk_110572b0(int Value);
};

UnkType_1104bab0_Manager* Unk_11056900();

struct UnkType_1104bab0
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
};

// Unk_1104bab0
void __stdcall Unk_1104bab0(UnkType_1104bab0* Record)
{
    if ( Record->unk_4 == 0 )
    {
        Unk_11056900()->Unk_110572b0(Record->unk_10);
    }
}
