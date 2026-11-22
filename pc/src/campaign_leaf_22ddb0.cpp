// campaign_leaf_22ddb0.cpp -- destructor of the class at VA 0x10b2ddb0, which destroys three
// 12-byte members. The class names are invented; the offsets and the member destructor's address
// (VA 0x1090ba70) are the binary's.

class UnkType_1090ba70
{
public:
    ~UnkType_1090ba70();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b2ddb0
{
public:
    ~UnkType_10b2ddb0();

private:
    int unk_00;
    int unk_04;
    UnkType_1090ba70 unk_08;
    UnkType_1090ba70 unk_14;
    UnkType_1090ba70 unk_20;
};

// UnkType_10b2ddb0::~UnkType_10b2ddb0
UnkType_10b2ddb0::~UnkType_10b2ddb0()
{
}
