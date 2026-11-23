// campaign_leaf_2e6670.cpp -- destructor at VA 0x10be6670 of a class with a vtable (VA 0x110ecab0):
// calls the method at VA 0x10cd7a30, then destroys the dynamic arrays at 0x314 and 0x308 (contents
// removed through the methods at VA 0x10be5f60 and VA 0x10be5ed0, element size 4 and 4; data freed
// through virtual slot 2 of the allocator at VA 0x111c88a0; three words cleared), and runs the base
// class destructor at VA 0x1092ad20. The class, member and method names are invented; the offsets
// and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10be6670_Base
{
public:
    virtual ~UnkType_10be6670_Base();

    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x308 - 0x04];
};

class UnkType_10be6670_308
{
public:
    ~UnkType_10be6670_308()
    {
        Unk_10be5ed0(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10be5ed0(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10be6670_314
{
public:
    ~UnkType_10be6670_314()
    {
        Unk_10be5f60(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10be5f60(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10be6670 : public UnkType_10be6670_Base
{
public:
    virtual ~UnkType_10be6670();

private:
    UnkType_10be6670_308 unk_308;
    UnkType_10be6670_314 unk_314;
};

// UnkType_10be6670::~UnkType_10be6670
UnkType_10be6670::~UnkType_10be6670()
{
    Unk_10cd7a30();
}
