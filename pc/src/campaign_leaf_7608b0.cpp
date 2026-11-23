// campaign_leaf_7608b0.cpp -- one function at file offset 0x7608b0, preferred VA 0x110608b0. When
// the pointer at 0x4 is set it passes it to the function at VA 0x109014a0 (which forwards it to
// slot 2 of the object at VA 0x111c88a0) and clears it. The class, method and member names are
// invented; the offsets and the callee's address are the binary's.

void Unk_109014a0(void* Pointer);

class UnkType_110608b0
{
public:
    void Unk_110608b0();

    int unk_0;
    void* unk_4;
};

// UnkType_110608b0::Unk_110608b0
void UnkType_110608b0::Unk_110608b0()
{
    if ( unk_4 != 0 )
    {
        Unk_109014a0(unk_4);
        unk_4 = 0;
    }
}
