// campaign_leaf_1ec600.cpp -- thiscall method at VA 0x10aec600. When the global at VA 0x111c88a4 is
// zero it returns 0. Otherwise it builds two strings from its argument through the functions at VA
// 0x10aea4d0 and 0x10aea580 and returns 1 when the method at VA 0x10aebbd0 accepts both, 0
// otherwise; the strings are destroyed through VA 0x1090ba70. The class, method and member names
// are invented.

#include "campaign_global_111c88a4.h"

class UnkType_10aec600_Arg;

class UnkType_10aec600_String
{
public:
    ~UnkType_10aec600_String();

private:
    unsigned short* unk_0;
    int unk_4;
    int unk_8;
};

UnkType_10aec600_String Unk_10aea4d0(UnkType_10aec600_Arg* Arg);
UnkType_10aec600_String Unk_10aea580(UnkType_10aec600_Arg* Arg);

class UnkType_10aec600
{
public:
    int Unk_10aec600(UnkType_10aec600_Arg* Arg);
    int Unk_10aebbd0(const UnkType_10aec600_String& Name);
};

// UnkType_10aec600::Unk_10aec600
int UnkType_10aec600::Unk_10aec600(UnkType_10aec600_Arg* Arg)
{
    if ( GUnk_111c88a4 == 0 )
    {
        return 0;
    }
    UnkType_10aec600_String First = Unk_10aea4d0(Arg);
    UnkType_10aec600_String Second = Unk_10aea580(Arg);
    return Unk_10aebbd0(First) && Unk_10aebbd0(Second);
}
