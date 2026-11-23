// campaign_leaf_255ed0.cpp -- a member function at VA 0x10b55ed0: when the byte at 0x3c is already
// set it returns true; otherwise, when the member at VA 0x10b65b30 accepts its argument, it calls
// the member at VA 0x10d2a530 of the object the pointer at 0x40 refers to with 1 and 1, sets that
// object's byte at 0xb5, stores in the bytes at 0x60 and 0x61 what that object's member at VA
// 0x10d2c120 returns for the globals at VA 0x1122e02c and 0x1122e030, and clears the int at 0x2c
// of the object the pointer at 0x44 refers to, when there is one. It stores and returns whether
// that happened. The class, method, member and global names are invented; the offsets and
// addresses are the binary's.

#include "campaign_global_1122e02c.h"
#include "campaign_global_1122e030.h"

class UnkType_10b55ed0_Target
{
public:
    bool Unk_10d2c120(int Name);
    void Unk_10d2a530(int First, int Second);

    unsigned char unk_00[0xb5];
    bool unk_b5;
};

class UnkType_10b55ed0_Other
{
public:
    unsigned char unk_00[0x2c];
    int unk_2c;
};

class UnkType_10b55ed0
{
public:
    bool Unk_10b65b30(int Value);
    bool Unk_10b55ed0(int Value);

private:
    unsigned char unk_00[0x3c];
    bool unk_3c;
    unsigned char unk_3d[0x40 - 0x3d];
    UnkType_10b55ed0_Target* unk_40;
    UnkType_10b55ed0_Other* unk_44;
    unsigned char unk_48[0x60 - 0x48];
    bool unk_60;
    bool unk_61;
};

// UnkType_10b55ed0::Unk_10b55ed0
bool UnkType_10b55ed0::Unk_10b55ed0(int Value)
{
    if ( unk_3c )
    {
        return true;
    }
    bool Result = false;
    if ( Unk_10b65b30(Value) )
    {
        Result = true;
        unk_40->Unk_10d2a530(1, 1);
        unk_40->unk_b5 = true;
        unk_60 = unk_40->Unk_10d2c120(GUnk_1122e02c);
        unk_61 = unk_40->Unk_10d2c120(GUnk_1122e030);
        if ( unk_44 )
        {
            unk_44->unk_2c = 0;
        }
    }
    unk_3c = Result;
    return Result;
}
