// campaign_leaf_6effb0.cpp -- destructor at VA 0x10feffb0 of a class whose vtable is at VA 0x1116fff0:
// deletes the object at 0x0c through its virtual destructor when it is set, then runs the base
// destructor at VA 0x10e066c0. The class and member names are invented; the offsets and addresses
// are the binary's.

class UnkType_10feffb0_Member
{
public:
    virtual ~UnkType_10feffb0_Member();
};

class UnkType_10feffb0_Base
{
public:
    virtual ~UnkType_10feffb0_Base();

private:
    int unk_4;
    int unk_8;
};

class UnkType_10feffb0 : public UnkType_10feffb0_Base
{
public:
    virtual ~UnkType_10feffb0();

private:
    UnkType_10feffb0_Member* unk_c;
};

// UnkType_10feffb0::~UnkType_10feffb0
UnkType_10feffb0::~UnkType_10feffb0()
{
    if ( unk_c )
    {
        delete unk_c;
    }
}
