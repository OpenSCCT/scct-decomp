// campaign_leaf_755de0.cpp -- one function at file offset 0x755de0, preferred VA 0x11055de0. When
// the word at 0x18 of the object is zero it passes the pointer at 0x0 to the stdcall function at
// VA 0x11049c70; it then passes the object to the stdcall function at VA 0x1103c870 (which
// forwards it to slot 2 of the object at VA 0x111c88a0). The type and function names are
// invented; the offsets and the addresses are the binary's.

void __stdcall Unk_11049c70(void* Pointer);
void __stdcall Unk_1103c870(void* Pointer);

struct UnkType_11055de0
{
    void* unk_0;
    unsigned char unk_4[0x18 - 0x4];
    int unk_18;
};

// Unk_11055de0
void Unk_11055de0(UnkType_11055de0* Object)
{
    if ( Object->unk_18 == 0 )
    {
        Unk_11049c70(Object->unk_0);
    }
    Unk_1103c870(Object);
}
