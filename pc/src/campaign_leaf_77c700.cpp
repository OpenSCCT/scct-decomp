// campaign_leaf_77c700.cpp -- one function at file offset 0x77c700, preferred VA 0x1107c700. It
// passes its argument, or 1 when the argument is zero, to the stdcall function at VA 0x1103c830
// and returns the result. The function names are invented; the offset and the callee's address
// are the binary's.

int __stdcall Unk_1103c830(int Value);

// Unk_1107c700
int Unk_1107c700(int Value)
{
    if ( Value == 0 )
    {
        Value = 1;
    }
    return Unk_1103c830(Value);
}
