// campaign_leaf_75d970.cpp -- one function at file offset 0x75d970, preferred VA 0x1105d970, with
// the same body as the one at 0x75d330. When the word at 0x0 is set it releases the pointer at
// 0x1c through the stdcall function at VA 0x1103c870 (which forwards it to slot 2 of the object
// at VA 0x111c88a0), clearing it, and then clears the word at 0x0. The class, method and member
// names are invented; the offsets and the callee's address are the binary's.

void __stdcall Unk_1103c870(void* Pointer);

class UnkType_1105d970
{
public:
    void Unk_1105d970();

    int unk_0;
    unsigned char unk_4[0x1c - 0x4];
    void* unk_1c;
};

// UnkType_1105d970::Unk_1105d970
void UnkType_1105d970::Unk_1105d970()
{
    if ( unk_0 != 0 )
    {
        if ( unk_1c != 0 )
        {
            Unk_1103c870(unk_1c);
            unk_1c = 0;
        }
        unk_0 = 0;
    }
}
