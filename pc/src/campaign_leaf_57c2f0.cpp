// campaign_leaf_57c2f0.cpp -- thiscall method at VA 0x10e7c2f0: replaces the members of a group.
// Every current member (pointer array at 0x1c) is passed the link at 0x18 through its method at VA
// 0x10e4fea0 and the array is emptied; when Members is not empty, it is copied in through the
// array's method at VA 0x10e53150 (index 0), and each new member that does not yet list the link
// in its pointer array at 0x7c is passed it through its method at VA 0x10e50310. guess: the first
// method unlinks and the last links. All names are invented; the addresses are the binary's.

struct UnkType_10e7c2f0_Link
{
    int unk_00;
};

struct UnkType_10e7c2f0_LinkArray
{
    UnkType_10e7c2f0_Link** unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e7c2f0_LinkArray::Find
    // guess: returns the index of Link, or -1.
    int Find(UnkType_10e7c2f0_Link* Link)
    {
        for ( int Index = 0; Index < unk_04; Index++ )
        {
            if ( unk_00[Index] == Link )
            {
                return Index;
            }
        }
        return -1;
    }
};

class UnkType_10e7c2f0_Member
{
public:
    void Unk_10e4fea0(UnkType_10e7c2f0_Link* Link);
    void Unk_10e50310(UnkType_10e7c2f0_Link* Link);

    int unk_00[0x7c / 4];
    UnkType_10e7c2f0_LinkArray unk_7c;
};

struct UnkType_10e7c2f0_MemberArray
{
    void Unk_10e53150(int Index, UnkType_10e7c2f0_MemberArray* Other);

    UnkType_10e7c2f0_Member** unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10e7c2f0
{
public:
    void Unk_10e7c2f0(UnkType_10e7c2f0_MemberArray* Members);

private:
    int unk_00[6];
    UnkType_10e7c2f0_Link unk_18;
    UnkType_10e7c2f0_MemberArray unk_1c;
};

// UnkType_10e7c2f0::Unk_10e7c2f0
void UnkType_10e7c2f0::Unk_10e7c2f0(UnkType_10e7c2f0_MemberArray* Members)
{
    int Index;

    for ( Index = 0; Index < unk_1c.unk_04; Index++ )
    {
        unk_1c.unk_00[Index]->Unk_10e4fea0(&unk_18);
    }
    unk_1c.unk_04 = 0;

    int Count = Members->unk_04;

    if ( Count > 0 )
    {
        unk_1c.Unk_10e53150(0, Members);
        for ( Index = 0; Index < Count; Index++ )
        {
            UnkType_10e7c2f0_Member* Member = unk_1c.unk_00[Index];

            if ( Member->unk_7c.Find(&unk_18) < 0 )
            {
                Member->Unk_10e50310(&unk_18);
            }
        }
    }
}
