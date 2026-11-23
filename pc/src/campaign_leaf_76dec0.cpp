// campaign_leaf_76dec0.cpp -- one function at file offset 0x76dec0, preferred VA 0x1106dec0. A
// destructor: it installs the vtable at VA 0x11176be0, releases the pointer at 0x28 through the
// stdcall function at VA 0x1103c870 (which forwards it to slot 2 of the object at VA 0x111c88a0)
// when it is set, clearing it, and runs the base destructor at VA 0x1105eee0. The class names are
// invented; the offsets and the addresses are the binary's.

void __stdcall Unk_1103c870(void* Pointer);

class UnkType_1106dec0_Base
{
public:
    virtual ~UnkType_1106dec0_Base();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_1106dec0 : public UnkType_1106dec0_Base
{
public:
    virtual ~UnkType_1106dec0();

    void* unk_28;
};

// UnkType_1106dec0::~UnkType_1106dec0
UnkType_1106dec0::~UnkType_1106dec0()
{
    if ( unk_28 != 0 )
    {
        Unk_1103c870(unk_28);
        unk_28 = 0;
    }
}
