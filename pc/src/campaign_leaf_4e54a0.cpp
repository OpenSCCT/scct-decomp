// campaign_leaf_4e54a0.cpp -- constructor at VA 0x10de54a0: constructs its base (VA 0x10de62b0)
// from its second argument and the member at 0xa4 (VA 0x10dad2c0), stores the first argument at
// 0x9c, clears the bytes at 0xa0 and 0xa1, sets 0x124 to 1, and stores at 0x98 and 0x94 two results
// of the method at VA 0x10de60c0 on the object at 0x9c. The class, member and parameter names are
// invented; the offsets and the addresses are the binary's.

class UnkType_10de54a0_Source
{
public:
    int Unk_10de60c0();
};

class UnkType_10de54a0_Base
{
public:
    UnkType_10de54a0_Base(int Arg);

    unsigned char unk_00[0x94];
};

class UnkType_10de54a0_Member
{
public:
    UnkType_10de54a0_Member();

    int unk_00[0x20];
};

class UnkType_10de54a0 : public UnkType_10de54a0_Base
{
public:
    UnkType_10de54a0(UnkType_10de54a0_Source* Source, int Arg);

    int unk_94;
    int unk_98;
    UnkType_10de54a0_Source* unk_9c;
    bool unk_a0;
    bool unk_a1;
    UnkType_10de54a0_Member unk_a4;
    int unk_124;
};

// UnkType_10de54a0::UnkType_10de54a0
UnkType_10de54a0::UnkType_10de54a0(UnkType_10de54a0_Source* Source, int Arg)
    : UnkType_10de54a0_Base(Arg)
{
    unk_a0 = false;
    unk_a1 = false;
    unk_9c = Source;
    unk_124 = 1;
    unk_98 = unk_9c->Unk_10de60c0();
    unk_94 = unk_9c->Unk_10de60c0();
}
