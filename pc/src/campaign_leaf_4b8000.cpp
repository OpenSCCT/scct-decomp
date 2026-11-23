// campaign_leaf_4b8000.cpp -- one function at file offset 0x4b8000, preferred VA 0x10db8000.
// The destructor calls the method at 0x10db8c30 and then the base destructor at 0x10da2970. The
// class names are invented; the offset and the bytes are the binary's.

class UnkType_10db8000_Base
{
public:
    virtual ~UnkType_10db8000_Base();
};

class UnkType_10db8000 : public UnkType_10db8000_Base
{
public:
    virtual ~UnkType_10db8000();

    void Unk_10db8c30();
};

// UnkType_10db8000::~UnkType_10db8000
UnkType_10db8000::~UnkType_10db8000()
{
    Unk_10db8c30();
}
