// campaign_leaf_2562d0.cpp -- the constructor at VA 0x10b562d0 taking two ints: it runs the base
// constructor at VA 0x10b65a90 with the first, clears the ints at 0x40 to 0x58 and the bytes at
// 0x60 and 0x61, installs the class's virtual tables at 0x00, 0x08 and 0x10, stores the second int
// at 0x5c and clears the ints at 0x64 to 0x6c. The class and member names are invented; the offsets
// and addresses are the binary's.

class UnkType_10b562d0_Face0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b562d0_Face8
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b562d0_Face10
{
public:
    virtual void VirtualSlot0();
};

class UnkType_10b562d0_Base : public UnkType_10b562d0_Face0,
                             public UnkType_10b562d0_Face8,
                             public UnkType_10b562d0_Face10
{
public:
    UnkType_10b562d0_Base(int Value);

private:
    unsigned char unk_14[0x40 - 0x14];
};

class UnkType_10b562d0 : public UnkType_10b562d0_Base
{
public:
    UnkType_10b562d0(int Value, int Second);

private:
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4c;
    int unk_50;
    int unk_54;
    int unk_58;
    int unk_5c;
    bool unk_60;
    bool unk_61;
    int unk_64[3];
};

// UnkType_10b562d0::UnkType_10b562d0
UnkType_10b562d0::UnkType_10b562d0(int Value, int Second)
    : UnkType_10b562d0_Base(Value),
      unk_40(0),
      unk_44(0),
      unk_48(0),
      unk_4c(0),
      unk_50(0),
      unk_54(0),
      unk_58(0),
      unk_60(false),
      unk_61(false)
{
    unk_5c = Second;
    for ( int i = 0; i < 3; i++ )
    {
        unk_64[i] = 0;
    }
}
