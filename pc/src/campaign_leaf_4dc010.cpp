// campaign_leaf_4dc010.cpp -- one function at file offset 0x4dc010, preferred VA 0x10ddc010.
// The virtual destructor deletes the object at offset 0x64, if any, through its virtual destructor
// and clears the pointer, then runs the base destructor at 0x10dc13b0. The class and member names
// are invented; the offset and the bytes are the binary's.

class UnkType_10ddc010_Item
{
public:
    virtual ~UnkType_10ddc010_Item();
};

class UnkType_10ddc010_Base
{
public:
    unsigned char unk_4[0x60];

    virtual ~UnkType_10ddc010_Base();
};

class UnkType_10ddc010 : public UnkType_10ddc010_Base
{
public:
    UnkType_10ddc010_Item* unk_64;

    virtual ~UnkType_10ddc010();
};

// UnkType_10ddc010::~UnkType_10ddc010
UnkType_10ddc010::~UnkType_10ddc010()
{
    if ( unk_64 != 0 )
    {
        delete unk_64;
        unk_64 = 0;
    }
}
