// campaign_leaf_0c8620.cpp -- one function at file offset 0xc8620, preferred VA 0x109c8620. It
// copies the three-word block that its argument points to into this object, sets the word at
// offset 0xc to zero, and returns this object. The class and method names are invented; the offset
// and the bytes are the binary's.

struct UnkType_109c8620_Triple
{
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109c8620
{
public:
    UnkType_109c8620 *UnkSetVec(const UnkType_109c8620_Triple *In);

private:
    UnkType_109c8620_Triple unk_00;
    int unk_0c;
};

// UnkType_109c8620::UnkSetVec
UnkType_109c8620 *UnkType_109c8620::UnkSetVec(const UnkType_109c8620_Triple *In)
{
    unk_00 = *In;
    unk_0c = 0;
    return this;
}
