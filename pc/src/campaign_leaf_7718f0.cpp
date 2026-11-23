// campaign_leaf_7718f0.cpp -- one function at file offset 0x7718f0, preferred VA 0x110718f0. It
// releases the block at 0x38, with its four buffers from 0x4 to 0x10 that are set, through the
// stdcall function at VA 0x1103c870, then stores there a new 0x14-byte block allocated through
// the stdcall function at VA 0x1103c830 and constructed from its argument by the constructor at
// VA 0x11071640 (null when the allocation fails). The class and member names are invented; the
// offsets and the addresses are the binary's.

#include <new>

void __stdcall Unk_1103c870(void* Pointer);
void* __stdcall Unk_1103c830(unsigned int Size);

class UnkType_110718f0_Block
{
public:
    UnkType_110718f0_Block(int Value);

    int unk_0;
    void* unk_4;
    void* unk_8;
    void* unk_c;
    void* unk_10;
};

class UnkType_110718f0
{
public:
    void Unk_110718f0(int Value);

    unsigned char unk_0[0x38];
    UnkType_110718f0_Block* unk_38;
};

// UnkType_110718f0::Unk_110718f0
void UnkType_110718f0::Unk_110718f0(int Value)
{
    UnkType_110718f0_Block* Old;

    Old = unk_38;
    if ( Old != 0 )
    {
        if ( Old->unk_4 != 0 )
        {
            Unk_1103c870(Old->unk_4);
        }
        if ( Old->unk_8 != 0 )
        {
            Unk_1103c870(Old->unk_8);
        }
        if ( Old->unk_c != 0 )
        {
            Unk_1103c870(Old->unk_c);
        }
        if ( Old->unk_10 != 0 )
        {
            Unk_1103c870(Old->unk_10);
        }
        Unk_1103c870(Old);
    }
    unk_38 = new (Unk_1103c830(sizeof(UnkType_110718f0_Block))) UnkType_110718f0_Block(Value);
}
