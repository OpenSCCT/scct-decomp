// campaign_leaf_05e680.cpp -- copy constructor at VA 0x1095e680: constructs the member at 0x08 with
// the constructor at VA 0x10d7ce90, copies the byte at 0x00 and the value at 0x04, passes the other
// object's member at 0x08 to the method at VA 0x10d7cfe0 of this one's, and copies the value at
// 0x0c. The class and member names are invented; the offsets and the addresses are the binary's.

class UnkType_10d7ce90_05e680
{
public:
    UnkType_10d7ce90_05e680();
    void Unk_10d7cfe0(const UnkType_10d7ce90_05e680& Other);
};

class UnkType_1095e680
{
public:
    UnkType_1095e680(const UnkType_1095e680& Other);

private:
    unsigned char unk_00;
    int unk_04;
    UnkType_10d7ce90_05e680 unk_08;
    int unk_0c;
};

// UnkType_1095e680::UnkType_1095e680
UnkType_1095e680::UnkType_1095e680(const UnkType_1095e680& Other)
{
    unk_00 = Other.unk_00;
    unk_04 = Other.unk_04;
    unk_08.Unk_10d7cfe0(Other.unk_08);
    unk_0c = Other.unk_0c;
}
