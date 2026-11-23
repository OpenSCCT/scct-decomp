// campaign_leaf_23cdb0.cpp -- a member function at VA 0x10b3cdb0 taking an object: when the byte at
// 0x0c is already set it returns true. Otherwise it looks up, with the member at VA 0x10d21780 of
// the object, the object named by the global at VA 0x1122d890, and in that, with the member at VA
// 0x10d30670, the object named by the global at VA 0x1122d894; when both are found it stores the
// second one's pointer at 0x08 at 0x08, passes an empty wide string to that pointer's member at VA
// 0x10ad8c90, sets the byte at 0x0c and returns true; otherwise false. The class, method, member,
// parameter and global names are invented; the offsets and addresses are the binary's.

#include "campaign_global_1122d890.h"
#include "campaign_global_1122d894.h"

class UnkType_10b3cdb0_Label
{
public:
    void Unk_10ad8c90(const unsigned short* Text);
};

class UnkType_10b3cdb0_Node
{
public:
    int unk_00;
    int unk_04;
    UnkType_10b3cdb0_Label* unk_08;
};

class UnkType_10b3cdb0_Group
{
public:
    UnkType_10b3cdb0_Node* Unk_10d30670(int Name);
};

class UnkType_10b3cdb0_Root
{
public:
    UnkType_10b3cdb0_Group* Unk_10d21780(int Name);
};

class UnkType_10b3cdb0
{
public:
    bool Unk_10b3cdb0(UnkType_10b3cdb0_Root* Root);

private:
    int unk_00;
    int unk_04;
    UnkType_10b3cdb0_Label* unk_08;
    bool unk_0c;
};

// UnkType_10b3cdb0::Unk_10b3cdb0
bool UnkType_10b3cdb0::Unk_10b3cdb0(UnkType_10b3cdb0_Root* Root)
{
    if ( unk_0c )
    {
        return true;
    }
    UnkType_10b3cdb0_Group* Group = Root->Unk_10d21780(GUnk_1122d890);
    if ( !Group )
    {
        return false;
    }
    UnkType_10b3cdb0_Node* Node = Group->Unk_10d30670(GUnk_1122d894);
    if ( !Node )
    {
        return false;
    }
    unk_08 = Node->unk_08;
    unk_08->Unk_10ad8c90(L"");
    unk_0c = true;
    return true;
}
