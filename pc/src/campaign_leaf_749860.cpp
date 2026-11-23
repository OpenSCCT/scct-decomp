// campaign_leaf_749860.cpp -- free function at VA 0x11049860: passes its argument to the stdcall
// function at VA 0x1104b740, then to the cdecl function at VA 0x1104f660. All names are invented.

void __stdcall Unk_1104b740(int Value);
void Unk_1104f660(int Value);

// Unk_11049860
void Unk_11049860(int Value)
{
    Unk_1104b740(Value);
    Unk_1104f660(Value);
}
