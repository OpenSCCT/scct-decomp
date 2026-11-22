// campaign_leaf_77c700.cpp -- free function at VA 0x1107c700: passes its argument, or 1 when the
// argument is zero, to the stdcall function at VA 0x1103c830. All names are invented.

void __stdcall Unk_1103c830(int Value);

// Unk_1107c700
void Unk_1107c700(int Value)
{
    if ( Value == 0 )
    {
        Value = 1;
    }
    Unk_1103c830(Value);
}
