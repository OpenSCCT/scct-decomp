// campaign_leaf_55d5d0.cpp -- constructor at VA 0x10e5d5d0: runs the base class constructor at VA
// 0x10e6d1a0 with the record it is given, installs this class's two vtables (VA 0x1114cf40 and,
// for the base part at 0x08, VA 0x1114cf30), constructs the cleared pairs at 0xac and passes
// the record to the method at VA 0x10e5d280. The class names are invented; the addresses are the
// binary's.

struct UnkType_10e5d5d0_Record
{
    int unk_00[4];
};

struct UnkType_10e5d5d0_Pair
{
    // UnkType_10e5d5d0_Pair::UnkType_10e5d5d0_Pair
    UnkType_10e5d5d0_Pair()
        : unk_00(0), unk_04(0)
    {
    }

    int unk_00;
    int unk_04;
};

class UnkType_10e5d5d0_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10e5d5d0_Base8
{
public:
    virtual void VirtualSlot0();

private:
    int unk_0c[5];
};

class UnkType_10e5d5d0_10e6d1a0 : public UnkType_10e5d5d0_Base0, public UnkType_10e5d5d0_Base8
{
public:
    UnkType_10e5d5d0_10e6d1a0(const UnkType_10e5d5d0_Record& Record);
};

class UnkType_10e5d5d0 : public UnkType_10e5d5d0_10e6d1a0
{
public:
    UnkType_10e5d5d0(const UnkType_10e5d5d0_Record& Record);

    void Unk_10e5d280(const UnkType_10e5d5d0_Record& Record);

private:
    int unk_20[0x8c / 4];
    UnkType_10e5d5d0_Pair unk_ac[7];
};

// UnkType_10e5d5d0::UnkType_10e5d5d0
UnkType_10e5d5d0::UnkType_10e5d5d0(const UnkType_10e5d5d0_Record& Record)
    : UnkType_10e5d5d0_10e6d1a0(Record)
{
    Unk_10e5d280(Record);
}
