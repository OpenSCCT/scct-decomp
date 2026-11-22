// versus_leaf_180460.cpp -- increments the counter at 0xc of its first argument and stores -1 or 1 through the second, by the byte at 0x318, at file offset 0x180460 (VA 0x10a80460).
// The class, record and method names are invented; the offsets, the argument sizes and the
// return conventions are the binary's.

struct UnkCounter_10a80460
{
    unsigned char unk_00[0xc];
    int unk_0c;                         // incremented by UnkFlagOut
};

class UnkType_10a80460
{
public:
    void UnkFlagOut(UnkCounter_10a80460 *Counter, int *Out);

private:
    unsigned char unk_00[0x318];        // not read by this function
    unsigned char unk_318;              // tested by UnkFlagOut
};

// UnkType_10a80460::UnkFlagOut
// Both arguments are popped (ret 8).
void UnkType_10a80460::UnkFlagOut(UnkCounter_10a80460 *Counter, int *Out)
{
    ++Counter->unk_0c;
    *Out = ( unk_318 & 1 ) ? -1 : 1;
}
