// campaign_leaf_47ded0.cpp -- destructor at VA 0x10d7ded0: destroys the members at offsets 4 and 0
// with the destructor at VA 0x10d7cf40, then runs the empty base destructor at VA 0x10d9d570. All
// names are invented.

class UnkType_10d9d570
{
public:
    ~UnkType_10d9d570();
};

class UnkType_10d7cf40
{
public:
    ~UnkType_10d7cf40();

private:
    int unk_00;
};

class UnkType_10d7ded0 : public UnkType_10d9d570
{
public:
    ~UnkType_10d7ded0();

private:
    UnkType_10d7cf40 unk_00;
    UnkType_10d7cf40 unk_04;
};

// UnkType_10d7ded0::~UnkType_10d7ded0
UnkType_10d7ded0::~UnkType_10d7ded0()
{
}
