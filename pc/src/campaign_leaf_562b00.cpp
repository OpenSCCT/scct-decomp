// campaign_leaf_562b00.cpp -- constructor at VA 0x10e62b00: runs the base class constructor at VA
// 0x10e6d1a0 with the record it is given, installs this class's two vtables (VA 0x1114d9c4 and,
// for the base part at 0x08, VA 0x1114d9b4), constructs the five cleared pairs at 0x70 and passes
// the record to the method at VA 0x10e628d0. The class names are invented; the addresses are the
// binary's.

struct UnkType_10e62b00_Record
{
    int unk_00[4];
};

struct UnkType_10e62b00_Pair
{
    // UnkType_10e62b00_Pair::UnkType_10e62b00_Pair
    UnkType_10e62b00_Pair()
        : unk_00(0), unk_04(0)
    {
    }

    int unk_00;
    int unk_04;
};

class UnkType_10e62b00_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10e62b00_Base8
{
public:
    virtual void VirtualSlot0();

private:
    int unk_0c[5];
};

class UnkType_10e62b00_10e6d1a0 : public UnkType_10e62b00_Base0, public UnkType_10e62b00_Base8
{
public:
    UnkType_10e62b00_10e6d1a0(const UnkType_10e62b00_Record& Record);
};

class UnkType_10e62b00 : public UnkType_10e62b00_10e6d1a0
{
public:
    UnkType_10e62b00(const UnkType_10e62b00_Record& Record);

    void Unk_10e628d0(const UnkType_10e62b00_Record& Record);

private:
    int unk_20[0x50 / 4];
    UnkType_10e62b00_Pair unk_70[5];
};

// UnkType_10e62b00::UnkType_10e62b00
UnkType_10e62b00::UnkType_10e62b00(const UnkType_10e62b00_Record& Record)
    : UnkType_10e62b00_10e6d1a0(Record)
{
    Unk_10e628d0(Record);
}
