// campaign_leaf_0d0220.cpp -- constructor at VA 0x109d0220 (vtable at VA 0x110cf8b8) taking two
// arguments: runs the base class constructor at VA 0x10aa4e00 with 2, the first argument and two
// zeros, stores the second argument at 0x1c and whether its word at 0x14 is set at 0x20. The class
// and member names are invented; the offsets and the addresses are the binary's.

class UnkType_109d0220_Info
{
public:
    unsigned char unk_00[0x14];
    int unk_14;
};

class UnkType_109d0220_Base
{
public:
    UnkType_109d0220_Base(int Kind, int Arg, unsigned char Flag, int Extra);
    virtual ~UnkType_109d0220_Base();

protected:
    unsigned char unk_04[0x1c - 0x04];
};

class UnkType_109d0220 : public UnkType_109d0220_Base
{
public:
    UnkType_109d0220(int Arg, UnkType_109d0220_Info* Info);
    virtual ~UnkType_109d0220();

private:
    UnkType_109d0220_Info* unk_1c;
    int unk_20;
};

// UnkType_109d0220::UnkType_109d0220
UnkType_109d0220::UnkType_109d0220(int Arg, UnkType_109d0220_Info* Info)
    : UnkType_109d0220_Base(2, Arg, 0, 0), unk_1c(Info), unk_20(Info->unk_14 != 0)
{
}
