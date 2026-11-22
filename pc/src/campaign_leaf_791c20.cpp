// campaign_leaf_791c20.cpp -- one function at file offset 0x791c20, preferred VA 0x11091c20. It
// swaps the three 32-bit values at offsets 0x0, 0x4 and 0x8 of this object with those of another
// object of the same layout. The class, method and member names are invented; the offset and the
// bytes are the binary's.

class UnkType_11091c20
{
public:
    void Swap(UnkType_11091c20& Other);

    int unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_11091c20::Swap
void UnkType_11091c20::Swap(UnkType_11091c20& Other)
{
    int Temp;

    Temp = unk_0;
    unk_0 = Other.unk_0;
    Other.unk_0 = Temp;
    Temp = unk_4;
    unk_4 = Other.unk_4;
    Other.unk_4 = Temp;
    Temp = unk_8;
    unk_8 = Other.unk_8;
    Other.unk_8 = Temp;
}
