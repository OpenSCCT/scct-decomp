// campaign_leaf_265cc0.cpp -- a member function at VA 0x10b65cc0 that looks up, with the member at
// VA 0x10d30670 of the object the pointer at 0x04 refers to, the object named by the global at VA
// 0x1122e4dc and stores it at 0x08; when found it clears bit 0 of its byte at 0x18 and stores its
// pointer at 0x08 at 0x0c. When that is set its pointer at 0x1c is stored at 0x10, and when that is
// set the pointer at 0x08 of the object it finds by the global at VA 0x1122e4e0 is stored at 0x14
// and it returns true; otherwise false. The class, method, member and global names are invented;
// the offsets and addresses are the binary's.

#include "campaign_global_1122e4dc.h"
#include "campaign_global_1122e4e0.h"

class UnkType_10b65cc0_Node
{
public:
    UnkType_10b65cc0_Node* Unk_10d30670(int Name);

    int unk_00;
    int unk_04;
    UnkType_10b65cc0_Node* unk_08;
    unsigned char unk_0c[0x18 - 0x0c];
    unsigned char unk_18;
    unsigned char unk_19[0x1c - 0x19];
    UnkType_10b65cc0_Node* unk_1c;
};

class UnkType_10b65cc0
{
public:
    bool Unk_10b65cc0();

private:
    int unk_00;
    UnkType_10b65cc0_Node* unk_04;
    UnkType_10b65cc0_Node* unk_08;
    UnkType_10b65cc0_Node* unk_0c;
    UnkType_10b65cc0_Node* unk_10;
    UnkType_10b65cc0_Node* unk_14;
};

// UnkType_10b65cc0::Unk_10b65cc0
bool UnkType_10b65cc0::Unk_10b65cc0()
{
    unk_08 = unk_04->Unk_10d30670(GUnk_1122e4dc);
    if ( unk_08 )
    {
        unk_08->unk_18 &= ~1;
        unk_0c = unk_08->unk_08;
    }
    if ( unk_0c )
    {
        unk_10 = unk_0c->unk_1c;
    }
    if ( unk_10 )
    {
        unk_14 = unk_10->Unk_10d30670(GUnk_1122e4e0)->unk_08;
        return true;
    }
    return false;
}
