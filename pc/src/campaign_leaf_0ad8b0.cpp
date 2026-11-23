// campaign_leaf_0ad8b0.cpp -- constructor at VA 0x109ad8b0 (vtable at VA 0x110ccd68): runs the base
// class constructor at VA 0x10cd7930, then the constructor at VA 0x10aa6d50 of the member at 0x84.
// The class and member names are invented; the offsets and the addresses are the binary's.

class UnkType_109ad8b0_Base
{
public:
    UnkType_109ad8b0_Base();
    virtual ~UnkType_109ad8b0_Base();

protected:
    unsigned char unk_04[0x84 - 0x04];
};

class UnkType_109ad8b0_Member
{
public:
    UnkType_109ad8b0_Member();

private:
    unsigned char unk_00[0x04];
};

class UnkType_109ad8b0 : public UnkType_109ad8b0_Base
{
public:
    UnkType_109ad8b0();
    virtual ~UnkType_109ad8b0();

private:
    UnkType_109ad8b0_Member unk_84;
};

// UnkType_109ad8b0::UnkType_109ad8b0
UnkType_109ad8b0::UnkType_109ad8b0()
{
}
