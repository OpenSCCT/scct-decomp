// campaign_leaf_478650.cpp -- destructor at VA 0x10d78650 of a class with two 12-byte members,
// each destroyed by the destructor at VA 0x10d77700. All names are invented.

class UnkType_10d77700
{
public:
    ~UnkType_10d77700();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10d78650
{
public:
    ~UnkType_10d78650();

private:
    UnkType_10d77700 unk_00;
    UnkType_10d77700 unk_0c;
};

// UnkType_10d78650::~UnkType_10d78650
UnkType_10d78650::~UnkType_10d78650()
{
}
