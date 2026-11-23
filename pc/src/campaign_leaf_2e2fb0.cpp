// campaign_leaf_2e2fb0.cpp -- assignment operator at VA 0x10be2fb0 of a 0x44-byte class: copies the
// four words at 0x00-0x0c and the two flag bits at the start of 0x10, then assigns the members at
// 0x14, 0x20, 0x2c and 0x38 through their own assignment operators (VA 0x10be2db0, VA 0x10936110,
// VA 0x10bdcb80 and VA 0x10936060); returns this object. The class and member names are invented;
// the offsets and the addresses are the binary's.

class UnkType_10be2fb0_14
{
public:
    UnkType_10be2fb0_14& operator=(const UnkType_10be2fb0_14& Other);

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10be2fb0_20
{
public:
    UnkType_10be2fb0_20& operator=(const UnkType_10be2fb0_20& Other);

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10be2fb0_2c
{
public:
    UnkType_10be2fb0_2c& operator=(const UnkType_10be2fb0_2c& Other);

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10be2fb0_38
{
public:
    UnkType_10be2fb0_38& operator=(const UnkType_10be2fb0_38& Other);

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10be2fb0
{
public:
    UnkType_10be2fb0& operator=(const UnkType_10be2fb0& Other);

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    unsigned int unk_10_bit0 : 1;
    unsigned int unk_10_bit1 : 1;
    UnkType_10be2fb0_14 unk_14;
    UnkType_10be2fb0_20 unk_20;
    UnkType_10be2fb0_2c unk_2c;
    UnkType_10be2fb0_38 unk_38;
};

// UnkType_10be2fb0::operator=
UnkType_10be2fb0& UnkType_10be2fb0::operator=(const UnkType_10be2fb0& Other)
{
    unk_00 = Other.unk_00;
    unk_04 = Other.unk_04;
    unk_08 = Other.unk_08;
    unk_0c = Other.unk_0c;
    unk_10_bit0 = Other.unk_10_bit0;
    unk_10_bit1 = Other.unk_10_bit1;
    unk_14 = Other.unk_14;
    unk_20 = Other.unk_20;
    unk_2c = Other.unk_2c;
    unk_38 = Other.unk_38;
    return *this;
}
