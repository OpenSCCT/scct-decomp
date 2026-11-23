// campaign_leaf_77c620.cpp -- one function at file offset 0x77c620, preferred VA 0x1107c620. It
// computes 8 minus the word at 0x4 of the record and, when that is below 8, passes the record, 0
// and the count to the function at VA 0x1107c2d0. The type and function names are invented; the
// offsets and the callee's address are the binary's.

struct UnkType_1107c620
{
    int unk_0;
    int unk_4;
};

void Unk_1107c2d0(UnkType_1107c620* Record, int Value, int Count);

// Unk_1107c620
void Unk_1107c620(UnkType_1107c620* Record)
{
    int Count;

    Count = 8 - Record->unk_4;
    if ( Count < 8 )
    {
        Unk_1107c2d0(Record, 0, Count);
    }
}
