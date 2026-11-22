// campaign_leaf_328d80.cpp -- destructor of the class at VA 0x10c28d80, which destroys two
// 12-byte members at 0x10 and 0x04 with the destructor at VA 0x1090ba70. The class names are
// invented; the offsets and the member destructor's address are the binary's.

class UnkType_1090ba70
{
public:
    ~UnkType_1090ba70();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10c28d80
{
public:
    ~UnkType_10c28d80();

private:
    int unk_00;
    UnkType_1090ba70 unk_04;
    UnkType_1090ba70 unk_10;
};

// UnkType_10c28d80::~UnkType_10c28d80
UnkType_10c28d80::~UnkType_10c28d80()
{
}
