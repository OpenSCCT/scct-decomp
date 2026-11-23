// campaign_leaf_753370.cpp -- one function at file offset 0x753370, preferred VA 0x11053370. When
// the word at 0xc of the record is set and the word at 0x38 is not, it passes the record and its
// second argument to the stdcall function at VA 0x11052970; it then clears the word at 0x4. The
// type and function names are invented; the offsets and the callee's address are the binary's.

struct UnkType_11053370
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    unsigned char unk_10[0x38 - 0x10];
    int unk_38;
};

void __stdcall Unk_11052970(UnkType_11053370* Record, int Value);

// Unk_11053370
void __stdcall Unk_11053370(UnkType_11053370* Record, int Value)
{
    if ( Record->unk_c != 0 && Record->unk_38 == 0 )
    {
        Unk_11052970(Record, Value);
    }
    Record->unk_4 = 0;
}
