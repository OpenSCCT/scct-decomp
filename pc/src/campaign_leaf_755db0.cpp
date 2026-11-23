// campaign_leaf_755db0.cpp -- one function at file offset 0x755db0, preferred VA 0x11055db0. It
// returns 1 when the word at 0x18 of the object is clear and the function at VA 0x11049c20 accepts
// the pointer at 0x0; otherwise it passes the object to the stdcall function at VA 0x1103c870
// (which forwards it to slot 2 of the object at VA 0x111c88a0) and returns 0. The type and
// function names are invented; the offsets and the addresses are the binary's.

void __stdcall Unk_1103c870(void* Pointer);
int Unk_11049c20(void* Pointer);

struct UnkType_11055db0
{
    void* unk_0;
    unsigned char unk_4[0x18 - 0x4];
    int unk_18;
};

// Unk_11055db0
int Unk_11055db0(UnkType_11055db0* Object)
{
    if ( Object->unk_18 == 0 && Unk_11049c20(Object->unk_0) != 0 )
    {
        return 1;
    }
    Unk_1103c870(Object);
    return 0;
}
