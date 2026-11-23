// campaign_leaf_762490.cpp -- one function at file offset 0x762490, preferred VA 0x11062490. For
// each of the blocks at 0x3c and 0x44 that is set it passes the block and 8 to the stdcall
// function at VA 0x1103c4d0, clears the block pointer and the word at 0x48 or 0x4c. The class,
// method and member names are invented; the offsets and the callee's address are the binary's.

void __stdcall Unk_1103c4d0(void* Block, int Alignment);

class UnkType_11062490
{
public:
    void Unk_11062490();

    unsigned char unk_0[0x3c];
    void* unk_3c;
    int unk_40;
    void* unk_44;
    int unk_48;
    int unk_4c;
};

// UnkType_11062490::Unk_11062490
void UnkType_11062490::Unk_11062490()
{
    if ( unk_3c != 0 )
    {
        Unk_1103c4d0(unk_3c, 8);
        unk_3c = 0;
        unk_48 = 0;
    }
    if ( unk_44 != 0 )
    {
        Unk_1103c4d0(unk_44, 8);
        unk_44 = 0;
        unk_4c = 0;
    }
}
