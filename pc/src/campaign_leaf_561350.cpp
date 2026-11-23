// campaign_leaf_561350.cpp -- constructor at VA 0x10e61350: runs the base class constructor at VA
// 0x10e6d1a0 with the record it is given, installs this class's two vtables (VA 0x1114d684 and,
// for the base part at 0x08, VA 0x1114d674), constructs the cleared pairs at 0xe4 and passes
// the record to the method at VA 0x10e61190. The class names are invented; the addresses are the
// binary's.

struct UnkType_10e61350_Record
{
    int unk_00[4];
};

struct UnkType_10e61350_Pair
{
    // UnkType_10e61350_Pair::UnkType_10e61350_Pair
    UnkType_10e61350_Pair()
        : unk_00(0), unk_04(0)
    {
    }

    int unk_00;
    int unk_04;
};

class UnkType_10e61350_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10e61350_Base8
{
public:
    virtual void VirtualSlot0();

private:
    int unk_0c[5];
};

class UnkType_10e61350_10e6d1a0 : public UnkType_10e61350_Base0, public UnkType_10e61350_Base8
{
public:
    UnkType_10e61350_10e6d1a0(const UnkType_10e61350_Record& Record);
};

class UnkType_10e61350 : public UnkType_10e61350_10e6d1a0
{
public:
    UnkType_10e61350(const UnkType_10e61350_Record& Record);

    void Unk_10e61190(const UnkType_10e61350_Record& Record);

private:
    int unk_20[0xc4 / 4];
    UnkType_10e61350_Pair unk_e4[7];
};

// UnkType_10e61350::UnkType_10e61350
UnkType_10e61350::UnkType_10e61350(const UnkType_10e61350_Record& Record)
    : UnkType_10e61350_10e6d1a0(Record)
{
    Unk_10e61190(Record);
}
