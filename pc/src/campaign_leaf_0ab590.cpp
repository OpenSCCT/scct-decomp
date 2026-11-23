// campaign_leaf_0ab590.cpp -- constructor at VA 0x109ab590 (vtable at VA 0x110ccb10) taking three
// words and a 12-byte vector: runs the base class constructor at VA 0x10cd7930, then stores the
// words at 0x28, 0x2c and 0x30 and the vector at 0x34. The class and member names are invented; the
// offsets and the addresses are the binary's.

struct UnkType_109ab590_Vector
{
    float unk_00;
    float unk_04;
    float unk_08;
};

class UnkType_109ab590_Base
{
public:
    UnkType_109ab590_Base();
    virtual ~UnkType_109ab590_Base();

private:
    unsigned char unk_04[0x28 - 0x04];
};

class UnkType_109ab590 : public UnkType_109ab590_Base
{
public:
    UnkType_109ab590(int InA, int InB, int InC, UnkType_109ab590_Vector InVector);
    virtual ~UnkType_109ab590();

private:
    int unk_28;
    int unk_2c;
    int unk_30;
    UnkType_109ab590_Vector unk_34;
};

// UnkType_109ab590::UnkType_109ab590
UnkType_109ab590::UnkType_109ab590(int InA, int InB, int InC, UnkType_109ab590_Vector InVector)
    : unk_28(InA), unk_2c(InB), unk_30(InC), unk_34(InVector)
{
}
