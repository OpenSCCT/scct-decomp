// campaign_leaf_76dd70.cpp -- one function at file offset 0x76dd70, preferred VA 0x1106dd70. When
// the pointer at 0x28 is set it passes it to the stdcall function at VA 0x1103c870 (which forwards
// it to slot 2 of the object at VA 0x111c88a0) and clears it. The class, method and member names
// are invented; the offset and the callee's address are the binary's.

void __stdcall Unk_1103c870(void* Pointer);

class UnkType_1106dd70
{
public:
    void Unk_1106dd70();

    unsigned char unk_0[0x28];
    void* unk_28;
};

// UnkType_1106dd70::Unk_1106dd70
void UnkType_1106dd70::Unk_1106dd70()
{
    if ( unk_28 != 0 )
    {
        Unk_1103c870(unk_28);
        unk_28 = 0;
    }
}
