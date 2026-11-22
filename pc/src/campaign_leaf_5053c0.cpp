// campaign_leaf_5053c0.cpp -- destructor at VA 0x10e053c0: destroys the member at offset 0x0c with
// the destructor at VA 0x10e016e0, then runs the base destructor at VA 0x10fedb30. All names are
// invented.

class UnkType_10fedb30
{
public:
    ~UnkType_10fedb30();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10e016e0
{
public:
    ~UnkType_10e016e0();

private:
    int unk_00;
};

class UnkType_10e053c0 : public UnkType_10fedb30
{
public:
    ~UnkType_10e053c0();

private:
    UnkType_10e016e0 unk_0c;
};

// UnkType_10e053c0::~UnkType_10e053c0
UnkType_10e053c0::~UnkType_10e053c0()
{
}
