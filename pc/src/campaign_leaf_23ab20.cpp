// campaign_leaf_23ab20.cpp -- destructor of the class at VA 0x10b3ab20, which destroys two
// 12-byte members at 0x00 and 0x10 with the destructor at VA 0x1090ba70. The class names are
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

class UnkType_10b3ab20
{
public:
    ~UnkType_10b3ab20();

private:
    UnkType_1090ba70 unk_00;
    int unk_0c;
    UnkType_1090ba70 unk_10;
};

// UnkType_10b3ab20::~UnkType_10b3ab20
UnkType_10b3ab20::~UnkType_10b3ab20()
{
}
