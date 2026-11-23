// campaign_leaf_4d6f00.cpp -- one function at file offset 0x4d6f00, preferred VA 0x10dd6f00.
// The virtual destructor passes the int at offset 0x68, when set, to the method at 0x10da8520 of
// the object at offset 0x64 and then runs the base destructor at 0x10dc13b0. The class, method and
// member names are invented; the offset and the bytes are the binary's.

class UnkType_10dd6f00_Callee
{
public:
    void Unk_10da8520(int Value);
};

class UnkType_10dd6f00_Base
{
public:
    unsigned char unk_4[0x60];

    virtual ~UnkType_10dd6f00_Base();
};

class UnkType_10dd6f00 : public UnkType_10dd6f00_Base
{
public:
    UnkType_10dd6f00_Callee* unk_64;
    int unk_68;

    virtual ~UnkType_10dd6f00();
};

// UnkType_10dd6f00::~UnkType_10dd6f00
UnkType_10dd6f00::~UnkType_10dd6f00()
{
    if ( unk_68 != 0 )
    {
        unk_64->Unk_10da8520(unk_68);
    }
}
