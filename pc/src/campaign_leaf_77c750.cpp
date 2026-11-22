// campaign_leaf_77c750.cpp -- one function at file offset 0x77c750, preferred VA 0x1107c750. It
// passes its argument, or 1 when the argument is zero, to the stdcall function at VA 0x1103c830
// (which forwards it to slot 0 of the object at VA 0x111c88a0) and stores the result at 0x0. The
// class, method and member names are invented; the offsets and the callee's address are the
// binary's.

int __stdcall Unk_1103c830(int Value);

class UnkType_1107c750
{
public:
    void Unk_1107c750(int Value);

    int unk_0;
};

// UnkType_1107c750::Unk_1107c750
void UnkType_1107c750::Unk_1107c750(int Value)
{
    if ( Value == 0 )
    {
        Value = 1;
    }
    unk_0 = Unk_1103c830(Value);
}
