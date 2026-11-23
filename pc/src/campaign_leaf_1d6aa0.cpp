// campaign_leaf_1d6aa0.cpp -- thiscall method at VA 0x10ad6aa0 taking eleven arguments. It stores
// the first word at 0x00, assigns the strings at 0x04, 0x10, 0x28 and 0x34 (assignment at VA
// 0x1090b9a0), stores three words at 0x1c, 0x20 and 0x24 and three bytes at 0x40, 0x41 and 0x42,
// and returns this. The class, method and member names are invented.

class UnkType_10ad6aa0_String
{
public:
    UnkType_10ad6aa0_String& operator=(const UnkType_10ad6aa0_String& Other);

private:
    unsigned short* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10ad6aa0
{
public:
    UnkType_10ad6aa0& Unk_10ad6aa0(int Value, const UnkType_10ad6aa0_String& First,
                                   const UnkType_10ad6aa0_String& Second, int Third, int Fourth,
                                   int Fifth, const UnkType_10ad6aa0_String& Sixth,
                                   const UnkType_10ad6aa0_String& Seventh, bool bFirst,
                                   bool bSecond, bool bThird);

private:
    int unk_00;
    UnkType_10ad6aa0_String unk_04;
    UnkType_10ad6aa0_String unk_10;
    int unk_1c;
    int unk_20;
    int unk_24;
    UnkType_10ad6aa0_String unk_28;
    UnkType_10ad6aa0_String unk_34;
    bool unk_40;
    bool unk_41;
    bool unk_42;
};

// UnkType_10ad6aa0::Unk_10ad6aa0
UnkType_10ad6aa0& UnkType_10ad6aa0::Unk_10ad6aa0(int Value, const UnkType_10ad6aa0_String& First,
                                                 const UnkType_10ad6aa0_String& Second, int Third,
                                                 int Fourth, int Fifth,
                                                 const UnkType_10ad6aa0_String& Sixth,
                                                 const UnkType_10ad6aa0_String& Seventh,
                                                 bool bFirst, bool bSecond, bool bThird)
{
    unk_00 = Value;
    unk_04 = First;
    unk_10 = Second;
    unk_1c = Third;
    unk_20 = Fourth;
    unk_24 = Fifth;
    unk_28 = Sixth;
    unk_34 = Seventh;
    unk_40 = bFirst;
    unk_41 = bSecond;
    unk_42 = bThird;
    return *this;
}
