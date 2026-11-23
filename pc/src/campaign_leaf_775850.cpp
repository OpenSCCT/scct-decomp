// campaign_leaf_775850.cpp -- one function at file offset 0x775850, preferred VA 0x11075850. A
// destructor: it installs the vtable at VA 0x11177708, releases the buffers at 0x68, 0x70, 0x74,
// 0x7c, 0x88, 0x54 and 0x58 that are set through the stdcall function at VA 0x1103c870 and runs
// the base destructor at VA 0x1106f8d0. The class names are invented; the offsets and the
// addresses are the binary's.

void __stdcall Unk_1103c870(void* Pointer);

class UnkType_11075850_Base
{
public:
    virtual ~UnkType_11075850_Base();

    unsigned char unk_4[0x54 - 0x4];
};

class UnkType_11075850 : public UnkType_11075850_Base
{
public:
    virtual ~UnkType_11075850();

    void* unk_54;
    void* unk_58;
    unsigned char unk_5c[0x68 - 0x5c];
    void* unk_68;
    unsigned char unk_6c[0x70 - 0x6c];
    void* unk_70;
    void* unk_74;
    unsigned char unk_78[0x7c - 0x78];
    void* unk_7c;
    unsigned char unk_80[0x88 - 0x80];
    void* unk_88;
};

// UnkType_11075850::~UnkType_11075850
UnkType_11075850::~UnkType_11075850()
{
    if ( unk_68 != 0 )
    {
        Unk_1103c870(unk_68);
    }
    if ( unk_70 != 0 )
    {
        Unk_1103c870(unk_70);
    }
    if ( unk_74 != 0 )
    {
        Unk_1103c870(unk_74);
    }
    if ( unk_7c != 0 )
    {
        Unk_1103c870(unk_7c);
    }
    if ( unk_88 != 0 )
    {
        Unk_1103c870(unk_88);
    }
    if ( unk_54 != 0 )
    {
        Unk_1103c870(unk_54);
    }
    if ( unk_58 != 0 )
    {
        Unk_1103c870(unk_58);
    }
}
