// campaign_leaf_096320.cpp -- virtual destructor at VA 0x10996320 (vtable at VA 0x110c8d30): calls
// the method at VA 0x10cd7a30, then destroys the dynamic array at 0x344 (method at VA 0x10992880),
// the dynamic array at 0x338 (method at VA 0x10929170, element size 4); each array is passed 0 and
// its count, then its data is freed through virtual slot 2 of the allocator global at VA
// 0x111c88a0; it ends in the outermost base destructor at VA 0x1092ad20. The class, member and
// method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10996320_Array1
{
public:
    ~UnkType_10996320_Array1()
    {
        Unk_10992880(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10992880(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10996320_Array2
{
public:
    ~UnkType_10996320_Array2()
    {
        Unk_10929170(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929170(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10996320_Base
{
public:
    virtual ~UnkType_10996320_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x338 - 0x04];
};

class UnkType_10996320 : public UnkType_10996320_Base
{
public:
    virtual ~UnkType_10996320();

private:
    UnkType_10996320_Array2 unk_338;
    UnkType_10996320_Array1 unk_344;
};

// UnkType_10996320::~UnkType_10996320
UnkType_10996320::~UnkType_10996320()
{
    Unk_10cd7a30();
}
