// campaign_leaf_143120.cpp -- one function at file offset 0x143120, preferred VA 0x10a43120.
// A constructor: it runs the middle class's constructor at VA 0x10a3b0d0, installs its virtual
// tables at offsets 0 and 0x28, constructs the member at offset 0x184 from an empty string
// (constructor at VA 0x10ad2120), clears three flags at 0x1cc, creates the helper at 0x1d4
// (allocated through the allocator at VA 0x111c88a0 with the tag "ProfileMgr", constructor at
// VA 0x10ae9780) for itself, and sets the members at 0x1d8 to -1 and 0xb4 to zero. Its class is
// the one destroyed by the destructor at VA 0x10a431c0.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

inline void* operator new(unsigned int Size, const unsigned short* Tag)
{
    return GUnk_111c88a0->Malloc(Size, Tag);
}

class UnkType_10a43120_Object
{
public:
    virtual ~UnkType_10a43120_Object();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a43120_Interface
{
public:
    virtual void Malloc();
};

class UnkType_10a43120_Middle : public UnkType_10a43120_Object, public UnkType_10a43120_Interface
{
public:
    unsigned char unk_2c[0xb4 - 0x2c];
    int unk_b4;
    unsigned char unk_b8[0x184 - 0xb8];

    UnkType_10a43120_Middle();
    virtual ~UnkType_10a43120_Middle();
};

class UnkType_10a43120_Member
{
public:
    unsigned char unk_0[0x48];

    UnkType_10a43120_Member(const unsigned short* Text);
    ~UnkType_10a43120_Member();
};

class UnkType_10a43120;

class UnkType_10a43120_Helper
{
public:
    void* unk_0;

    UnkType_10a43120_Helper(UnkType_10a43120* Owner);
};

class UnkType_10a43120 : public UnkType_10a43120_Middle
{
public:
    UnkType_10a43120_Member unk_184;
    unsigned int unk_1cc_0 : 4;
    unsigned int unk_1cc_4 : 1;
    unsigned int unk_1cc_5 : 1;
    unsigned int unk_1cc_6 : 1;
    unsigned char unk_1d0[0x1d4 - 0x1d0];
    UnkType_10a43120_Helper* unk_1d4;
    int unk_1d8;

    UnkType_10a43120();
    virtual ~UnkType_10a43120();
};

// UnkType_10a43120::UnkType_10a43120
UnkType_10a43120::UnkType_10a43120()
    : unk_184(L"")
{
    unk_1cc_4 = 0;
    unk_1cc_5 = 0;
    unk_1cc_6 = 0;
    unk_1d4 = new(L"ProfileMgr") UnkType_10a43120_Helper(this);
    unk_1d8 = -1;
    unk_b4 = 0;
}
