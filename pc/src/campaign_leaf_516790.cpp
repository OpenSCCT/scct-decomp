// campaign_leaf_516790.cpp -- assignment operator at VA 0x10e16790: assigns the base part (VA
// 0x10e16420), then copies the eleven words at 0x50-0x78 and the bytes at 0x7c and 0x7d. The class
// and member names are invented; the offsets and the address are the binary's.

class UnkType_10e16790_Base
{
public:
    UnkType_10e16790_Base& operator=(const UnkType_10e16790_Base& Other);

    int unk_00[0x14];
};

class UnkType_10e16790 : public UnkType_10e16790_Base
{
public:
    UnkType_10e16790& operator=(const UnkType_10e16790& Other);

    int unk_50;
    int unk_54;
    int unk_58;
    int unk_5c;
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6c;
    int unk_70;
    int unk_74;
    int unk_78;
    bool unk_7c;
    bool unk_7d;
};

// UnkType_10e16790::operator=
UnkType_10e16790& UnkType_10e16790::operator=(const UnkType_10e16790& Other)
{
    UnkType_10e16790_Base::operator=(Other);
    unk_50 = Other.unk_50;
    unk_54 = Other.unk_54;
    unk_58 = Other.unk_58;
    unk_5c = Other.unk_5c;
    unk_60 = Other.unk_60;
    unk_64 = Other.unk_64;
    unk_68 = Other.unk_68;
    unk_6c = Other.unk_6c;
    unk_70 = Other.unk_70;
    unk_74 = Other.unk_74;
    unk_78 = Other.unk_78;
    unk_7c = Other.unk_7c;
    unk_7d = Other.unk_7d;
    return *this;
}
