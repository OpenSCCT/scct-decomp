// campaign_leaf_1ce210.cpp -- returns the element at the index argument of the 20-byte element
// array at offset 0x00 of this, or the last element when the index is not below the count at
// offset 0x14. File offset 0x1ce210, VA 0x10ace210. The class and method names are invented; the
// offsets are the binary's. The element type is a guess.

class UnkType_10ace210Elem
{
public:
    unsigned char unk_00[0x14];
};

class UnkType_10ace210
{
public:
    UnkType_10ace210Elem *UnkMethod_10ace210(int index);

private:
    UnkType_10ace210Elem *unk_00;
    unsigned char unk_04[0x10];     // not read by this function
    int unk_14;
};

// UnkType_10ace210::UnkMethod_10ace210
UnkType_10ace210Elem *UnkType_10ace210::UnkMethod_10ace210(int index)
{
    if (index < unk_14)
        return &unk_00[index];
    return &unk_00[unk_14 - 1];
}
