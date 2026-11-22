// campaign_leaf_49be10.cpp -- destructor at VA 0x10d9be10 of a polymorphic class whose vtable is at
// VA 0x1113e14c; destroys the member at offset 0x10 with the destructor at VA 0x10d8edb0, then
// runs the base destructor at VA 0x10dae3c0. All names are invented.

class UnkType_10dae3c0
{
public:
    virtual ~UnkType_10dae3c0();

private:
    unsigned char unk_04[0xc];
};

class UnkType_10d8edb0
{
public:
    ~UnkType_10d8edb0();

private:
    int unk_00;
};

class UnkType_10d9be10 : public UnkType_10dae3c0
{
public:
    virtual ~UnkType_10d9be10();

private:
    UnkType_10d8edb0 unk_10;
};

// UnkType_10d9be10::~UnkType_10d9be10
UnkType_10d9be10::~UnkType_10d9be10()
{
}
