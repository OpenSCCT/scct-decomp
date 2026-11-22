// campaign_leaf_4d53c0.cpp -- destructor at VA 0x10dd53c0 of a class with two members at 0 and
// 0x04, each destroyed by the destructor at VA 0x10d7cf40. All names are invented.

class UnkType_10d7cf40
{
public:
    ~UnkType_10d7cf40();

private:
    int unk_00;
};

class UnkType_10dd53c0
{
public:
    ~UnkType_10dd53c0();

private:
    UnkType_10d7cf40 unk_00;
    UnkType_10d7cf40 unk_04;
};

// UnkType_10dd53c0::~UnkType_10dd53c0
UnkType_10dd53c0::~UnkType_10dd53c0()
{
}
