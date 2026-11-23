// campaign_leaf_140e80.cpp -- one function at file offset 0x140e80, preferred VA 0x10a40e80.
// The assignment operator: it assigns the 12-byte members at offsets 0, 0xc, 0x1c and 0x34 with
// the method at VA 0x109097e0, the one at offset 0x28 with the method at VA 0x1091c210 and copies
// the words at offsets 0x18 and 0x40; it returns its object.
// The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10a40e80_Text
{
public:
    void* unk_0;
    int unk_4;
    int unk_8;

    UnkType_10a40e80_Text& operator=(const UnkType_10a40e80_Text& Other);
};

class UnkType_10a40e80_List
{
public:
    void* unk_0;
    int unk_4;
    int unk_8;

    UnkType_10a40e80_List& operator=(const UnkType_10a40e80_List& Other);
};

class UnkType_10a40e80
{
public:
    UnkType_10a40e80_Text unk_0;
    UnkType_10a40e80_Text unk_c;
    int unk_18;
    UnkType_10a40e80_Text unk_1c;
    UnkType_10a40e80_List unk_28;
    UnkType_10a40e80_Text unk_34;
    int unk_40;

    UnkType_10a40e80& operator=(const UnkType_10a40e80& Other);
};

// UnkType_10a40e80::operator=
UnkType_10a40e80& UnkType_10a40e80::operator=(const UnkType_10a40e80& Other)
{
    unk_0 = Other.unk_0;
    unk_c = Other.unk_c;
    unk_18 = Other.unk_18;
    unk_1c = Other.unk_1c;
    unk_28 = Other.unk_28;
    unk_34 = Other.unk_34;
    unk_40 = Other.unk_40;
    return *this;
}
