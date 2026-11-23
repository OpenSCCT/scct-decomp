// campaign_leaf_76a730.cpp -- one function at file offset 0x76a730, preferred VA 0x1106a730. A
// destructor: it installs the vtable at VA 0x111768f8, releases the pointer at 0x50 through the
// stdcall function at VA 0x1103c870 (which forwards it to slot 2 of the object at VA 0x111c88a0)
// when it is set, clearing the words at 0x50, 0x4c and 0x3c, and runs the base destructor at VA
// 0x11061e60. The class names are invented; the offsets and the addresses are the binary's.

void __stdcall Unk_1103c870(void* Pointer);

class UnkType_1106a730_Base
{
public:
    virtual ~UnkType_1106a730_Base();

    unsigned char unk_4[0x3c - 0x4];
};

class UnkType_1106a730 : public UnkType_1106a730_Base
{
public:
    virtual ~UnkType_1106a730();

    int unk_3c;
    unsigned char unk_40[0x4c - 0x40];
    int unk_4c;
    void* unk_50;
};

// UnkType_1106a730::~UnkType_1106a730
UnkType_1106a730::~UnkType_1106a730()
{
    if ( unk_50 != 0 )
    {
        Unk_1103c870(unk_50);
        unk_50 = 0;
        unk_4c = 0;
        unk_3c = 0;
    }
}
