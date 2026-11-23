// campaign_leaf_1aec80.cpp -- assignment operator at VA 0x10aaec80. It assigns the two 0x0c-byte
// members at 0x00 and 0x0c through their assignment operator (VA 0x1090b9a0), copies the eight
// words from 0x18 to 0x34, and returns this. The class and member names are invented.

class UnkType_10aaec80_1090b9a0
{
public:
    UnkType_10aaec80_1090b9a0& operator=(const UnkType_10aaec80_1090b9a0& Other);

private:
    int unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10aaec80
{
public:
    UnkType_10aaec80& operator=(const UnkType_10aaec80& Other);

private:
    UnkType_10aaec80_1090b9a0 unk_00;
    UnkType_10aaec80_1090b9a0 unk_0c;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
};

// UnkType_10aaec80::operator=
UnkType_10aaec80& UnkType_10aaec80::operator=(const UnkType_10aaec80& Other)
{
    unk_00 = Other.unk_00;
    unk_0c = Other.unk_0c;
    unk_18 = Other.unk_18;
    unk_1c = Other.unk_1c;
    unk_20 = Other.unk_20;
    unk_24 = Other.unk_24;
    unk_28 = Other.unk_28;
    unk_2c = Other.unk_2c;
    unk_30 = Other.unk_30;
    unk_34 = Other.unk_34;
    return *this;
}
