// campaign_leaf_4d6c70.cpp -- one function at file offset 0x4d6c70, preferred VA 0x10dd6c70.
// When the pointer at offset 8 is set it passes the result of the function at 0x10d8b460, called
// with that pointer and 10, to the function at 0x10d8b550 and clears the pointer; the same bytes as
// 0x4b49c0. The class, function and member names are invented; the offset and the bytes are the
// binary's.

void* Unk_10d8b460(void* Block, int Kind);
void Unk_10d8b550(void* Block);

class UnkType_10dd6c70
{
public:
    int unk_0;
    int unk_4;
    void* unk_8;

    void Unk_10dd6c70();
};

// UnkType_10dd6c70::Unk_10dd6c70
void UnkType_10dd6c70::Unk_10dd6c70()
{
    if ( unk_8 != 0 )
    {
        Unk_10d8b550(Unk_10d8b460(unk_8, 10));
        unk_8 = 0;
    }
}
