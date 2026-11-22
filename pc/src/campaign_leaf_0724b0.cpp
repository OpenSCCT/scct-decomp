// campaign_leaf_0724b0.cpp -- one function at file offset 0x724b0, preferred VA 0x109724b0. It
// copies the three words that its first argument points to into the words at offset 0, copies the
// three words that its second argument points to into the words at offset 0xc, sets the byte at
// offset 0x18 to 1, and returns this object. The class, struct, method and parameter names are
// invented; the offset and the bytes are the binary's.

struct UnkType_109724b0_Triple
{
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109724b0
{
public:
    UnkType_109724b0 *UnkSetPair(const UnkType_109724b0_Triple *First,
                                 const UnkType_109724b0_Triple *Second);

private:
    UnkType_109724b0_Triple unk_00;
    UnkType_109724b0_Triple unk_0c;
    unsigned char unk_18;           // set to 1
};

// UnkType_109724b0::UnkSetPair
UnkType_109724b0 *UnkType_109724b0::UnkSetPair(const UnkType_109724b0_Triple *First,
                                               const UnkType_109724b0_Triple *Second)
{
    unk_00 = *First;
    unk_0c = *Second;
    unk_18 = 1;
    return this;
}
