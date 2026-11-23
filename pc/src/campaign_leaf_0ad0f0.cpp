// campaign_leaf_0ad0f0.cpp -- free function at VA 0x109ad0f0 taking an object: for each of three
// indices stores the index in the first word of the 0x1c-byte record at 0x40 and passes the index
// to the methods at VA 0x109ac3d0, 0x109ac6e0 and 0x109acc10 of the three 0x38-byte members of the
// 0xa8-byte record at 0x98; then stores 3 at 0x94 and passes 3 to the method at VA 0x109ac3d0 of
// the member at 0x290. The class, member and function names are invented; the offsets and the
// addresses are the binary's.

class UnkType_109ad0f0_First
{
public:
    void Unk_109ac3d0(unsigned int Index);

private:
    unsigned char unk_00[0x38];
};

class UnkType_109ad0f0_Second
{
public:
    void Unk_109ac6e0(unsigned int Index);

private:
    unsigned char unk_00[0x38];
};

class UnkType_109ad0f0_Third
{
public:
    void Unk_109acc10(unsigned int Index);

private:
    unsigned char unk_00[0x38];
};

struct UnkType_109ad0f0_Group
{
    UnkType_109ad0f0_First unk_00;
    UnkType_109ad0f0_Second unk_38;
    UnkType_109ad0f0_Third unk_70;
};

struct UnkType_109ad0f0_Slot
{
    int unk_00;
    unsigned char unk_04[0x1c - 0x04];
};

class UnkType_109ad0f0
{
public:
    unsigned char unk_00[0x40];
    UnkType_109ad0f0_Slot unk_40[3];
    int unk_94;
    UnkType_109ad0f0_Group unk_98[3];
    UnkType_109ad0f0_First unk_290;
};

// Unk_109ad0f0
void Unk_109ad0f0(UnkType_109ad0f0* Object)
{
    for ( unsigned int i = 0; i < 3; i++ )
    {
        Object->unk_40[i].unk_00 = i;
        Object->unk_98[i].unk_00.Unk_109ac3d0(i);
        Object->unk_98[i].unk_38.Unk_109ac6e0(i);
        Object->unk_98[i].unk_70.Unk_109acc10(i);
    }
    Object->unk_94 = 3;
    Object->unk_290.Unk_109ac3d0(3);
}
