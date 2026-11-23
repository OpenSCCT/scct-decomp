// campaign_leaf_253160.cpp -- a member function at VA 0x10b53160: when the byte at 0x3c is already
// set it returns true; otherwise, when the member at VA 0x10b65b30 accepts its argument, it stores
// in the bytes at 0x44 and 0x45 what the member at VA 0x10d2c120 of the object the pointer at 0x40
// refers to returns for the globals at VA 0x1122ded4 and 0x1122ded8, sets that object's byte at
// 0xb5 and calls its member at VA 0x10d2a530 with 1 and 1. It stores and returns whether that
// happened. The class, method, member and global names are invented; the offsets and addresses
// are the binary's.

#include "campaign_global_1122ded4.h"
#include "campaign_global_1122ded8.h"

class UnkType_10b53160_Target
{
public:
    bool Unk_10d2c120(int Name);
    void Unk_10d2a530(int First, int Second);

    unsigned char unk_00[0xb5];
    bool unk_b5;
};

class UnkType_10b53160
{
public:
    bool Unk_10b65b30(int Value);
    bool Unk_10b53160(int Value);

private:
    unsigned char unk_00[0x3c];
    bool unk_3c;
    unsigned char unk_3d[0x40 - 0x3d];
    UnkType_10b53160_Target* unk_40;
    bool unk_44;
    bool unk_45;
};

// UnkType_10b53160::Unk_10b53160
bool UnkType_10b53160::Unk_10b53160(int Value)
{
    if ( unk_3c )
    {
        return true;
    }
    bool Result = false;
    if ( Unk_10b65b30(Value) )
    {
        unk_44 = unk_40->Unk_10d2c120(GUnk_1122ded4);
        unk_45 = unk_40->Unk_10d2c120(GUnk_1122ded8);
        Result = true;
        unk_40->unk_b5 = true;
        unk_40->Unk_10d2a530(1, 1);
    }
    unk_3c = Result;
    return Result;
}
