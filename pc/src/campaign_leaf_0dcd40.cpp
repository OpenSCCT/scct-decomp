// campaign_leaf_0dcd40.cpp -- copy constructor at VA 0x109dcd40 of a dynamic array of 4-byte words
// (data pointer at 0x00, count at 0x04): clears the pointer, takes the other's count, calls the
// method at VA 0x10ccb3c0 with the element size 4 and copies every word. The class, member and
// method names are invented; the offsets and the address are the binary's.

class UnkType_109dcd40_Base
{
public:
    UnkType_109dcd40_Base(int Count, int ElementSize)
        : unk_00(0), unk_04(Count)
    {
        Unk_10ccb3c0(ElementSize);
    }

    void Unk_10ccb3c0(int ElementSize);

protected:
    void* unk_00;
    int unk_04;
};

class UnkType_109dcd40 : public UnkType_109dcd40_Base
{
public:
    UnkType_109dcd40(const UnkType_109dcd40& Other);
};

// UnkType_109dcd40::UnkType_109dcd40
UnkType_109dcd40::UnkType_109dcd40(const UnkType_109dcd40& Other)
    : UnkType_109dcd40_Base(Other.unk_04, sizeof(int))
{
    for ( int i = 0; i < unk_04; i++ )
    {
        ((int*)unk_00)[i] = ((int*)Other.unk_00)[i];
    }
}
