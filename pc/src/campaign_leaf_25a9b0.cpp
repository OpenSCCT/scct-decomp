// campaign_leaf_25a9b0.cpp -- the constructor at VA 0x10b5a9b0 taking an int: it runs the base
// constructor at VA 0x10b65a90 with the int, installs the class's virtual tables at 0x00, 0x08 and
// 0x10, clears the ints at 0x40 to 0x78 and clears the byte at 0x7c. The class and member names are
// invented; the offsets and addresses are the binary's.

class UnkType_10b5a9b0_Face0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b5a9b0_Face8
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b5a9b0_Face10
{
public:
    virtual void VirtualSlot0();
};

class UnkType_10b5a9b0_Base : public UnkType_10b5a9b0_Face0,
                             public UnkType_10b5a9b0_Face8,
                             public UnkType_10b5a9b0_Face10
{
public:
    UnkType_10b5a9b0_Base(int Value);

private:
    unsigned char unk_14[0x40 - 0x14];
};

class UnkType_10b5a9b0 : public UnkType_10b5a9b0_Base
{
public:
    UnkType_10b5a9b0(int Value);

private:
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4c;
    int unk_50;
    int unk_54;
    int unk_58;
    int unk_5c;
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6c;
    int unk_70;
    int unk_74;
    int unk_78;
    bool unk_7c;
};

// UnkType_10b5a9b0::UnkType_10b5a9b0
UnkType_10b5a9b0::UnkType_10b5a9b0(int Value)
    : UnkType_10b5a9b0_Base(Value),
      unk_40(0),
      unk_44(0),
      unk_48(0),
      unk_4c(0),
      unk_50(0),
      unk_54(0),
      unk_58(0),
      unk_5c(0),
      unk_60(0),
      unk_64(0),
      unk_68(0),
      unk_6c(0),
      unk_70(0),
      unk_74(0),
      unk_78(0),
      unk_7c(false)
{
}
