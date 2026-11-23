// campaign_leaf_0a1980.cpp -- constructor at VA 0x109a1980 (vtable at VA 0x110ca510): runs the base
// class constructor at VA 0x10cd7930 and the inline constructor of the intermediate class, then
// zeroes the 16-byte record at 0x1cc except its float at 0x1d4, which it sets to 1e-8, and zeroes
// the word at 0x2b4. The class and member names are invented; the offsets, the values and the
// addresses are the binary's.

struct UnkType_109a1980_Sub
{
    UnkType_109a1980_Sub() : unk_00(0), unk_04(0), unk_08(1e-8f), unk_0c(0)
    {
    }

    int unk_00;
    int unk_04;
    float unk_08;
    int unk_0c;
};

class UnkType_109a1980_Base
{
public:
    UnkType_109a1980_Base();
    virtual ~UnkType_109a1980_Base();

private:
    unsigned char unk_04[0x1cc - 0x04];
};

class UnkType_109a1980_Middle : public UnkType_109a1980_Base
{
public:
    virtual ~UnkType_109a1980_Middle();

private:
    UnkType_109a1980_Sub unk_1cc;
};

class UnkType_109a1980 : public UnkType_109a1980_Middle
{
public:
    UnkType_109a1980();
    virtual ~UnkType_109a1980();

private:
    unsigned char unk_1dc[0x2b4 - 0x1dc];
    int unk_2b4;
};

// UnkType_109a1980::UnkType_109a1980
UnkType_109a1980::UnkType_109a1980() : unk_2b4(0)
{
}
