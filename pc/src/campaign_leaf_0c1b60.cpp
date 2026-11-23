// campaign_leaf_0c1b60.cpp -- constructor at VA 0x109c1b60 (vtable at VA 0x110ce278): runs the base
// class constructor at VA 0x10aa79d0, then zeroes the word at 0x2c. The class and member names are
// invented; the offsets and the addresses are the binary's.

class UnkType_109c1b60_Base
{
public:
    UnkType_109c1b60_Base();
    virtual ~UnkType_109c1b60_Base();

protected:
    unsigned char unk_04[0x2c - 0x04];
};

class UnkType_109c1b60 : public UnkType_109c1b60_Base
{
public:
    UnkType_109c1b60();
    virtual ~UnkType_109c1b60();

private:
    int unk_2c;
};

// UnkType_109c1b60::UnkType_109c1b60
UnkType_109c1b60::UnkType_109c1b60() : unk_2c(0)
{
}
