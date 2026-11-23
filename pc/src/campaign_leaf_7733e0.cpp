// campaign_leaf_7733e0.cpp -- one function at file offset 0x7733e0, preferred VA 0x110733e0. A
// destructor: it installs the vtable at VA 0x11177210, releases the pointer at 0x50 through the
// stdcall function at VA 0x1103c870 (which forwards it to slot 2 of the object at VA 0x111c88a0)
// when it is set, clearing the words at 0x50 and 0x54, and runs the base destructor at VA
// 0x1106eb50. The class names are invented; the offsets and the addresses are the binary's.

void __stdcall Unk_1103c870(void* Pointer);

class UnkType_110733e0_Base
{
public:
    virtual ~UnkType_110733e0_Base();

    unsigned char unk_4[0x50 - 0x4];
};

class UnkType_110733e0 : public UnkType_110733e0_Base
{
public:
    virtual ~UnkType_110733e0();

    void* unk_50;
    int unk_54;
};

// UnkType_110733e0::~UnkType_110733e0
UnkType_110733e0::~UnkType_110733e0()
{
    if ( unk_50 != 0 )
    {
        Unk_1103c870(unk_50);
        unk_50 = 0;
        unk_54 = 0;
    }
}
