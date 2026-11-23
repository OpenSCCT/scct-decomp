// campaign_leaf_75ad80.cpp -- one function at file offset 0x75ad80, preferred VA 0x1105ad80. It
// calls the method at VA 0x1105acc0 with 0, clears the word at 0x0 and stores its argument at 0xc.
// The class, method and member names are invented; the offsets and the callee's address are the
// binary's.

class UnkType_1105ad80
{
public:
    void Unk_1105acc0(int Value);
    void Unk_1105ad80(int Value);

    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
};

// UnkType_1105ad80::Unk_1105ad80
void UnkType_1105ad80::Unk_1105ad80(int Value)
{
    Unk_1105acc0(0);
    unk_0 = 0;
    unk_c = Value;
}
