// campaign_leaf_22de00.cpp -- the copy constructor at VA 0x10b2de00 of a 0x50-byte class: it copies
// the four strings at 0x00, 0x0c, 0x18 and 0x24 with the string copy constructor at VA 0x1090b9a0,
// the bytes at 0x30, 0x31 and 0x3c, the ints at 0x34, 0x38 and 0x40, and the string at 0x44. The
// class and member names are invented; the offsets and addresses are the binary's.

class UnkType_10b2de00_String
{
public:
    UnkType_10b2de00_String(const UnkType_10b2de00_String& Other);

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b2de00
{
public:
    UnkType_10b2de00(const UnkType_10b2de00& Other);

private:
    UnkType_10b2de00_String unk_00;
    UnkType_10b2de00_String unk_0c;
    UnkType_10b2de00_String unk_18;
    UnkType_10b2de00_String unk_24;
    unsigned char unk_30;
    unsigned char unk_31;
    int unk_34;
    int unk_38;
    unsigned char unk_3c;
    int unk_40;
    UnkType_10b2de00_String unk_44;
};

// UnkType_10b2de00::UnkType_10b2de00
UnkType_10b2de00::UnkType_10b2de00(const UnkType_10b2de00& Other)
    : unk_00(Other.unk_00),
      unk_0c(Other.unk_0c),
      unk_18(Other.unk_18),
      unk_24(Other.unk_24),
      unk_30(Other.unk_30),
      unk_31(Other.unk_31),
      unk_34(Other.unk_34),
      unk_38(Other.unk_38),
      unk_3c(Other.unk_3c),
      unk_40(Other.unk_40),
      unk_44(Other.unk_44)
{
}
