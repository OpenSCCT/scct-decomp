// campaign_leaf_2220d0.cpp -- a member function at VA 0x10b220d0 returning true: when there is a
// target (what the member at VA 0x10a45b50 of the object at 0x64 of the entry the member at VA
// 0x10a0e220 of the object the pointer at 0x04 refers to gives for the byte at 0x0c returns), it
// passes whether the target's member at VA 0x10b219d0 returns non-zero for 2 to the member at VA
// 0x10b710e0 of the member at 0xd64, and for 3 to the member at VA 0x10b6fdb0 of the member at
// 0xdd0; each call is skipped when the target's pointer at 0x5c0 is set, that object's byte at
// 0xb4 is set and the answer is non-zero. It then passes 0 to the member at VA 0x10b67080 of the
// member at 0xa2c. The class, method and member names are invented; the offsets and addresses are
// the binary's.

class UnkType_10b220d0_State
{
public:
    unsigned char unk_00[0xb4];
    bool unk_b4;
};

class UnkType_10b220d0_Target
{
public:
    int Unk_10b219d0(int Kind);

    unsigned char unk_000[0x5c0];
    UnkType_10b220d0_State* unk_5c0;
};

class UnkType_10b220d0_Lookup
{
public:
    UnkType_10b220d0_Target* Unk_10a45b50();
};

class UnkType_10b220d0_Entry
{
public:
    unsigned char unk_00[0x64];
    UnkType_10b220d0_Lookup* unk_64;
};

class UnkType_10b220d0_Table
{
public:
    UnkType_10b220d0_Entry* Unk_10a0e220(unsigned char Index);
};

class UnkType_10b220d0_Unka2c
{
public:
    void Unk_10b67080(int Value);

private:
    unsigned char unk_00[0x338];
};

class UnkType_10b220d0_Unkd64
{
public:
    void Unk_10b710e0(bool Flag);

private:
    unsigned char unk_00[0x6c];
};

class UnkType_10b220d0_Unkdd0
{
public:
    void Unk_10b6fdb0(bool Flag);
};

class UnkType_10b220d0
{
public:
    bool Unk_10b220d0();

private:
    int unk_000;
    UnkType_10b220d0_Table* unk_004;
    int unk_008;
    unsigned char unk_00c;
    unsigned char unk_00d[0xa2c - 0x00d];
    UnkType_10b220d0_Unka2c unk_a2c;
    UnkType_10b220d0_Unkd64 unk_d64;
    UnkType_10b220d0_Unkdd0 unk_dd0;
};

// UnkType_10b220d0::Unk_10b220d0
bool UnkType_10b220d0::Unk_10b220d0()
{
    UnkType_10b220d0_Target* Target = unk_004->Unk_10a0e220(unk_00c)->unk_64->Unk_10a45b50();
    if ( Target )
    {
        int Locked = Target->unk_5c0 && Target->unk_5c0->unk_b4;
        if ( !Locked || !Target->Unk_10b219d0(2) )
        {
            unk_d64.Unk_10b710e0(Target->Unk_10b219d0(2) != 0);
        }
        if ( !Locked || !Target->Unk_10b219d0(3) )
        {
            unk_dd0.Unk_10b6fdb0(Target->Unk_10b219d0(3) != 0);
        }
        unk_a2c.Unk_10b67080(0);
    }
    return true;
}
