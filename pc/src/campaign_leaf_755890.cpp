// campaign_leaf_755890.cpp -- one function at file offset 0x755890, preferred VA 0x11055890. When
// the word at 0x8 of the object is zero it passes the pointer at 0x0 to the stdcall function at VA
// 0x11049c70; it then passes the object to the stdcall function at VA 0x1103c870 (which forwards
// it to slot 2 of the object at VA 0x111c88a0). The type and function names are invented; the
// offsets and the addresses are the binary's.

void __stdcall Unk_11049c70(void* Pointer);
void __stdcall Unk_1103c870(void* Pointer);

struct UnkType_11055890
{
    void* unk_0;
    int unk_4;
    int unk_8;
};

// Unk_11055890
void Unk_11055890(UnkType_11055890* Object)
{
    if ( Object->unk_8 == 0 )
    {
        Unk_11049c70(Object->unk_0);
    }
    Unk_1103c870(Object);
}
