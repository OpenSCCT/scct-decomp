// campaign_leaf_615340.cpp -- thiscall method at VA 0x10f15340: calls the method at VA 0x10f15610
// with the addresses of nine locals; when that returns true, passes them to virtual slot 0 (vtable
// offset 0x00) of the object at 0x10 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

struct UnkType_10f15340_Second
{
    unsigned char unk_00[0x10];
};

struct UnkType_10f15340_Third
{
    unsigned char unk_00[0x24];
};

struct UnkType_10f15340_Fourth
{
    unsigned char unk_00[0x24];
};

struct UnkType_10f15340_Fifth
{
    unsigned char unk_00[0x44];
};

struct UnkType_10f15340_Sixth
{
    unsigned char unk_00[0x84];
};

struct UnkType_10f15340_Seventh
{
    unsigned char unk_00[0xc];
};

struct UnkType_10f15340_Eighth
{
    unsigned char unk_00[0x84];
};

class UnkType_10f15340_Target
{
public:
    virtual void VirtualSlot0(int First, UnkType_10f15340_Second* Second,
                              UnkType_10f15340_Third* Third, UnkType_10f15340_Fourth* Fourth,
                              UnkType_10f15340_Fifth* Fifth, UnkType_10f15340_Sixth* Sixth,
                              UnkType_10f15340_Seventh* Seventh, UnkType_10f15340_Eighth* Eighth,
                              int Ninth);
};

class UnkType_10f15340
{
public:
    bool Unk_10f15340();
    bool Unk_10f15610(int* First, UnkType_10f15340_Second* Second, UnkType_10f15340_Third* Third,
                      UnkType_10f15340_Fourth* Fourth, UnkType_10f15340_Fifth* Fifth,
                      UnkType_10f15340_Sixth* Sixth, UnkType_10f15340_Seventh* Seventh,
                      UnkType_10f15340_Eighth* Eighth, int* Ninth);

private:
    unsigned char unk_00[0x10];
    UnkType_10f15340_Target* unk_10;
};

// UnkType_10f15340::Unk_10f15340
bool UnkType_10f15340::Unk_10f15340()
{
    int First;
    UnkType_10f15340_Second Second;
    UnkType_10f15340_Third Third;
    UnkType_10f15340_Fourth Fourth;
    UnkType_10f15340_Fifth Fifth;
    UnkType_10f15340_Sixth Sixth;
    UnkType_10f15340_Seventh Seventh;
    UnkType_10f15340_Eighth Eighth;
    int Ninth;

    if ( Unk_10f15610(&First, &Second, &Third, &Fourth, &Fifth, &Sixth, &Seventh, &Eighth, &Ninth) )
    {
        unk_10->VirtualSlot0(First, &Second, &Third, &Fourth, &Fifth, &Sixth, &Seventh, &Eighth,
                             Ninth);
        return true;
    }
    return false;
}
