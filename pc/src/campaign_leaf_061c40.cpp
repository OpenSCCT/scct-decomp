// campaign_leaf_061c40.cpp -- constructor at VA 0x10961c40 taking two values: stores the first at
// 0x00, constructs the member at 0x04 with the constructor at VA 0x10d8ebd0, clears the values at
// 0x10-0x18 and 0x20, sets the byte at 0x1c, and passes the second value to the method at VA
// 0x10d87c80; then, when the first value is 0, passes 0 to the method at VA 0x10d8eee0 of the
// member at 0x04, and otherwise calls the methods at VA 0x10961ad0 and 0x10961b50 (with 1). The
// class, member and method names are invented; the offsets and the addresses are the binary's.

class UnkType_10961c40_04
{
public:
    UnkType_10961c40_04();
    void Unk_10d8eee0(const int& Value);

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1090ba70_061c40
{
public:
    UnkType_1090ba70_061c40()
    : unk_00(0)
    , unk_04(0)
    , unk_08(0)
    {
    }

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10961c40
{
public:
    UnkType_10961c40(int Arg0, int Arg1);
    void Unk_10d87c80(int Value);
    void Unk_10961ad0();
    void Unk_10961b50(int Value);

private:
    int unk_00;
    UnkType_10961c40_04 unk_04;
    UnkType_1090ba70_061c40 unk_10;
    unsigned char unk_1c;
    int unk_20;
};

// UnkType_10961c40::UnkType_10961c40
UnkType_10961c40::UnkType_10961c40(int Arg0, int Arg1)
: unk_00(Arg0)
, unk_1c(1)
, unk_20(0)
{
    Unk_10d87c80(Arg1);
    if ( !unk_00 )
    {
        unk_04.Unk_10d8eee0(0);
    }
    else
    {
        Unk_10961ad0();
        Unk_10961b50(1);
    }
}
