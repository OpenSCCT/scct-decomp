// campaign_leaf_4ab4f0.cpp -- destructor at VA 0x10dab4f0 of a class with two members at 0 and
// 0x30, each destroyed by the destructor at VA 0x10d9d610. All names are invented.

class UnkType_10d9d610
{
public:
    ~UnkType_10d9d610();

private:
    unsigned char unk_00[0x30];
};

class UnkType_10dab4f0
{
public:
    ~UnkType_10dab4f0();

private:
    UnkType_10d9d610 unk_00;
    UnkType_10d9d610 unk_30;
};

// UnkType_10dab4f0::~UnkType_10dab4f0
UnkType_10dab4f0::~UnkType_10dab4f0()
{
}
