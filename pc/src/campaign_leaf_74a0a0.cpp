// campaign_leaf_74a0a0.cpp -- one function at file offset 0x74a0a0, preferred VA 0x1104a0a0. When
// the word at 0x0 of the record is clear it passes the word at 0x14 to the function at VA
// 0x1104f950 if the word at 0x4 is set, then clears the word at 0x10 and sets the word at 0x0 to
// 1. The type and function names are invented; the offsets and the callee's address are the
// binary's.

struct UnkType_1104a0a0
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
};

void Unk_1104f950(int Value);

// Unk_1104a0a0
void Unk_1104a0a0(UnkType_1104a0a0* Record)
{
    if ( Record->unk_0 == 0 )
    {
        if ( Record->unk_4 != 0 )
        {
            Unk_1104f950(Record->unk_14);
        }
        Record->unk_10 = 0;
        Record->unk_0 = 1;
    }
}
