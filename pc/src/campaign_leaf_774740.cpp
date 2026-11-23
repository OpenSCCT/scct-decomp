// campaign_leaf_774740.cpp -- one function at file offset 0x774740, preferred VA 0x11074740. A
// destructor: it installs the vtable at VA 0x11177260, calls the method at VA 0x11073a70 when the
// word at 0x28 is set, and runs the base destructor at VA 0x1106f8d0. The class, method and member
// names are invented; the offsets and the addresses are the binary's.

class UnkType_11074740_Root
{
public:
    UnkType_11074740_Root();
    virtual ~UnkType_11074740_Root();
};

class UnkType_11074740_Base : public UnkType_11074740_Root
{
public:
    UnkType_11074740_Base();
    virtual ~UnkType_11074740_Base();

    unsigned char unk_4[0x20 - 0x4];
    int unk_20;
};

class UnkType_11074740 : public UnkType_11074740_Base
{
public:
    virtual ~UnkType_11074740();
    void Unk_11073a70();

    int unk_24;
    int unk_28;
};

// UnkType_11074740::~UnkType_11074740
UnkType_11074740::~UnkType_11074740()
{
    if ( unk_28 != 0 )
    {
        Unk_11073a70();
    }
}
