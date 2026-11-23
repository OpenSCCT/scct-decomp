// campaign_leaf_749840.cpp -- one function at file offset 0x749840, preferred VA 0x11049840. It
// passes its argument to the stdcall function at VA 0x1104b3b0 and then to the function at VA
// 0x1104f640. The function names are invented; the offset and the addresses are the binary's.

void __stdcall Unk_1104b3b0(int Value);
void Unk_1104f640(int Value);

// Unk_11049840
void Unk_11049840(int Value)
{
    Unk_1104b3b0(Value);
    Unk_1104f640(Value);
}
