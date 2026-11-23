// campaign_leaf_76e210.cpp -- one function at file offset 0x76e210, preferred VA 0x1106e210. It
// fills the first 0xdc bytes of the record with zero through the stdcall function at VA 0x1103c650,
// stores its second argument at 0x4 and its third at 0x0, the byte 0x40 at 0x8 and 1 at 0x24. The
// type and function names are invented; the offsets and the callee's address are the binary's.

struct UnkType_1106e210
{
    int unk_0;
    int unk_4;
    unsigned char unk_8;
    unsigned char unk_9[0x24 - 0x9];
    int unk_24;
};

void __stdcall Unk_1103c650(void* Block, int Value, int Size);

// Unk_1106e210
void __stdcall Unk_1106e210(UnkType_1106e210* Record, int Second, int Third)
{
    Unk_1103c650(Record, 0, 0xdc);
    Record->unk_4 = Second;
    Record->unk_0 = Third;
    Record->unk_8 = 0x40;
    Record->unk_24 = 1;
}
