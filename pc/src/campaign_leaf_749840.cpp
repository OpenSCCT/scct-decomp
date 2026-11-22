// campaign_leaf_749840.cpp -- free function at VA 0x11049840: passes its argument to the stdcall function
// at VA 0x1104b3b0, then to the cdecl function at VA 0x1104f640. All names are invented.

void __stdcall Unk_1104b3b0(int Value);
void Unk_1104f640(int Value);

// Unk_11049840
void Unk_11049840(int Value)
{
    Unk_1104b3b0(Value);
    Unk_1104f640(Value);
}
