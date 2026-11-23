// campaign_leaf_7731c0.cpp -- one function at file offset 0x7731c0, preferred VA 0x110731c0. When
// the pointer at 0x50 is set it passes it to the stdcall function at VA 0x1103c870 (which forwards
// it to slot 2 of the object at VA 0x111c88a0) and clears the words at 0x50 and 0x54. The class,
// method and member names are invented; the offsets and the callee's address are the binary's.

void __stdcall Unk_1103c870(void* Pointer);

class UnkType_110731c0
{
public:
    void Unk_110731c0();

    unsigned char unk_0[0x50];
    void* unk_50;
    int unk_54;
};

// UnkType_110731c0::Unk_110731c0
void UnkType_110731c0::Unk_110731c0()
{
    if ( unk_50 != 0 )
    {
        Unk_1103c870(unk_50);
        unk_50 = 0;
        unk_54 = 0;
    }
}
