// campaign_leaf_472620.cpp -- destructor at VA 0x10d72620 of a class with two 12-byte members,
// each destroyed by the destructor at VA 0x10d6fff0. All names are invented.

class UnkType_10d6fff0
{
public:
    ~UnkType_10d6fff0();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10d72620
{
public:
    ~UnkType_10d72620();

private:
    UnkType_10d6fff0 unk_00;
    UnkType_10d6fff0 unk_0c;
};

// UnkType_10d72620::~UnkType_10d72620
UnkType_10d72620::~UnkType_10d72620()
{
}
