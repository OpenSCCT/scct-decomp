// campaign_leaf_0b7540.cpp -- constructor at VA 0x109b7540 (vtable at VA 0x110ce10c) taking four
// arguments: runs the base class constructor at VA 0x10aa4e00 with 3 when the third argument is set
// (1 otherwise), the first, the third and the fourth arguments, stores the second argument at 0x1c
// and whether its word at 0x08 is set at 0x20. The class and member names are invented; the offsets
// and the addresses are the binary's.

class UnkType_109b7540_Info
{
public:
    unsigned char unk_00[0x08];
    int unk_08;
};

class UnkType_109b7540_Base
{
public:
    UnkType_109b7540_Base(int Kind, int Arg, unsigned char Flag, int Extra);
    virtual ~UnkType_109b7540_Base();

protected:
    unsigned char unk_04[0x1c - 0x04];
};

class UnkType_109b7540 : public UnkType_109b7540_Base
{
public:
    UnkType_109b7540(int Arg, UnkType_109b7540_Info* Info, unsigned char Flag,
                     int Extra);
    virtual ~UnkType_109b7540();

private:
    UnkType_109b7540_Info* unk_1c;
    int unk_20;
};

// UnkType_109b7540::UnkType_109b7540
UnkType_109b7540::UnkType_109b7540(int Arg, UnkType_109b7540_Info* Info, unsigned char Flag,
                                   int Extra)
    : UnkType_109b7540_Base(Flag ? 3 : 1, Arg, Flag, Extra), unk_1c(Info),
      unk_20(Info->unk_08 != 0)
{
}
