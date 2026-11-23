// campaign_leaf_106b00.cpp -- one function at file offset 0x106b00, preferred VA 0x10a06b00.
// A destructor: it installs its class's virtual table, calls the base's method at VA 0x10cd7a30,
// destroys the array at offset 0x124 (its method at VA 0x10929260 removes every element), the array
// at offset 0x118 (its method at VA 0x10929260 removes every element), the member at offset 0x34
// (destructor at VA 0x1093a2f0), the array at offset 0x28 (its method at VA 0x10a06950 removes
// every element), freeing each block through the allocator at VA 0x111c88a0, and the base
// destructor at VA 0x10cdc460 runs last.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a06b00_Object
{
public:
    virtual ~UnkType_10a06b00_Object();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a06b00_ArrayA
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10929260(int Index, int Count, int ElementSize);

    ~UnkType_10a06b00_ArrayA()
    {
        Unk_10929260(0, ArrayNum, 12);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a06b00_ArrayB
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a06950(int Index, int Count, int ElementSize);

    ~UnkType_10a06b00_ArrayB()
    {
        Unk_10a06950(0, ArrayNum, 48);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a06b00_Member
{
public:
    int unk_0;

    ~UnkType_10a06b00_Member();
};

class UnkType_10a06b00 : public UnkType_10a06b00_Object
{
public:
    UnkType_10a06b00_ArrayB unk_28;
    UnkType_10a06b00_Member unk_34;
    unsigned char unk_38[0x118 - 0x38];
    UnkType_10a06b00_ArrayA unk_118;
    UnkType_10a06b00_ArrayA unk_124;

    virtual ~UnkType_10a06b00();
};

// UnkType_10a06b00::~UnkType_10a06b00
UnkType_10a06b00::~UnkType_10a06b00()
{
    Unk_10cd7a30();
}
