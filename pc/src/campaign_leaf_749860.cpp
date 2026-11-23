// campaign_leaf_749860.cpp -- one function at file offset 0x749860, preferred VA 0x11049860. It
// passes its argument to the stdcall function at VA 0x1104b740 and then to the function at VA
// 0x1104f660. The function names are invented; the offset and the addresses are the binary's.

void __stdcall Unk_1104b740(int Value);
void Unk_1104f660(int Value);

// Unk_11049860
void Unk_11049860(int Value)
{
    Unk_1104b740(Value);
    Unk_1104f660(Value);
}
