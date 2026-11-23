// campaign_leaf_75fb80.cpp -- one function at file offset 0x75fb80, preferred VA 0x1105fb80. When
// the pointer at 0x0 is set it passes it to the function at VA 0x109014a0 (which forwards it to
// slot 2 of the object at VA 0x111c88a0) and clears it; it then zeroes the words at 0x14, 0x4, 0x8
// and 0xc. The class, method and member names are invented; the offsets and the callee's address
// are the binary's.

void Unk_109014a0(void* Pointer);

class UnkType_1105fb80
{
public:
    void Unk_1105fb80();

    void* unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
};

// UnkType_1105fb80::Unk_1105fb80
void UnkType_1105fb80::Unk_1105fb80()
{
    if ( unk_0 != 0 )
    {
        Unk_109014a0(unk_0);
        unk_0 = 0;
    }
    unk_14 = 0;
    unk_4 = 0;
    unk_8 = 0;
    unk_c = 0;
}
